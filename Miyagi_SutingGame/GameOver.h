#pragma once
#include "AbstractScene.h"

class GameOver :public AbstractScene
	
{

public:
	

public:

	void Update()override;
	void Draw()const override;

	AbstractScene* ChangeScene()override;

};



