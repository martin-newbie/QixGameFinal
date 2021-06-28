#include "DXUT.h"
#include "cPlayer.h"
#include "cNormal.h"
#include "cLaser.h"
#include "cHoming.h"

void cPlayer::Init()
{
	pTex = RENDER->GetTexture("Player");
	vPos = { 288,162 };
	fSpeed = 3;
	ColliderSet(10, this);
	nItem = 0;
}

void cPlayer::Update()
{
	if (!GAME->isBossSpawn)
	{
		if (GAME->nLife <= 0)
		{
			CAMERA->ZoomIn(vPos, 3);
			if (CAMERA->fScale > 2.98)
			{
				auto obj = ObjAdd(ObjTag::EFFECT, cAnimEffect());
				obj->vPos = vPos;
				SCENE->ChangeScene("Ending");
				CAMERA->fScale = 1;
				CAMERA->vCamPos = { 800,450 };
			}
		}
		if (nHp <= 0) PlayerDead();
		if (KeyDown(VK_F1))
			Cheat = true;
		if(KeyDown(VK_F2))
			RandItem();
		if (KeyDown(VK_F3))
			nHp += 50;
		if (KeyDown(VK_F4))
			nHp -= 50;
		Move();
		HP();
		Item();
	}
}

void cPlayer::Render()
{
	RENDER->Render(pTex, vPos, fRot, 0.5f);
	RENDER->Render("HP  " + to_string(nHp), Vec2(100, 780), 100);
	//RENDER->Render("ITEM  " + sItem, Vec2(1050, 50), 60);
}

void cPlayer::Release()
{

}

void cPlayer::OnCollision(cCollider* col)
{
	if (!Cheat)
	{
		switch (col->parent->tag)
		{
		case ENEMY:
		{
			/*if (col->parent->name == "Wave" && !isInvincible)
			{
				if (auto find = collider->colEnterList.find(col->parent); find != collider->colEnterList.end())
					break;
				nHp -= 25;
				CAMERA->CameraShake(0.5, 0.25);
			}*/
			if (!isEnable && !isInvincible)
			{
				PlayerDead();
			}
			break;
		}
		default:
			break;
		}
	}
}

void cPlayer::Move()
{
	if (KeyPress(VK_SPACE))
	{
		if (KeyPress(VK_UP))
		{
			Vec2 prev = vPos;

			vPos.y -= Speed(vPos.y, -1, false);

			LineDraw(prev.y, vPos.y, false);

			if (GAME->GetCell(vPos) == Cell::Enable && isLineDraw)
			{
				GAME->MapCheck(vPos, -1, 1, BossCheck(vPos.x -1, vPos.y+ 1) == 0, false);
				LineClear();
				isLineDraw = false;
			}
		}
		else if (KeyPress(VK_DOWN))
		{
			Vec2 prev = vPos;

			vPos.y += Speed(vPos.y, 1, false);

			LineDraw(prev.y, vPos.y, false);

			if (GAME->GetCell(vPos) == Cell::Enable && isLineDraw)
			{
				GAME->MapCheck(vPos, -1, -1, BossCheck(vPos.x-1, vPos.y -1) == 0, false);
				LineClear();
				isLineDraw = false;
			}
		}
		else if (KeyPress(VK_LEFT))
		{
			Vec2 prev = vPos;

			vPos.x -= Speed(vPos.x, -1, true);

			LineDraw(prev.x, vPos.x, true);

			if (GAME->GetCell(vPos) == Cell::Enable && isLineDraw)
			{
				GAME->MapCheck(vPos, 1, -1, BossCheck(vPos.x+1, vPos.y -1) == 0, true);
				LineClear();
				isLineDraw = false;
			}
		}
		else if (KeyPress(VK_RIGHT))
		{
			Vec2 prev = vPos;

			vPos.x += Speed(vPos.x, 1, true);

			LineDraw(prev.x, vPos.x, true);

			if (GAME->GetCell(vPos) == Cell::Enable && isLineDraw)
			{
				GAME->MapCheck(vPos, -1, -1, BossCheck(vPos.x - 1, vPos.y - 1) == 0, true);
				LineClear();
				isLineDraw = false;
			}
		}
	}
	else
	{
		if (KeyPress(VK_UP))
		{
			vPos.y -= ISpeed(vPos.y, -1, false);
		}
		else if (KeyPress(VK_DOWN))
		{
			vPos.y += ISpeed(vPos.y, 1, false);
		}
		else if (KeyPress(VK_LEFT))
		{
			vPos.x -= ISpeed(vPos.x, -1, true);
		}
		else if (KeyPress(VK_RIGHT))
		{
			vPos.x += ISpeed(vPos.x, 1, true);
		}
	}

	if (KeyPress(VK_UP))
	{
		fRot = D3DXToRadian(270);
	}
	else if (KeyPress(VK_DOWN))
	{
		fRot = D3DXToRadian(90);
	}
	else if (KeyPress(VK_LEFT))
	{
		fRot = D3DXToRadian(180);
	}
	else if (KeyPress(VK_RIGHT))
	{
		fRot = D3DXToRadian(0);
	}
}

