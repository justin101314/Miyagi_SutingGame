#include "DxLib.h"
#include "Enemy.h"
#include "StraightBullets.h"
#include "KeyManager.h"
#include "CircleBullet.h"


struct T_MoveInformation
{
	int pattern;//���������Ȃ�
	T_Location destination;
	int nextArrayNum;//���ɍs���z��
	int waitTimeFlameTime;//���W�p�^�[���̎���
	int attackType;//�U���p�^�[��
};

T_MoveInformation moveInfo[5] = {

	{0,640,   150,1, 0, 0},//�U�����Ȃ�
	{0,1200.4,150,2, 0, 2},//2�ōU��
	{1,  0,    0, 3,300,1},//1�ōU��
	{0,80.2,  150,4, 0, 2},//2�ōU��
	{1,  0,    0, 1,300,1},//1�ōU��
	//{1200.4,150,0,2, 0, 1},

};

T_Location locations[3] = {

	//�ړ���̍��W
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
int waitcount = 0;

Enemy::Enemy(T_Location location)
	:CharaBase(location, 20.f, T_Location{5,4,})//0.5
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

	//���ړ�
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

		//��ʊO�ɍs�����狅������
		if (bullets[bulletCount]->isScreenOut()) {


			DeleteBullet(bulletCount);
			bulletCount--;

		}

	}
	if (bulletCount < 1000 && bullets[bulletCount] == nullptr) {

		//�e��
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

	//�����W�����̍��W�ɑ��
	T_Location nextLocation = GetLocation();

	//x,y �������ꏊ�ɂ�����
	if ((nextLocation.y == locations[current].y) &&
		(nextLocation.x == locations[current].x))
	{

		//���̍��W�Ɏ擾
		current = next[current];
	}
	//�ړI�n�ɂ��Ȃ������Ƃ�
	else {
		//y�����ǂ蒅���Ă��Ȃ��Ƃ�
		if (nextLocation.y != locations[current].y)
		{

			//�����W���ړI�n���傫���Ƃ�
			if (nextLocation.y < locations[current].y)
			{
				//y�ɒl�𑝂₷
				nextLocation.y += speed.y;

				//���̍��W�����ړI�n���傫���ĖړI�n�������̍��W���傫��
				if ((GetLocation().y <= locations[current].y) &&
					(locations[current].y <= nextLocation.y))
				{

					//�ړI�n���щz�����ꍇ���̒n�_���㏑��
					nextLocation.y = locations[current].y;
				}

			}
			//�傫���Ƃ�
			else {
				//y�̒l�����炷
				nextLocation.y -= speed.y;

				//���̍��W�����ړI�n���傫���ĖړI�n�������̍��W���傫��
				if ((nextLocation.y <= locations[current].y) &&
					(locations[current].y <= GetLocation().y))

				{

					//�ړI�n���щz�����ꍇ���̒n�_���㏑��
					nextLocation.y = locations[current].y;
				}
			}

		}

		//x�ɂ��ǂ蒅���Ă��Ȃ��Ƃ�
		if (nextLocation.x != locations[current].x)
		{
			//�����W���ړI�n���傫���Ƃ�
			if (nextLocation.x < locations[current].x)
			{
				//x�ɒl�𑝂₷
				nextLocation.x += speed.x;
				if ((GetLocation().x <= locations[current].x) &&
					(locations[current].x <= nextLocation.x))
				{
					//�ړI�n���щz�����ꍇ���̒n�_���㏑��
					nextLocation.x = locations[current].x;
				}
			}
			//�傫���Ƃ�
			else {
				//x�̒l�����炷
				nextLocation.x -= speed.x;

				//���̍��W�����ړI�n���傫���ĖړI�n�������̍��W���傫��
				if ((nextLocation.x <= locations[current].x) &&
					(locations[current].y <= GetLocation().x))
				{
					//�ړI�n���щz�����ꍇ���̒n�_���㏑��
					nextLocation.x = locations[current].x;
						
				}
			}

		}

	}

	SetLocation(nextLocation);

}


