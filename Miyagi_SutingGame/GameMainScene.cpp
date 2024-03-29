
#include "GameMainScene.h"
#include "DxLib.h"
#include "Recovery.h"
#include "GameOver.h"
#include "GameClear.h"

#include "KeyManager.h"


GameMainScene::GameMainScene() {


	T_Location location = T_Location{ 640,440 };//初期位置
	player = new Player(location);
	enemy = new Enemy * [10];

	for (int i = 0; i < 10; i++) {

		enemy[i] = nullptr;
	}

	//下 //エネミー数1体
	enemy[0] = new Enemy(T_Location{ 640,5 }, "../CSVEnemy/CSVEnemy.csv");
	//enemy[1] = new Enemy(T_Location{ 1280,5 },"../CSVEnemy/CSVEnemy.csv");

	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++) {

		items[i] = nullptr;
	}


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

		for (int bulletCount = 0; bulletCount < 100; bulletCount++) {


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

					
					for (int i = 0; i < 10; i++) {

						if (items[i] == nullptr) {
							items[i] = new Recovery(enemy[enemyCount]->GetLocation());
							break;
						}
					}
					//スコアの加算
					player->AddScore(enemy[enemyCount]->GetPoint());


					//エネミーの削除
					delete enemy[enemyCount];
					enemy[enemyCount] = nullptr;




					//配列を前に詰める
					for (int i = enemyCount + 1; i < 10; i++) {//例外処理防ぐため

						if (enemy[i] == nullptr) {//NULLと一致したら抜ける
							break;
						}
						enemy[i - 1] = enemy[i];//奥のものを手前の自分に入れる
						enemy[i] = nullptr;
					}

					enemyCount--;



					break;

				}
			}
		}
		//敵の弾を取ってくる
					//for(弾をループする){
					  //if(敵の弾とプレイヤーの当たり判定){
					  //}
					//}

		for (enemyCount = 0; enemyCount < 10; enemyCount++) {

			if (enemy[enemyCount] == nullptr) {
				break;
			}
			bullet = enemy[enemyCount]->GetBullets();

			//いじったとこ2
			for (int i = 0; i < 1000; i++) {//30

				if (bullet[i] == nullptr) {

					break;
				}


				if (player->HitSphere(bullet[i])) {

					//プレイヤーにダメージを与える
					player->Hit(bullet[i]->GetDamage());

					//敵の弾を削除する
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

		//アイテムとプレイヤーのヒット
		if (items[itemCount]->HitSphere(player)) {

			//回復処理
			player->Hit(items[itemCount]);

			delete items[itemCount];
			items[itemCount] = nullptr;

			//前詰め
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

//描画に関することを実装
void GameMainScene::Draw() const {


	//フォントサイズ
	SetFontSize(40);

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

	//一体目以外のものと一致したとき
	if (enemy[0] == nullptr) {

		DrawString(640,320,"LSHIFTを押して次のステージへ",0xffff00);

	}
	else if(enemy[0] == nullptr){


		DrawString(640, 350, "クリア画面へ", 0xffff00);

	}
		

}

//シーン変更処理
AbstractScene* GameMainScene::ChangeScene() {

	if (player->LifeCheck()) //HPが0になったら
	{
		//ゲームオーバーへ
		return dynamic_cast<AbstractScene*> (new (GameOver));

	}

	//ゲームクリア確認が一致したら↓
	if (enemy[0] == nullptr)
	{
		//LSHIFT押されたら
		if (KeyManager::OnKeyClicked(KEY_INPUT_LSHIFT)) {

			//次のステージへ
			if (stagecount == 1) {

				//エネミーを生成
				for (int i = 0; i < 10; i++) {

					enemy[i] = nullptr;
				}

				//下 //エネミー数1体
				enemy[0] = new Enemy(T_Location{ 640,5 }, "../CSVEnemy/CSVEnemy.csv");
				enemy[1] = new Enemy(T_Location{ 1280,10 }, "../CSVEnemy/CSVEnemy.csv");
				//enemy[2] = new Enemy(T_Location{ -640,15 }, "../CSVEnemy/CSVEnemy.csv");
				//ステージに + 1
				stagecount++;
			}
			else
			{
				return dynamic_cast<AbstractScene*> (new (GameClear));
			}
		}
		
	}

	return this;
}