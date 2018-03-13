#pragma once
// include header, before including add opencv header file path to additional include  directories at project property
#include "opencv2\opencv.hpp"	

// OpenCV 3.4.1, check preprocessor
#if _DEBUG
// debug mode
#pragma comment(lib, "opencv_world341d.lib")
#elif NDEBUG
// release mode
#pragma comment(lib, "opencv_world341.lib")
#endif