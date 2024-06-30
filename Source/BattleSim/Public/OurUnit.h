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
	double sideAngle; // 侧边角度,以玩家的右侧为基准,-90向下翻倒,,90向上翻倒,0°水平


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
	double getSideAngle(); // 获取侧边角度
	void setSideAngle(double sideAngle); // 设定侧边角度

	void loop(double dTime);

};

