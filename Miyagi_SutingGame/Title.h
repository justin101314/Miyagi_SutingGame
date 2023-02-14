#pragma once
#include "AbstractScene.h"
#define _FIRST 0

class Title : public AbstractScene

{
public:
	

public:

	 void Update ()override ;
	 void Draw ()const override;

	 AbstractScene* ChangeScene()override;

};

