#pragma once
class cObject
{
public:
	Vec2 vPos;
	Vec2 vSpeed;
	Vec2 vDir = {0,0};
	float fSpeed;
	float fSize = 1;
	float fRot = 0;

	texture* pTex;
	vector<texture*> vTex;

	Color color = Color(1,1,1,1);

	cCollider* collider;
	bool isMove = true;

	int tag;

	bool isDestroy = false;

	string name;

	cObject() {}
	virtual ~cObject() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void OnCollision(cCollider* col) = 0;

	void DestroyCollider();
	void ColliderSet(float rad, cObject* parent);
};

