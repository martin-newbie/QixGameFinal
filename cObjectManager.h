#pragma once
#include "singleton.h"

enum ObjTag :char
{
    PLAYER,
    ENEMY,
    BULLET,
    EFFECT,
    UI,
    ITEM,
    END
};

class cObjectManager :
    public singleton<cObjectManager>
{
public:
    list<cObject*> objList[END];

    void Update();
    void Render();
    void Release();

    ~cObjectManager() { Release(); }

    cObject* CreateObj(ObjTag tag, cObject* obj);

    list<cObject*> GetObjList(ObjTag tag)
    {
        return objList[tag];
    }

    cObject* GetPlayer()
    {
        return objList[PLAYER].front();
    }
};

#define OBJECT cObjectManager::Get()
#define ObjAdd(tag, obj) OBJECT->CreateObj(tag, new obj);