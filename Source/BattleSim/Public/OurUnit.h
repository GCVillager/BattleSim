#pragma once
#include "Position.h"
#include "CoreUtils.h"

/*
* �ҷ���λ��,ֻ��һ������
*/
class OurUnit
{
private:
	

	Position position;
	double velocity;
	double verticalAngle;
	double horizontalAngle;
	int target; // ����Ŀ��
	double timeCount; // ��ʱ��


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

