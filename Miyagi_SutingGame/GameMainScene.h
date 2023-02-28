#pragma once

#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "ItemBase.h"


class GameMainScene : public AbstractScene
{

private:
	Player* player;
	Enemy** enemy;
	ItemBase** items;
	//int select_num;
	int stagecount = 1;
	

public:

	GameMainScene();

	//デストラクタ
	virtual ~GameMainScene() {};

	//描画以外の更新を実装
	virtual void Update() override;

	//描画に関することを実装
	virtual void Draw() const override;

	//シーン変更処理
	virtual AbstractScene* ChangeScene() override;


};
