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

		//�z���O�ɋl�߂�
		//for (int i = bulletCount; i < (30-1);i++) {//��O�����h������

		//	if (bullets[i + 1] == nullptr) {//�O������NULL�ƈ�v�����甲����
		//		break;
		//	}
		//	bullets[i] = bullets[i + 1];//���̂��̂���O�̎����ɓ����
		//	bullets[i + 1] = nullptr;
		//}
		//bulletCount--;

		for (int i = bulletNum + 1; i < 30; i++) {//��O�����h������

			if (bullets[i] == nullptr) {//NULL�ƈ�v�����甲����
				break;
			}
			bullets[i - 1] = bullets[i];//���̂��̂���O�̎����ɓ����
			bullets[i] = nullptr;
		}
		
}