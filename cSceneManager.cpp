#include "DXUT.h"
#include "cSceneManager.h"

void cSceneManager::Update()
{
	if (next)
	{
		Lerp(&fAlpha, fAlpha, 255.f, 5 * Delta);
		if (fAlpha > 254)
		{
			if (now)
			{
				now->Release();
				OBJECT->Release();
			}
			next->Init();
			now = next;
			next = nullptr;
		}
	}
	else if (now)
	{
		Lerp(&fAlpha, fAlpha, 0.f, 5 * Delta);
		if (fAlpha < 5)
		{
			now->Update();
			OBJECT->Update();
		}
	}
}

void cSceneManager::Render()
{
	if (now)
	{
		now->Render();
		OBJECT->Render();
	}
	RENDER->Render(tex, Vec2(800, 450), 0, 2, D3DCOLOR_ARGB((int)fAlpha, 255, 255, 255));
}

void cSceneManager::Release()
{
	if (now)
	{
		now->Release();
		OBJECT->Release();
	}
	for (auto iter : sceneList)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	sceneList.clear();
}

void cSceneManager::AddScene(string key, cScene* scene)
{
	sceneList.insert(make_pair(key, scene));
}

void cSceneManager::ChangeScene(string key)
{
	next = sceneList.find(key)->second;
	RENDER->StopAll();
}

void cSceneManager::Add()
{
	RENDER->AddTexture("PurifiedCarry", "Enemy/PurifiedCarry");
	RENDER->AddTexture("PurifiedWaveE", "Enemy/PurifiedWaveE");
	RENDER->AddTexture("PurifiedDivider", "Enemy/PurifiedDivider");
	RENDER->AddTexture("Back", "Background/Back", 3);
	RENDER->AddTexture("Virus", "Background/Virus", 3);
	RENDER->AddTexture("Line", "Background/Line");
	RENDER->AddTexture("Stroke", "Background/Stroke");

	RENDER->AddTexture("WaterEnemy", "WaterEnemy", 3);
	RENDER->AddTexture("FireEnemy", "FireEnemy", 3);
	RENDER->AddTexture("BtnStart", "BtnStart");
	RENDER->AddTexture("BtnExit", "BtnExit");
	RENDER->AddTexture("BtnCredit", "BtnCredit");
	RENDER->AddTexture("Credit", "Credit");

	RENDER->AddTexture("HPDefault", "HPDefault");
	RENDER->AddTexture("HPvoid", "HPvoid");

	RENDER->AddTexture("Item", "Item");

	RENDER->AddTexture("Player", "Player");
	RENDER->AddTexture("change", "Change");
	RENDER->AddTexture("fog", "fog");
	RENDER->AddTexture("Wave", "Wave");
	RENDER->AddTexture("Intro", "IntroBack");
	RENDER->AddTexture("Intro_1", "Intro");
	RENDER->AddTexture("Title_name", "Title_name");
	RENDER->AddTexture("Title", "Title");
	RENDER->AddTexture("Start", "Start");
	RENDER->AddTexture("Rank", "Rank");
	RENDER->AddTexture("Credit", "Credit");
	RENDER->AddTexture("Credit_1", "Credit_1");
	RENDER->AddTexture("Exit", "Exit");
	RENDER->AddTexture("window1", "window1");
	RENDER->AddTexture("Normal", "Normal");
	RENDER->AddTexture("Laser", "Laser");
	RENDER->AddTexture("Homing", "Homing");
	RENDER->AddTexture("Particle", "Effect/Particle");

	RENDER->AddTexture("Expl", "Effect/Expl/Expl", 32);
	RENDER->AddTexture("Smoke", "Effect/Smoke/Smoke", 32);

	RENDER->AddTexture("Speed", "Enemy/Speed");
	RENDER->AddTexture("Size", "Enemy/Size");
	RENDER->AddTexture("Carry", "Enemy/Carry");
	RENDER->AddTexture("Divider", "Enemy/Divider");
	RENDER->AddTexture("Divied", "Enemy/Divied");
	RENDER->AddTexture("Inter", "Enemy/Inter");
	RENDER->AddTexture("WaveE", "Enemy/WaveE");
	RENDER->AddTexture("Flash", "Enemy/Flash");


	RENDER->AddSound("Bullet", L"Bullet");
	RENDER->AddSound("Clear", L"Clear");
	RENDER->AddSound("Expl", L"Expl");
	RENDER->AddSound("InGame_0", L"InGame_0");
	RENDER->AddSound("InGame_1", L"InGame_1");
	RENDER->AddSound("InGame_2", L"InGame_2");
	RENDER->AddSound("Intro", L"Intro");
	RENDER->AddSound("Item", L"Item");
	RENDER->AddSound("Judo", L"Judo");
	RENDER->AddSound("Laser_0", L"Laser_0");
	RENDER->AddSound("Laser_1", L"Laser_1");
	RENDER->AddSound("Menu", L"Menu");
	RENDER->AddSound("Shooting", L"Shooting");
	RENDER->AddSound("Button", L"Button");
	RENDER->AddSound("Clash", L"Clash");
	RENDER->AddSound("Heal", L"Heal");
	tex = RENDER->GetTexture("change");
}
