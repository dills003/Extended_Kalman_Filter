## **Extended Kalman Filter**

Once again, without all of the lectures and quizes in this module, I would not have stood a chance. I used a couple of different files to complete this project. The source code for this project can be found in the src folder of this repository.

The goals / steps of this project are the following:

* The goal of this project is to implement an Extended Kalman filter in C++. I was provided simulated lidar and radar measurements detecting a bicycle (graphic is a car though?) that travels around a vehicle. I used a Kalman filter, lidar measurements, and radar measurements to track the bicycle's(possibly a car's) position and velocity.

[//]: # (Image References)

[image1]: ./Runs/Dataset1.PNG "Dataset 1"
[image2]: ./Runs/Dataset2.PNG "Dataset 2"


## [Rubric](https://review.udacity.com/#!/rubrics/748/view) Points
Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

---

# Compiling

1. Code must compile with cmake and make.

This was my first time using cmake and make. After getting everything loaded into Windows correctly, I still had issues trying to run it from the Windows command prompt. I then discovered Windows 10 has 'Bash on Ubuntu for Windows". Thank goodness, because everything worked fine when I use that. No changes were made to the CMakeLists.txt file, so it should be good to go on any platform

# Accuracy

1. Your algorithm will be run against Dataset 1 in the simulator which is the same as "data/obj_pose-laser-radar-synthetic-input.txt" in the repository. We'll collect the positions that your algorithm outputs and compare them to ground truth data. Your px, py, vx, and vy RMSE should be less than or equal to the values [.11, .11, 0.52, 0.52].

I passed while using Dataset #1, and just missed when using Dataset #2. Below are my results:

 Dataset 1
![alt text][image1]

 Dataset 2
![alt text][image2]

# Follows Correct Algorithm

1. Follows general processing as taught in the lessons.

I decided to search window positions at fixed scale and location. I made a giant, oversized grid. I think I ended up with 488 different boxes to search. I went with three layers of boxes, because one wasn't cutting it. I also used rectangular boxes instead of square, because that is how the car looked to me. I honestly did a bunch of 'guess and check' over the test images until I found a solution that worked. The code for this can be found in the fifth code cell of the 'P5Video' IPython notebook, named "Step 3: Create Pipeline and Function Classes."  Below is an example an image of search grid:


2. Kalman Filter handles the first measurements properly.

Ultimately I searched on all of the YCrCb 3-channel HOG features. To improve the reliability of the classifier i.e., fewer false positives and more reliable car detections I made sure I scalled the HOG features that I found and also set the feature_vec of the hog function to true. This "returns the data as a feature vector by calling .ravel() on the result just before returning". The goal was to input video data the same way as the SVC trained.

3. Kalman Filter first predicts then updates.


4. Kalman Filter can handle radar and lidar measurements.


### Discussion


