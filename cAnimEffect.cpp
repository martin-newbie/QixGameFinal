#include "DXUT.h"
#include "cAnimEffect.h"

void cAnimEffect::Init()
{
	vTex = RENDER->VecTexture("Expl", 32);
}

void cAnimEffect::Update()
{
	timer += Delta;
	if (timer > vTex.size() / 15500)
	{
		frame++;
		if (frame >= vTex.size()) isDestroy = true;
	}
}

void cAnimEffect::Render()
{
	RENDER->Render(vTex[frame], vPos, 0, fSize);
}

void cAnimEffect::Release()
{
}

void cAnimEffect::OnCollision(cCollider* col)
{
}
