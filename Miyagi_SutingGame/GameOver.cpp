#include "DxLib.h"
#include "GameOver.h"
#include "Title.h"
#include "KeyManager.h"
#include "GameMainScene.h"


void GameOver::Update() {



}

void GameOver::Draw() const {

	DrawString(610, 320, "GAMEOVER",GetColor(220,20,60));
	DrawString(610, 340, "Z_KEY‚ð‰Ÿ‚µ‚Äƒ^ƒCƒgƒ‹‚Ö", 0xffffff);
}

AbstractScene* GameOver::ChangeScene() {

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