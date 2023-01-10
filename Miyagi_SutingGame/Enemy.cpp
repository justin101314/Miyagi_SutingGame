#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "KeyManager.h"
#include "CircleBullet.h"


struct MoveInformation
{
	T_Location targetLocation;
	int pattern;//動く動かない
	int next;//次に行く配列
	int waitTimeFlame;//座標パターンの時間
	int attackpatern;//攻撃パターン
};

MoveInformation moveInfo[10] = {

	{640,   150,0,1, 0, 0},
	{1200.4,150,0,2, 0, 0},
	{  0,    0, 1,3,180,1},
	{80.2,  150,0,4, 0, 2},
	{  0,    0, 1,5, 180,1},
	{1200.4,150,0,2, 0, 1},
};

T_Location locations[3] = {

	//移動先の座標
	{640,150},
	{1200.4,150},
	{80.2,150},

};

int next[3] = {

	1,
	2,
	1

};

int current = 0;

Enemy::Enemy(T_Location location)
	:CharaBase(location, 20.f, T_Location{ 8,1, })//0.5
	, hp(10), point(10), shotNum(0)
{

	//30
	bullets = new BulletsBase * [1000];
	for (int i = 0; i < 1000; i++) {
		bullets[i] = nullptr;
	}

}
void  Enemy::Update() {

	//T_Location newLocation = GetLocation();
	//newLocation.y += speed.y;
	//SetLocation(newLocation);



	Move();

		//下移動
	/*T_Location newLocation = GetLocation();
	if (GetLocation().y != locations[1].y)
	{
		newLocation.y += speed.y;
		SetLocation(newLocation);


	}*/

	/*if (GetLocation().x == locations[2].x) {

		newLocation.x -= speed.x;
		SetLocation(newLocation);

	}*/

	int bulletCount;
	for (bulletCount = 0; bulletCount < 1000; bulletCount++) {

		if (bullets[bulletCount] == nullptr) {

			break;
		}

		bullets[bulletCount]->Update();

		//画面外に行ったら球を消す
		if (bullets[bulletCount]->isScreenOut()) {


			DeleteBullet(bulletCount);
			bulletCount--;

		}

	}
	if (bulletCount < 1000 && bullets[bulletCount] == nullptr) {

		//弾幕
		bullets[bulletCount] =
			new CircleBullet(GetLocation(), 2.f, (75 * shotNum));//2.f,20

		shotNum++;


		//bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0, -2 });

	}


}
void Enemy::Draw() {

	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 255, 0));

	int bulletCount;
	for (bulletCount = 0; bulletCount < 1000; bulletCount++) {

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

void Enemy::Move() {

	//現座標を次の座標に代入
	T_Location nextLocation = GetLocation();

	//x,y が同じ場所にいたら
	if ((nextLocation.y == locations[current].y) &&
		(nextLocation.x == locations[current].x))
	{

		//次の座標に取得
		current = next[current];
	}
	//目的地にいなかったとき
	else {
		//yがたどり着いていないとき
		if (nextLocation.y != locations[current].y)
		{

			//現座標より目的地が大きいとき
			if (nextLocation.y < locations[current].y)
			{
				//yに値を増やす
				nextLocation.y += speed.y;

				//今の座標よりも目的地が大きくて目的地よりも次の座標が大きい
				if ((GetLocation().y <= locations[current].y) &&
					(locations[current].y <= nextLocation.y))
				{

					//目的地を飛び越えた場合次の地点を上書き
					nextLocation.y = locations[current].y;
				}

			}
			//大きいとき
			else {
				//yの値を減らす
				nextLocation.y -= speed.y;

				//今の座標よりも目的地が大きくて目的地よりも次の座標が大きい
				if ((nextLocation.y <= locations[current].y) &&
					(locations[current].y <= GetLocation().y))

				{

					//目的地を飛び越えた場合次の地点を上書き
					nextLocation.y = locations[current].y;
				}
			}

		}

		//xにたどり着いていないとき
		if (nextLocation.x != locations[current].x)
		{
			//現座標より目的地が大きいとき
			if (nextLocation.x < locations[current].x)
			{
				//xに値を増やす
				nextLocation.x += speed.x;
				if ((GetLocation().x <= locations[current].x) &&
					(locations[current].x <= nextLocation.x))
				{
					//目的地を飛び越えた場合次の地点を上書き
					nextLocation.x = locations[current].x;
				}
			}
			//大きいとき
			else {
				//xの値を減らす
				nextLocation.x -= speed.x;

				//今の座標よりも目的地が大きくて目的地よりも次の座標が大きい
				if ((nextLocation.x <= locations[current].x) &&
					(locations[current].y <= GetLocation().x))
				{
					//目的地を飛び越えた場合次の地点を上書き
					nextLocation.x = locations[current].x;
						
				}
			}

		}

	}

	SetLocation(nextLocation);

}


