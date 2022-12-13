#include "CharaBase.h"

CharaBase::CharaBase(T_Location location ,float radius,T_Location speed) 
	:SphereCollider(location, radius),speed(speed),image (nullptr),bullets(nullptr)
{




}


BulletsBase** CharaBase::GetBullets()
{
	return bullets;
}


void CharaBase::DeleteBullet(int bulletNum) {


		delete bullets[bulletNum];
		bullets[bulletNum] = nullptr;

		//配列を前に詰める
		//for (int i = bulletCount; i < (30-1);i++) {//例外処理防ぐため

		//	if (bullets[i + 1] == nullptr) {//前を見てNULLと一致したら抜ける
		//		break;
		//	}
		//	bullets[i] = bullets[i + 1];//奥のものを手前の自分に入れる
		//	bullets[i + 1] = nullptr;
		//}
		//bulletCount--;

		//いじったとこ1
		for (int i = bulletNum + 1; i < 1000; i++) {//例外処理防ぐため //30

			if (bullets[i] == nullptr) {//NULLと一致したら抜ける
				break;
			}
			bullets[i - 1] = bullets[i];//奥のものを手前の自分に入れる
			bullets[i] = nullptr;
		}
		
}