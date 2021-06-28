#pragma once
#include "cObject.h"
class cNormal :
    public cObject
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void OnCollision(cCollider* col) override;
};

