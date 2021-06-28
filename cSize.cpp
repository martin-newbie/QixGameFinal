#include "DXUT.h"
#include "cSize.h"

void cSize::Init()
{
	pTex = RENDER->GetTexture("Size");
	Stage();
	ColliderSet(20, this);
	fSpeed = 5.f;
	vDir = Rot2Vec(rand() % 360);
}

void cSize::Update()
{
	isDead();
	if (isMove)
	{
		Vec2 prev = vDir;
		Reflect();
		vSpeed = vDir * fSpeed;
		vPos += vSpeed;
		if (vDir != prev) Pattern();
		fRot = Vec2Rot(vDir);
	}
}

void cSize::Render()
{
	RENDER->Render(pTex, vPos, fRot, 0.5f, color);
}

void cSize::Release()
{
}

void cSize::OnCollision(cCollider* col)
{
	switch (col->parent->tag)
	{
	case BULLET:
		isErase = true;
		break;
	default:
		break;
	}
}

void cSize::Pattern()
{
	switch (GAME->Stage)
	{
	case Carry:
		break;
	case Wave:
	{
		auto obj = ObjAdd(ObjTag::ENEMY, cWave());
		obj->vPos = vPos;
		obj->fSize = 0.05;
		obj->fRot = 0.05 * 15;
		break;
	}
	case Divide:
		break;
	default:
		break;
	}
}

void cSize::Stage()
{
	switch (GAME->Stage)
	{
	case Carry:
		color = D3DCOLOR_XRGB(170, 90, 8);
		break;
	case Wave:
		color = D3DCOLOR_XRGB(100, 65, 250);
		break;
	case Divide:
		break;
	default:
		break;
	}
}