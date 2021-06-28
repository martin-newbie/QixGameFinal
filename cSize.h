#pragma once
#include "cEnemy.h"
class cSize :
    public cEnemy
{
    // cEnemy을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void OnCollision(cCollider* col) override;
    void Pattern();
    void Stage();
};

