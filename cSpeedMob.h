#pragma once
#include "cEnemy.h"
class cSpeedMob :
    public cEnemy
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void OnCollision(cCollider* col) override;

    void Pattern();
    void Stage();
};

