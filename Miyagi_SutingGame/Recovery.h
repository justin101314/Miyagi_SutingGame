#pragma once
#include "ItemBase.h"


class Recovery :public ItemBase
    
{


private:

    int volume;
    int recoveryimages = 0;

public:


    Recovery(T_Location location);
    virtual void Update() override;
    virtual void  Draw() override;
    int GetVolume();


};

