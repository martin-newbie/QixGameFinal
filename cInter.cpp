#include "DXUT.h"
#include "cInter.h"

void cInter::Init()
{
}

void cInter::Update()
{
}

void cInter::Render()
{
}

void cInter::Release()
{
}

void cInter::OnCollision(cCollider* col)
{
	switch (col->parent->tag)
	{
	case BULLET:
		isDestroy = true;
		break;
	default:
		break;
	}
}
