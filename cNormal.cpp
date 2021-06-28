#include "DXUT.h"
#include "cNormal.h"

void cNormal::Init()
{
	pTex = RENDER->GetTexture("Normal");
	name = "Normal";
	ColliderSet(5, this);
}

void cNormal::Update()
{
	vPos += vDir * fSpeed * Delta;
	if (vPos.x < 288 || vPos.x > 1312 ||
		vPos.y < 162 || vPos.y > 738) isDestroy = true;
}

void cNormal::Render()
{
	RENDER->Render(pTex, vPos, Vec2Rot(vDir), 1);
}

void cNormal::Release()
{
	auto obj1 = ObjAdd(ObjTag::EFFECT, cWaveEffect());
	obj1->vPos = vPos;
	obj1->fSize = 0.01f;
	obj1->fRot = obj1->fSize * 50;
	obj1->color = Color(0, 1, 0, 1);
}

void cNormal::OnCollision(cCollider* col)
{
	switch (col->parent->tag)
	{
	case ENEMY:
		isDestroy = true;
		break;
	default:
		break;
	}
}
