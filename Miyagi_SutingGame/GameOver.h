#pragma once
#include "AbstractScene.h"

class GameOver :public AbstractScene
	
{

public:
	//int GameOver = 0;

public:

	void Update()override;
	void Draw()const override;

	AbstractScene* ChangeScene()override;

};



