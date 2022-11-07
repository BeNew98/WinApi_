#pragma once
#include "CObj.h"

class CTexture;

class CPlayer :
    public CObj
{
private:  
    float       m_fSpeed;   // ¼Ó·Â ( scalar )


public:
    virtual void tick() override;    
    virtual void render(HDC _dc) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    void SetSpeed(float _f)
    {
        m_fSpeed = _f;
    }

public:
    CLONE(CPlayer);

public:
    CPlayer();
    CPlayer(const CPlayer& _other);
    ~CPlayer();
};

