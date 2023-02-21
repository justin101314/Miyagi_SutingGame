#include "DxLib.h"
#include "StraightBullets.h"




StraightBullets::StraightBullets(T_Location location, T_Location speed)
	:BulletsBase(location, 50.f, 100, speed)
{

	enemystraightB = LoadGraph("images/enemystraight.png");


}


void StraightBullets::Update() {

	T_Location newLocation = GetLocation();
	newLocation.y -= speed.y;
	SetLocation(newLocation);

}


void StraightBullets::Draw() {

	DrawRotaGraph(GetLocation().x, GetLocation().y,1,0,  enemystraightB,TRUE);
	//DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));

}

bool StraightBullets::isScreenOut() {

	bool ret = ((GetLocation().y + GetRadius()) <= 0);
	if (ret) {
		return ret;
	}

	ret = (SCREEN_HEIGHT <= GetLocation().y - GetRadius());

	return ret;
}