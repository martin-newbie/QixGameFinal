#include "DXUT.h"
#include "cWaveEffect.h"

void cWaveEffect::Init()
{
	pTex = RENDER->GetTexture("Wave");
}

void cWaveEffect::Update()
{
	Lerp(&fSize, fSize, fRot, 2 * Delta);
	Lerp(&color.a, color.a, 0.f, 3 * Delta);
	if (color.a < 0.01f)
	{
		isDestroy = true;
	}
}

void cWaveEffect::Render()
{
	RENDER->Render(pTex, vPos, 0, fSize, color);
}

void cWaveEffect::Release()
{
}

void cWaveEffect::OnCollision(cCollider* col)
{
}
