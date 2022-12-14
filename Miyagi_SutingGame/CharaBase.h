#pragma once
#include "SphereCollider.h"
#include "BulletsBase.h"



class CharaBase : public SphereCollider
{

protected:
    
	T_Location speed;
	BulletsBase** bullets;
	int* image;



public:

	CharaBase(T_Location location, float radius, T_Location speed);

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Hit(int damege) = 0;
	BulletsBase** GetBullets();

	void DeleteBullet(int bulletNum);
};

