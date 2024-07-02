#include "TargetManager.h"
#include <random>
#include <cmath>
#include <iostream>
#include <algorithm>

OurUnit* TargetManager::getUnit() {
	return unit;
}
std::vector<Target> TargetManager::getTargetList() {
	return TargetList;
}

void TargetManager::setSideAngle() {
	Position position = unit->getPosition();
	double horizontalAngle = unit->getHorizontalAngle();
	unit->setSideAngle(setVerticalRotation(position, horizontalAngle));

	if (TargetList.empty())return;

	for (int i = 0; i < TargetList.size(); i++) {
		if (TargetList[i].getDeath())continue;
		if (TargetList[i].getType() == PLANE) continue;
		position = TargetList[i].getPosition();
		horizontalAngle = unit->getHorizontalAngle();
		TargetList[i].setSideAngle(setVerticalRotation(position, horizontalAngle));

	}

}


TargetManager::TargetManager() {}


void TargetManager::ready() {


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(100, 400);
	std::uniform_real_distribution<double> dist_velocity(20, 25);
	Position position(dist(gen), dist(gen));
	this->unit = new OurUnit(position, dist_velocity(gen)); // ��ʼ���ҷ���λ��
	std::uniform_real_distribution<double> dist_angle(0, 359);
	this->unit->setHorizontalAngle(dist_angle(gen));


	std::uniform_int_distribution<int> dist_type(1, 3);

	// ��ʼ���з���
	initialTarget(100);
	clusters.resize(K);
	// �����ʼ��K����������
	for (int i = 0; i < K; i++)
		for (double j : TargetList.at(rand() % TargetList.size()).weights)
			clusters[i].push_back(j);

	
	correctPosition();
	setRotation(); // �趨ÿ����λ����ֱ����
	setSideAngle(); // �趨ÿ����λ�Ĳ�߳���
}
bool cmp(const Target& a, const Target& b) {
	return a.getScore() > b.getScore();
}

void TargetManager::loop(double dTime) {
	setRotation(); // �趨ÿ����λ����ֱ����
	setSideAngle(); // �趨ÿ����λ�Ĳ�߳���
	executeLoop(dTime);// ִ��ÿ����λ��ѭ��(�н�,������Ե�ģ)

	checkTransgression(); // ���ÿ��Ԫ���Ƿ�Խ��,�з�Խ�����,�ҷ����������ýǶȺ�λ��

	runKMean(); // ִ��KMean�㷨Ϊÿ��Ԫ�ط���
	std::sort(TargetList.begin(), TargetList.end(), cmp); // ���ݷ�������

	if (unit->canKillTarget) {
		if (TargetList.empty()) return;
		for (int i = 0; i < TargetList.size(); i++) {
			if (TargetList[i].getDeath() or TargetList[i].markedKilled)continue;
			TargetList[i].markedKilled = true;
			break;
		}
		unit->canKillTarget = false;
	}
	// test();
}



