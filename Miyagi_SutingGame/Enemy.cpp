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

	FILE* fp; //FILE�^�\����
	errno_t error; //fopen_s�̃G���[�̊m�F
	error = fopen_s(&fp, "../CSVEnemy/CSVEnemy.csv", "r");

	if (errno != 0) {

		//�G���[����
		return;
	}
	else {
		//�t�@�C�����J����
		char line [100];
		for (int i = 0; fgets(line, 100, fp) != NULL; i++) {
			//while (fgets(line, 100, fp) != NULL) 

			sscanf_s(line, "%d,%f,%f,%d,%d,%d",
				&moveInfo[i].pattern,//���������Ȃ�//A
				&moveInfo[i].destination.x,//�ړI�n.x//B
				&moveInfo[i].destination.y,//�ړI�n.y//C
				&moveInfo[i].nextArrayNum,//���ɍs���z��//D
				&moveInfo[i].waitTimeFlameTime,//���W�p�^�[���̎���//E
				&moveInfo[i].attackType//�U���p�^�[��//F
				);

		}

		return;
	}


	fclose(fp); //�t�@�C�������

}



Enemy::Enemy(T_Location location)
	:CharaBase(location, 50.f, T_Location{ 3.5,4, })//��T_Location//���̑傫��//0.5 //��󂩂�̓G���̑���
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
	//////�����̃p�^�[���Ȃ�//////
	if (moveInfo[current].attackType != 0) {

		if (bulletCount < 1000 && bullets[bulletCount] == nullptr) {

			//���U��
			if (moveInfo[current].attackType == 1) {

				bullets[bulletCount] = new StraightBullets
				(GetLocation(), T_Location{ 0,-2 });

			}

			else if (moveInfo[current].attackType == 2) {

				shotNum++;
				bullets[bulletCount] = new CircleBullet
				(GetLocation(), 6.f, (2.f * shotNum));//���̑���������(2.f)//�藠���^75.f
			}

			/*else if(moveInfo[current].attackType == 1) {

				bullets[bulletCount] = new StraightBullets
				(GetLocation(), T_Location{ 0,45 });

			}*/


			//�e������낤
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

	//�����W�����̍��W�ɑ��
	T_Location nextLocation = GetLocation();

	//x,y �������ꏊ�ɂ�����
	if ((nextLocation.y == moveInfo[current].destination.y) &&
		(nextLocation.x == moveInfo[current].destination.x))
	{

		//���̍��W�Ɏ擾
		current = moveInfo[current].nextArrayNum;
		return;
	}
	//�ړI�n�ɂ��Ȃ������Ƃ�
	else {
		//y�����ǂ蒅���Ă��Ȃ��Ƃ�
		if (nextLocation.y != moveInfo[current].destination.y)
		{

			//�����W���ړI�n���傫���Ƃ�
			if (nextLocation.y < moveInfo[current].destination.y)
			{
				//y�ɒl�𑝂₷
				nextLocation.y += speed.y;

				//���̍��W�����ړI�n���傫���ĖړI�n�������̍��W���傫��
				if ((GetLocation().y <= moveInfo[current].destination.y) &&
					(moveInfo[current].destination.y <= nextLocation.y))
				{

					//�ړI�n���щz�����ꍇ���̒n�_���㏑��
					nextLocation.y = moveInfo[current].destination.y;
				}

			}
			//�傫���Ƃ�
			else {
				//y�̒l�����炷
				nextLocation.y -= speed.y;

				//���̍��W�����ړI�n���傫���ĖړI�n�������̍��W���傫��
				if ((nextLocation.y <= moveInfo[current].destination.y) &&
					(moveInfo[current].destination.y <= GetLocation().y))

				{

					//�ړI�n���щz�����ꍇ���̒n�_���㏑��
					nextLocation.y = moveInfo[current].destination.y;
				}
			}

		}

		//x�ɂ��ǂ蒅���Ă��Ȃ��Ƃ�
		if (nextLocation.x != moveInfo[current].destination.x)
		{
			//�����W���ړI�n���傫���Ƃ�
			if (nextLocation.x < moveInfo[current].destination.x)
			{
				//x�ɒl�𑝂₷
				nextLocation.x += speed.x;
				if ((GetLocation().x <= moveInfo[current].destination.x) &&
					(moveInfo[current].destination.x <= nextLocation.x))
				{
					//�ړI�n���щz�����ꍇ���̒n�_���㏑��
					nextLocation.x = moveInfo[current].destination.x;
				}
			}
			//�傫���Ƃ�
			else {
				//x�̒l�����炷
				nextLocation.x -= speed.x;

				//���̍��W�����ړI�n���傫���ĖړI�n�������̍��W���傫��
				if ((nextLocation.x <= moveInfo[current].destination.x) &&
					(moveInfo[current].destination.y <= GetLocation().x))
				{
					//�ړI�n���щz�����ꍇ���̒n�_���㏑��
					nextLocation.x = moveInfo[current].destination.x;

				}
			}

		}

	}

	SetLocation(nextLocation);

}


