## **Extended Kalman Filter**

Once again, without all of the lectures and quizes in this module, I would not have stood a chance. I used a couple of different files to complete this project. The source code for this project can be found in the src folder of this repository.

The goals / steps of this project are the following:

* The goal of this project is to implement an Extended Kalman filter in C++. I was provided simulated lidar and radar measurements detecting a bicycle (graphic is a car though?) that travels around a vehicle. I used a Kalman filter, lidar measurements, and radar measurements to track the bicycle's(possibly a car's) position and velocity.

[//]: # (Image References)
[image1]: ./Runs/Dataset1.png "Dataset #1"
[image2]: ./Runs/Dataset2.png "Dataset #2"


## [Rubric](https://review.udacity.com/#!/rubrics/513/view) Points
Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

---

# Your code should compile

1. Code must compile with cmake and make.

This was my first time using cmake and make. After getting everything loaded into Windows correctly, I still had issues trying to run it from the Windows command prompt. I then discovered Windows 10 has 'Bash on Ubuntu for Windows". Thank goodness, because everything worked fine when I use that. No changes were made to the CMakeLists.txt file, so it should be good to go on any platform

# px, py, vx, vy output coordinates must have an RMSE <= [.11, .11, 0.52, 0.52] 

1. Your algorithm will be run against Dataset 1 in the simulator which is the same as "data/obj_pose-laser-radar-synthetic-input.txt" in the repository. We'll collect the positions that your algorithm outputs and compare them to ground truth data. Your px, py, vx, and vy RMSE should be less than or equal to the values [.11, .11, 0.52, 0.52].

I passed while using Dataset #1, and just missed when using Dataset #2. Below are my results

![alt text][image1]

![alt text][image2]

## Sliding Window Search

1. Describe how (and identify where in your code) you implemented a sliding window search.  How did you decide what scales to search and how much to overlap windows?

I decided to search window positions at fixed scale and location. I made a giant, oversized grid. I think I ended up with 488 different boxes to search. I went with three layers of boxes, because one wasn't cutting it. I also used rectangular boxes instead of square, because that is how the car looked to me. I honestly did a bunch of 'guess and check' over the test images until I found a solution that worked. The code for this can be found in the fifth code cell of the 'P5Video' IPython notebook, named "Step 3: Create Pipeline and Function Classes."  Below is an example an image of search grid:

![alt text][image4]

2. Show some examples of test images to demonstrate how your pipeline is working.  What did you do to optimize the performance of your classifier?

Ultimately I searched on all of the YCrCb 3-channel HOG features. To improve the reliability of the classifier i.e., fewer false positives and more reliable car detections I made sure I scalled the HOG features that I found and also set the feature_vec of the hog function to true. This "returns the data as a feature vector by calling .ravel() on the result just before returning". The goal was to input video data the same way as the SVC trained.

### Video Implementation

1. Provide a link to your final video output.  Your pipeline should perform reasonably well on the entire project video (somewhat wobbly or unstable bounding boxes are ok as long as you are identifying the vehicles most of the time with minimal false positives.)

Here are my three best from my different ideas;

#SVC(RBF, C=10):
Here's a [link to my video result](./myVideo_finalt1RBF.mp4)


#LinearSVC without Moving Average:
Here's a [link to my video result](./myVideo_finalt2LIN.mp4)

#LinearSVC with Moving Average:
Here's a [link to my video result](./myVideo_ma5t3LIN.mp4)

2. Describe how (and identify where in your code) you implemented some kind of filter for false positives and some method for combining overlapping bounding boxes.

I recorded the positions of positive detections in each frame of the video.  From the positive detections I created a heatmap and then thresholded that map to identify vehicle positions.  I then used `scipy.ndimage.measurements.label()` to identify individual blobs in the heatmap.  I then assumed each blob corresponded to a vehicle.  I constructed bounding boxes to cover the area of each blob detected.

I used the heat mapping threshold idea shown in lecture. The code for this can be found in the sixth code cell of the 'P5Video' IPython notebook, named "Step 3: Create Pipeline and Function Classes." I also implemented a moving average of the heat maps, but that idea, which I thought was awesome, turned out not to work so well. Here is an example image before and after heat mapping was applied:

#Pre-Heat Map

![alt text][image5]

#Post-Heat Map

![alt text][image6]
---
| RSME Dataset #1 |  
|:-------------:|:-------------:|  
| px     | 0.9505        | 
| py     | 0.9675        | 
| vx     | 0.9818       | 
| vy     | 0.9843        | 
---

### Discussion

1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your pipeline likely fail?  What could you do to make it more robust?

Here I'll talk about the approach I took, what techniques I used, what worked and why, where the pipeline might fail and how I might improve it if I were going to pursue this project further.  

The amount of improvements that could be made to my project are endless. There is literally not enough internet to hold everything that probably should be fixed. Using the YCrCb colorspace combinded with the SVC(RBF kernel) worked well, but is very, very slow and probably could never be used in any real-time application. Also, I sort of cheated myself by not looking into spatially binned color and histograms of color in the feature vector, because my inital pass through had excellent results. So I think those could probably add some value. Since I am on the topic of speed, my 'grid' needs far less windows to search. This eats a lot of time and with enough tinkering, I think I could find a more optimal search pattern.

My video has some misses in detecting cars, so maybe a heat threshold isn't all we need. I tried to get a moving average to work, because it made sense in my head, but I think a more sophisticated filter may be needed. As with any classifier, I could train it using more data. The more data the better. Also, instead of using the classic '.predict' I would like to see how the 'decision_function' could be used for SVCs.

The biggest thing that I took away from this project is that I need to start thinking more like a scientist rather then an engineer. There are so many knobs that are available to turn that each one, from colorspace to threshold, needs to be carefully looked at. 

