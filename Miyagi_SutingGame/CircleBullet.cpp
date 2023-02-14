#include "DxLib.h"
#include "CircleBullet.h"
#include "StraightBullets.h"
#define _USE_MATH_DEFINES
#include <math.h>


CircleBullet::CircleBullet(T_Location location,float speed, int degAngle)
	:BulletsBase(location, 5.f, 1, T_Location{ 0,0 })

{
	//エネミー弾画像
	enemybulletimages = LoadGraph("images/enemybullet.png");

	int deg = degAngle % 360;//360
	double rad = (M_PI / 180) * deg;//180
	float x = (abs(deg) == 90 || abs(deg) == 270) ? 0 : cos(rad);//90,270どちらかがTRUE(右側)かFALSE(左側)になったら場合によって選ばれる(参考演算子)
	float y = sin(rad);

	this->speed = T_Location{ (speed * x),(speed * y) };

}


void CircleBullet::Update() {

	T_Location newLocation = GetLocation();
	newLocation.y += speed.y;
	newLocation.x += speed.x;
	SetLocation(newLocation);

}


void CircleBullet::Draw() {

	//エネミー弾書き込み
	DrawRotaGraph(GetLocation().x, GetLocation().y,1,0, enemybulletimages,TRUE);
	// DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));

}

bool CircleBullet::isScreenOut() {

	bool ret = ((GetLocation().y + GetRadius()) <= 0);
	if (ret) {
		return ret;
	}

	ret = (SCREEN_HEIGHT <= GetLocation().y - GetRadius());
	if (ret) {
		return ret;
	}
	

	ret = (GetLocation().x + GetRadius() <= 0);
	if (ret) {
		return ret;
	}

	ret = SCREEN_WIDTH <= (GetLocation().y - GetRadius());

	return ret;

}