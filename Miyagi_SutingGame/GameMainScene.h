#pragma once

#include "AbstractScene.h"
class GameMainScene : public AbstractScene
{
public:

	//デストラクタ
	virtual ~GameMainScene() {};

	//描画以外の更新を実装
	virtual void Update() override;

	//描画に関することを実装
	virtual void Draw() const override;

	//シーン変更処理
	virtual AbstractScene* ChangeScene() override;


};
