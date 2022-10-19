#pragma once
#include "BulletsBase.h"
class StraightBullets : public BulletsBase
 
{


public:


	StraightBullets(T_Location location);
	virtual void Update()override ;
	virtual	void Draw()override ;
};

