#include <iostream>
#include "src\opencv_3_3_0.h"

using namespace std;
using namespace cv;

struct inputdata {
	Mat image;
	Point2i center;
};

void onMouse(int event, int x, int y, int flags, void* userdata);

int main()
{
	VideoCapture vid;	// create videocpature class 
	Mat frame;			// to save frame from connected device(imaging unit)
	inputdata data;		// data paramter about mouse component

	vid.open(0);		// connect index 0 device
	if (!vid.isOpened())
		return -1;

	namedWindow("", CV_NORMAL);

	while (1) {
		vid >> frame;		// read frame from device
		if (frame.empty())
			break;
		
		///
		// initialize parameter about mouse component
		data.center = Point2i(0, 0);
		data.image = frame;
		///

		// hold function to window to control
		setMouseCallback("", onMouse, &data);
		imshow("", frame);
		

		int key = waitKey();
		if (key == 27)
			break;
		else if (key == 97)
			continue;

	}

    return 0;
}

void onMouse(int event, int x, int y, int flags, void* userdata)
{
	
	inputdata *p = (inputdata*)userdata;
	if (event == CV_EVENT_LBUTTONDOWN) {
		p->center.x = x; p->center.y = y;
		circle(p->image, p->center, 5, Scalar(0), -1);	
		imshow("", p->image);
	}
}
