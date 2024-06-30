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
	* �淶���Ƕ�,ʹ֮λ��[0��,360��)֮��
	* @param - angle ��Ҫ�淶���ĽǶ�
	* @result ���ع淶����ĽǶ�[0,360)
	*/
	double normalizeAngle360(double angle);
	/*
	* �淶���Ƕ�,-90Ϊz������,90Ϊz������,����90ʱ,����z���������
	* ����:
	*     normalizeAngle180(91) ������89��,normalizeAngle180(-91) ������-89
	* @param - angle ��ת���ĽǶ�,����������ֵ
	* @return ���ع淶��Ƕ�(-90�� - 90��)
	*/
	double normalizeAngle180(double angle);
	/*
	* �淶������,ʹ֮λ��[0,2PI)֮��
	* @param - angle ��Ҫ�淶���Ļ���
	* @result ���ع淶����Ļ���[0,2PI)
	*/
	double normalizeRadian2PI(double angle);
	/*
	* �淶������,-PIΪz������,PIΪz������,����PIʱ,����z���������
	* ����:
	*     normalizeRadianPI(PI+1) ������PI-1 ,normalizeRadianPI(-PI-1) ������-PI+1
	* @param - radian ��ת���Ļ���,����������ֵ
	* @return ���ع淶�󻡶�(-PI - PI)
	*/
	double normalizeRadianPI(double angle);
	/*
	* ������ת��Ϊ�Ƕ�
	* @param - Angle ��ת���ĽǶ�,����������ֵ
	* @return ������Ӧ�Ļ���[0,360)
	*/
	double transformToAngle360(double radian);
	/*
	* ���Ƕ�ת��Ϊ����
	* @param - radian ��ת���Ļ���,����������ֵ
	* @return ������Ӧ�Ļ���[0,2*PI)
	*/
	double transformToRadian2PI(double angle);
	/*
	* ������ת��Ϊ�Ƕ�
	* @param - radian ��ת���Ļ���,����������ֵ
	* @return ������Ӧ�Ļ���[-90,90)
	*/
	double transformToAngle180(double radian);
	/*
	* ���Ƕ�ת��Ϊ����
	* @param - Angle ��ת���ĽǶ�,����������ֵ
	* @return ������Ӧ�Ļ���[-PI,PI]
	*/
	double transformToRadianPI(double Angle);

	float PerlinNoise2D(float X, float Y);
}