#pragma once
#include <opencv2/opencv.hpp>

class CoordsConverter
{
public:
	CoordsConverter();
	~CoordsConverter() = default;

	cv::Mat matrix;
	double k;
	cv::Point distortion_center;
	cv::Point offset;

	cv::Point camera_to_visualisation_cords(cv::Point point);

private:
	cv::Point distorted_to_undistorted_point(cv::Point dist_point);
	cv::Point persp_point(cv::Point);

};

