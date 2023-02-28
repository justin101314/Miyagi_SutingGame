#include "DxLib.h"
#include "GameClear.h"
#include "Title.h"
#include "KeyManager.h"
#include "GameMainScene.h"




void GameClear::Update() {



}

void GameClear::Draw() const {


	DrawString(620, 320, "GAMECLEAR", GetColor(255,215,0));
	DrawString(620, 360, "Z_KEY‚ð‰Ÿ‚µ‚Äƒ^ƒCƒgƒ‹‚Ö", 0xffffff);
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


