#pragma once



class KeyManager
{

private:
	static char oldKey[256];
	static char nowKey[256];
	KeyManager() = default;

public:
	static void Update();
	static bool OnClicked(int key);//�L�[���������u��
	static bool OnReleased(int key);//�L�[�𗣂��Ă�u��
	static bool OnPressed(int key);//�L�[�������Ă��

};

