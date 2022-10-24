#include "DxLib.h"
#include "Player.h"
#include "StraightBullets.h"
#include "KeyManager.h"


Player::Player(T_Location location)
	:CharaBase(location, 10.f, T_Location{ 2,2 }), score(0), life(11)
{

	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++) {
		bullets[i] = nullptr;
	}

}

void Player::Update() {

	T_Location newLocation = GetLocation();
	newLocation.x += 1;
	SetLocation(newLocation);

	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++) {

		if (bullets[bulletCount] == nullptr) {

			break;
		}

		bullets[bulletCount]->Update();
	}


	if ((KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT) != 0)) {//���N���b�N�ň������

		if (bulletCount < 30 && bullets[bulletCount] == nullptr) {

			bullets[bulletCount] = new StraightBullets(GetLocation());

		}
	}
}

void Player::Draw() {

	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 255, 255));

	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++) {

		if (bullets[bulletCount] == nullptr) {

			break;
		}

		bullets[bulletCount]->Draw();
	}

}

void  Player::Hit() {


}

bool  Player::LifeCheck() {

	bool ret = (life <= 0);
	return ret;
}

int  Player::GetScore() {

	return score;

}