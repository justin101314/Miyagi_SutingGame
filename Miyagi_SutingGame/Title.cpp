#include "DxLib.h"
#include "Title.h"
#include "KeyManager.h"
#include "GameMainScene.h"


void Title::Update() {





}

void Title::Draw() const {


	DrawString(640, 360 ,"Z_KEY‚ð‰Ÿ‚µ‚ÄGAME_START", 0xfff);

}

AbstractScene* Title::ChangeScene() {

	switch (_FIRST)
	{
	case 0:
		if (KeyManager::OnKeyClicked(KEY_INPUT_Z)) {
			return dynamic_cast<AbstractScene*> (new (GameMainScene));
		}
		break;
	default:
		break;
	}

	return this;

}
