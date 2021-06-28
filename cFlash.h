#pragma once
#include "cEnemy.h"
class cFlash :
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
    void Move();

    float prevSize = 0;
    float moveTimer = 0;
    bool isMove1 = true;
};

