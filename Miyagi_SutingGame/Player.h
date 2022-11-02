#pragma once
#include "CharaBase.h"

class Player : public CharaBase
{
private:

	int score;
	int life;

	
public:

    Player(T_Location location);
	void Update() override;
	void Draw() override;
	void Hit(int damege) override;
	bool LifeCheck();
	int GetScore();
	

};