void cPlayer::HP()
{
	if (GAME->GetCell(vPos) == Enable)
	{
		isEnable = true;
		fHpTimer += Delta;
		if (fHpTimer >= 0.15f)
		{
			fHpTimer = 0;
			nHp -= 1;
		}
	}
	else
	{
		isEnable = false;
	}
}

void cPlayer::Item()
{
	if (isInvincible)
	{
		fInvincibleTimer += Delta;
		if (fInvincibleTimer >= 3)
		{
			isInvincible = false;
			nItem = 0;
			Item();
		}
	}
	switch (nItem)
	{
	case 0:
		fSpeed = 3;
		sItem = "NONE";
		break;
	case 1:
		fSpeed = 6;
		sItem = "SPEED";
		break;
	case 2:
		fSpeed = 3;
		isInvincible = true;
		sItem = "INVINCIBLE";
		break;
	case 3:
		fSpeed = 3;
		if (GAME->nLife < 5)
			GAME->nLife++;
		else
			GAME->Score += GAME->Score * 0.1;
		nItem = 0;
		Item(); 
		break;
	case 4:
		fSpeed = 3;
		sItem = "MACHINEGUN";
		if (nLimit == 0)
		{
			nItem = 0;
			Item();
		}
		shotTimer += Delta;
		if (KeyPress(VK_SPACE) && shotTimer >= 0.3f)
		{
			auto obj = ObjAdd(ObjTag::BULLET, cNormal());
			obj->vPos = vPos;
			obj->vDir = Rot2Vec(fRot);
			obj->fSpeed = 1200;
			RENDER->Play("Bullet", obj->vPos);
			nLimit--;
			shotTimer = 0;
		}
		break;
	case 5:
		fSpeed = 3;
		sItem = "HOMING";
		if (nLimit == 0)
		{
			nItem = 0;
			Item();
		}
		shotTimer += Delta;
		if (KeyPress(VK_SPACE) && shotTimer >= 1)
		{
			auto obj = ObjAdd(ObjTag::BULLET, cHoming());
			obj->vPos = vPos;
			//obj->vDir = Rot2Vec(fRot);
			obj->fSpeed = 600;
			RENDER->Play("Judo", obj->vPos);
			nLimit--;
			shotTimer = 0;
		}
		break;
	case 6:
		fSpeed = 3;
		sItem = "LASER";
		if (nLimit == 0)
		{
			nItem = 0;
			Item();
		}
		shotTimer += Delta;
		if (KeyPress(VK_SPACE) && shotTimer >= 0.7f)
		{
			auto obj = ObjAdd(ObjTag::BULLET, cLaser());
			obj->vPos = vPos;
			obj->vDir = Rot2Vec(fRot);
			obj->fSpeed = 1800;
			RENDER->Play("Laser_0", obj->vPos);
			nLimit--;
			shotTimer = 0;
		}
		break;
	default:
		break;
	}
}

