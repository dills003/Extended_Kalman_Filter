#include "kalman_filter.h"
#include <iostream>
#define PI 3.14159265359
#define TINY_NUMBER .2 //used to check if radar px py are close to an axis

using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

KalmanFilter::KalmanFilter() {}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
	MatrixXd &H_in, MatrixXd &R_in, MatrixXd &Q_in) {
	x_ = x_in;
	P_ = P_in;
	F_ = F_in;
	H_ = H_in;
	R_ = R_in;
	Q_ = Q_in;
}

void KalmanFilter::Predict() {
	/**
	TODO:
	  * predict the state
	*/
	x_ = F_ * x_; // new state prediction - From Quiz
	MatrixXd Ft = F_.transpose(); //to get math to work
	P_ = F_ * P_ * Ft + Q_; //new state covariance matrix
	//cout << "P_: " << endl << P_ << endl;
}

void KalmanFilter::Update(const VectorXd &z) {
	/**
	TODO:
	  * update the state by using Kalman Filter equations
	*/
	VectorXd y = z - (H_ * x_); //raw measurement subtract the guess, called error

	//dump error into UpdateShared, got rid of duplicate code, all fancy nonlinear does
	//is find error
	UpdateShared(y);
	//cout << "y from KF: " << endl << y << endl;
}

void KalmanFilter::UpdateEKF(const VectorXd &z) {
	/**
	TODO:
	  * update the state by using Extended Kalman Filter equations
	*/
	//we need to take the state(x) and convert it back into polar
	//opposite of what we did with initialize
	float Px = x_(0); //position of x
	float Py = x_(1); //position of y
	float Vx = x_(2); //velocity in x
	float Vy = x_(3); //velocity in y

	float rho = sqrt((Px * Px) + (Py * Py)); //from lecture math
	float theta = atan2(Py, Px); //help says to use atan2
	float rhoDot = (((Px * Vx) + (Py * Vy)) / (rho));

	//check if Px and Py are not near their 0 respective axis points
	if (fabs(Px) > TINY_NUMBER && fabs(Py) > TINY_NUMBER)
	{
		//atan2 can return values larger than PI or smaller than -PI, fix it here
		while (theta > PI || theta < -PI)
		{
			if (theta > PI)
			{
				theta = theta - (2 * PI);
			}
			else if (theta < -PI)
			{
				theta = theta + (2 * PI);
			}
		}

		VectorXd hx = VectorXd(3); //creating my H * x polar vector
		hx << rho, theta, rhoDot;

		VectorXd y = z - hx; //error

		UpdateShared(y); //finish my update
	}

}

void KalmanFilter::UpdateShared(const VectorXd &y) {
	//Copied from Quiz
	MatrixXd Ht = H_.transpose(); //for KF calculation
	MatrixXd S = H_ * P_ * Ht + R_; //for KF calculation
	MatrixXd Si = S.inverse(); //for KF calculation
	MatrixXd PHt = P_ * Ht; //for KF calculation
	MatrixXd K = PHt * Si; //Kalman Gain

	//new estimates
	x_ = x_ + (K * y); //state estimate
	long x_size = x_.size();
	MatrixXd I = MatrixXd::Identity(x_size, x_size);
	P_ = (I - (K * H_)) * P_; //state covariance estimate
}
