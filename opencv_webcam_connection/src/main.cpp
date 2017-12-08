#include "opencv2\opencv.hpp"	/// include opencv header file
#include <iostream>

/// load opencv library 
#if _DEBUG
	// debug 
	#pragma comment(lib, "opencv_world330d.lib")
#else
	// release
	#pragma comment(lib, "opencv_world330.lib")
#endif

/// namespace for opencv , cv
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	VideoCapture vid;	// class about webcam
	vid.open(0);
	if (!vid.isOpened())
	{
		cout << "open error" << endl;
		return -1;
	}
	else {
		while (1) {
			Mat img;
			vid >> img;	// capture image from webcam
			if (img.empty())
				break;
			else {
				imshow("", img);
				if (waitKey(1000 / 30) == 30)
					break;
			}
		}
	}

	return 0;
}