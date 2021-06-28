#pragma once
#include "cObject.h"
class cEnemy :
    public cObject
{
public:
    // cObject을(를) 통해 상속됨
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Release() = 0;
    virtual void OnCollision(cCollider* col) = 0;
    bool isErase = false;
    float respawnTimer = -1;
    float fRadius = 0;

    void Reflect();
    void isDead();
};

