#include "DxLib.h"
#include "GameClear.h"
#include "Title.h"
#include "KeyManager.h"
#include "GameMainScene.h"
#include"Enemy.h"



void GameClear::Update() {



}

void GameClear::Draw() const {

	DrawString(640, 320, "GAMECLEAR", 0xff);
	DrawString(640, 340, "Z_KEY‚ð‰Ÿ‚µ‚Äƒ^ƒCƒgƒ‹‚Ö", 0xff);
}

AbstractScene* GameClear::ChangeScene() {

	switch (_FIRST)
	{
	case 0:
		if (KeyManager::OnKeyClicked(KEY_INPUT_Z)) {
			return dynamic_cast<AbstractScene*> (new (Title));
		}
		break;
	default:
		break;
	}

	return this;

}


