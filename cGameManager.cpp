#include "DXUT.h"
#include "cGameManager.h"

void cGameManager::Init()
{
    srand(time(NULL));
    TexAdd();

    rank.insert(make_pair(-1, "PHS"));
    rank.insert(make_pair(-2, "BTS"));
    rank.insert(make_pair(-3, "LAC"));
    rank.insert(make_pair(-4, "KDJ"));
    rank.insert(make_pair(-9999, "IAU"));
    nPoint = 0;
    MapReset();
}

void cGameManager::Update()
{
    if (KeyDown(VK_F9))
        GAME->nPoint = GAME->nMasPoint;
    if(KeyDown(VK_F10))
        SCENE->ChangeScene("Title");
}

void cGameManager::MapReset()
{
    for (int i = 0; i <= CellX; i++)
    {
        for (int j = 0; j <= CellY; j++)
        {
            Map[i][j] = Cell::Empty;
            LineDraw(i + 288, j + 162, NoColor);
            ColorChange(i + 288, j + 162, true);
        }
    }

    for (int i = 0; i <= CellX; i++)
    {
        Map[i][0] = Cell::Enable;
        Map[i][576] = Cell::Enable;
        LineList.push_back(Vec2(i + 288, 162));
        LineList.push_back(Vec2(i + 288, CellY+162));
    }

    for (int j = 0; j <= CellY; j++)
    {
        Map[0][j] = Cell::Enable;
        Map[1024][j] = Cell::Enable;
        LineList.push_back(Vec2(288, 162 + j));
        LineList.push_back(Vec2(CellX + 288, 162 + j));
    }

    gMapPercent = 0;
}

void cGameManager::MapPercent()
{
    float n = 0;
    for (int i = 0; i <= CellX; i++)
    {
        for (int j = 0; j <= CellY; j++)
        {
            if (GetCell(i, j) == Cell::Disable)
                n++;
        }
    }
    gMapPercent = n * 100 / ((CellX + 1) * (CellY + 1));
}

void cGameManager::MapCheck(Vec2 pos, int x, int y, bool isBoss, bool isX)
{
    if (!isBoss)
    {
        BossFill(pos.x + x, pos.y + y);
        if (isX) y *= -1;
        else x *= -1;
        Fill(pos.x + x, pos.y + y);
        MapPercent();
        LineCheck();
        Score += (rand() % 20 + 10) * FillCount;
        FillCount = 0;
    }
    else
    {
        Fill(pos.x + x, pos.y + y);
        MapPercent();
        LineCheck();
        Score += (rand() % 20 + 10) * FillCount;
        FillCount = 0;
    }
}

void cGameManager::LineCheck()
{
    for (auto iter : LineList)
    {
        if (iter == OBJECT->GetPlayer()->vPos) goto CON;
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (GetCell(iter.x + i, iter.y + j) == Cell::Empty) goto CON;
            }
        }
        SetCell(iter, Cell::Disable);
        ColorChange(iter);
        LineDraw(iter, NoColor);
    CON:
        continue;
    }
}

void cGameManager::Fill(Vec2 pos)
{
	if (GetCell(pos) != Cell::Empty &&
		GetCell(pos) != Cell::BossCheck) return;
	SetCell(pos, Cell::Disable);
	ColorChange(pos);
    FillCount++;
	Fill(Vec2(pos.x + 1, pos.y));
	Fill(Vec2(pos.x - 1, pos.y));
	Fill(Vec2(pos.x, pos.y + 1));
	Fill(Vec2(pos.x, pos.y - 1));
}

void cGameManager::Fill(int x, int y)
{
    if (GetCell(x,y) != Cell::Empty &&
        GetCell(x, y) != Cell::BossCheck) return;
    SetCell(x, y, Cell::Disable);
    ColorChange(x, y);
    FillCount++;
    Fill(x + 1, y);
    Fill(x - 1, y);
    Fill(x, y + 1);
    Fill(x, y - 1);
}

