#include "DXUT.h"
#include "cDivide.h"

void cDivide::Init()
{
	pTex = RENDER->GetTexture("Divied");
	vDir = Rot2Vec(rand() % 360);
	fSpeed = 10.f;
}

void cDivide::Update()
{
	isDead();
	if (isMove)
	{
		Vec2 prev = vDir;
		Reflect();
		vSpeed = vDir * fSpeed;
		vPos += vSpeed;
		if (vDir != prev) Pattern();
		fRot += D3DXToRadian(60);
	}
}

void cDivide::Render()
{
	RENDER->Render(pTex, vPos, fRot, fSize, color);
}

void cDivide::Release()
{
}

void cDivide::OnCollision(cCollider* col)
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

void cDivide::Pattern()
{
	if (fSize > 0.8f)
	{
		auto obj = ObjAdd(ObjTag::ENEMY, cDivide());
		obj->vPos = vPos;
		fSize *= 0.9;
		obj->fSize = fSize;
		obj->ColliderSet(100 * fSize, obj);
	}
}