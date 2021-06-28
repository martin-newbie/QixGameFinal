#include "DXUT.h"
#include "cTitle.h"

void cTitle::Init()
{
	RENDER->StopAll();
	RENDER->Play("Intro", {800,450}, true);
	GAME->Score = 0;
	GAME->nLife = 5;
	GAME->Stage = 0;
	menu = 0;
	pos = { 2000, 150 };
	fAlpha = 0;
	isCredit = false;
}

void cTitle::Update()
{
	if (pos.x > 801)
	{
		Lerp(&pos, pos, Vec2(800, 150), 5 * Delta);
	}
	else if (fAlpha < 254)
	{
		Lerp(&fAlpha, fAlpha, 255.f, 4 * Delta);
	}
	if (fAlpha > 254)
	{
		if (KeyDown(VK_DOWN) && menu < 4) { 
			menu++; 
			isCredit = false;
			RENDER->Play("Button");
		}
		if (KeyDown(VK_UP) && menu > 0) {
			menu--; 
			isCredit = false;
			RENDER->Play("Button");
		}
	}
	if (KeyDown(VK_SPACE))
	{
		switch (menu)
		{
		case 0:
			break;
		case 1:
			SCENE->ChangeScene("InGame");
			break;
		case 2:
			isCredit = isCredit ? false : true;
			break;
		case 3:
			exit(0);
			break;
		case 4:
			break;
		default:
			break;
		}
	}
}

void cTitle::Render()
{
	RENDER->Render(RENDER->GetTexture("Title"), Vec2(800,450));
	RENDER->Render(RENDER->GetTexture("Title_name"), pos);
	float size[6];
	for (int i = 0; i < 6; i++) size[i] = 1;
	size[menu] = 1.2f;

	RENDER->Render(RENDER->GetTexture("BtnStart"), Vec2(1400, 350), 0, size[1], D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));
	RENDER->Render(RENDER->GetTexture("BtnCredit"), Vec2(1400, 500), 0, size[2], D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));
	RENDER->Render(RENDER->GetTexture("BtnExit"), Vec2(1400, 650), 0, size[3], D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));

	if (isCredit)
	{
		RENDER->Render(RENDER->GetTexture("Credit"), Vec2(800, 450), 0, 0.8);
	}
}

void cTitle::Release()
{
}
