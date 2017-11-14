#pragma warning (disable : 4996)
#include <iostream>
#include "opencv_3_3_0.h"

using namespace std;
using namespace cv;

cv::Point2d rotateVector(cv::Point2d vec, double degree);
void steering_movement(double angle);
void propulsion_movement(bool Direction = true);

cv::Point2d p_head, p_center, p_tail;
cv::Point2d p_fov_left, p_fov_center, p_fov_right;

double length, dis_work, FOV, propulsion;

int main(int argc, char* argv[])
{
	p_head = cv::Point2d(100, 300);
	length = 20, dis_work = length*1.5;
	p_tail = cv::Point2d(100., 300-20);

	p_center = (p_head + p_tail) / 2.;
	FOV = 156., propulsion = 3;
	steering_movement(0);

	cv::Mat map = cv::Mat(600, 600, CV_8UC1);
	map = cv::Scalar(0);
	cv::namedWindow("", CV_NORMAL);
	cv::resizeWindow("", 600, 600);
	while (true)
	{
		cv::Mat img = map.clone();
		//
		cv::Point2d center = cv::Point2d(300, 300);
		double radius = 200;
		double a, b, c;
		double m[2], n[2];
		double dis[2];
		cv::Point2d p_contact[2];

		cv::ellipse(img, center, cv::Size(radius, radius), 0, 0, 360, cv::Scalar(200), 1, 2);
		cv::line(img, cv::Point(100, 0), cv::Point(100, 300), cv::Scalar(200));
		cv::line(img, cv::Point(300, 500), cv::Point(600, 500), cv::Scalar(200));

		cv::line(img, p_head, p_tail, cv::Scalar(255), 1);

		
		a = (pow(center.x - p_head.x, 2) - pow(radius, 2));
		b = 2*(center.x - p_head.x)*(p_head.y - center.y);
		c = pow(p_head.y - center.y, 2) - pow(radius, 2);
		if (b*b - a*c >= 0) {
			if (a == 0) {
				if (p_head.y == center.y) {
					m[0] = m[1] = n[0] = n[1] = 0.;
				}
				else {
					m[0] = -c / b;
					n[0] = p_head.y - m[0] * p_head.x;
					m[1] = n[1] = 0.;
					cout << m[0] << "," << n[0] << endl;
				}
			}
			else {
				m[0] = (-b + sqrt(b*b - a*c)) / a;
				m[1] = (-b - sqrt(b*b - a*c)) / a;
				n[0] = p_head.y - m[0] * p_head.x;
				n[1] = p_head.y - m[1] * p_head.x;
				cout << m[0] << "," << n[0] << endl;
				cout << m[1] << "," << n[1] << endl;
			}
		}
		else {
			
		}
		cout << p_head << endl;
		cout << p_head.x << "," << m[0] * p_head.x + n[0] << endl;
		cout << p_head.x << "," << m[1] * p_head.x + n[1] << endl;


		double gradient, constant;
		double denominator, numerator;
		denominator = p_fov_center.x - p_fov_right.x;
		numerator = p_fov_center.y - p_fov_right.y;
		cv::circle(img, p_fov_left, 3, cv::Scalar(255), -1);
		cv::circle(img, p_fov_right, 3, cv::Scalar(255), -1);
		cv::line(img, p_fov_left, p_fov_right, cv::Scalar(255), 1);
		if (m[0] == m[1])
		{
			p_contact[0] = p_fov_center;
			cv::circle(img, p_contact[0], 4, cv::Scalar(255));
			p_contact[0].x = p_fov_center.x;
			p_contact[0].y = 0;
			p_contact[1].x = p_fov_center.x;
			p_contact[1].y = 600;
			cv::line(img, p_contact[0], p_contact[1], cv::Scalar(100));
		}
		else if (m[1] == 0) {
			if (abs(denominator) < .05) {
				p_contact[0].x = p_fov_center.x;
				p_contact[0].y = m[0] * p_contact[0].x + n[0];
				cv::circle(img, p_contact[0], 4, cv::Scalar(255));
			}
			else if (abs(numerator) < .05) {
				p_contact[0].y = p_fov_center.y;
				p_contact[0].x = (p_contact[0].y - n[0]) / m[0];
				cv::circle(img, p_contact[0], 4, cv::Scalar(255));
			}
			else {
				gradient = numerator / denominator;
				constant = p_fov_center.y - gradient*p_fov_center.x;
				p_contact[0].x = (constant - n[0]) / (m[0] - gradient);
				p_contact[0].y = m[0] * p_contact[0].x + n[0];
				cv::circle(img, p_contact[0], 4, cv::Scalar(255));
				cout << p_contact[0] << endl;
			}
			//
			p_contact[0].x = 0;
			p_contact[0].y = m[0] * p_contact[0].x + n[0];
			p_contact[1].x = 600;
			p_contact[1].y = m[0] * p_contact[1].x + n[0];
			cv::line(img, p_contact[0], p_contact[1], cv::Scalar(100));
		}
		else {
			if (abs(denominator) < .05) {
				p_contact[0].x = p_fov_center.x;
				p_contact[0].y = m[0] * p_contact[0].x + n[0];
				p_contact[1].x = p_fov_center.x;
				p_contact[1].y = m[1] * p_contact[1].x + n[1];
				dis[0] = cv::norm(p_contact[0] - center);
				dis[1] = cv::norm(p_contact[1] - center);
				if (dis[0] <= dis[1])
					cv::circle(img, p_contact[0], 4, cv::Scalar(255));
				else
					cv::circle(img, p_contact[1], 4, cv::Scalar(255));
			}
			else if (abs(numerator) < .05) {
				p_contact[0].y = p_fov_center.y;
				p_contact[0].x = (p_contact[0].y - n[0]) / m[0];
				p_contact[1].y = p_fov_center.y;
				p_contact[1].x = (p_contact[1].y - n[1]) / m[1];
				dis[0] = cv::norm(p_contact[0] - center);
				dis[1] = cv::norm(p_contact[1] - center);
				if (dis[0] <= dis[1])
					cv::circle(img, p_contact[0], 4, cv::Scalar(255));
				else
					cv::circle(img, p_contact[1], 4, cv::Scalar(255));
			}
			else {
				gradient = numerator / denominator;
				constant = p_fov_center.y - gradient*p_fov_center.x;
				p_contact[0].x = (constant - n[0]) / (m[0] - gradient);
				p_contact[0].y = m[0] * p_contact[0].x + n[0];
				p_contact[1].x = (constant - n[1]) / (m[1] - gradient);
				p_contact[1].y = m[1] * p_contact[1].x + n[1];
				dis[0] = cv::norm(p_contact[0] - center);
				dis[1] = cv::norm(p_contact[1] - center);
				if (dis[0] <= dis[1])
					cv::circle(img, p_contact[0], 4, cv::Scalar(255));
				else
					cv::circle(img, p_contact[1], 4, cv::Scalar(255));
				cout << p_contact[0] << endl;
				cout << p_contact[1] << endl;
			}
			//
			p_contact[0].x = 0;
			p_contact[0].y = m[0] * p_contact[0].x + n[0];
			p_contact[1].x = 600;
			p_contact[1].y = m[0] * p_contact[1].x + n[0];
			cv::line(img, p_contact[0], p_contact[1], cv::Scalar(100));

			p_contact[0].x = 0;
			p_contact[0].y = m[1] * p_contact[0].x + n[1];
			p_contact[1].x = 600;
			p_contact[1].y = m[1] * p_contact[1].x + n[1];
			cv::line(img, p_contact[0], p_contact[1], cv::Scalar(100));
		}

		
		cv::flip(img, img, 0);
		cv::imshow("", img);

		int key = waitKey(0);
		//
		if (key == 97)
			steering_movement(-1);
		else if (key == 100)
			steering_movement(1);
		else if (key == 119)
			propulsion_movement(true);
		else if (key == 115)
			propulsion_movement(false);
		else if (key == 27)
			break;

	}

}

