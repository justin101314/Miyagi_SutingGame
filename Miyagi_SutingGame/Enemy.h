#pragma once
#include "CharaBase.h"


class Enemy :public CharaBase

{
protected:

private:

	int hp;
	int point;
	int shotNum;

public:
	Enemy(T_Location location);
	virtual void  Update() override;
	virtual void Draw() override;
	virtual void Hit(int damege) override;
	bool HpCheck();
	int GetPoint();



};

