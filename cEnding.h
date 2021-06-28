#pragma once
#include "cScene.h"
class cEnding :
    public cScene
{
public:
    int nSche = 0;
    int nScore = 0;

    char name[10] = "???";
    int ntype = 0;
    bool Type = true;


    float fScoreY = 400;

    float timer = 0;

    int nLife = 0;

    bool isRank = false;

    // cScene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

