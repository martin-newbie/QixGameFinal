#pragma once
#include "cObject.h"
class cHoming :
    public cObject
{
public:
    bool lockON = true;
    Vec2* target_vec;
    Vec2 _target_vec;
    // cObject을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void OnCollision(cCollider* col) override;
};