int cPlayer::BossCheck(int x, int y)
{
	int n = 0;
	if (x == (int)GAME->BossPos.x && y == (int)GAME->BossPos.y) return 1;
	if (GAME->GetCell(x, y) != Empty) return 0;
	GAME->SetCell(x, y, Cell::BossCheck);
	n += BossCheck(x + 1, y);
	n += BossCheck(x - 1, y);
	n += BossCheck(x, y + 1);
	n += BossCheck(x, y - 1);
	return n;
}

int cPlayer::Speed(int pos, int dir, bool isX)
{
	int move = 0;
	int iter, limit;
	if (dir == -1)
	{
		iter = pos - fSpeed;
		limit = pos + dir;
	}
	else
	{
		limit = pos + fSpeed;
		iter = pos + dir;
	}

	if (isX)
	{
		while (iter <= limit)
		{

			if (iter < 288 || iter > 1312) return move;
			if (GAME->GetCell(iter + 1, vPos.y) == Player && dir == 1) return move;
			if (GAME->GetCell(iter, vPos.y) == Player && dir == -1) move = -1;
			if (GAME->GetCell(iter, vPos.y) == Disable && dir == 1) return move;
			if (GAME->GetCell(iter, vPos.y) == Disable && dir == -1) move = 0;

			if (GAME->GetCell(iter, vPos.y) == Empty ||
				GAME->GetCell(iter, vPos.y) == Enable) move++;
			iter++;
		}
	}
	else
	{
		while (iter <= limit)
		{
			if (iter < 162 || iter > 738) return move;
			if (GAME->GetCell(vPos.x, iter + 1) == Player && dir == 1) return move;
			if (GAME->GetCell(vPos.x, iter) == Player && dir == -1) move = -1;
			if (GAME->GetCell(vPos.x, iter) == Disable && dir == 1) return move;
			if (GAME->GetCell(vPos.x, iter) == Disable && dir == -1) move = 0;

			if (GAME->GetCell(vPos.x, iter) == Empty ||
				GAME->GetCell(vPos.x, iter) == Enable) move++;
			iter++;
		}
	}
	return Clamp(move, 0, (int)fSpeed);
}

int cPlayer::ISpeed(int pos, int dir, bool isX)
{
	int move = 0;
	int iter, limit;
	if (dir == -1)
	{
		iter = pos - fSpeed;
		limit = pos + dir;
	}
	else
	{
		limit = pos + fSpeed;
		iter = pos + dir;
	}

	if (isX)
	{
		while (iter <= limit)
		{
			if (iter < 288 || iter > 1312) return move;
			if (GAME->GetCell(iter, vPos.y) == Empty && dir == 1) return move;
			if (GAME->GetCell(iter, vPos.y) == Empty && dir == -1) move = 0;
			if (GAME->GetCell(iter, vPos.y) == Disable && dir == 1) return move;
			if (GAME->GetCell(iter, vPos.y) == Disable && dir == -1) move = 0;

			if (GAME->GetCell(iter, vPos.y) == Enable) move++;
			iter++;
		}
	}
	else
	{
		while (iter <= limit)
		{
			if (iter < 162 || iter > 738) return move;
			if (GAME->GetCell(vPos.x, iter) == Empty && dir == 1) return move;
			if (GAME->GetCell(vPos.x, iter) == Empty && dir == -1) move = 0;
			if (GAME->GetCell(vPos.x, iter) == Disable && dir == 1) return move;
			if (GAME->GetCell(vPos.x, iter) == Disable && dir == -1) move = 0;

			if (GAME->GetCell(vPos.x, iter) == Enable) move++;
			iter++;
		}
	}
	return Clamp(move, 0, (int)fSpeed);
}

