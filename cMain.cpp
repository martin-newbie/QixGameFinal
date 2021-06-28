#include "DXUT.h"
#include "cMain.h"
#include "cIngame.h"
#include "cIntro.h"
#include "cTitle.h"
#include "cCheck.h"
#include "cEnding.h"

void cMain::Init()
{
	SCENE->Add();
	GAME->Init();
	SCENE->AddScene("InGame", new cIngame());
	SCENE->AddScene("Intro", new cIntro());
	SCENE->AddScene("Title", new cTitle());
	SCENE->AddScene("Check", new cCheck());
	SCENE->AddScene("Ending", new cEnding());
	SCENE->ChangeScene("Intro");
}

void cMain::Update()
{
	SCENE->Update();
	COLL->Update();
	GAME->Update();
	CAMERA->Update();
}

void cMain::Redner()
{
	RENDER->Begin();
	CAMERA->SetTransform();
	SCENE->Render();
	RENDER->End();
}

void cMain::Release()
{
	cCameraManager::Del();
	cSceneManager::Del();
	cObjectManager::Del();
	cColliderManager::Del();
	cGameManager::Del();
	cRenderManager::Del();
}

void cMain::Reset()
{
	RENDER->Reset();
}

void cMain::Lost()
{
	RENDER->Lost();
}

