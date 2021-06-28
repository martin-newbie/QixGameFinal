#pragma once
#include "cEnemy.h"
class cBoss :
    public cEnemy
{
public:
    // cEnemy을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void OnCollision(cCollider* col) override;

    int nCount = 0;
    int nEvent = 0;

    float fEventTimer = 0;


    void Stage();

    void Pattern();
    void PatternC();
    void PatternW();
    void PatternD();

    void PatternUp();
    void PatternUpC();
    void PatternUpW();
    void PatternUpD();

    void Awake();
    void AwakeC();
    void AwakeW();
    void AwakeD();

    void Dead();
    void DeadC();
    void DeadW();
    void DeadD();

    void MobSpawn();
};

