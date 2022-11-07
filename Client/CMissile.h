#pragma once
#include "CObj.h"

class CMissile :
    public CObj
{
private:
    float   m_fSpeed;
    float   m_fDegree;

    float   m_fTime;

    CObj*   m_pTargetObject;


public:
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetDir(float _fDegree) { m_fDegree = _fDegree; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _pOther) override;

    CLONE(CMissile);
public:
    CMissile();
    ~CMissile();
};

