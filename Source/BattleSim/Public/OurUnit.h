#pragma once
#include "Position.h"
#include "CoreUtils.h"

/*
* 我方单位类,只有一个对象
*/
class OurUnit
{
private:
	

	Position position;
	double velocity;
	double verticalAngle;
	double horizontalAngle;
	int target; // 击打目标
	double timeCount; // 计时器


public:
	OurUnit(Position position,double velocity = -1);
	bool canKillTarget;

	Position getPosition();
	double getVelocity();
	double getVerticalAngle();
	double getHorizontalAngle();
	int getTarget();

	void setPosition(Position position);
	void setVelocity(double velocity);
	void setVerticaAngle(double vertical_angle);
	void setHorizontalAngle(double horizontal_angle);
	void setTarget(int id);

	void loop(double dTime);

};

