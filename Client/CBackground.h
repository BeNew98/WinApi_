#pragma once
#include "CObj.h"

class CTexture;

class CBackground :
    public CObj
{
private:
    CTexture* m_pTex;


public:
    void SetTex(CTexture* _pTex);
    
    virtual void render(HDC _dc)override;

public:
    CLONE(CBackground);

public:
    CBackground();
    ~CBackground();
};

