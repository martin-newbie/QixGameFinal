#pragma once
#include "singleton.h"
class cCameraManager :
    public singleton<cCameraManager>
{
public:
    void Update();
    void SetTransform();
    void CameraShake(float s, float t);
    void ZoomIn(Vec2 pos, float s);
    void ZoomOut();


    Vec2 vCamPos = {800, 450};
    Vec2 vShakePos;
    float fScale = 1;
    float fShScale;
    float fShTimer;
    bool isShake = false;

    Mat matView;

    Mat GetMat()
    {
        Mat mat;
        D3DXMatrixInverse(&mat, 0, &matView);
        return mat;
    }

};

#define CAMERA cCameraManager::Get()