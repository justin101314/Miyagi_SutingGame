#pragma once
#include "BulletsBase.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


class StraightBullets : public BulletsBase
 
{
private:
	int enemystraightB = 0;

public:

	StraightBullets(T_Location location ,T_Location speed);
	virtual void Update()override ;
	virtual	void Draw()override ;
	virtual bool isScreenOut() override;
};

