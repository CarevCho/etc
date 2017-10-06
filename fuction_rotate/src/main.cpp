#include <iostream>

using namespace std;

/**
* degree to radian transformation
*
* @brief : convert degree unit to radian unit
* @param degree : to be converted degree value
*/
double ch_DtoR(double degree)
{
	return degree * 3.14159265359 / 180.;
}

/**
* radian to degree transformation
*
* @brief : convert radian unit to degree unit
* @param degree : to be converted radian value
*/
double ch_RtoD(double radian)
{
	return radian / 3.14159265359 * 180.;
}

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
double ch_rotate(double angle, double x, double y, bool return_type = true, double origin_x = 0., double origin_y = 0.)
{
	double result = 0.;
	double radian = ch_DtoR(angle);
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

int main(int argc, char* argv[]) 
{
	/*
	// rotate function test
	double x = 0.;
	double y = 2.;

	double rotated_x = ch_rotate(-0, x, y,true,0,1);
	double rotated_y = ch_rotate(-0, x, y, false,0,1);

	cout << rotated_x << "," << rotated_y << endl;
	*/

	double capsule_head_x, capsule_head_y;	// capsule head point
	double capsule_fov_left_x, capsule_fov_left_y, capsule_fov_right_x, capsule_fov_right_y;	// capsule fov dimension left to right point
	double capsule_width, capsule_diameter;	// capsule component
	double capsule_fov_angle, capsule_working_distance;	// capsule component
	capsule_fov_angle = 90.; capsule_working_distance = 1.;
	capsule_head_x = 1.; capsule_head_y = 2.;
	capsule_width = 2.; capsule_diameter = 3.;
	
	double gradient = tan(ch_DtoR(90 - capsule_fov_angle / 2.));
	capsule_fov_right_y = capsule_head_y + capsule_working_distance;
	capsule_fov_right_x = (gradient*capsule_head_x - capsule_head_y + capsule_fov_right_y) / gradient;
	gradient = tan(ch_DtoR(90 + capsule_fov_angle / 2.));
	capsule_fov_left_y = capsule_head_y + capsule_working_distance;
	capsule_fov_left_x = (gradient*capsule_head_x - capsule_head_y + capsule_fov_right_y) / gradient;

	return 0;
}

