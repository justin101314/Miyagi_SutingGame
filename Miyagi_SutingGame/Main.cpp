#include "DxLib.h"
#include "SceneManager.h"
#include "GameMainScene.h"
#include "KeyManager.h"


/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	// タイトルを test に変更
	SetMainWindowText("シューティングゲーム");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理


	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	SetFontSize(20);		// 文字サイズを設定

	//シンマネオブジェクトの作成
	SceneManager sceneMng(dynamic_cast<AbstractScene*> (new GameMainScene()));

	// ゲームループ
	while (ProcessMessage() == 0) {


		ClearDrawScreen();		// 画面の初期化


		/*KeyManager::Update();

		if (KeyManager::OnMousePressed(MOUSE_INPUT_LEFT)) {
			DrawFormatString(200, 200, 0xffffff, "ABC");
		}*/

		//シンマネ処理

		sceneMng.Update();//シーン更新
		sceneMng.Draw();//シーン描画

		if (sceneMng.ChangeScene() == nullptr) { //シーン変更処理

			DxLib_End();	// DXライブラリ使用の終了処理

			return 0;	// ソフトの終了
		}


		ScreenFlip();			// 裏画面の内容を表画面に反映

	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}