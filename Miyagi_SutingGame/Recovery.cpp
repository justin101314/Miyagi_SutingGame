#include "Recovery.h"
#include "DxLib.h"

void Recovery::Update() {



}

void  Recovery::Draw() {

	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 255, 0));

}

int Recovery::GetVolume() {

	return volume;

}