void TargetManager::runKMean() {

	for (int iter = 0; iter < maxIters; ++iter) {

		std::vector<int> counts(K, 0); // ÿ�������ڵ�Ŀ�����
		std::vector<std::vector<double>> new_centroids(K, { 0,0,0,0,0,0,0 }); // ȡƽ��ֵ����¾����б�

		// Ϊÿ��Ŀ�������������Ĵ�(�洢����)
		for (auto it = TargetList.begin(); it < TargetList.end(); ++it) {
			double min_dist = 1000000; // ��С����
			int closest_centroid = -1; // �洢������������


			for (int j = 0; j < clusters.size(); ++j) {
				// ����ÿ����������

				double dist = it->getWeightDifference(clusters.at(j).data()); // ÿ����
				if (dist < min_dist) {
					// ѡ������С��,�������������Ϊ�����
					min_dist = dist;
					closest_centroid = j;
				}
			}

			it->centerIndex = closest_centroid; // ����ľ���

			counts.at(it->centerIndex)++; // ����,һ�����ڵ�Ŀ�����
			// һ���´�,�洢�������е�Ȩֵ��
			for (int m = 0; m < 7; m++) {
				new_centroids.at(it->centerIndex)[m] += it->weights[m];
			}

		}



		for (int i = 0; i < K; ++i) {
			if (counts[i] != 0) {
				for (int j = 0; j < 7; ++j) {
					new_centroids[i][j] /= counts[i]; // �´�ȡƽ��ֵ
				}
			}
			else {
				// ��һ������û������,�������һ��
				for (int i_ = 0; i_ < 7; i_++)
					new_centroids[i][i_] = TargetList.at(rand() % TargetList.size()).weights[i_];

			}
		}

		// �������
		bool converged = true;
		for (int i = 0; i < K; ++i) {
			if (Target::getWeightDifference(new_centroids[i].data(), clusters[i].data()) > 1e-4) {
				converged = false;
				break;
			}
		}

		clusters = new_centroids;
		if (converged) {
			break;
		}
	}

	double weights[15] = { 0 }; // ��¼ÿ�����ڵķ���
	for (int i = 0; i < clusters.size(); i++) {
		weights[i] = Target::getScore(clusters[i].data());
	}
	prioritization.clear(); // ��������б�

	// �������ȼ�����

	for (int i = 0; i < K; i++) {
		int tmp = 0;
		for (int j = 0; j < K; j++) {
			if (weights[tmp] < weights[j])
				tmp = j;
		}
		prioritization.push_back(tmp);
		weights[tmp] = -1;
	}

	for (int i = 0; i < TargetList.size(); i++) {
		int index = TargetList[i].centerIndex;
		int j;
		for (j = 0; j < prioritization.size(); j++) {
			if (prioritization[j] == index)break;
		}
		TargetList[i].setLevel(j);
	}

}

PRAGMA_DISABLE_OPTIMIZATION
double TargetManager::setVerticalRotation(Position position, double horizontal_rotation) {
	int x = position.x;
	int y = position.y;


	double z1 = utils::PerlinNoise2D(x,y); // ��ȡ��ǰ�Լ�����ĸ߶�(km)
	double z2 = 0;
	double delta__ = 0.01;

	Position tmp_p(x, y);
	tmp_p=tmp_p.forwardXY(horizontal_rotation, delta__);
	/*
	bool tmp = false;
	if (0 <= horizontal_rotation and horizontal_rotation <= 18.435 or horizontal_rotation >= 341.565 and horizontal_rotation <= 360) {
		z2 = utils::PerlinNoise2D(x + delta__, y);
	}
	else if (horizontal_rotation > 18.435 and horizontal_rotation <= 71.565) {
		tmp = true;
		z2 = utils::PerlinNoise2D(x + delta__, y + delta__);
	}
	else if (horizontal_rotation > 71.565 and horizontal_rotation <= 108.435) {
		z2 = utils::PerlinNoise2D(x, y + delta__);
	}
	else if (horizontal_rotation > 108.435 and horizontal_rotation <= 161.565) {
		tmp = true;
		z2 = utils::PerlinNoise2D(x - delta__, y+ delta__);
	}
	else if (horizontal_rotation > 161.565 and horizontal_rotation <= 198.435) {
		z2 = utils::PerlinNoise2D(x - delta__, y);
	}
	else if (horizontal_rotation > 198.435 and horizontal_rotation <= 251.565) {
		tmp = true;
		z2 = utils::PerlinNoise2D(x - delta__, y - delta__);

	}
	else if (horizontal_rotation > 251.565 and horizontal_rotation <= 288.435) {
		z2 = utils::PerlinNoise2D(x, y - delta__);
	}
	else {
		tmp = true;
		z2 = utils::PerlinNoise2D(x + delta__, y + delta__);
	}
	double deltaZ = z2 - z1;
	double deltaX = (tmp == true) ? delta__ * pow(2, 0.5) : delta__;
	
	
	return utils::transformToAngle180(atan2(deltaZ, deltaX));
	*/
	double deltaZ = utils::PerlinNoise2D(tmp_p.x,tmp_p.y)- z1;
	return utils::transformToAngle180(atan2(deltaZ*300/15, delta__));
}
PRAGMA_ENABLE_OPTIMIZATION

