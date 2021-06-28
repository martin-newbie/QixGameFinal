#include "DXUT.h"
#include "cIngame.h"
#include "cPlayer.h"
#include "cBoss.h"

void cIngame::Init()
{
	GAME->MapReset();
	ObjAdd(ObjTag::PLAYER, cPlayer());
	auto obj = ObjAdd(ObjTag::ENEMY, cBoss());
	obj->vPos = { 800, 450 };
	GAME->isBossSpawn = true;
	GAME->isBossDead = false;
	switch (GAME->Stage)
	{
	case 0:
		RENDER->Play("InGame_0");
		break;
	case 1:
		RENDER->Play("InGame_1");
		break;
	case 2:
		RENDER->Play("InGame_2");
		break;
	default:
		break;
	}

	auto item1 = ObjAdd(ObjTag::ITEM, cItem());
	auto item2 = ObjAdd(ObjTag::ITEM, cItem());
	auto item3 = ObjAdd(ObjTag::ITEM, cItem());

	item1->vPos = Vec2(rand() % 1024 + 288, rand() % 576 + 162);
	item2->vPos = Vec2(rand() % 1024 + 288, rand() % 576 + 162);
	item3->vPos = Vec2(rand() % 1024 + 288, rand() % 576 + 162);
	GAME->nPoint = 0;
} 

void cIngame::Update()
{
	if (GAME->Next)
	{
		GAME->Next = false;
		if (GAME->Stage == 2)
			SCENE->ChangeScene("Ending");
		else
		{
			GAME->Stage++;
			SCENE->ChangeScene("InGame");
		}
	}
}

void cIngame::Render()
{
	RENDER->Render(GAME->Stroke, Vec2(800, 450));
	RENDER->Render(GAME->BackTex[GAME->Stage], Vec2(800, 450));
	RENDER->Render(GAME->VirusTex[GAME->Stage], Vec2(800, 450));
	RENDER->Render(GAME->Line, Vec2(800, 450));


	RENDER->UIRender(RENDER->GetTexture("fog"), Vec2(800, 450));

	if(!GAME->isBossSpawn && alram)
		Lerp(&fAlpha, fAlpha, 255.f, Delta * 5);
	else if(!GAME->isBossSpawn)
		Lerp(&fAlpha, fAlpha, 0.f, Delta * 1);

	if (fAlpha > 254) alram = false;

	if(!GAME->isBossSpawn && CAMERA->fScale == 1)
		RENDER->Render("STAGE " + to_string(GAME->Stage + 1), { 650, 400 }, 100, D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));

	RENDER->Render("SCORE " + to_string(GAME->Score), { 450, 780 }, 100);

	char a[32];
	sprintf(a, "%.2f%%", GAME->gMapPercent);
	RENDER->Render(a, Vec2(700, 30), 100);

	for (int i = 0; i < 5; i++)
	{
		RENDER->Render(RENDER->GetTexture("HPvoid"), Vec2(160 + i * 70, 60), 0, 1);
	}

	for (int i = 0; i < GAME->nLife; i++)
	{
		RENDER->Render(RENDER->GetTexture("HPDefault"), Vec2(160 + i * 70, 60 ), 0, 1);
	}

	for (int i = 0; i < GAME->nPoint; i++)
	{
		RENDER->Render(RENDER->GetTexture("Item"), Vec2(1150 + i * 115, 85), 0, 2);
	}
}

void cIngame::Release()
{
}
