#include "DXUT.h"
#include "cObject.h"

void cObject::DestroyCollider()
{
	if (collider)
	{
		COLL->UnRegister(collider);
		collider->colEnterList.clear();
		SAFE_DELETE(collider);
	}
}

void cObject::ColliderSet(float rad, cObject* parent)
{
	collider = new cCollider();
	collider->fRadius = rad;
	collider->parent = parent;
	COLL->Register(collider);
}