void TargetManager::setRotation() {

	Position position = unit->getPosition(); // ��ȡ�ҷ���λ������
	double horizontal_rotation = unit->getHorizontalAngle(); // ��ȡˮƽ����
	double vertical_angle = setVerticalRotation(position, horizontal_rotation + 90); // ע��,����0��Ϊ�Ҳ࿪ʼ,������Ҫ��90�ȸ���Ϊǰ��
	unit->setVerticaAngle(vertical_angle);
	if (TargetList.empty()) return;
	for (auto it = TargetList.begin(); it < TargetList.end(); it++) {
		if (it->getDeath()) continue;
		if (it->getType() == PLANE) continue; // �ɻ�����Ҫ�ı䴹ֱ����
		position = it->getPosition();
		horizontal_rotation = it->getHorizontalAngle();
		it->setVerticalAngle(setVerticalRotation(position, horizontal_rotation+90));
	}
}

void TargetManager::correctPosition() {
	Position position;
	position = unit->getPosition();
	int x = position.x;
	int y = position.y;
	position.z = map[x][y];
	unit->setPosition(position);
	if (TargetList.empty())return;
	for (auto it = TargetList.begin(); it < TargetList.end(); it++) {
		if (it->getDeath()) continue;
		if (it->getType() == PLANE)continue; // �ɻ�����ҪУ׼����
		position = it->getPosition();
		x = position.x;
		y = position.y;
		position.z = map[x][y];
		it->setPosition(position);
	}

}

void TargetManager::initialMap(double map[500][500]) {

	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 500; j++) {
			this->map[i][j] = map[i][j]/15;
		}
	}
}

void TargetManager::initialTarget(int quantity) {
	std::random_device rd;
	std::mt19937 gen(rd());
	TYPE type;
	Position position;
	double velocity;
	STATUS status;
	double threat_distance;
	double jamming1;
	double jamming2;

	std::uniform_int_distribution<int> dist_type(1, 3);
	std::uniform_real_distribution<double> dist_pos(50, 450);
	std::uniform_real_distribution<double> dist_velocity(0, 5);
	std::uniform_int_distribution<int> dist_status(1, 3);
	std::uniform_real_distribution<double> dist_threat(0, 100);
	std::uniform_real_distribution<double> dist_jamming(0, 100);
	std::uniform_real_distribution<double> dist_horizontal(0, 365);


	for (int i = 0; i < quantity; i++) {
		int type_index = dist_type(gen);
		int status_index = dist_status(gen);

		if (type_index == 1) {
			type = TYPE::PLANE;
		}
		else if (type_index == 2) {
			type = TYPE::TANK;
		}
		else {
			type = TYPE::ARMORED_CAR;
		}

		position.x = dist_pos(gen);
		position.y = dist_pos(gen);

		if (status_index == 1 or type == PLANE) {
			status = STATUS::FIGHT;
		}
		else if (status_index == 2) {
			status = STATUS::STANDBY;
		}
		else {
			status = STATUS::RESTING;
		}

		if (type == TYPE::PLANE) {
			int tmp = dist_pos(gen);
			position.z = tmp % 20 + 30;
		}

		velocity = (status == STATUS::FIGHT) ? dist_velocity(gen) : 0;
		velocity += (type == PLANE) ? 15 : 0;
		threat_distance = dist_threat(gen);
		jamming1 = dist_jamming(gen);
		jamming2 = dist_jamming(gen);
		Target tmp(i, type, position, velocity, status, threat_distance, jamming1, jamming2, this->unit);

		tmp.setHorizontalAngle(dist_horizontal(gen));
		if (type == TYPE::PLANE) {
			tmp.setVerticalAngle(0);
			tmp.setSideAngle(0);
		}
		TargetList.push_back(tmp);

	}
}

