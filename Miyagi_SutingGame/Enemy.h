#pragma once
#include "CharaBase.h"

struct T_MoveInformation
{
	int pattern;//���������Ȃ�
	T_Location destination;//�ړI�n
	int nextArrayNum;//���ɍs���z��
	int waitTimeFlameTime;//���W�p�^�[���̎���
	int attackType;//�U���p�^�[��
};

class Enemy :public CharaBase

{
protected:

private:

	int hp;
	int point;
	int shotNum;
	int current = 0;
	int waitcount = 0;
	int enemyimages = 0;

public:
	Enemy(T_Location location);
	virtual void  Update() override;
	virtual void Draw() override;
	virtual void Hit(int damege) override;
	bool HpCheck();
	int GetPoint();
	void Move();
	void inputCSV();

};

