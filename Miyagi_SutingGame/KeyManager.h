#pragma once



class KeyManager
{

private:
	static char oldKey[256];
	static char nowKey[256];
	KeyManager() = default;

public:
	static void Update();
	static bool OnClicked(int key);//キーを押した瞬間
	static bool OnReleased(int key);//キーを離してる瞬間
	static bool OnPressed(int key);//キーを押してる間

};

