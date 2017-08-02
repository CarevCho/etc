#pragma once
#pragma warning (disable:4996)

#define PI 3.141592
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rotation.h"

/**
* struct for head containing carPoint struct
*/
typedef struct head {
	carPoint* det;
}head;

/**
* polar coordinate point
* r is radial, t is theta
*/
typedef struct polPoint {
	float r;
	float t;
}polPoint;

void gap_sino(int head_num, float detector_width, float xrSampling_mm, int detector_num, float gap_angle, int imageWidth, char* filename);
void gap_sino(int head_num, float detector_width, float xrSampling_mm, int detector_num, float dis_head, char* filename);
int num_yr(int num_detecter, int num_head);
