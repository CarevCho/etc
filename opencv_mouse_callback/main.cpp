#include <iostream>
#include "src\opencv_3_3_0.h"

///
#include <io.h>
#include <string>
///

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

	string path = "D:\\MMMIL\\Project\\CapsuleEndoscopy\\data\\simulation\\*.*";
	cv::String dirPath = "D:\\MMMIL\\Project\\CapsuleEndoscopy\\data\\simulation\\";
	struct _finddata_t fd;
	intptr_t handle;
	int number = 0;
	if ((handle = _findfirst(path.c_str(), &fd)) == -1L)
		cout << "No file in directory!" << endl;
	do
	{
		String file = fd.name;
		//cout << fd.name << endl;
		cout << dirPath + file << endl;
		if (number >= 2) {

			frame = imread(dirPath + file, IMREAD_GRAYSCALE);		// read frame from device
			if (frame.empty())
				break;
			Mat grayimg = frame(Rect(5, 0, frame.cols - 20, frame.rows));
			equalizeHist(grayimg, grayimg);

			///
			// initialize parameter about mouse component
			data.center = Point2i(0, 0);
			data.image = grayimg;
			///

			// hold function to window to control
			setMouseCallback("", onMouse, &data);
			imshow("", grayimg);


			int key = waitKey();
			if (key == 27)
				break;
			else if (key == 97)
				continue;
		}number++;
	} while (_findnext(handle, &fd) == 0);
	_findclose(handle);

    return 0;
}

void onMouse(int event, int x, int y, int flags, void* userdata)
{
	
	inputdata *p = (inputdata*)userdata;
	if (event == CV_EVENT_LBUTTONDOWN) {
		p->center.x = x; p->center.y = y;
		circle(p->image, p->center, 5, Scalar(255), -1);	
		imshow("", p->image);
	}
}
