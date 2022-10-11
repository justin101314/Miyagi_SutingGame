#pragma once
#include "AbstractScene.h"

//シーンマネジャークラス
//各シーンの切り替え
class SceneManager : public AbstractScene {

private:
	AbstractScene* mScene; //現在のシーン

public:
	//コンストラクタ
	SceneManager(AbstractScene* scene) : mScene(scene) {}

	//デストラクタ
	~SceneManager() {
		delete mScene;
	}

	//描画以外の更新を実装
	void Update() override;

	//描画に関することを実装
	void Draw() const override;

	//シーン変更処理
	AbstractScene* ChangeScene() override;
};

