#pragma once
#include "common.h"


class SphereCollider
{
private:

	T_Location location; //中心座標
	float radius;//半径

public:
	SphereCollider(T_Location location, float radius);


public:

	bool HitSphere(const SphereCollider* collider)const;
	T_Location GetLocation ()const; //中心座標の取得
	void SetLocation(T_Location location);//中心座標の設定
	float Getradius()const; //半径の取得




};

