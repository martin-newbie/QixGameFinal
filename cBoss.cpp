#include "DXUT.h"
#include "cBoss.h"
#include "cDivide.h"
#include "cSize.h"
#include "cSpeedMob.h"
#include "cFlash.h"
#include "cInter.h"

void cBoss::Init()
{
	name = "Boss";
	vPos = { 800,450 };
	GAME->BossPos = vPos;
	Stage();
}

void cBoss::Update()
{
	if (GAME->isBossSpawn)
		Awake();
	else if (GAME->isBossDead)
		Dead();
	else
	{
		if (GAME->nPoint >= GAME->nMasPoint)
		{
			GAME->isBossDead = true;
			nCount = 0;
		}
		PatternUp();
		Vec2 prev = vDir;
		Reflect();
		vSpeed = vDir * fSpeed;
		vPos += vSpeed;
		if (vDir != prev) Pattern();
		if (GAME->Stage == Boss::Divide) fRot += D3DXToRadian(60);
		else fRot = Vec2Rot(vDir);
		GAME->BossPos = vPos;
	}
}

void cBoss::Render()
{
	RENDER->Render(pTex, vPos, fRot, fSize);
}

void cBoss::Release()
{
}

void cBoss::OnCollision(cCollider* col)
{
}

void cBoss::Stage()
{
	vDir = Rot2Vec(rand() % 360);
	switch (GAME->Stage)
	{
	case Carry:
		pTex = RENDER->GetTexture("Carry");
		ColliderSet(50, this);
		fSize = 0;
		fSpeed = 6.f;
		break;
	case Wave:
		pTex = RENDER->GetTexture("WaveE");
		ColliderSet(55, this);
		fSpeed = 5.f;
		fSize = 0;
		break;
	case Divide:
		pTex = RENDER->GetTexture("Divider");
		ColliderSet(100, this);
		fSpeed = 8.f;
		fSize = 0.01;
		break;
	default:
		break;
	}
}

void cBoss::Pattern()
{
	CAMERA->CameraShake(2, 0.25f);
	RENDER->Play("Clash", vPos);
	switch (GAME->Stage) 
	{
	case Carry:
		PatternC();
		break;
	case Wave:
		PatternW();
		break;
	case Divide:
		PatternD();
		break;
	default:
		break;
	}
}

void cBoss::PatternC()
{
	if (nCount < 10)
	{

	}
}

void cBoss::PatternW()
{
	fSpeed = 5;
	auto obj = ObjAdd(ObjTag::ENEMY, cWave());
	obj->vPos = vPos;
}

void cBoss::PatternD()
{
	if (fSize > 0.8f)
	{
		auto obj = ObjAdd(ObjTag::ENEMY, cDivide());
		obj->vPos = vPos;
		fSize *= 0.9;
		obj->fSize = fSize;
		obj->ColliderSet(100 * fSize, obj);
	}
}

#pragma region 업데이트


void cBoss::PatternUp()
{
	switch (GAME->Stage)
	{
	case Carry:
		PatternUpC();
		break;
	case Wave:
		PatternUpW();
		break;
	case Divide:
		PatternUpD();
		break;
	default:
		break;
	}
}

void cBoss::PatternUpC()
{
}

void cBoss::PatternUpW()
{
	fSpeed *= 1.02f;
}

void cBoss::PatternUpD()
{
}
#pragma endregion

#pragma region 출현


void cBoss::Awake()
{
	switch (GAME->Stage)
	{
	case Carry:
		AwakeC();
		break;
	case Wave:
		AwakeW();
		break;
	case Divide:
		AwakeD();
		break;
	default:
		break;
	}
}

void cBoss::AwakeC()
{
	switch (nEvent)
	{
	case 0:
		CAMERA->ZoomIn(vPos, 2);
		if (CAMERA->fScale > 1.98) { 
			nEvent++; 
			CAMERA->CameraShake(4, 2);
		}
		break;
	case 1:
		Lerp(&fSize, fSize, 1.f, 3 * Delta);
		if (fSize > 0.98)
		{
			fSize = 1;
			nEvent++;
		}
		break;
	case 2:
		fEventTimer += Delta;
		if (fEventTimer >= 1 && nCount < 3)
		{
			fEventTimer = 0;
			auto obj = ObjAdd(ObjTag::ENEMY, cSpeedMob());
			obj->vPos = vPos;
			nCount++;
		}
		else if (nCount == 3)
		{
			CAMERA->CameraShake(4, 2);
			nEvent++;
		}
		break;
	case 3:
		CAMERA->ZoomOut();
		if (CAMERA->fScale < 1.01)
		{
			CAMERA->fScale = 1;
			GAME->isBossSpawn = false;
			MobSpawn();
			nEvent = 0;
		}
		break;
	default:
		break;
	}
}

