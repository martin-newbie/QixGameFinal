#pragma once
#include "cScene.h"
class cCheck :
    public cScene
{
public:
    int nSche = 0;
    int nScore = 0;

    float timer = 0;

    int nLife = 0;

    // cScene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

