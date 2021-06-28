#include "DXUT.h"
#include "cCheck.h"

void cCheck::Init()
{
	nSche = 0;
	nLife = 0;
	if (GAME->Stage == 0)
		nScore = 0;
	RENDER->Play("Clear");
}

void cCheck::Update()
{
	switch (nSche)
	{
	case 0:
		if (nScore + (GAME->Score * 0.01) <= GAME->Score)
		{
			timer += Delta;
			if (timer >= 0.01f)
			{
				nScore += (GAME->Score * 0.01);
				timer = 0;
			}
		}
		else
		{
			nSche++;
		}
		break;
	case 1:
		if (nLife + 1 <= GAME->nLife)
		{
			timer += Delta;
			if (timer >= 0.5f)
			{
				nLife++;
				GAME->Score += (GAME->Score * 0.1);
				nScore = GAME->Score;
				timer = 0;
			}
		}
		else
		{
			timer += Delta;
			if (timer >= 1.f)
			{
				timer = 0;
				GAME->Stage++;
				
				SCENE->ChangeScene("InGame");
			}
		}
		break;
	default:
		break;
	}
}

void cCheck::Render()
{
	RENDER->Render("Score : " + to_string(nScore), { 450, 400 }, 100);
	for (int i = 0; i < nLife; i++)
	{
		RENDER->Render(RENDER->GetTexture("HPDefault"), Vec2(600 + i * 100, 700), 0, 1.5f);
	}
}

void cCheck::Release()
{
}
