#include <iostream>

using namespace std;

/**
* rotate point with specific angle
*
* @brief : rotate point from origin(0. , 0.) to specific angle and return x component
* @param angle : to rotate angle, positive angle means clockwise, negative angle means counter clockwise
* @param x : component x to be rotated
* @param y : compenent y to be rotated
* @param return_type : return x component or y component. default is true( x component )
* @param origin_x : rotating axis x component. default is 0.
* @param origin_y : rotating axis y component. default is 0.
*/
double ch_rotate(double angle, double x, double y ,bool return_type = true, double origin_x = 0., double origin_y = 0.)
{
	double result = 0.;
	double radian = angle * 3.14159265359 / 180.;
	double rotate_matrix[2][2];
	rotate_matrix[0][0] = cos(radian); rotate_matrix[0][1] = -sin(radian);
	rotate_matrix[1][0] = sin(radian); rotate_matrix[1][1] = cos(radian);

	if (return_type) {
		// return rotated angle x component
		result = (x - origin_x)*rotate_matrix[0][0] + (y - origin_y)*rotate_matrix[1][0] + origin_x;
	}
	else {
		// return rotated angle y component
		result = (x - origin_x)*rotate_matrix[0][1] + (y - origin_y)*rotate_matrix[1][1] + origin_y;
	}
	
	return result;
}

double ch_intersection(double angle, double value_x,double value_y, bool return_type = true) 
{
	double result = 0.;

	if (return_type) {
		// return x compoent of intersection
		// define f(x)

	}
	else {
		// return y compoent of intersection
		// define f(x)

	}
	return result;
}


int main(int argc, char* argv[]) 
{
	/*
	double x = 0.;
	double y = 2.;

	double rotated_x = ch_rotate(-0, x, y,true,0,1);
	double rotated_y = ch_rotate(-0, x, y, false,0,1);

	cout << rotated_x << "," << rotated_y << endl;
	*/

	double x = 0.;
	double y = 0.;

	// x^2 + y^2 = 10^2

	// atan return -pi/2 ~ pi/2
	// atan2 return -pi ~ pi, selected
	double diff_x, diff_y;
	diff_x = 1; diff_y = 1/2.;
	double angle = atan2(diff_y,diff_x);

	angle = angle / 3.14159265359 * 180.;
	if (angle < 0) 
		angle += 180;
	angle = angle * 3.14159265359 / 180.;
	double gradient = tan(angle);
	angle = angle / 3.14159265359 * 180.;

	cout << gradient << "," << angle << endl;

	
	return 0;
}

