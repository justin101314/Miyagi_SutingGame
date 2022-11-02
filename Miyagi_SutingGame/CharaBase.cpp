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

		//”z—ñ‚ð‘O‚É‹l‚ß‚é
		//for (int i = bulletCount; i < (30-1);i++) {//—áŠOˆ—–h‚®‚½‚ß

		//	if (bullets[i + 1] == nullptr) {//‘O‚ðŒ©‚ÄNULL‚Æˆê’v‚µ‚½‚ç”²‚¯‚é
		//		break;
		//	}
		//	bullets[i] = bullets[i + 1];//‰œ‚Ì‚à‚Ì‚ðŽè‘O‚ÌŽ©•ª‚É“ü‚ê‚é
		//	bullets[i + 1] = nullptr;
		//}
		//bulletCount--;

		for (int i = bulletNum + 1; i < 30; i++) {//—áŠOˆ—–h‚®‚½‚ß

			if (bullets[i] == nullptr) {//NULL‚Æˆê’v‚µ‚½‚ç”²‚¯‚é
				break;
			}
			bullets[i - 1] = bullets[i];//‰œ‚Ì‚à‚Ì‚ðŽè‘O‚ÌŽ©•ª‚É“ü‚ê‚é
			bullets[i] = nullptr;
		}
		
}