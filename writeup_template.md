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

I passed while using Dataset #1, and just missed when using Dataset #2, unless rounding is allowed. Below are my results:

 Dataset 1
![alt text][image1]

 Dataset 2
![alt text][image2]

# Follows Correct Algorithm

1. Follows general processing as taught in the lessons.

My program follows the general processing as taught in the lessons. My program:
  1. Takes in a first measurement
  2. Initializes the State and State Covariance matricies
  3. Takes in another measurement
  4. Updates the Process Covariance matrix
  5. Predicts the State and State Covariance matrices
  6. Finds the loss (Difference from Prediction and what Sensor says) 
  7. Finds the new Kalman Gain (how much weight to give the Prediction or Sensor)
  8. Gives a new estimate of the State and State Covariance matricies
  9. Returns to step #3 and keeps repeating

This can be found in FusionEKF.cpp and kalman_filter.cpp files in the src folder.

2. Kalman Filter handles the first measurements properly.

This is shown in lines 80-125 fo the FusionEKF.cpp file. Weather it be a lidar or radar sensor that is read first, I initialize px and py from the sensor only. Lidar only gives position and Radar, enough though it has range rate, it does not contain enough information to determine velocities (From the 'Tips and Tricks'). Therefore, I intialize the velocites, vx and vy, to 2. I played with a few numbers, but 2 worked the best. 

3. Kalman Filter first predicts then updates.

This is shown in lines 160-190 fo the FusionEKF.cpp file. It calls .Predict() first and then it calls an update based on the sensor that is giving us the data.

4. Kalman Filter can handle radar and lidar measurements.

This is shown in lines 30-102 of the kalman_filter.cpp file. I added an 'UpdateShared' function to the KalmanFilter class. I did this because the lidar and radar share the same update steps once the loss is found and it made it easier to bail out of a radar update if px or py where really close to their respective axis (lines 65-87). Looking back I proabably would have done more math in the FusionEKF.cpp file to weed out potential issues, but this was an okay solution. I also fix really large or small theta values (sorry for not using phi, I think flux when I hear that word. Electrical Engineering did this to me.) in this same block of code.

# Smell Test
1. For not using C++ in 7 years, this was rough to follow at first. I can't wait to improve.

### Discussion
Kalman Filter, what an amazing tool! In four years of Engineering school and a few Graduate Robotics courses, I can't believe this was not introduced. Once you get past all of the goofy nomenclature (Q = Process Covariance and P = State Covariance) and scripting, it such a powerful simple tool for tracking. Up to this point, I only relied upon what a sensor was telling me. 

For improvment on this project, I would probably start by filtering out some of the radar sensor readings. Some of them were pretty far off the path.



