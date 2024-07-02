#include "Position.h"
#include "CoreUtils.h"

Position::Position(double x, double y, double z) :x(x), y(y), z(z) {}

Position operator+(const Position& a, const Position& b) {
	Position result = Position(0, 0, 0);
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

Position operator-(const Position& a, const Position& b) {
	Position result = Position(0, 0, 0);
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

Position Position::forwardXY(const double rotation,const double step) const {
	return forwardXY(*this, rotation, step);
}

Position Position::forwardXY(const Position position ,const double rotation, const double step){
	Position result = position;
	double radian = utils::transformToRadian2PI(rotation);
	result.x += cos(radian) * step;
	result.y += sin(radian) * step;
	return result;
}

Position Position::forwardXYZ(const double horizontal_rotation, const double vertical_rotation, const double step) const{
	return forwardXYZ(*this, horizontal_rotation, vertical_rotation, step);
}

Position Position::forwardXYZ(const Position position, const double horizontal_rotation, const double vertical_rotation, const double step) {
	Position result = position;
	double vertical_radian = utils::transformToRadianPI(vertical_rotation);
	double horizontal_radian = utils::transformToRadian2PI(horizontal_rotation);

	double r = cos(vertical_radian) * step;
	result.z += sin(vertical_radian) * step;

	result.x += cos(horizontal_radian) * r;
	result.y += sin(horizontal_radian) * r;
	return result;
}

Position::Position(const Position& a) {
	x = a.x;
	y = a.y;
	z = a.z;
}


double Position::getHorizontalAngle(const Position direction) const {
	return getHorizontalAngle(*this, direction);
}

double Position::getHorizontalAngle(const Position source, const Position direction) {
	double deltaX = direction.x - source.x;
	double deltaY = direction.y - source.y;
	double result = utils::transformToAngle360(atan2(deltaY, deltaX));
	return result;
}


double Position::getVerticalAngle(const Position direction) const {
	return getVerticalAngle(*this, direction);
}

double Position::getVerticalAngle(const Position source, const Position direction) {
	double deltaZ = direction.z - source.z;
	double deltaR = distanceXY(source, direction);
	double result = utils::transformToAngle180(atan2(deltaZ, deltaR));
	return result;
}

double Position::distanceXY(const Position source, const Position direction) {
	double deltaX = fabs(source.x - direction.x);
	double deltaY = fabs(source.y - direction.y);
	double result = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	return result;
}

double Position::distanceXY(const Position direction) const {
	return distanceXY(*this, direction);
}

double Position::distanceXYZ(const Position direction) const {
	return distanceXYZ(*this, direction);
}


double Position::distanceXYZ(const Position source, const Position direction) {
	double deltaX = fabs(source.x - direction.x);
	double deltaY = fabs(source.y - direction.y);
	double deltaZ = fabs(source.z - direction.z);
	double result = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
	return result;
}