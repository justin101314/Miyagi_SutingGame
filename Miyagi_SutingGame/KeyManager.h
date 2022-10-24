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

	static bool OnKeyClicked(int key);//�L�[���������u��
	static bool OnKeyReleased(int key);//�L�[�𗣂��Ă�u��
	static bool OnKeyPressed(int key);//�L�[�������Ă��

	static bool OnMouseClicked(int key);//�}�E�X���������u��
	static bool OnMouseReleased(int key);//�}�E�X�𗣂��Ă�u��
	static bool OnMousePressed(int key);//�}�E�X�������Ă��
};

