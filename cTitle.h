#pragma once
#include "cScene.h"
class cTitle :
    public cScene
{
public:
    Vec2 pos = { 2000, 150 };
    float fAlpha = 0;

    bool isCredit = false;

    int menu = 0;
    // cScene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

