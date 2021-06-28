#include "DXUT.h"
#include "cCameraManager.h"

void cCameraManager::Update()
{
	if (isShake)
	{
		fShTimer -= Delta;
		if (fShTimer <= 0)
		{
			isShake = false;
		}
		float x = rand() % 2 == 0 ? fShScale : -fShScale;
		float y = rand() % 2 == 0 ? fShScale : -fShScale;
		vShakePos += Vec2(x, y);
	}
	Lerp(&vShakePos, vShakePos, Vec2(0, 0), 3 * Delta);
	D3DXMatrixTransformation2D(&matView, &vCamPos, 0, &Vec2(fScale, fScale),
		nullptr, 0, &(-vCamPos + Vec2(800, 450) +vShakePos));
}

void cCameraManager::SetTransform()
{
	gDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCameraManager::CameraShake(float s, float t)
{
	isShake = true;
	fShScale = s;
	fShTimer = t;
}

void cCameraManager::ZoomIn(Vec2 pos, float s)
{
	Lerp(&vCamPos, vCamPos, pos, 3 * Delta);
	Lerp(&fScale, fScale, s, 3 * Delta);
}

void cCameraManager::ZoomOut()
{
	Lerp(&vCamPos, vCamPos, Vec2(800,450), 3 * Delta);
	Lerp(&fScale, fScale, 1.f, 3 * Delta);
}
