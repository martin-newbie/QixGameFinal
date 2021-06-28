#include "DXUT.h"
#include "cWave.h"

void cWave::Init()
{
	fSize = 0.1f;
	fRot = fSize * 15;
	color = Color(1, 0, 0, 1);
	name = "Wave";
	pTex = RENDER->GetTexture("Wave");
	ColliderSet(50 * fSize, this);
}

void cWave::Update()
{
	Lerp(&fSize, fSize, fRot, 2 * Delta);
	collider->fRadius = 50 * fSize;
	Lerp(&color.a, color.a, 0.f, 2 * Delta);
	if (color.a < 0.01f)
	{
		isDestroy = true;
	}
}

void cWave::Render()
{
	RENDER->Render(pTex, vPos, 0, fSize, color);
}

void cWave::Release()
{
}

void cWave::OnCollision(cCollider* col)
{
}
