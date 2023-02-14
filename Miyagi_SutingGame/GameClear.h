#pragma once
#include "AbstractScene.h"
class GameClear :public AbstractScene
{
public:

public:

	void Update()override;
	void Draw()const override;

	AbstractScene* ChangeScene()override;

};