void cPlayer::LineDraw(int prev, int now, bool isX)
{
	int iter, limit;
	if (prev < now)
	{
		iter = prev;
		limit = now;
	}
	else
	{
		limit = prev;
		iter = now;
	}

	if (isX)
	{
		while (iter <= limit)
		{
			if (GAME->GetCell(iter, vPos.y) == Empty)
			{
				isLineDraw = true;
				GAME->LineDraw(iter, vPos.y);
				GAME->SetCell(iter, vPos.y, Cell::Player);
				lineList.push_back(Vec2(iter, vPos.y));
			}
			iter++;
		}
	}
	else
	{
		while (iter <= limit)
		{
			if (GAME->GetCell(vPos.x, iter) == Empty)
			{
				isLineDraw = true;
				GAME->LineDraw(vPos.x, iter);
				GAME->SetCell(vPos.x, iter, Cell::Player);
				lineList.push_back(Vec2(vPos.x, iter));
			}
			iter++;
		}
	}
}

void cPlayer::LineClear()
{
	for (auto iter : lineList)
	{
		GAME->SetCell(iter, Cell::Enable);
		auto obj = ObjAdd(ObjTag::EFFECT, cParticle());
		obj->vPos = iter;
		obj->fSpeed = rand() % 25 + 25;
		obj->vDir = Rot2Vec(rand() % 360);
		GAME->LineList.push_back(iter);
	}
	auto obj1 = ObjAdd(ObjTag::EFFECT, cWaveEffect());
	obj1->vPos = vPos;
	obj1->fSize = (float)(rand() % 50 + 50) / 100;
	obj1->fRot = obj1->fSize * 2;
	obj1->color = Color(0, 1, 0, 1);

	ItemDrop();

	RENDER->Play("Heal");

	lineList.clear();
}

void cPlayer::ItemDrop()
{
	int percent = rand() % 8;
	if (percent == 0)
	{
		RandItem();
	}
}

void cPlayer::RandItem()
{
	int a = rand() % 100;
	if (a >= 0 && a < 40)
		nItem = 1;
	else if (a >= 40 && a < 50)
		nItem = 2;
	else if (a >= 50 && a < 70)
		nItem = 3;
	else if (a >= 70 && a < 85)
	{
		nItem = 4;
		nLimit = 5;
	}
	else if (a >= 85 && a < 95)
	{
		nItem = 5;
		nLimit = 5;
	}
	else if (a >= 95 && a < 100)
	{
		nItem = 6;
		nLimit = 5;
	}

	if (nItem <= 3)
		RENDER->Play("Item", vPos);
	else
		RENDER->Play("Shooting", vPos);
}

void cPlayer::PlayerDead()
{
	auto obj1 = ObjAdd(ObjTag::EFFECT, cWaveEffect());
	obj1->vPos = vPos;
	obj1->fSize = (float)(rand() % 50 + 50) / 100;
	obj1->fRot = obj1->fSize * 2;
	obj1->color = Color(1, 0, 0, 1);
	RENDER->Play("Expl", vPos);

	GAME->nLife--;
	nHp = 500;

	CAMERA->CameraShake(4, 0.5);
	isLineDraw = false;
	int n = rand() % GAME->LineList.size();
	while (GAME->GetCell(GAME->LineList[n]) != Enable)
	{
		n = rand() % GAME->LineList.size();
	}
	vPos = GAME->LineList[n];

	for (int i = 0; i < rand() % 20 + 10; i++)
	{
		auto obj = ObjAdd(ObjTag::EFFECT, cParticle());
		obj->fSpeed = rand() % 25 + 25;
		obj->fSize = (float)(rand() % 15 + 5) / 10;
		obj->vPos = vPos + Rot2Vec(rand() % 360) * (obj->fSpeed);
		obj->color = Green;
		D3DXVec2Normalize(&obj->vDir, &(vPos - obj->vPos));
	}
	auto obj2 = ObjAdd(ObjTag::EFFECT, cWaveEffect());
	obj2->vPos = vPos;
	obj2->fSize = 2;
	obj2->fRot = obj2->fSize * 0.1f;
	obj2->color = Color(0, 1, 0, 1);
	for (auto iter : lineList)
	{
		GAME->SetCell(iter, Cell::Empty);
		GAME->LineDraw(iter, NoColor);
	}
	lineList.clear();
}
