#include <iostream>
#include "src\opencv_3_3_0.h"

///
#include <io.h>
#include <string>
///

// header for write reference point
#include <fstream>

using namespace cv;
using namespace std;

struct inputdata {
	Mat image;
	Point2i center;
};

void onMouse(int event, int x, int y, int flags, void* userdata);

int main()
{
	// file write
	std::ofstream fileout;
	fileout.open("reference.txt");
	if (fileout.is_open()) {
		std::cout << "open success" << std::endl;
	}
	VideoCapture vid;	// create videocpature class 
	Mat frame;			// to save frame from connected device(imaging unit)
	inputdata data;		// data paramter about mouse component

	vid.open(0);		// connect index 0 device
	if (!vid.isOpened())
		return -1;

	namedWindow("", CV_NORMAL);

	std::string path = "D:\\MMMIL\\Project\\CapsuleEndoscopy\\data\\simulation\\*.*";
	cv::String dirPath = "D:\\MMMIL\\Project\\CapsuleEndoscopy\\data\\simulation\\";
	struct _finddata_t fd;
	intptr_t handle;
	int number = 0;
	if ((handle = _findfirst(path.c_str(), &fd)) == -1L)
		std::cout << "No file in directory!" << std::endl;
	do
	{
		String file = fd.name;
		//cout << fd.name << endl;
		std::cout << dirPath + file << std::endl;
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
			if (key == 27)		// 'ESC' key
				break;
			else if (key == 97)	// 'a' key
				continue;
			else if (key == 32) {	// space bar
				fileout << data.center.x << "," << data.center.y << endl;
			}

		}number++;
	} while (_findnext(handle, &fd) == 0);
	_findclose(handle);
	fileout.close();

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
