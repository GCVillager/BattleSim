#pragma once

#include <cmath>

/*
* ��λ:km,��Χ 500*500*500
* x����������Ϊ�Ƕ�0��,z�Ḻ������Ϊ�Ƕ�0��
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
	* @param - rotation ƽ�淽λ(��, ���Զ�ת��Ϊ0 - 360)
	* @param - step ����(km)
	* @return һ���µ�Position(�����λ�ò�����ı�), ֻ��ƽ���˶�
	*/ 
	Position forwardXY(const double rotation,const double step) const;
	/*
	* @param - position �����������
	* @param - rotation ƽ�淽λ(��, ���Զ�ת��Ϊ0 - 360)
	* @param - step ����(km)
	* @return һ���µ�Position(�����λ�ò�����ı�), ֻ��ƽ���˶�
	*/
	static Position forwardXY(const Position position,const double rotation, const double step);
	/*
	* @param - horizontal_rotation ƽ�淽λ(��, ���Զ�ת��Ϊ0 - 360)
	* @param - vertical_rotation ��ֱ��λ(��, ���Զ�ת��Ϊ0 - 180)
	* @param - step ����(km)
	* @return һ���µ�Position(�����λ�ò�����ı�)
	*/
	Position forwardXYZ(const double horizontal_rotation,const double vertical_rotation,const double step) const;
	/*
	* @param - position �����������
	* @param - horizontal_rotation ƽ�淽λ(��, ���Զ�ת��Ϊ0 - 360)
	* @param - vertical_rotation ��ֱ��λ(��, ���Զ�ת��Ϊ-90 - 90)
	* @param - step ����(km)
	* @return һ���µ�Position(�����λ�ò�����ı�)
	*/
	static Position forwardXYZ(const Position position,const double horizontal_rotation, const double vertical_rotation, const double step);
	/**
	* ��������Ŀ�ĵؿ��������(��x,y)
	* @param - direction Ŀ������
	* @return �Ƕ�(��,0 - 360)
	*/
	double getHorizontalAngle(const Position direction) const;
	/**
	* ��������Ŀ�ĵؿ��������(��x,y)
	* @param - source ��ʼ����
	* @param - direction Ŀ������
	* @return �Ƕ�(��,0 - 360)
	*/
	static double getHorizontalAngle(const Position source, const Position direction);
	/**
	* ��������Ŀ�ĵؿ��������(��z)
	* @param - direction Ŀ������
	* @return �Ƕ�(��, 0 - 360)
	*/
	double getVerticalAngle(const Position direction) const;
	/**
	* ��������Ŀ�ĵؿ��������(��z)
	* @param - source ��ʼ����
	* @param - direction Ŀ������
	* @return �Ƕ�(��,0 - 180)
	*/
	static double getVerticalAngle(const Position source, const Position direction);
	/**
	* ��������Ŀ�ĵص�ƽ��ŷ�Ͼ���(x,y)
	* @param - direction Ŀ������
	* @return �Ƕ�(��,0 - 180)
	*/
	double distanceXY(const Position direction) const;
	/**
	* ��������Ŀ�ĵص�ƽ��ŷ�Ͼ���(x,y)
	* @param - source ��ʼ����
	* @param - direction Ŀ������
	* @return ƽ��ŷ�Ͼ������
	*/
	static double distanceXY(const Position source,const Position direction);
	/**
	* ��������Ŀ�ĵص�����ŷ�Ͼ���(x,y)
	* @param - direction Ŀ������
	* @return ����ŷ�Ͼ������
	*/
	double distanceXYZ(const Position direction) const;
	/**
	* ��������Ŀ�ĵص�����ŷ�Ͼ���(x,y)
	* @param - source ��ʼ����
	* @param - direction Ŀ������
	* @return ����ŷ�Ͼ������
	*/
	static double distanceXYZ(const Position source,const Position direction);
};