void steering_movement(double angle) {
	double radian = angle * CV_PI / 180.;
	double matrix[2][2];
	matrix[0][0] = cos(radian), matrix[0][1] = -sin(radian);
	matrix[1][0] = sin(radian), matrix[1][1] = cos(radian);
	cv::Point2d vec_direc = (p_head - p_center) / cv::norm(p_head - p_center);

	double tmp_x, tmp_y;
	tmp_x = vec_direc.x * matrix[0][0] + vec_direc.y * matrix[0][1];
	tmp_y = vec_direc.x * matrix[1][0] + vec_direc.y * matrix[1][1];
	vec_direc.x = tmp_x, vec_direc.y = tmp_y;
	vec_direc /= cv::norm(vec_direc);

	p_center = p_head - vec_direc *length / 2.;
	p_tail = p_head - vec_direc * length / 1.;

	vec_direc = (p_head - p_center) / cv::norm(p_head - p_center);
	p_fov_left = p_head + rotateVector(vec_direc * dis_work / cos(FOV / 2.*CV_PI / 180.), FOV / 2.);
	p_fov_right = p_head + rotateVector(vec_direc * dis_work / cos(FOV / 2.*CV_PI / 180.), -FOV / 2.);
	p_fov_center = (p_fov_right + p_fov_left) / 2.;

}


cv::Point2d rotateVector(cv::Point2d vec, double degree) {
	cv::Point2d vRotated(0.0, 0.0);
	double radian = degree * CV_PI / 180.;
	double cosTheta = cos(radian);
	double sinTheta = sin(radian);

	vRotated.x = (vec.x * cosTheta) + (vec.y * -sinTheta);
	vRotated.y = (vec.x * sinTheta) + (vec.y * cosTheta);

	return vRotated;
}

void propulsion_movement(bool Direction) {
	cv::Point2d vec_direc = (p_head - p_center) / cv::norm(p_head - p_center);
	if (Direction) {
		p_head += vec_direc * propulsion;
		p_tail += vec_direc * propulsion;
		p_center += vec_direc * propulsion;

		p_fov_center += vec_direc * propulsion;
		p_fov_right += vec_direc * propulsion;
		p_fov_left += vec_direc * propulsion;
	}
	else {
		p_head -= vec_direc * propulsion;
		p_tail -= vec_direc * propulsion;
		p_center -= vec_direc * propulsion;

		p_fov_center -= vec_direc * propulsion;
		p_fov_right -= vec_direc * propulsion;
		p_fov_left -= vec_direc * propulsion;
	}
}
