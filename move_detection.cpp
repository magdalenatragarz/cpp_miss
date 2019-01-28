#include "MovementTracker.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;


int main()
{
	MovementTracker tracker("D:krk_ok3.mov", "D:fromabove.jpg");
	tracker.run();

	return 0;
}