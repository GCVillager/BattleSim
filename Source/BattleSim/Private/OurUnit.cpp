#include "OurUnit.h"

OurUnit::OurUnit(Position position,double velocity) {
	this->position = position;
	this->velocity = velocity;
	timeCount = 0;
	canKillTarget = false;
}

void OurUnit::loop(double dTime) {
	// 每次循环时,都会向前行进

	this->position = position.forwardXYZ(this->horizontalAngle, this->verticalAngle, this->velocity * dTime); // 行进

	timeCount += dTime;
	if (timeCount > 3.5) {
		canKillTarget = true;
		timeCount = 0;
	}
}


Position OurUnit::getPosition() {
	return this->position;
}
double OurUnit::getVelocity() {
	return this->velocity;
} 
double OurUnit::getVerticalAngle() {
	return this->velocity;
}

double OurUnit::getHorizontalAngle() {
	return this->horizontalAngle;
}
int OurUnit::getTarget() {
	return this->target;
}

void OurUnit::setPosition(Position position) {
	this->position = position;
}
void OurUnit::setVelocity(double velocity) {
	this->velocity = velocity;
}
void OurUnit::setVerticaAngle(double vertical_angle) {
	this->verticalAngle = vertical_angle;
}
void OurUnit::setHorizontalAngle(double horizontal_angle) {
	this, horizontalAngle = horizontal_angle;
}
void OurUnit::setTarget(int id) {
	this->target = id;
}