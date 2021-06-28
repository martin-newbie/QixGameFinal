#include "DXUT.h"
#include "cLaser.h"

void cLaser::Init()
{
	pTex = RENDER->GetTexture("Laser");
	name = "Laser";
	ColliderSet(5, this);
}

void cLaser::Update()
{
	vPos += vDir * fSpeed * Delta;
	if (vPos.x < 288 || vPos.x > 1312 ||
		vPos.y < 162 || vPos.y > 738) isDestroy = true;
}

void cLaser::Render()
{
	RENDER->Render(pTex, vPos, Vec2Rot(vDir), 1);
}

void cLaser::Release()
{
	auto obj1 = ObjAdd(ObjTag::EFFECT, cWaveEffect());
	obj1->vPos = vPos;
	obj1->fSize = 0.01f;
	obj1->fRot = obj1->fSize * 50;
	obj1->color = Color(0, 0.7, 1, 1);
}

void cLaser::OnCollision(cCollider* col)
{
}