void cBoss::AwakeW()
{
	switch (nEvent)
	{
	case 0:
		CAMERA->ZoomIn(vPos, 2);
		if (CAMERA->fScale > 1.98) {
			nEvent++;
			CAMERA->CameraShake(4, 7);
		}
		break;
	case 1:
		Lerp(&fSize, fSize, 1.f, 3 * Delta);
		if (fSize > 0.98)
		{
			fSize = 1;
			nEvent++;
		}
		break;
	case 2:
	{
		fEventTimer += Delta;
		auto obj1 = ObjAdd(ObjTag::EFFECT, cWaveEffect());
		obj1->vPos = vPos;
		obj1->fSize = 1.f;
		obj1->fRot = obj1->fSize * 15;
		obj1->color = Color(1, 0, 0, 1);
		if (fEventTimer >= 3)
		{
			CAMERA->CameraShake(4, 2);
			fEventTimer = 0;
			nEvent++;
		}
		break;
	}
	case 3:
		CAMERA->ZoomOut();
		if (CAMERA->fScale < 1.01)
		{
			CAMERA->fScale = 1;
			GAME->isBossSpawn = false;
			MobSpawn();
			nEvent = 0;
		}
		break;
	default:
		break;
	}
}

void cBoss::AwakeD()
{
	switch (nEvent)
	{
	case 0:
		CAMERA->ZoomIn(vPos, 2);
		if (CAMERA->fScale > 1.98) {
			nEvent++;
			CAMERA->CameraShake(4, 2);
		}
		break;
	case 1:
		fEventTimer += Delta;
		if (fEventTimer >= 0.025 && fSize < 1)
		{
			fEventTimer = 0;
			auto obj = ObjAdd(ObjTag::EFFECT, cParticle());
			obj->pTex = RENDER->GetTexture("Divied");
			obj->fSpeed = fSize *100 + 250;
			obj->fSize = fSize;
			obj->vPos = vPos + Rot2Vec(rand() % 360) * (obj->fSpeed/ 2);
			D3DXVec2Normalize(&obj->vDir, &(vPos - obj->vPos));
			fSize += 0.01;
		}
		else if (fSize >= 1)
		{
			CAMERA->CameraShake(4, 2);
			nEvent++;
		}
		break;
	case 2:
		CAMERA->ZoomOut();
		if (CAMERA->fScale < 1.01)
		{
			CAMERA->fScale = 1;
			GAME->isBossSpawn = false;
			MobSpawn();
			nEvent = 0;
		}
		break;
	default:
		break;
	}
}

#pragma endregion

#pragma region 소멸
void cBoss::Dead()
{
	switch (nEvent)
	{
	case 0:
		fEventTimer += Delta;
		if (fEventTimer >= 0.05 && nCount < 100)
		{
			fEventTimer = 0;
			auto obj = ObjAdd(ObjTag::ENEMY, cAnimEffect());
			obj->vPos = Vec2(rand() % 1024 + 288, rand() % 576 + 162);
			RENDER->Play("Expl", obj->vPos);
			nCount++;
		}
		else if (nCount >= 100)
			nEvent++;
		break;
	case 1:
		CAMERA->ZoomIn(vPos, 2);
		if (CAMERA->fScale > 1.98) {
			nEvent++;
		}
		else 
		break;
	case 2:
		CAMERA->ZoomOut();
		if (CAMERA->fScale < 1.01)
		{
			CAMERA->fScale = 1;
			auto obj = ObjAdd(ObjTag::EFFECT, cAnimEffect());
			obj->fSize = 3;
			obj->vPos = vPos;
			GAME->Next = true;
			nEvent = 0;
		}

		break;
	default:
		break;
	}
}

void cBoss::DeadC()
{
	switch (nEvent)
	{
	default:
		break;
	}
}

void cBoss::DeadW()
{
}

void cBoss::DeadD()
{
}

#pragma endregion

void cBoss::MobSpawn()
{
	for (int i = 0; i < 2; i++)
	{
		auto obj = ObjAdd(ObjTag::ENEMY, cSpeedMob());
		obj->vPos = vPos;
		auto obj1 = ObjAdd(ObjTag::ENEMY, cFlash());
		obj1->vPos = vPos;
		auto obj2 = ObjAdd(ObjTag::ENEMY, cSize());
		obj2->vPos = vPos;
	}
}