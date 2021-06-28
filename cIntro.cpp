#include "DXUT.h"
#include "cIntro.h"

void cIntro::Init()
{
	RENDER->Play("Menu");
}

void cIntro::Update()
{
	switch (Schedule)
	{
	case 0:
		Lerp(&pPos, pPos, Vec2(1050, 400), 3 * Delta);
		Lerp(&ePos, ePos, Vec2(700, 550), 3 * Delta);
		if (ePos.y > 549)
			Schedule++;
		break;
	case 1:
		Lerp(&fAlpha, fAlpha, 255.f, 5 * Delta);
		if (fAlpha > 254)
			Schedule++;
		break;
	case 2:
		SCENE->ChangeScene("Title");
		break;
	default:
		break;
	}
}

void cIntro::Render()
{
	RENDER->Render(RENDER->GetTexture("Intro"), Vec2(800,450));
	RENDER->Render(RENDER->GetTexture("Player"), pPos, Vec2Rot(Vec2(1050, 400) - pPos));
	RENDER->Render(RENDER->GetTexture("Speed"), ePos, Vec2Rot(Vec2(700, 550) - ePos));
	RENDER->Render(RENDER->GetTexture("Intro_1"), Vec2(800,450), 0, 1, D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));
}

void cIntro::Release()
{
}
