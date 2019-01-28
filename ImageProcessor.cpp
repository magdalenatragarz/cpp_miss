#include <opencv2/opencv.hpp>
#include <algorithm>

#include "ImageProcessor.h"

void ImageProcessor::resizeFrame(std::shared_ptr<cv::Mat> frame)
{
	cv::resize(*frame, *frame, cv::Size(700, 500));
}

void ImageProcessor::processFrame(std::shared_ptr<cv::Mat> frame)
{
	auto kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(6, 3), cv::Point(-1, -1));

	cv::cvtColor(*frame, *frame, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(*frame, *frame, cv::Size(7, 7), 1);
	cv::threshold(*frame, *frame, 10, 255, cv::THRESH_BINARY);
	cv::morphologyEx(*frame, *frame, cv::MORPH_CLOSE, kernel);
	cv::dilate(*frame, *frame, kernel);
}

std::shared_ptr<cv::Mat> ImageProcessor::subtractFrames(std::shared_ptr<cv::Mat> frame1, std::shared_ptr<cv::Mat> frame2)
{
	auto frameDifference = std::make_shared<cv::Mat>();
	cv::absdiff(*frame1, *frame2, *frameDifference);
	return frameDifference;
}

std::vector<std::vector<cv::Point>> ImageProcessor::getContours(std::shared_ptr<cv::Mat> frame)
{
	using namespace std;
	using namespace cv;

	vector<vector<Point>> contours;
	cv::findContours(*frame, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	return contours;
}

std::vector<std::vector<cv::Point>> ImageProcessor::getMovement(std::shared_ptr<cv::Mat> frame1, std::shared_ptr<cv::Mat> frame2)
{
	ImageProcessor::resizeFrame(frame1);
	ImageProcessor::resizeFrame(frame2);

	auto difference = ImageProcessor::subtractFrames(frame1, frame2);
	ImageProcessor::processFrame(difference);
	return ImageProcessor::getContours(difference);
}


std::vector<cv::Rect> ImageProcessor::convertToBoundingBoxes(std::vector<std::vector<cv::Point>> contours)
{
	std::vector<cv::Rect> boundingBoxes;
	std::for_each(contours.begin(), contours.end(), [&](std::vector<cv::Point>& contour) {
		boundingBoxes.push_back(cv::boundingRect(contour));
	});
	return boundingBoxes;
}

void ImageProcessor::mergeContoursIntoFrame(std::vector<cv::Rect> contours, std::shared_ptr<cv::Mat> frame)
{
	std::for_each(contours.begin(), contours.end(), [&](cv::Rect& rectangle) {
		cv::rectangle(*frame,rectangle,cv::Scalar(0,255,0));
	});
}

void ImageProcessor::mergeDotsIntoFrame(std::vector<cv::Point> points, std::shared_ptr<cv::Mat> frame)
{
	std::for_each(points.begin(), points.end(), [&](cv::Point& point) {
		cv::circle(*frame, point,2, cv::Scalar(0, 255, 0));
	});
}



