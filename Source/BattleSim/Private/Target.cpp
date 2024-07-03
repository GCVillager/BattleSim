#include "Target.h"
#include <cmath>
#include <random>

void Target::setLevel(int level) {
	this->level = level;
}
int Target::getLevel() {
	return level;
}


void Target::loop(double dTime) {
	//this->calculateRotation();

	if (this->markedDeath)return;

	if (this->status != STATUS::FIGHT) {
		// 如果自己的状态不是战斗
		this->velocity = 0;
	}

	this->forward(dTime);

	// 计算各自对应的权重
	// 根据种类判定
	if (this->type == TYPE::PLANE) {
		weights[0] = 30000;
	}
	else if (this->type == TYPE::TANK) {
		weights[0] = 20000;
	}
	else {
		weights[0] = 10000;
	}
	// 根据距离判定
	double distance = this->position.distanceXY(unit->getPosition());
	weights[1] = 710 - distance; //距离越近优先级越高
	// 根据状态判定
	if (this->status == FIGHT) {
		weights[2] = 5000;
	}
	else if (this->status == STANDBY) {
		weights[2] = 3000;
	}
	else {
		weights[2] = 1000;
	}
	// 根据威胁距离判定
	weights[3] = (threatDistance >= distance) ? 100 : 0;
	// 根据距离我方的方位判定
	angleToOurUnit = unit->getPosition().getHorizontalAngle(this->position);
	if (angleToOurUnit >= 45 and angleToOurUnit <= 135 or angleToOurUnit >= 225 and angleToOurUnit <= 315) {
		weights[4] = 50;
	}
	else {
		weights[4] = 0; 
	}

	weights[5] = (jammingStrength1 >= distance) ? 30 : 0;
	weights[6] = (jammingStrength2 >= distance) ? 20 : 0;
	double tmp_weights[7] = { 0 };
	score = getWeightDifference(this->weights, tmp_weights);

	timeCount += dTime; // 加时

	if (timeCount > 20) {
		// 超过20s时,随机更新状态
		if (type == PLANE) {
			timeCount = 0;
			return;
		}
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int<int> dist_int(1, 5);
		int tmp = dist_int(gen);
		if (tmp == 4) {
			std::uniform_int_distribution<int> dist_status(1, 8);
			std::uniform_real_distribution<double> dist_velocity(5, 10);
			tmp = dist_status(gen);
			if (tmp <= 6) {
				status = FIGHT;
				velocity = dist_velocity(gen);
			}
			else if (tmp == 7) {
				status = STANDBY;
				velocity = 0;
			}
			else if (tmp == 8) {
				status = RESTING;
				velocity = 0;
			}
			timeCount = 0;
		}
	}

}


double Target::getScore() const {
	return this->score;
}

double Target::getScore(double weight[7]) {
	double tmp[7] = { 0 };
	return getWeightDifference(weight, tmp);
}

double Target::getWeightDifference(double weight[7]) const {
	double result = 0;
	for (int i = 0; i < 7; i++) {
		result += pow(weight[i] - this->weights[i], 2);
	}
	return sqrt(result);
}

double Target::getWeightDifference(double weightA[7], double weightB[7]) {
	double result = 0;
	for (int i = 0; i < 7; i++) {
		result += pow(weightA[i] - weightB[i], 2);
	}
	return sqrt(result);
}


Target::Target(int id, TYPE type, Position position, double velocity, STATUS status, double threatDistance, double jammingStrength1, double jammingStrength2, OurUnit* unit) :
	id(id), type(type), position(position), velocity(velocity), status(status), threatDistance(threatDistance), jammingStrength1(jammingStrength1), jammingStrength2(jammingStrength2), unit(unit)
{
	angleToOurUnit = -1;
	horizontalAngle = -1;
	verticalAngle = -1;
	score = -1;
	for (int i = 0; i < 7; i++) {
		weights[i] = 0;
	}
	centerIndex = -1;
	markedDeath = false;
	timeCount = 0;
	markedKilled = false;
	level = -1;
}

int Target::getId() const {
	return this->id;
}

TYPE Target::getType() const {
	return this->type;
}

Position Target::getPosition() const {
	return this->position;
}

double Target::getVelocity() const {
	return this->velocity;
}

STATUS Target::getStatus() const {
	return this->status;
}

double Target::getThreatDistance() const {
	return this->threatDistance;
}

double Target::getAngleToOurUnit() const {
	return this->angleToOurUnit;
}

double Target::getJammingStrength1() const {
	return this->jammingStrength1;
}

double Target::getJammingStrength2() const {
	return this->jammingStrength2;
}

double Target::getHorizontalAngle() const {
	return this->horizontalAngle;
}

double Target::getVerticalAngle() const {
	return this->verticalAngle;
}

double Target::getSideAngle() {
	return this->sideAngle;
}
void Target::setSideAngle(double sideAngle) {
	this->sideAngle = sideAngle;
}

void Target::setId(int id) {
	this->id = id;
}

void Target::setType(TYPE type) {
	this->type = type;
}

void Target::setPosition(Position position) {
	this->position = position;
}

void Target::setVelocity(double velocity) {
	this->velocity = velocity;
}

void Target::setStatus(STATUS status) {
	this->status = status;
}

void Target::setThreatDistance(double threat_distance) {
	this->threatDistance = threat_distance;
}

void Target::setAngleToOurUnit(double angle_to_out_unit) {
	this->angleToOurUnit = angle_to_out_unit;
}

void Target::setJammingStrength1(double jamming_strength) {
	this->jammingStrength1 = jamming_strength;
}

void Target::setJammingStrength2(double jamming_strength) {
	this->jammingStrength2 = jamming_strength;
}

void Target::setHorizontalAngle(double horizontal_angle) {
	this->horizontalAngle = horizontal_angle;
}

void Target::setVerticalAngle(double vertical_angle) {
	this->verticalAngle = vertical_angle;
}

void Target::forward(double dTime) {
	this->position = this->position.forwardXYZ(this->horizontalAngle + 90, this->verticalAngle, this->velocity * dTime);// 0度指向的是右边,需要加90度
}

bool Target::getDeath() const {
	return this->markedDeath;
}

void Target::setDeath(bool death) {
	this->markedDeath = death;
}