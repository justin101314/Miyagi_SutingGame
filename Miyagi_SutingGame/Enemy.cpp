#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "KeyManager.h"
#include "CircleBullet.h"


Enemy::Enemy(T_Location location)
	:CharaBase(location, 20.f, T_Location{ 0,0.1 })//0.5
	, hp(10), point(10),shotNum(0)
{

	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++) {
		bullets[i] = nullptr;
	}

}
void  Enemy::Update() {

	//T_Location newLocation = GetLocation();
	//newLocation.y += speed.y;
	//SetLocation(newLocation);


	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++) {

		if (bullets[bulletCount] == nullptr) {

			break;
		}

		bullets[bulletCount]->Update();

		//‰æ–ÊŠO‚És‚Á‚½‚ç‹…‚ðÁ‚·
		if (bullets[bulletCount]->isScreenOut()) {


			DeleteBullet(bulletCount);
			bulletCount--;

		}

	}


		if (bulletCount < 30 && bullets[bulletCount] == nullptr) {

			//’e–‹
			bullets[bulletCount] =
				new CircleBullet(GetLocation(), 2.f, (20 * shotNum));

			shotNum++;


			//bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0, -2 });

		}
	

}
void Enemy::Draw() {

	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 255, 0));

	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++) {

		if (bullets[bulletCount] == nullptr) {

			break;
		}

		bullets[bulletCount]->Draw();
	}
}


void Enemy::Hit(int damege) {

	if (0 < damege) {

		hp -= damege;
		if (hp < 0) {
			hp = 0;
		}

	}


}
bool Enemy::HpCheck() {


	bool ret = (hp <= 0);
	return ret;


}
int Enemy::GetPoint() {

	return point;

}

