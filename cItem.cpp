#include "DXUT.h"
#include "cItem.h"

void cItem::Init()
{
	Stage();
	ColliderSet(10, this);
	pTex = RENDER->GetTexture("Item");
}

void cItem::Update()
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
		isErase = false;
		GAME->nPoint++;
		this->isDestroy = true;
	}
}

void cItem::Render()
{
	RENDER->Render(pTex, vPos, 0, 1);
}

void cItem::Release()
{
}

void cItem::OnCollision(cCollider* col)
{
}

void cItem::Pattern()
{
}

void cItem::Stage()
{
}
