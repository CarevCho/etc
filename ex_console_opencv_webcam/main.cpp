#include <iostream>
#include "opencv_3_4_1.h"

int main(int argc, char* argv)
{
	cv::VideoCapture vid;
	cv::Mat frame;
	int num_frame = 0;

	vid.open(0);	// -1 : select connected device
	
	// check connected or not
	if (vid.isOpened())
		std::cout << "connected" << std::endl;
	else
		std::cout << "No connection with any device" << std::endl;
	
	cv::namedWindow("camera", CV_NORMAL);	// make display window
	while (1)
	{
		vid >> frame;	// grab() & retrieve() from webcam
		if (frame.empty())	// check 
			continue;
		cv::imshow("camera", frame);	// show retrieved frame to window
		int key = cv::waitKey(30);	// wait until key down for 30ms
		if (key == 27)	// terminate when Escape(ESC) key pressed
			break;
		frame = cv::Mat();	// make frame empty
	}
	return 0;
}