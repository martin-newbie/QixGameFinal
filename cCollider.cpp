#include "DXUT.h"
#include "cCollider.h"

void cCollider::OnCollision(cCollider* col)
{
	parent->OnCollision(col);
}