void TargetManager::checkTransgression() {
	// �ж�Խ��
	if (unit->getPosition().x >= 499 or unit->getPosition().y >= 499 or unit->getPosition().x <= 1 or unit->getPosition().y <= 1) {
		// ����ҷ�Խ����
		//std::cout << "�ҷ�Խ����!" << std::endl;
		Position position(0, 0, 0);
		position = unit->getPosition();
		int horizontal_angle[2] = {0,0};
		if (unit->getPosition().x >= 499) {

			position.x = 498;
			horizontal_angle[0] = 2;

		}
		else if (unit->getPosition().x <= 1) {
			position.x = 2;
			horizontal_angle[0] = 1;
		}
		if (unit->getPosition().y >= 499) {
			position.y = 498;
			horizontal_angle[1] = 2;
		}
		else if (unit->getPosition().y <= 1) {
			position.y = 2;
			horizontal_angle[1] = 1;
		}

		unit->setPosition(position); // δ�趨z��,z��Ϊ0
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dist(30, 150);
		double horizontal_angle_result;
		if (horizontal_angle[1] == 1) {
			horizontal_angle_result = dist(gen)-90;
		}
		else if (horizontal_angle[0] == 2) {
			horizontal_angle_result = dist(gen) + 90-90;
		}
		else if (horizontal_angle[1]==2) {
			horizontal_angle_result = dist(gen) + 180-90;
		}
		else if(horizontal_angle[0]==1) {
			horizontal_angle_result = dist(gen) + 270-90;
		}

		if (unit->getPosition().x > 400 and unit->getPosition().y > 400) {
			horizontal_angle_result = dist(gen)/2 + 180-90;
		}
		else if (unit->getPosition().x > 400 and unit->getPosition().y < 100) {
			horizontal_angle_result = dist(gen)/2 + 90-90;
		}
		else if (unit->getPosition().x < 100 and unit->getPosition().y>400) {
			horizontal_angle_result = dist(gen)/2 + 270-90;
		}
		else if (unit->getPosition().x < 100 and unit->getPosition().y < 100) {
			horizontal_angle_result = dist(gen)/2-90;
		}
		unit->setHorizontalAngle(horizontal_angle_result);

	}
	if (this->TargetList.empty()) return;
	for (auto it = TargetList.begin(); it < TargetList.end(); it++) {
		if (it->getDeath())continue;
		if ((*it).getPosition().x >= 499 or (*it).getPosition().y >= 499 or (*it).getPosition().x <= 1 or (*it).getPosition().y <= 1) {
			it->setDeath(true);

			std::cout << "����!" << it->getId() << std::endl;
		}
	}
}

void TargetManager::executeLoop(double dTime) {
	unit->loop(dTime);
	Position position = unit->getPosition();
	position.z = utils::PerlinNoise2D(position.x, position.y) * 300 / 15;
	unit->setPosition(position);
	if (this->TargetList.empty())return;
	for (auto it = TargetList.begin(); it < TargetList.end(); it++) {
		it->loop(dTime);
		if (it->getType() == PLANE) continue;
		position = it->getPosition();
		position.z = utils::PerlinNoise2D(position.x, position.y) * 300 / 15;
		it->setPosition(position);
	}
}


void TargetManager::test() {
	std::cout << unit->getPosition().x << unit->getPosition().y << unit->getPosition().z << "�ҷ�" << std::endl;
	for (auto it = TargetList.begin(); it < TargetList.end(); it++) {
		if (it->getVelocity() != 0) {
			std::cout << it->getId() << std::endl;
		}
	}

}