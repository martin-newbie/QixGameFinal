#include "DXUT.h"
#include "cHoming.h"

void cHoming::Init()
{
	pTex = RENDER->GetTexture("Homing");
	name = "Homing";
	ColliderSet(5, this);
}

void cHoming::Update()
{
	if (lockON)
	{
		int close = 10000;
		for (auto iter : OBJECT->GetObjList(ObjTag::ENEMY))
		{
			if (close > GetLength(vPos, iter->vPos) && iter->isMove && iter->name != "Boss" && iter->name != "Wave")
			{
				close = GetLength(vPos, iter->vPos);
				target_vec = &iter->vPos;
			}
		}
		lockON = false;
	}
	if (target_vec)
	{
		_target_vec.x = target_vec->x;
		_target_vec.y = target_vec->y;
		D3DXVec2Normalize(&_target_vec, &(_target_vec -vPos));
		vDir += _target_vec * 5 * Delta;
		D3DXVec2Normalize(&vDir, &vDir);
		vPos += vDir * fSpeed * Delta;
		
	}
	else
		isDestroy = true;
	if (vPos.x < 288 || vPos.x > 1312 ||
		vPos.y < 162 || vPos.y > 738) isDestroy = true;
}

void cHoming::Render()
{
	RENDER->Render(pTex, vPos);
}

void cHoming::Release()
{
	auto obj1 = ObjAdd(ObjTag::EFFECT, cWaveEffect());
	obj1->vPos = vPos;
	obj1->fSize = 0.01f;
	obj1->fRot = obj1->fSize * 50;
	obj1->color = Color(0, 1, 0, 1);
}

void cHoming::OnCollision(cCollider* col)
{
	switch (col->parent->tag)
	{
	case ENEMY:
		isDestroy = true;
		break;
	default:
		break;
	}
}
