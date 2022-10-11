#include "SceneManager.h"


void SceneManager::Update() {

	
	//���݂̃V�[���̃A�b�v�f�[�g
	mScene->Update();


}

void SceneManager::Draw() const {
	mScene->Draw();
}


//�V�[���ύX����
AbstractScene* SceneManager::ChangeScene() {

	
	AbstractScene* nextScene = mScene->ChangeScene();

	//���̃V�[�������݂̃V�[���ƕʂȂ�ύX
	if (nextScene != mScene) {

		delete mScene;
		mScene = nextScene;

	}

	return nextScene;

}