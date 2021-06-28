#pragma once
#include "cScene.h"
class cIntro :
    public cScene
{
public:
    int Schedule = 0;
    float fAlpha = 0;

    Vec2 pPos = { 2500, -100 };
    Vec2 ePos = { 1700, 100 };

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

