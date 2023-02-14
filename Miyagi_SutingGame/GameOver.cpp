#include "DxLib.h"
#include "GameOver.h"
#include "Title.h"
#include "KeyManager.h"
#include "GameMainScene.h"


void GameOver::Update() {



}

void GameOver::Draw() const {

	DrawString(640, 320, "GAMEOVER",0xffffff);
	DrawString(640, 340, "Z_KEYを押してタイトルへ", 0xffffff);
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