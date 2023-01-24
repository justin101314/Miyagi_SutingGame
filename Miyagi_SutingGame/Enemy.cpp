#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "KeyManager.h"
#include "CircleBullet.h"


struct T_MoveInformation
{
	int pattern;//動く動かない
	T_Location destination;
	int nextArrayNum;//次に行く配列
	int waitTimeFlameTime;//座標パターンの時間
	int attackType;//攻撃パターン
};

T_MoveInformation moveInfo[5] = {

	{0,640,   150,1, 0, 0},//攻撃しない
	{0,1200.4,150,2, 0, 2},//2で攻撃
	{1,  0,    0, 3,150,1},//1で攻撃
	{0,80.2,  150,4, 0, 2},//2で攻撃
	{1,  0,    0, 1,150,1},//1で攻撃
	//{1200.4,150,0,2, 0, 1},

};

//T_Location moveInfo[3] = {
//
//	//移動先の座標
//	{640,150},
//	{1200.4,150},
//	{80.2,150},
//
//};

int next[3] = {

	1,
	2,
	1

};

int current = 0;
int waitcount = 0;

Enemy::Enemy(T_Location location)
	:CharaBase(location, 20.f, T_Location{ 5,4, })//0.5 
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

	switch (moveInfo[current].pattern)
	{

	case 0:
		Move();
		break;
	case 1:
		waitcount++;
		if (moveInfo[current].waitTimeFlameTime <= waitcount)
		{
			waitcount = 0;
			current = moveInfo[current].nextArrayNum;
		}
		break;

	default:
		break;
	}

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
	if (moveInfo[current].attackType != 0) {

		if (bulletCount < 1000 && bullets[bulletCount] == nullptr) {

			if (moveInfo[current].attackType == 1) {

				bullets[bulletCount] = new StraightBullets
				(GetLocation(), T_Location{ 0,-2 });

			}

			else if (moveInfo[current].attackType == 2) {

				shotNum++;
				bullets[bulletCount] = new CircleBullet
				(GetLocation(), 2.f, (75 * shotNum));
			}





			//弾幕を作ろう
			//bullets[bulletCount] =
			//	new CircleBullet(GetLocation(), 2.f, (75 * shotNum));//2.f,20

			//shotNum++;


			//bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0, -2 });

		}
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
	if ((nextLocation.y == moveInfo[current].destination.y) &&
		(nextLocation.x == moveInfo[current].destination.x))
	{

		//次の座標に取得
		current = moveInfo[current].nextArrayNum;
		return;
	}
	//目的地にいなかったとき
	else {
		//yがたどり着いていないとき
		if (nextLocation.y != moveInfo[current].destination.y)
		{

			//現座標より目的地が大きいとき
			if (nextLocation.y < moveInfo[current].destination.y)
			{
				//yに値を増やす
				nextLocation.y += speed.y;

				//今の座標よりも目的地が大きくて目的地よりも次の座標が大きい
				if ((GetLocation().y <= moveInfo[current].destination.y) &&
					(moveInfo[current].destination.y <= nextLocation.y))
				{

					//目的地を飛び越えた場合次の地点を上書き
					nextLocation.y = moveInfo[current].destination.y;
				}

			}
			//大きいとき
			else {
				//yの値を減らす
				nextLocation.y -= speed.y;

				//今の座標よりも目的地が大きくて目的地よりも次の座標が大きい
				if ((nextLocation.y <= moveInfo[current].destination.y) &&
					(moveInfo[current].destination.y <= GetLocation().y))

				{

					//目的地を飛び越えた場合次の地点を上書き
					nextLocation.y = moveInfo[current].destination.y;
				}
			}

		}

		//xにたどり着いていないとき
		if (nextLocation.x != moveInfo[current].destination.x)
		{
			//現座標より目的地が大きいとき
			if (nextLocation.x < moveInfo[current].destination.x)
			{
				//xに値を増やす
				nextLocation.x += speed.x;
				if ((GetLocation().x <= moveInfo[current].destination.x) &&
					(moveInfo[current].destination.x <= nextLocation.x))
				{
					//目的地を飛び越えた場合次の地点を上書き
					nextLocation.x = moveInfo[current].destination.x;
				}
			}
			//大きいとき
			else {
				//xの値を減らす
				nextLocation.x -= speed.x;

				//今の座標よりも目的地が大きくて目的地よりも次の座標が大きい
				if ((nextLocation.x <= moveInfo[current].destination.x) &&
					(moveInfo[current].destination.y <= GetLocation().x))
				{
					//目的地を飛び越えた場合次の地点を上書き
					nextLocation.x = moveInfo[current].destination.x;

				}
			}

		}

	}

	SetLocation(nextLocation);

}


