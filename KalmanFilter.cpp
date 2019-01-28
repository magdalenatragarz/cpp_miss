#include "KalmanFilter.h"

KalmanFilter::KalmanFilter()
{
	filter = std::make_unique<cv::KalmanFilter>(2, 1, 0);
	filter->transitionMatrix = (cv::Mat_<float>(2, 2) << 1, 1, 0, 1);
	cv::setIdentity(filter->measurementMatrix);
	cv::setIdentity(filter->processNoiseCov, cv::Scalar::all(1e-5));
	cv::setIdentity(filter->measurementNoiseCov, cv::Scalar::all(1e-5));
	cv::setIdentity(filter->errorCovPost, cv::Scalar::all(1));
	cv::randn(filter->statePost, cv::Scalar::all(0), cv::Scalar::all(0.1));
}

