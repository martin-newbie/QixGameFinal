#pragma once
#include "cScene.h"
class cIngame :
    public cScene
{
public:
    bool alram = true;
    float fAlpha = 0;
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

