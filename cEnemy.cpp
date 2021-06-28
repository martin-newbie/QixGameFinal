#include "DXUT.h"
#include "cEnemy.h"

void cEnemy::Reflect()
{
	bool isH = GAME->GetCell(vPos.x, vPos.y + (collider->fRadius / 2) + vSpeed.y) != Empty ||
		GAME->GetCell(vPos.x, vPos.y - (collider->fRadius / 2) + vSpeed.y) != Empty;
	bool isV = GAME->GetCell(vPos.x + (collider->fRadius / 2) + vSpeed.x, vPos.y) != Empty ||
		GAME->GetCell(vPos.x - (collider->fRadius / 2) + vSpeed.x, vPos.y) != Empty;

	if (isH) vDir.y *= -1;
	if (isV) vDir.x *= -1;
}

void cEnemy::isDead()
{
	if (GAME->GetCell(vPos) == Cell::Disable)
		isErase = true;
	if (isErase)
	{
		for (int i = 0; i < rand() % 20 + 10; i++)
		{
			auto obj = ObjAdd(ObjTag::EFFECT, cParticle());
			obj->fSpeed = rand() % 25 + 25;
			obj->fSize = (float)(rand() % 15 + 5) / 10;
			obj->vPos = vPos;
			obj->color = color;
			obj->vDir = Rot2Vec(rand() % 360);
		}
		RENDER->Play("Expl", vPos);
		vPos = GAME->BossPos;
		fRadius = collider->fRadius;
		collider->fRadius = -1;
		color.a = 0;
		respawnTimer = 8;
		isMove = false;
		isErase = false;
		
	}
	if (respawnTimer >= 0)
	{
		respawnTimer -= Delta;
		if (respawnTimer <= 0)
		{

			color.a = 1;
			isMove = true;
			collider->fRadius = fRadius;
			for (int i = 0; i < rand() % 20 + 10; i++)
			{
				auto obj = ObjAdd(ObjTag::EFFECT, cParticle());
				obj->fSpeed = rand() % 25 + 25;
				obj->fSize = (float)(rand() % 15 + 5) / 10;
				obj->vPos = vPos + Rot2Vec(rand() % 360) * (obj->fSpeed);
				obj->color = color;
				D3DXVec2Normalize(&obj->vDir, &(vPos - obj->vPos));
			}
		}
	}
}
