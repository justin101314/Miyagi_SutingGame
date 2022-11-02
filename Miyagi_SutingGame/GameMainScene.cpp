
#include "GameMainScene.h"


GameMainScene::GameMainScene() {

	T_Location location = T_Location{ 320,440 };//初期位置
	player = new Player(location);
	enemy = new Enemy * [10];

	for (int i = 0; i < 10; i++) {

		enemy[i] = nullptr;
	}
	enemy[0] = new Enemy(T_Location{ 200,0 });
}
//描画以外の更新を実装
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


				//エネミーにプレイヤーの弾がヒットしている

				//エネミーにダメージを与える
				enemy[enemyCount]->Hit(bullet[bulletCount]->GetDamage());
				 
				//弾を削除
				player->DeleteBullet(bulletCount);
				bulletCount--;
		
				//エネミーのHPが0以下だったら、エネミーを削除する
				if (enemy[enemyCount]->HpCheck()) {

					//エネミーの削除


				}
			}
		}
	}

}

//描画に関することを実装
void GameMainScene::Draw() const {

	player->Draw();

	for (int enemyCount = 0; enemyCount < 10; enemyCount++) {

		if (enemy[enemyCount] == nullptr) {
			break;
		}
		enemy[enemyCount]->Draw();

	}
}

//シーン変更処理
AbstractScene* GameMainScene::ChangeScene() {


	return this;
}