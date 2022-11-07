#pragma once
#include "CComponent.h"


class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>       m_mapAnim;
    CAnimation*                     m_pCurAnim;
    bool                            m_bRepeat;

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;


public:
    void Play(const wstring& _strName, bool _bRepeat);

    void CreateAnimation(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, int _iMaxFrmCount, float _fDuration);
    CAnimation* FindAnimation(const wstring& _strName);
    CAnimation* LoadAnimation(const wstring& _strRelativePath);

public:
    CLONE(CAnimator);

public:
    CAnimator(CObj* _pOwner);
    CAnimator(const CAnimator& _other);
    ~CAnimator();
};

