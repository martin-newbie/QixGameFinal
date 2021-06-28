#pragma once
#include "cObject.h"
class cAnimEffect :
    public cObject
{
public:
    int frame = 0;

    float timer = 0;

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void OnCollision(cCollider* col) override;
};

