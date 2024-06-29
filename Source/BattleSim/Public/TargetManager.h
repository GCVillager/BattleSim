#pragma once
#include "CoreUtils.h"
#include "Target.h"
#include "OurUnit.h"
#include <vector>

/*
* 用管理全局的类
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

	int K; // k 个聚类中心
	std::vector<std::vector<double>> clusters; // 存储聚类
	std::vector<int> prioritization; // 由高到低的优先级存储各个聚类中心
	double convergenceRadius; // 收敛半径
	int maxIters; // 最大迭代次数

	/*
	* 当被加载时执行
	*/
	void ready();

	/*
	* 每当循环时,执行
	*/
	void loop(double dTime);


	/*
	* 初始化地图,传入500*500的地图
	*/
	void initialMap(double map[500][500]);
	/*
	* 初始化敌方
	*/
	void initialTarget(int quantity);

	/*
	* 检查列表中是否越出地图,若越出,消除
	*/
	void checkTransgression();
	/*
	* 执行每个元素的loop函数
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

	// 测试方法
	void test();
};