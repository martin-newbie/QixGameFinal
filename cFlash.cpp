#include "DXUT.h"
#include "cFlash.h"

void cFlash::Init()
{
	pTex = RENDER->GetTexture("Flash");
	fSize = (float)(rand() % 8 + 7) / 10;
	prevSize = fSize;
	Stage();
	ColliderSet(15 * fSize, this);
}

void cFlash::Update()
{
	isDead();
	if(isMove)
		Move();
}

void cFlash::Render()
{
	RENDER->Render(pTex, vPos, 0, fSize, color);
}

void cFlash::Release()
{
}

void cFlash::OnCollision(cCollider* col)
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

void cFlash::Stage()
{
}

void cFlash::Pattern()
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

void cFlash::Move()
{
	moveTimer += Delta;
	if(isMove1)
		Lerp(&fSize, fSize, 0.f, 4 * Delta);
	if (moveTimer >= 2 && isMove1)
	{
		Vec2 a = Vec2((rand() % 400) - 200, (rand() % 400) - 200);
		while(GAME->GetCell(vPos+a) != Empty)
			a = Vec2((rand() % 400) - 200, (rand() % 400) - 200);
		vPos = vPos + a;
		Pattern();
		isMove1 = false;
		moveTimer = 0;
	}
	else if (!isMove1)
	{
		Lerp(&fSize, fSize, prevSize, 4 * Delta);
		if (moveTimer >= 2) { isMove1 = true; moveTimer = 0; }
	}
}
