#include "DxLib.h"
#include "KeyManager.h"


char KeyManager:: oldKey[256];
char KeyManager:: nowKey[256];
 int KeyManager::oldMouse;
 int KeyManager::nowMouse;


void KeyManager::Update() {



	for (int i = 0; i < 256; i++) {

		oldKey[i] = nowKey[i];
	}

	if (GetHitKeyStateAll(nowKey) == -1) {

		throw - 1;
	}

	oldMouse = nowMouse;
	nowMouse = GetMouseInput();

}

bool KeyManager::OnKeyClicked(int key) {

	bool ret = ((nowKey[key] == 1) && (oldKey[key] != 1));//�L�[���������u��
	return ret;
}


bool KeyManager:: OnKeyReleased(int key) {

	bool ret = ((nowKey[key] == 0) && (oldKey[key] == 1));//�L�[�𗣂��Ă�u��
	return ret;
}
bool KeyManager:: OnKeyPressed(int key) {

	bool ret = ((nowKey[key] == 1)); //�L�[�������đ����Ă��
	return ret;


}


//�}�E�X��

bool KeyManager::OnMouseClicked(int key) {

	bool ret = ((nowMouse & key) && (~oldMouse & key));//�L�[���������u��
	return ret;
}


bool KeyManager::OnMouseReleased(int key) {

	bool ret = ((~nowMouse & key) && (oldMouse & key));//�L�[�𗣂��Ă�u��
	return ret;
}
bool KeyManager::OnMousePressed(int key) {

	bool ret = ((nowMouse & key)); //�L�[�������đ����Ă��
	return ret;


}