#pragma once

#include <opencv2/imgproc/imgproc.hpp>

class Position
{
public:

	cv::Point coordinates;
	int timestamp;

	Position(cv::Point coordinates, int timestamp);
	~Position() = default;
};

