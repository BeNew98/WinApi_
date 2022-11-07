#pragma once
#include "CObj.h"


class CForce :
    public CObj
{
private:
    float   m_fAccTime;
    float   m_fLifeTime;
    float   m_fForce;       // ÈûÀÇ Å©±â
    float   m_fRadius;      // ÈûÀÇ ¹Ý°æ



public:
    void SetLifeTime(float _fLifeTime) { m_fLifeTime = _fLifeTime; }
    void SetForceScale(float _fScale) { m_fForce = _fScale; }
    void SetForceRadius(float _fRadius) { m_fRadius = _fRadius; }

public:
    void tick();
    void render(HDC _dc);

    CLONE(CForce);

public:
    CForce();
    ~CForce();
};

