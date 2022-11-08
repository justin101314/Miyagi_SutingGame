
#include "GameMainScene.h"
#include "DxLib.h"

GameMainScene::GameMainScene() {

	T_Location location = T_Location{ 320,440 };//�����ʒu
	player = new Player(location);
	enemy = new Enemy * [10];

	for (int i = 0; i < 10; i++) {

		enemy[i] = nullptr;
	}
	enemy[0] = new Enemy(T_Location{ 200,0 });
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

					//�X�R�A�̉��Z
					player->AddScore(enemy[enemyCount]->GetPoint());
					DrawFormatString(0, 0, (255, 255, 255), "�X�R�A:%d");

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
}

//�V�[���ύX����
AbstractScene* GameMainScene::ChangeScene() {


	return this;
}