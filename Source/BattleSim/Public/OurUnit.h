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
	double sideAngle; // ��߽Ƕ�,����ҵ��Ҳ�Ϊ��׼,-90���·���,,90���Ϸ���,0��ˮƽ


public:
	OurUnit(Position position, double velocity = -1);
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
	double getSideAngle(); // ��ȡ��߽Ƕ�
	void setSideAngle(double sideAngle); // �趨��߽Ƕ�

	void loop(double dTime);

};

