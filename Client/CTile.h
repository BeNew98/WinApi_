#pragma once
#include "CObj.h"

class CTile :
    public CObj
{
private:
    CTexture*       m_pAtlas;
    int             m_iImgIdx;

public:
    void SetAtlas(CTexture* _pAtlas) { m_pAtlas = _pAtlas; }
    void SetImgIdx(int _imgidx);
    void AddImgIdx();

    virtual void tick();
    virtual void render(HDC _dc);
    
    void Save(FILE* _pFile);
    void Load(FILE* _pFile);

public:
    CLONE(CTile);

public:
    CTile();
    ~CTile();
};

