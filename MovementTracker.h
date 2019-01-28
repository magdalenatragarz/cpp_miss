#pragma once

#include <opencv2/opencv.hpp>
#include "CoordsConverter.h"
#include "Person.h"

class MovementTracker
{
public:
	MovementTracker(std::string videoPath, std::string picPath);

	CoordsConverter converter;
	std::shared_ptr<cv::Mat> pic;
	std::string picPath;
	cv::VideoCapture capture;
	std::vector<Person> people;

	void run();

private:
	std::vector<std::vector<cv::Point>> filterDetectedContours(std::vector<std::vector<cv::Point>> contours);
	std::vector<cv::Point> bboxesToDots(std::vector<cv::Rect> contours);
	void markPeopleNotUpdated();
	

};

