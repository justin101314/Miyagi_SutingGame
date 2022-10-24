#pragma once



class KeyManager
{

private:

	static char oldKey[256];
	static char nowKey[256];

	static int oldMouse;
	static int nowMouse;

	KeyManager() = default;

public:
	static void Update();

	static bool OnKeyClicked(int key);//キーを押した瞬間
	static bool OnKeyReleased(int key);//キーを離してる瞬間
	static bool OnKeyPressed(int key);//キーを押してる間

	static bool OnMouseClicked(int key);//マウスを押した瞬間
	static bool OnMouseReleased(int key);//マウスを離してる瞬間
	static bool OnMousePressed(int key);//マウスを押してる間
};

