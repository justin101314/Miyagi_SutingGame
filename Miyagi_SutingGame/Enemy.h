#pragma once
#include "CharaBase.h"

struct T_MoveInformation
{
	int pattern;//動く動かない
	T_Location destination;//目的地
	int nextArrayNum;//次に行く配列
	int waitTimeFlameTime;//座標パターンの時間
	int attackType;//攻撃パターン
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

