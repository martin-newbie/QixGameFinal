#pragma once
#include "cEnemy.h"
class cDivide :
    public cEnemy
{
public:
    // cEnemy을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void OnCollision(cCollider* col) override;

    void Stage();

    void Pattern();
};

