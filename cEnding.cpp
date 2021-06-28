#include "DXUT.h"
#include "cEnding.h"

void cEnding::Init()
{
	nSche = 0;
	nScore = 0;
	isRank = false;
	RENDER->Play("Clear");
}

void cEnding::Update()
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
		Lerp(&fScoreY, fScoreY, 200.f, 4 * Delta);
		if (fScoreY < 201)
			nSche++;
		break;
	case 2:
		isRank = true;
		nSche++;
		break;
	case 3:
		if (Type)
		{
			for (int i = 0; i < 128; i++)
			{
				if (KeyDown(i) && !KeyDown(VK_BACK) && ntype < 3)
				{
					name[ntype] = i;
					ntype++;
				}
			}
			if (KeyDown(VK_BACK) && ntype > 0)
			{
				ntype--;
				name[ntype] = ' ';
			}
			if (KeyDown(VK_SPACE) && ntype == 3)
			{
				GAME->rank.insert(make_pair(GAME->Score, name));
				nSche++;
			}
		}
		break;
	case 4:
		if (KeyDown(VK_SPACE))
		{
			SCENE->ChangeScene("Title");
		}
		break;
	default:
		break;
	}
}

void cEnding::Render()
{
	RENDER->Render("Score : " + to_string(nScore), { 450, fScoreY }, 100);
	if (isRank)
	{
		for (int i = 0; i < 3; i++)
		{
			char a[2];
			sprintf(a, "%c", name[i]);
			RENDER->Render(a, Vec2(740 + i * 60, 100), 100);
		}
		int i = 0;
		for (auto iter : GAME->rank)
		{
			if (i >= 500) break;
			RENDER->Render(iter.second, Vec2(450, 400 + i), 100);
			RENDER->Render(to_string(iter.first), Vec2(750, 400 + i), 100);
			i += 100;
		}

	}
}

void cEnding::Release()
{
}
