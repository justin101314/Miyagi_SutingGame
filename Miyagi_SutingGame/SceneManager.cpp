#include "SceneManager.h"


void SceneManager::Update() {

	
	//現在のシーンのアップデート
	mScene->Update();


}

void SceneManager::Draw() const {
	mScene->Draw();
}


//シーン変更処理
AbstractScene* SceneManager::ChangeScene() {

	
	AbstractScene* nextScene = mScene->ChangeScene();

	//次のシーンが現在のシーンと別なら変更
	if (nextScene != mScene) {

		delete mScene;
		mScene = nextScene;

	}

	return nextScene;

}