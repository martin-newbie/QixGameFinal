#include "DXUT.h"
#include "cSpeedMob.h"

void cSpeedMob::Init()
{
	Stage();
	ColliderSet(10, this);
	vDir = Rot2Vec(rand()%360);
	pTex = RENDER->GetTexture("Speed");
	fSpeed = 7.f;
}

void cSpeedMob::Update()
{
	isDead();
	if (isMove)
	{
		Vec2 prev = vDir;
		Reflect();
		vSpeed = vDir * fSpeed;
		vPos += vSpeed;
		if (vDir != prev) Pattern();
		Lerp(&fSpeed, fSpeed, 7.f, 5 * Delta);
		fRot = Vec2Rot(vDir);
	}
}

void cSpeedMob::Render()
{
	RENDER->Render(pTex, vPos, fRot, 0.5f, color);
}

void cSpeedMob::Release()
{
	
}

void cSpeedMob::OnCollision(cCollider* col)
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

void cSpeedMob::Pattern()
{
	fSpeed = 10.f;
	switch (GAME->Stage)
	{
	case Carry:
		break;
	case Wave:
	{
		auto obj = ObjAdd(ObjTag::ENEMY, cWave());
		obj->vPos = vPos;
		obj->fSize = 0.025;
		obj->fRot = 0.025 * 15;
		break;
	}
	case Divide:
		break;
	default:
		break;
	}
}

void cSpeedMob::Stage()
{
	switch (GAME->Stage)
	{
	case Carry:
		color = D3DCOLOR_XRGB(170, 70, 8);
		break;
	case Wave:
		color = D3DCOLOR_XRGB(40, 65, 90);
		break;
	case Divide:
		break;
	default:
		break;
	}
}
