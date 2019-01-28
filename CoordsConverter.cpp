#include "CoordsConverter.h"

CoordsConverter::CoordsConverter()
{
	k = 0.00000059;
	matrix = cv::Mat(3, 3, CV_32F);
	matrix.at<float>(0, 0) = -3.38526910e-01;
	matrix.at<float>(0, 1) = -1.40003218e+00;
	matrix.at<float>(0, 2) = 8.24632206e+02;
	matrix.at<float>(1, 0) = 4.25965620e-02;
	matrix.at<float>(1, 1) = -1.89572814e+00;
	matrix.at<float>(1, 2) = 1.13225776e+03;
	matrix.at<float>(2, 0) = 9.63151393e-05;
	matrix.at<float>(2, 1) = -2.34425794e-03;
	matrix.at<float>(2, 2) = 1.00000000e+00;

	distortion_center.x = 312;
	distortion_center.y = 462;

	offset.x = -541;
	offset.y = -604;
}

cv::Point CoordsConverter::camera_to_visualisation_cords(cv::Point point_)
{
	auto point = distorted_to_undistorted_point(point_);
	point.x = point.x - offset.x;
	point.y = point.y - offset.y;
	return persp_point(point);
}

cv::Point CoordsConverter::distorted_to_undistorted_point(cv::Point dist_point)
{
	auto r_2 = (distortion_center.y - dist_point.y) * (distortion_center.y - dist_point.y) + (distortion_center.x - dist_point.x) * (distortion_center.x - dist_point.x);
	auto x_ = (int)(distortion_center.y + (dist_point.y - distortion_center.y) * (1 + k * r_2));
	auto y_ = (int)(distortion_center.x + (dist_point.x - distortion_center.x) * (1 + k * r_2));
	return cv::Point(x_, y_);
}

cv::Point CoordsConverter::persp_point(cv::Point point)
{
	auto aaa = matrix.at<float>(2, 0);
	auto A = point.x * matrix.at<float>(2, 0) + point.y * matrix.at<float>(2, 1) + matrix.at<float>(2, 2);
	auto x = point.x * matrix.at<float>(0, 0) + point.y * matrix.at<float>(0, 1) + matrix.at<float>(0, 2);
	auto y = point.x * matrix.at<float>(1, 0) + point.y * matrix.at<float>(1, 1) + matrix.at<float>(1, 2);
	x = (int)(x / A);
	y = (int)(y / A);
	return cv::Point(x, y);
}




