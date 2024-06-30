#pragma once
#define and &&
#define or ||
#pragma warning(disable: 4458)

#include "CoreMinimal.h"

enum TYPE {
	PLANE,
	TANK,
	ARMORED_CAR
};

enum STATUS
{
	FIGHT,
	STANDBY,
	RESTING
};

namespace utils {
	/*
	* 规范化角度,使之位于[0°,360°)之间
	* @param - angle 需要规范化的角度
	* @result 返回规范化后的角度[0,360)
	*/
	double normalizeAngle360(double angle);
	/*
	* 规范化角度,-90为z负方向,90为z正方向,超过90时,逐渐向z负方向进行
	* 例如:
	*     normalizeAngle180(91) 将返回89°,normalizeAngle180(-91) 将返回-89
	* @param - angle 需转化的角度,可以是任意值
	* @return 返回规范后角度(-90° - 90°)
	*/
	double normalizeAngle180(double angle);
	/*
	* 规范化弧度,使之位于[0,2PI)之间
	* @param - angle 需要规范化的弧度
	* @result 返回规范化后的弧度[0,2PI)
	*/
	double normalizeRadian2PI(double angle);
	/*
	* 规范化弧度,-PI为z负方向,PI为z正方向,超过PI时,逐渐向z负方向进行
	* 例如:
	*     normalizeRadianPI(PI+1) 将返回PI-1 ,normalizeRadianPI(-PI-1) 将返回-PI+1
	* @param - radian 需转化的弧度,可以是任意值
	* @return 返回规范后弧度(-PI - PI)
	*/
	double normalizeRadianPI(double angle);
	/*
	* 将弧度转化为角度
	* @param - Angle 需转化的角度,可以是任意值
	* @return 返回相应的弧度[0,360)
	*/
	double transformToAngle360(double radian);
	/*
	* 将角度转化为弧度
	* @param - radian 需转化的弧度,可以是任意值
	* @return 返回相应的弧度[0,2*PI)
	*/
	double transformToRadian2PI(double angle);
	/*
	* 将弧度转化为角度
	* @param - radian 需转化的弧度,可以是任意值
	* @return 返回相应的弧度[-90,90)
	*/
	double transformToAngle180(double radian);
	/*
	* 将角度转化为弧度
	* @param - Angle 需转化的角度,可以是任意值
	* @return 返回相应的弧度[-PI,PI]
	*/
	double transformToRadianPI(double Angle);

	float PerlinNoise2D(float X, float Y);
}