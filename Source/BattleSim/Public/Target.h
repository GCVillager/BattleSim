#pragma once
#include "CoreUtils.h"
#include "Position.h"
#include "OurUnit.h"


/*
* Ŀ����
* ����:
*	- type:Ŀ������ ���Է�ΪPLANE,TANK,ARMORED_CAR ��в�ȼ�
*	- position;λ��
*	- velocity;�ٶ� ����,��FIGHT�����ٶ�,��STANDBY��RESTING�ٶ�Ϊ0
*	- status;��ս״̬ ���Է�Ϊ FIGHT,STANDBY,RESTING
*	- threatDistance ;��в���� (��x,y)
*	- angleToOurUnit:�����ҷ���λ (0-360,ˮƽ)
*	- jammingStrength1:��Ÿ���1
*	- jammingStrength2:��Ÿ���2
*
*	- HorizontalAngle : ��ֱ��,���ҷ���Ψһ�Ƕ�
*
*/
class Target
{
private:
	int id;
	TYPE type;
	Position position; // λ��
	double velocity; // km/s 0-5000 ע��,�ٶ��������,���Ƿɻ�,û��z����ٶ�
	STATUS status; //  FIGHT>STANDBY>RESTING,
	double threatDistance; // ��в����,������в��������ȵȼ����
	double angleToOurUnit; // �����ҷ��ķ�λ,��λ��, 0-360( ˮƽ ),���ҷ�ָ��з�
	double jammingStrength1; // ��Ÿ���ǿ��1 ���ҷ��ڸ���ǿ����,���ȼ����
	double jammingStrength2; // ��Ÿ���ǿ��2 ���ҷ��ڸ���ǿ����,���ȼ����

	double horizontalAngle; // ��ֱ�ĽǶ� -90 - 90, �ɵз�����
	double verticalAngle; // �з�����ˮƽ�ĽǶ�

	double score; // ���ȵȼ�

	bool markedDeath; // �������

	double timeCount; // �ڲ���ʱϵͳ,���������º�״̬��0


	int level; // �ڼ�����

	OurUnit* unit; // �ҷ���λ

	double sideAngle; // ��߽Ƕ�,����ҵ��Ҳ�Ϊ��׼,-90���·���,,90���Ϸ���,0��ˮƽ

	int timeDeath;

public:

	int centerIndex; // ��Ӧ�ľ�����������
	bool markedKilled; // ��Ǳ����
	double weights[7]; // �߸�Ȩ����ֵ

	void setLevel(int level);
	int getLevel();

	Target(int id, TYPE type, Position position, double velocity, STATUS status, double threatDistance, double jammingStrength1, double jammingStrength2, OurUnit* unit);
	/*
	* ÿһ��ѭ���󶼻�ִ�еĴ���
	* @param - dTime ������һ֡��ʱ��
	*/
	void loop(double dTime);
	double getSideAngle(); // ��ȡ��߽Ƕ�
	void setSideAngle(double sideAngle); // �趨��߽Ƕ�

	static double getWeightDifference(double weightA[7], double weightB[7]);
	/*
	* ��ȡĿ�����id
	*/
	int getId() const;
	/*
	* ��ȡĿ���������
	* @return Type ö�ٱ���,��PLANE,TANK,ARMORED_CAR��������
	*/
	TYPE getType() const;
	/*
	* ��ȡĿ���������
	* @return ����
	*/
	Position getPosition() const;
	/*
	* ��ȡĿ������ٶ�
	* @return ����Ŀ������ٶ�(km/s),����
	*/
	double getVelocity() const;
	/*
	* ��ȡ�з���״̬
	* @return STATUS ��FIGHT,STANDBY,RESTING,����,���ȶȷֱ���FIGHT>STANDBY>RESTING.
	*/
	STATUS getStatus() const;
	/*
	* ��ȡĿ�������в����
	* @return ���صз�����в����,����в���������ȶȽ����
	*/
	double getThreatDistance() const;
	/*
	* ��ȡ�ҷ�����з��ĽǶ�,[45,135]��[225,315]���ȼ���
	* @return �ҷ�����з��ĽǶ�,��x,y.
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
	* ��ȡĿ������ˮƽ�Ƕ�,[0-360]
	* @return ˮƽ�Ƕ�
	*/
	double getHorizontalAngle() const;
	/*
	* ��ȡĿ��������ֱ�Ƕ�[-90 - 90]
	* @return ��ֱ�Ƕ�
	*/
	double getVerticalAngle() const;

	/*
	* �趨Ŀ�����id
	*/
	void setId(int id);
	/*
	* �趨Ŀ���������
	* @param - type ö�ٱ���,��PLANE,TANK,ARMORED_CAR��������
	*/
	void setType(TYPE type);
	/*
	* �趨Ŀ���������
	* @param - position ����,Position����
	*/
	void setPosition(Position position);
	/*
	* ����Ŀ������ٶ�
	* @param - velocity Ŀ������ٶ�(km/s),����
	*/
	void setVelocity(double velocity);
	/*
	* �趨�з���״̬
	* @param status ��FIGHT,STANDBY,RESTING,����,���ȶȷֱ���FIGHT>STANDBY>RESTING.
	*/
	void setStatus(STATUS status);
	/*
	* �趨Ŀ�������в����
	* @param �з�����в����,����в���������ȶȽ����
	*/
	void setThreatDistance(double distance);
	/*
	* �趨�ҷ�����з��ĽǶ�,[45,135]��[225,315]���ȼ���
	* @param - angle �ҷ�����з��ĽǶ�,��x,y.
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
	* �趨Ŀ������ˮƽ�Ƕ�,[0-360)
	* @param - horizontal ˮƽ�Ƕ�
	*/
	void setHorizontalAngle(double horizontal);
	/*
	* �趨Ŀ��������ֱ�Ƕ�[-90 - 90]
	* @param - horizontal ��ֱ�Ƕ�
	*/
	void setVerticalAngle(double horizontal);

	/*
	* ��ǰ�н�
	* @param - dTime ������һ֡��ȥ��ʱ��
	*/
	void forward(double dTime);

	double getWeightDifference(double weight[7]) const;

	/*
	*  ��ȡĿ������ȼ�,-1��ʾδ����
	*/
	double getScore() const;

	/*
	* ��ȡĿ�����ȼ�
	*/
	static double getScore(double weight[7]);

	/*
	* ��ȡ��ҵ�������Ϣ,���������,����true
	*/
	bool getDeath() const;

	void setDeath(bool death);
};

