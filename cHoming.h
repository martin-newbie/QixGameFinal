#pragma once
#include "cObject.h"
class cHoming :
    public cObject
{
public:
    bool lockON = true;
    Vec2* target_vec;
    Vec2 _target_vec;
    // cObject��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void OnCollision(cCollider* col) override;
};

