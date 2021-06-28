#pragma once
#include "cObject.h"
class cPlayer :
    public cObject
{
public:
    bool isLineDraw = false;
    list<Vec2> lineList;

    bool isEnable = true;
    bool isInvincible = false;
    bool Cheat = false;
    int nHp = 500;
    float fHpTimer = 0;
    float fInvincibleTimer = 0;

    int nItem = 0;
    string sItem = "NONE";

    float shotTimer = 0;
    int nLimit = 0;

    // cObject을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void OnCollision(cCollider* col) override;

    void Move();
    void HP();
    void Item();

    int BossCheck(int x, int y);
    int Speed(int pos, int dir, bool isX);
    int ISpeed(int pos, int dir, bool isX);
    void LineDraw(int prev, int now, bool isX);
    void LineClear();

    void ItemDrop();
    void RandItem();
    void PlayerDead();
};

