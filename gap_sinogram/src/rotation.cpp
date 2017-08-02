#include "rotation.h"

/**
* convert degree to radian angle
* @param degree : degree angle
* @return : radian angle
*/
float degreeToradian(float degree)
{
	return degree*PI / 180.;
}

/**
* convert radian to degree angle
* @param degree : radian angle
* @return : degree angle
*/
float radianTodegree(float radian) 
{
	return radian * 180. / PI;
}

/**
* rotate cartesian coordinate point by input degree ( direction : clockwise )
* @param carPoint : struct indicate cartesian coordinat such that x and y
* @param degree : specific angle to rotate
* @return : rotated point
*/
carPoint rotClock(carPoint object, float degree)
{
	carPoint result;
	degree = degreeToradian(degree);
	
	float rotMatrix[4] = {0,};
	rotMatrix[0] = cos(degree); rotMatrix[1] = sin(degree); 
	rotMatrix[2] = -sin(degree); rotMatrix[3] = cos(degree);
	
	result.x = object.x*rotMatrix[0] + object.y*rotMatrix[1];
	result.y = object.x*rotMatrix[2] + object.y*rotMatrix[3];

	return result;
}

/**
* rotate cartesian coordinate point by input degree ( direction : counter clockwise )
* @param carPoint : struct indicate cartesian coordinat such that x and y
* @param degree : specific angle to rotate
* @return : rotated point
*/
carPoint rotCounterClock(carPoint object, float degree)
{
	carPoint result;
	degree = degreeToradian(degree);
	
	float rotMatrix[4] = { 0, };
	rotMatrix[0] = cos(degree); rotMatrix[1] = -sin(degree);
	rotMatrix[2] = sin(degree); rotMatrix[3] = cos(degree);

	result.x = object.x*rotMatrix[0] + object.y*rotMatrix[1];
	result.y = object.x*rotMatrix[2] + object.y*rotMatrix[3];

	return result;
}