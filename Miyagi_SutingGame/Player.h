#pragma once
#include "CharaBase.h"

class Player : public CharaBase
{
private:

	int score;
	int life;
	int playerimages = 0;
	
public:

    Player(T_Location location);
	void Update() override;
	void Draw() override;
	void Hit(int damege) override;
	void Hit( class ItemBase* item);
	bool LifeCheck();
	int GetScore();
	void AddScore(int score);

};

