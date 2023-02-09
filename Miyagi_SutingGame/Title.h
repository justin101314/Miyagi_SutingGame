#pragma once
#include "AbstractScene.h"
#define _FIRST 0

class Title : public AbstractScene

{
public:
	//int title = 0;

public:

	 void Update ()override ;
	 void Draw ()const override;

	 AbstractScene* ChangeScene()override;

};

