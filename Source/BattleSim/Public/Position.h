#pragma once

#include <cmath>

/*
* 单位:km,范围 500*500*500
* x轴正方向作为角度0°,z轴负方向作为角度0°
*/
class Position
{
public:
	double x;
	double y;
	double z;


	Position(double x = 0, double y = 0, double z = 0);
	Position(const Position&);
	friend Position operator+(const Position&, const Position&);
	friend Position operator-(const Position&, const Position&);
	
	/*
	* @param - rotation 平面方位(°, 会自动转化为0 - 360)
	* @param - step 步数(km)
	* @return 一个新的Position(自身的位置并不会改变), 只有平面运动
	*/ 
	Position forwardXY(const double rotation,const double step) const;
	/*
	* @param - position 需操作的坐标
	* @param - rotation 平面方位(°, 会自动转化为0 - 360)
	* @param - step 步数(km)
	* @return 一个新的Position(自身的位置并不会改变), 只有平面运动
	*/
	static Position forwardXY(const Position position,const double rotation, const double step);
	/*
	* @param - horizontal_rotation 平面方位(°, 会自动转化为0 - 360)
	* @param - vertical_rotation 垂直方位(°, 会自动转化为0 - 180)
	* @param - step 步数(km)
	* @return 一个新的Position(自身的位置并不会改变)
	*/
	Position forwardXYZ(const double horizontal_rotation,const double vertical_rotation,const double step) const;
	/*
	* @param - position 需操作的坐标
	* @param - horizontal_rotation 平面方位(°, 会自动转化为0 - 360)
	* @param - vertical_rotation 垂直方位(°, 会自动转化为-90 - 90)
	* @param - step 步数(km)
	* @return 一个新的Position(自身的位置并不会改变)
	*/
	static Position forwardXYZ(const Position position,const double horizontal_rotation, const double vertical_rotation, const double step);
	/**
	* 从自身向目的地看向的坐标(仅x,y)
	* @param - direction 目标坐标
	* @return 角度(°,0 - 360)
	*/
	double getHorizontalAngle(const Position direction) const;
	/**
	* 从自身向目的地看向的坐标(仅x,y)
	* @param - source 起始坐标
	* @param - direction 目标坐标
	* @return 角度(°,0 - 360)
	*/
	static double getHorizontalAngle(const Position source, const Position direction);
	/**
	* 从自身向目的地看向的坐标(仅z)
	* @param - direction 目标坐标
	* @return 角度(°, 0 - 360)
	*/
	double getVerticalAngle(const Position direction) const;
	/**
	* 从自身向目的地看向的坐标(仅z)
	* @param - source 起始坐标
	* @param - direction 目标坐标
	* @return 角度(°,0 - 180)
	*/
	static double getVerticalAngle(const Position source, const Position direction);
	/**
	* 从自身向目的地的平面欧氏距离(x,y)
	* @param - direction 目标坐标
	* @return 角度(°,0 - 180)
	*/
	double distanceXY(const Position direction) const;
	/**
	* 从自身向目的地的平面欧氏距离(x,y)
	* @param - source 起始坐标
	* @param - direction 目标坐标
	* @return 平面欧氏距离距离
	*/
	static double distanceXY(const Position source,const Position direction);
	/**
	* 从自身向目的地的立体欧氏距离(x,y)
	* @param - direction 目标坐标
	* @return 立体欧氏距离距离
	*/
	double distanceXYZ(const Position direction) const;
	/**
	* 从自身向目的地的立体欧氏距离(x,y)
	* @param - source 起始坐标
	* @param - direction 目标坐标
	* @return 立体欧氏距离距离
	*/
	static double distanceXYZ(const Position source,const Position direction);
};
