#pragma once

#include <string>

#include "opencv2/opencv.hpp"

class ImageProcessor
{
public:
	static std::vector<std::vector<cv::Point>> getMovement(std::shared_ptr<cv::Mat> frame1, std::shared_ptr<cv::Mat> frame);
	static void mergeContoursIntoFrame(std::vector<cv::Rect> contours, std::shared_ptr<cv::Mat> frame);
	static void mergeDotsIntoFrame(std::vector<cv::Point> points, std::shared_ptr<cv::Mat> frame);
	static std::vector<cv::Rect> convertToBoundingBoxes(std::vector<std::vector<cv::Point>> contours);

private:
	static void resizeFrame(std::shared_ptr<cv::Mat> frame);
	static void processFrame(std::shared_ptr<cv::Mat> frame);
	static std::shared_ptr<cv::Mat> subtractFrames(std::shared_ptr<cv::Mat> frame1, std::shared_ptr<cv::Mat> frame2);
	static std::vector<std::vector<cv::Point>> getContours(std::shared_ptr<cv::Mat> frame);
};

