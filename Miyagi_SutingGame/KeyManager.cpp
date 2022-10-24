#include "DxLib.h"
#include "KeyManager.h"

void KeyManager::Update() {



	for (int i = 0; i < 256; i++) {

		oldKey[i] = nowKey[i];
	}

	if (GetHitKeyStateAll(nowKey) == -1) {

		throw - 1;
	}


}

bool KeyManager::OnClicked(int key) {

	bool ret = ((nowKey[key] == 1) && (oldKey[key] != 1));//キーを押した瞬間
	return ret;
}


bool KeyManager:: OnReleased(int key) {

	bool ret = ((nowKey[key] == 0) && (oldKey[key] == 1));//キーを離してる瞬間
	return ret;
}
bool KeyManager:: OnPressed(int key) {

	bool ret = ((nowKey[key] == 1)); //キーを押して続けてる間
	return ret;


}