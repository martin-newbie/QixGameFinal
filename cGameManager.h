#pragma once
#include "singleton.h"

enum Cell
{
    Empty,
    Player,
    Enable,
    Disable,
    BossCheck,
    Enemy,

};

enum Boss : int
{
    Carry,
    Wave,
    Divide
};

#define CellX 1024
#define CellY 576

#define Red Color(1,0,0,1)
#define Green Color(0,1,0,1)
#define Blue Color(0,0,1,1)
#define NoColor Color(0,0,0,0)

class cGameManager :
    public singleton<cGameManager>
{
public:
    int Map[CellX + 1][CellY + 1];
    int Stage = Carry;

    int nLife = 5;
    int nPoint = 0;
    int nMasPoint = 3;
    Vec2 BossPos = { 0,0 };
    vector<Vec2> LineList;


    float gMapPercent = 0;
    int FillCount = 0;
    int Score = 0;

    bool isBossSpawn = false;
    bool isBossDead = false;
    bool Next = false;

    texture* Line;
    texture* Stroke;
    vector<texture*> VirusTex;
    vector<texture*> BackTex;
    map<int, string, greater<int>> rank;

    void Init();
    void Update();
    void MapReset();
    void MapPercent();
    void MapCheck(Vec2 pos, int x, int y, bool isBoss, bool isX);
    void LineCheck();
    void Fill(Vec2 pos);
    void Fill(int x, int y);
    void BossFill(Vec2 pos);
    void BossFill(int x, int y);
    void ColorChange(Vec2 pos, bool isFill = false);
    void ColorChange(int x, int y, bool isFill = false);
    void LineDraw(Vec2 pos, Color color = Red);
    void LineDraw(int x, int y, Color color = Red);
    int GetCell(Vec2 pos);
    int GetCell(int x, int y);
    void SetCell(Vec2 pos, Cell cell);
    void SetCell(int x, int y, Cell cell);

    void TexAdd();
};

#define GAME cGameManager::Get()