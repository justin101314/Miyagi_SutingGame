#include "DxLib.h"
#include "Recovery.h"


Recovery::Recovery(T_Location location)//回復//回復薬T_Location(位置)
	:ItemBase(location, 6.f, E_ITEM_TYPE:: Heal, T_Location{ 0,1 }), volume (2)
{

}
void Recovery::Update() {

	T_Location newLocation = GetLocation();
	newLocation.y += speed.y;
	SetLocation(newLocation);



}

void  Recovery::Draw() {

	//アイテム画像
	recoveryimages = LoadGraph("images/RecoveryAgents.png");
	DrawRotaGraph(GetLocation().x, GetLocation().y,1,0,recoveryimages,TRUE);
	//DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 255, 0));

}

int Recovery::GetVolume() {

	return volume;

}