void cGameManager::BossFill(Vec2 pos)
{
    if (GetCell(pos) != Cell::BossCheck) return;
    SetCell(pos, Cell::Empty);
    BossFill(Vec2(pos.x + 1, pos.y));
    BossFill(Vec2(pos.x - 1, pos.y));
    BossFill(Vec2(pos.x, pos.y + 1));
    BossFill(Vec2(pos.x, pos.y - 1));
}

void cGameManager::BossFill(int x, int y)
{
    if (GetCell(x, y) != Cell::BossCheck) return;
    SetCell(x, y, Cell::Empty);
    BossFill(x + 1, y);
    BossFill(x - 1, y);
    BossFill(x, y + 1);
    BossFill(x, y - 1);
}

void cGameManager::ColorChange(Vec2 pos, bool isFill)
{
    pos -= Vec2(288, 162);
    D3DLOCKED_RECT lr;
    if (SUCCEEDED(VirusTex[Stage]->tex->LockRect(0, &lr, nullptr, D3DLOCK_DISCARD)))
    {
        DWORD* texColor = (DWORD*)lr.pBits;
        int i = pos.y * VirusTex[Stage]->info.Width + pos.x;
        D3DXCOLOR a = texColor[i];
        a.a = isFill;
        texColor[i] = a;
        VirusTex[Stage]->tex->UnlockRect(0);
    }
}

void cGameManager::ColorChange(int x, int y, bool isFill)
{
    x -= 288;
    y -= 162;
    D3DLOCKED_RECT lr;
    if (SUCCEEDED(VirusTex[Stage]->tex->LockRect(0, &lr, nullptr, D3DLOCK_DISCARD)))
    {
        DWORD* texColor = (DWORD*)lr.pBits;
        int i = y * VirusTex[Stage]->info.Width + x;
        D3DXCOLOR a = texColor[i];
        a.a = isFill;
        texColor[i] = a;
        VirusTex[Stage]->tex->UnlockRect(0);
    }
}

void cGameManager::LineDraw(Vec2 pos, Color color)
{
    pos -= Vec2(288, 162);
    D3DLOCKED_RECT lr;
    if (SUCCEEDED(Line->tex->LockRect(0, &lr, nullptr, D3DLOCK_DISCARD)))
    {
        DWORD* texColor = (DWORD*)lr.pBits;
        int i = pos.y * Line->info.Width + pos.x;
        texColor[i] = color;
        Line->tex->UnlockRect(0);
    }
}

void cGameManager::LineDraw(int x, int y, Color color)
{
    x -= 288;
    y -= 162;
    D3DLOCKED_RECT lr;
    if (SUCCEEDED(Line->tex->LockRect(0, &lr, nullptr, D3DLOCK_DISCARD)))
    {
        DWORD* texColor = (DWORD*)lr.pBits;
        int i = y * Line->info.Width + x;
        texColor[i] = color;
        Line->tex->UnlockRect(0);
    }
}

int cGameManager::GetCell(Vec2 pos)
{
    return Map[Clamp((int)pos.x - 288 , 0, 1024)][Clamp((int)pos.y - 162, 0, 576)];
}

int cGameManager::GetCell(int x, int y)
{
    return Map[Clamp(x - 288, 0, 1024)][Clamp(y - 162, 0, 576)];
}

void cGameManager::SetCell(Vec2 pos, Cell cell)
{
    Map[Clamp((int)pos.x - 288, 0, 1024)][Clamp((int)pos.y - 162, 0, 576)] = cell;
}

void cGameManager::SetCell(int x, int y, Cell cell)
{
    Map[Clamp(x - 288, 0, 1024)][Clamp(y - 162, 0, 576)] = cell;
}

void cGameManager::TexAdd()
{
    VirusTex = RENDER->VecTexture("Virus", 3);
    BackTex = RENDER->VecTexture("Back", 3);
    Stroke = RENDER->GetTexture("Stroke");
    Line = RENDER->GetTexture("Line");
}
