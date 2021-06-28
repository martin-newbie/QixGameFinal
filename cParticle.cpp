#include "DXUT.h"
#include "cParticle.h"

void cParticle::Init()
{
	pTex = RENDER->GetTexture("Particle");
	fSize = (float)(rand() % 5 + 2) / 10;
}

void cParticle::Update()
{
	Lerp(&fSpeed, fSpeed, 0.f, 2 * Delta);
	Lerp(&color.a, color.a, 0.f, 2* Delta);
	vPos += vDir * fSpeed * Delta;
	if (fSpeed <= 0.1) isDestroy = true;
}

void cParticle::Render()
{
	RENDER->Render(pTex, vPos, 0, fSize, color);
}

void cParticle::Release()
{
}

void cParticle::OnCollision(cCollider* col)
{
}
