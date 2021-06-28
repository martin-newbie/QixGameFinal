#pragma once
class cObject;
class cCollider
{
public:
	cObject* parent;
	float fRadius;
	set<cObject*> colEnterList;

	void OnCollision(cCollider* col);
};

