#pragma once

#include <opencv2/video/tracking.hpp>

class KalmanFilter
{
public:
	KalmanFilter();

	std::unique_ptr<cv::KalmanFilter> filter;
};

