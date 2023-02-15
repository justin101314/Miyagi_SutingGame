#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "KeyManager.h"
#include "CircleBullet.h"
#include "CharaBase.h"

T_MoveInformation moveInfo[5] = {

	

};


//int next[3] = {
//
//	1,
//	2,
//	1
//
//};


//CSV
void Enemy::inputCSV() {

	FILE* fp; //FILE型構造体
	errno_t error; //fopen_sのエラーの確認
	error = fopen_s(&fp, "../CSVEnemy/CSVEnemy.csv", "r");

	if (errno != 0) {

		//エラー発生
		return;
	}
	else {
		//ファイルを開いた
		char line [100];
		for (int i = 0; fgets(line, 100, fp) != NULL; i++) {
			//while (fgets(line, 100, fp) != NULL) 

			sscanf_s(line, "%d,%f,%f,%d,%d,%d",
				&moveInfo[i].pattern,//動く動かない//A
				&moveInfo[i].destination.x,//目的地.x//B
				&moveInfo[i].destination.y,//目的地.y//C
				&moveInfo[i].nextArrayNum,//次に行く配列//D
				&moveInfo[i].waitTimeFlameTime,//座標パターンの時間//E
				&moveInfo[i].attackType//攻撃パターン//F
				);

		}

		return;
	}


	fclose(fp); //ファイルを閉じる

}



Enemy::Enemy(T_Location location)
	:CharaBase(location, 50.f, T_Location{ 3.5,4, })//→T_Location//球の大きさ//0.5 //上空からの敵球の速さ
	, hp(10), point(10), shotNum(0)
{
	inputCSV();


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
	//////動きのパターンなど//////
	if (moveInfo[current].attackType != 0) {

		if (bulletCount < 1000 && bullets[bulletCount] == nullptr) {

			//下攻撃
			if (moveInfo[current].attackType == 1) {

				bullets[bulletCount] = new StraightBullets
				(GetLocation(), T_Location{ 0,-2 });

			}

			else if (moveInfo[current].attackType == 2) {

				shotNum++;
				bullets[bulletCount] = new CircleBullet
				(GetLocation(), 6.f, (2.f * shotNum));//球の速さ初期時(2.f)//手裏剣型75.f
			}

			/*else if(moveInfo[current].attackType == 1) {

				bullets[bulletCount] = new StraightBullets
				(GetLocation(), T_Location{ 0,45 });

			}*/


			//弾幕を作ろう
			//bullets[bulletCount] =
			//	new CircleBullet(GetLocation(), 2.f, (75 * shotNum));//2.f,20

			//shotNum++;


			//bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0, -2 });

		}
	}


}
void Enemy::Draw() {

	enemyimages = LoadGraph("images/Jet2.png");

	DrawRotaGraph(GetLocation().x, GetLocation().y,2,0, enemyimages, TRUE);

	//DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 255, 0));

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


