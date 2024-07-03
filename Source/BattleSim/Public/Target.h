#pragma once
#include "CoreUtils.h"
#include "Position.h"
#include "OurUnit.h"


/*
* 目标类
* 属性:
*	- type:目标类型 可以分为PLANE,TANK,ARMORED_CAR 威胁等级
*	- position;位置
*	- velocity;速度 其中,仅FIGHT具有速度,当STANDBY和RESTING速度为0
*	- status;作战状态 可以分为 FIGHT,STANDBY,RESTING
*	- threatDistance ;威胁距离 (仅x,y)
*	- angleToOurUnit:距离我方方位 (0-360,水平)
*	- jammingStrength1:电磁干扰1
*	- jammingStrength2:电磁干扰2
*
*	- HorizontalAngle : 垂直角,向我方的唯一角度
*
*/
class Target
{
private:
	int id;
	TYPE type;
	Position position; // 位置
	double velocity; // km/s 0-5000 注意,速度是立体的,若是飞机,没有z轴的速度
	STATUS status; //  FIGHT>STANDBY>RESTING,
	double threatDistance; // 威胁距离,进入威胁距离后优先等级提高
	double angleToOurUnit; // 距离我方的方位,单位°, 0-360( 水平 ),由我方指向敌方
	double jammingStrength1; // 电磁干扰强度1 若我方在干扰强度内,优先级提高
	double jammingStrength2; // 电磁干扰强度2 若我方在干扰强度内,优先级提高

	double horizontalAngle; // 竖直的角度 -90 - 90, 由敌方发出
	double verticalAngle; // 敌方发出水平的角度

	double score; // 优先等级

	bool markedDeath; // 标记死亡

	double timeCount; // 内部计时系统,当发生更新后状态归0


	int level; // 第几聚类

	OurUnit* unit; // 我方单位

	double sideAngle; // 侧边角度,以玩家的右侧为基准,-90向下翻倒,,90向上翻倒,0°水平

	int timeDeath;

public:

	int centerIndex; // 对应的聚类中心索引
	bool markedKilled; // 标记被打击
	double weights[7]; // 七个权重数值

	void setLevel(int level);
	int getLevel();

	Target(int id, TYPE type, Position position, double velocity, STATUS status, double threatDistance, double jammingStrength1, double jammingStrength2, OurUnit* unit);
	/*
	* 每一次循环后都会执行的代码
	* @param - dTime 距离上一帧的时间
	*/
	void loop(double dTime);
	double getSideAngle(); // 获取侧边角度
	void setSideAngle(double sideAngle); // 设定侧边角度

	static double getWeightDifference(double weightA[7], double weightB[7]);
	/*
	* 获取目标类的id
	*/
	int getId() const;
	/*
	* 获取目标类的种类
	* @return Type 枚举变量,有PLANE,TANK,ARMORED_CAR三种类型
	*/
	TYPE getType() const;
	/*
	* 获取目标类的坐标
	* @return 坐标
	*/
	Position getPosition() const;
	/*
	* 获取目标类的速度
	* @return 返回目标类的速度(km/s),立体
	*/
	double getVelocity() const;
	/*
	* 获取敌方的状态
	* @return STATUS 有FIGHT,STANDBY,RESTING,三种,优先度分别是FIGHT>STANDBY>RESTING.
	*/
	STATUS getStatus() const;
	/*
	* 获取目标类的威胁距离
	* @return 返回敌方的威胁距离,在威胁距离内优先度将提高
	*/
	double getThreatDistance() const;
	/*
	* 获取我方面向敌方的角度,[45,135]与[225,315]优先级高
	* @return 我方面向敌方的角度,仅x,y.
	*/
	double getAngleToOurUnit() const;
	/*
	* ?
	*/
	double getJammingStrength1() const;
	/*
	* ?
	*/
	double getJammingStrength2() const;

	/*
	* 获取目标对象的水平角度,[0-360]
	* @return 水平角度
	*/
	double getHorizontalAngle() const;
	/*
	* 获取目标对象的竖直角度[-90 - 90]
	* @return 竖直角度
	*/
	double getVerticalAngle() const;

	/*
	* 设定目标类的id
	*/
	void setId(int id);
	/*
	* 设定目标类的种类
	* @param - type 枚举变量,有PLANE,TANK,ARMORED_CAR三种类型
	*/
	void setType(TYPE type);
	/*
	* 设定目标类的种类
	* @param - position 坐标,Position类型
	*/
	void setPosition(Position position);
	/*
	* 设置目标类的速度
	* @param - velocity 目标类的速度(km/s),立体
	*/
	void setVelocity(double velocity);
	/*
	* 设定敌方的状态
	* @param status 有FIGHT,STANDBY,RESTING,三种,优先度分别是FIGHT>STANDBY>RESTING.
	*/
	void setStatus(STATUS status);
	/*
	* 设定目标类的威胁距离
	* @param 敌方的威胁距离,在威胁距离内优先度将提高
	*/
	void setThreatDistance(double distance);
	/*
	* 设定我方面向敌方的角度,[45,135]与[225,315]优先级高
	* @param - angle 我方面向敌方的角度,仅x,y.
	*/
	void setAngleToOurUnit(double angle);
	/*
	* ?
	*/
	void setJammingStrength1(double strength);
	/*
	* ?
	*/
	void setJammingStrength2(double strength);

	/*
	* 设定目标对象的水平角度,[0-360)
	* @param - horizontal 水平角度
	*/
	void setHorizontalAngle(double horizontal);
	/*
	* 设定目标对象的竖直角度[-90 - 90]
	* @param - horizontal 竖直角度
	*/
	void setVerticalAngle(double horizontal);

	/*
	* 向前行进
	* @param - dTime 距离上一帧过去的时间
	*/
	void forward(double dTime);

	double getWeightDifference(double weight[7]) const;

	/*
	*  获取目标的优先级,-1表示未定义
	*/
	double getScore() const;

	/*
	* 获取目标优先级
	*/
	static double getScore(double weight[7]);

	/*
	* 获取玩家的死亡信息,若玩家死亡,返回true
	*/
	bool getDeath() const;

	void setDeath(bool death);
};

