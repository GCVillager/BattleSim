#include "CoreUtils.h"
#include <cmath>

double utils::normalizeAngle360(double angle){
	return angle - floor(angle / 360) * 360;
}

double utils::normalizeAngle180(double angle) {
	double tmp = fmod(angle, 360); // 将角度转化至-360 - 360
	double result;
	if (tmp < -90) {
		result = -180 - tmp;
	}
	else if (tmp > 90) {
		result = 180 - tmp;
	}
	else {
		result = tmp;
	}

	return result;
}

double utils::normalizeRadian2PI(double radian) {
	return radian - floor(radian / (2*PI)) * (2*PI);
}

double utils::normalizeRadianPI(double radian) {
	double tmp = fmod(radian, 2*PI); // 将角度转化至-360 - 360
	double result;
	if (tmp < -PI/2) {
		result = -PI - tmp;
	}
	else if (tmp > PI/2) {
		result = PI - tmp;
	}
	else {
		result = tmp;
	}

	return result;
}

double utils::transformToAngle360(double radian) {
	radian = utils::normalizeRadian2PI(radian);
	return radian * 180 / PI;
}

double utils::transformToAngle180(double radian) {
	radian = utils::normalizeRadianPI(radian);
	return radian * 180 / PI;
}

double utils::transformToRadian2PI(double angle) {
	angle = utils::normalizeAngle360(angle);
	return angle * PI / 180;
}

double utils::transformToRadianPI(double angle) {
	angle = utils::normalizeAngle180(angle);
	return angle * PI / 180;
}
