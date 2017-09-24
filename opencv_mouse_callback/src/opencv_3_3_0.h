#pragma once

#include "opencv2\opencv.hpp"

#pragma warning(disable :4819)

#if _DEBUG
#pragma comment(lib, "opencv_world330d.lib")
#else
#pragma comment(lib, "opencv_world330.lib")
#endif