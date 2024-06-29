#pragma once
#include "CoreUtils.h"
#include "Target.h"
#include "OurUnit.h"
#include <vector>

/*
* �ù���ȫ�ֵ���
*/
class TargetManager
{
private:
	double map[500][500];
	OurUnit* unit;
	std::vector<Target> TargetList;

	
public:
	TargetManager();
	OurUnit* getUnit();
	std::vector<Target> getTargetList();

	int K; // k ����������
	std::vector<std::vector<double>> clusters; // �洢����
	std::vector<int> prioritization; // �ɸߵ��͵����ȼ��洢������������
	double convergenceRadius; // �����뾶
	int maxIters; // ����������

	/*
	* ��������ʱִ��
	*/
	void ready();

	/*
	* ÿ��ѭ��ʱ,ִ��
	*/
	void loop(double dTime);


	/*
	* ��ʼ����ͼ,����500*500�ĵ�ͼ
	*/
	void initialMap(double map[500][500]);
	/*
	* ��ʼ���з�
	*/
	void initialTarget(int quantity);

	/*
	* ����б����Ƿ�Խ����ͼ,��Խ��,����
	*/
	void checkTransgression();
	/*
	* ִ��ÿ��Ԫ�ص�loop����
	*/
	void executeLoop(double dTime);

	~TargetManager()
	{
		delete unit;
	}

	void setRotation();
	double setVerticalRotation(Position position, double horizontal_angle);
	void correctPosition();

	void runKMean();

	// ���Է���
	void test();
};