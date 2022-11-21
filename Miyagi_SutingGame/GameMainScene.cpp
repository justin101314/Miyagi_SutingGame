
#include "GameMainScene.h"
#include "DxLib.h"
#include "Recovery.h"





GameMainScene::GameMainScene() {

	T_Location location = T_Location{ 320,440 };//�����ʒu
	player = new Player(location);
	enemy = new Enemy * [10];

	for (int i = 0; i < 10; i++) {

		enemy[i] = nullptr;
	}
	enemy[0] = new Enemy(T_Location{ 200,0 });

	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++) {

		items[i] = nullptr;
	}


}
//�`��ȊO�̍X�V������
void GameMainScene::Update() {


	player->Update();

	int enemyCount;
	for (enemyCount = 0; enemyCount < 10; enemyCount++) {

		if (enemy[enemyCount] == nullptr) {
			break;
		}
		enemy[enemyCount]->Update();
	}

	for (int i = 0; i < 10; i++) {
		if (items[i] == nullptr) {
			break;
		}
		items[i]->Update();
	}

	BulletsBase** bullet = player->GetBullets();


	for (enemyCount = 0; enemyCount < 10; enemyCount++) {

		if (enemy[enemyCount] == nullptr) {
			break;
		}

		for (int bulletCount = 0; bulletCount < 30; bulletCount++) {





			if (bullet[bulletCount] == nullptr) {
				break;
			}

			if (enemy[enemyCount]->HitSphere(bullet[bulletCount])) {


				//�G�l�~�[�Ƀv���C���[�̒e���q�b�g���Ă���
				//�G�l�~�[�Ƀ_���[�W��^����
				enemy[enemyCount]->Hit(bullet[bulletCount]->GetDamage());

				//�e���폜
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//�G�l�~�[��HP��0�ȉ���������A�G�l�~�[���폜����
				if (enemy[enemyCount]->HpCheck()) {


					for (int i = 0; i < 10; i++) {

						if (items[i] == nullptr) {
							items[i] = new Recovery(enemy[enemyCount]->GetLocation());
							break;
						}
					}
					//�X�R�A�̉��Z
					player->AddScore(enemy[enemyCount]->GetPoint());


					//�G�l�~�[�̍폜
					delete enemy[enemyCount];
					enemy[enemyCount] = nullptr;

					//�z���O�ɋl�߂�
					for (int i = enemyCount + 1; i < 10; i++) {//��O�����h������

						if (enemy[i] == nullptr) {//NULL�ƈ�v�����甲����
							break;
						}
						enemy[i - 1] = enemy[i];//���̂��̂���O�̎����ɓ����
						enemy[i] = nullptr;
					}

					enemyCount--;
					break;

				}
			}
		}
		//�G�̒e������Ă���
					//for(�e�����[�v����){
					  //if(�G�̒e�ƃv���C���[�̓����蔻��){
					  //}
					//}

		for (enemyCount = 0; enemyCount < 10; enemyCount++) {

			if (enemy[enemyCount] == nullptr) {
				break;
			}
			bullet = enemy[enemyCount]->GetBullets();

			for (int i = 0; i < 30; i++) {

				if (bullet[i] == nullptr) {

					break;
				}


				if (player->HitSphere(bullet[i])) {

					//�v���C���[�Ƀ_���[�W��^����
					player->Hit(bullet[i]->GetDamage());

					//�G�̒e���폜����
					enemy[enemyCount]->DeleteBullet(i);
					i--;
				}
			}
		}
	}


	for (int itemCount = 0; itemCount < 10; itemCount++) {

		if (items[itemCount] == nullptr) {
			break;
		}

		//�A�C�e���ƃv���C���[�̃q�b�g
		if (items[itemCount]->HitSphere(player)) {

			//�񕜏���
			player->Hit(items[itemCount]);

			delete items[itemCount];
			items[itemCount] = nullptr;

			//�O�l��
			for (int i = itemCount; i < 10; i++) {

				if (items[i] == nullptr) {
					break;
				}

				items[i - 1] = items[i];
				items[i] == nullptr;


			}

			itemCount--;

		}

	}


}

//�`��Ɋւ��邱�Ƃ�����
void GameMainScene::Draw() const {

	player->Draw();

	for (int enemyCount = 0; enemyCount < 10; enemyCount++) {

		if (enemy[enemyCount] == nullptr) {
			break;
		}
		enemy[enemyCount]->Draw();

	}

	for (int i = 0; i < 10; i++) {
		if (items[i] == nullptr) {
			break;
		}
		items[i]->Draw();
	}
}

//�V�[���ύX����
AbstractScene* GameMainScene::ChangeScene() {


	return this;
}