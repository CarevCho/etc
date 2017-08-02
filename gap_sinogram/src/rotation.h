#pragma once

#define PI 3.141592
#include <math.h>

/**
* struct cartesian coordinate point
*/
typedef struct carPoint {
	float x;
	float y;
}carPoint;

/**
* convert degree to radian angle
* @param degree : degree angle
* @return : radian angle
*/
float degreeToradian(float degree);
/**
* convert radian to degree angle
* @param degree : radian angle
* @return : degree angle
*/
float radianTodegree(float radian);
/**
* rotate cartesian coordinate point by input degree ( direction : clockwise )
* @param carPoint : struct indicate cartesian coordinat such that x and y
* @param degree : specific angle to rotate
* @return : rotated point
*/
carPoint rotClock(carPoint object, float degree);
/**
* rotate cartesian coordinate point by input degree ( direction : counter clockwise )
* @param carPoint : struct indicate cartesian coordinat such that x and y
* @param degree : specific angle to rotate
* @return : rotated point
*/
carPoint rotCounterClock(carPoint object, float degree);