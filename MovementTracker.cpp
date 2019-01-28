#include "MovementTracker.h"
#include "ImageProcessor.h"
#include "CoordsConverter.h"

MovementTracker::MovementTracker(std::string videoPath_, std::string picPath_) : 
	capture(videoPath_),
	picPath(picPath_),
	converter()
{
}

void MovementTracker::run()
{
	
	pic = std::make_shared<cv::Mat>();
	*pic = cv::imread(picPath);
	auto pic_cpy = pic;
	
	if (!capture.isOpened()) {
		return;
	}
	cv::namedWindow("", 2);
	cv::namedWindow("aaa", 1);

	auto frame_tmp = std::make_shared<cv::Mat>();
	auto frame1 = std::make_shared<cv::Mat>();
	auto frame2 = std::make_shared<cv::Mat>();

	while (capture.isOpened())
	{
		capture >> *frame_tmp;
		capture >> *frame1;
		capture >> *frame2;

		auto contours = ImageProcessor::getMovement(frame1, frame2);
		auto newContours = filterDetectedContours(contours);
		auto boundingBoxes = ImageProcessor::convertToBoundingBoxes(newContours);
		auto dots = bboxesToDots(boundingBoxes);

		ImageProcessor::mergeDotsIntoFrame(dots, pic_cpy);
		ImageProcessor::mergeContoursIntoFrame(boundingBoxes, frame1);

		cv::imshow("", *pic_cpy);
		cv::imshow("aaa", *frame1);

		pic_cpy = pic;

		if (cv::waitKey(30) >= 0) break;
	}
	cv::destroyAllWindows();
}

std::vector<std::vector<cv::Point>> MovementTracker::filterDetectedContours(std::vector<std::vector<cv::Point>> contours)
{
	contours.erase(std::remove_if(contours.begin(), contours.end(), [&](std::vector<cv::Point> contour) { 
		return cv::contourArea(contour) < 100; 
	}),contours.end());

	contours.erase(std::remove_if(contours.begin(), contours.end(), [&](std::vector<cv::Point> contour) {
		return contour.at(0).y < 350;
	}),contours.end());

	return contours;
}

void MovementTracker::markPeopleNotUpdated()
{
	std::for_each(people.begin(), people.end(), [&](Person& person) {
		person.markNotUpdated();
	});
}

std::vector<cv::Point> MovementTracker::bboxesToDots(std::vector<cv::Rect> contours) 
{
	std::vector<cv::Point> dots;
	for (int i = 0; i < contours.size(); i++) {
		dots.push_back(converter.camera_to_visualisation_cords(cv::Point(contours.at(i).x, contours.at(i).x)));
		std::cout << "from: " << contours.at(i).x << ", " << contours.at(i).x << " to "  <<  dots.at(i).x << "," << dots.at(i).x << std::endl;
	}
	return dots;
}
