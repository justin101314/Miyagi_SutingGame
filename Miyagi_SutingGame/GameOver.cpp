#include "DxLib.h"
#include "GameOver.h"
//#include "Title.h"
//#include "KeyManager.h"
#include "GameMainScene.h"
//#include "Player.h"



void GameOver::Update() {



}

void GameOver::Draw() const {


	DrawString(640, 320, "GAMEOVER",0xffffff);

}

AbstractScene* GameOver::ChangeScene() {

	
	return this;

}