#pragma once
#include "CObj.h"

class CUI :
    public CObj
{
private:    
    vector<CUI*>    m_vecChildUI;
    CUI*            m_pParentUI;
    Vec2            m_vFinalPos;

    CTexture*       m_pIdleTex;

    bool            m_bLbtnDown;
    bool            m_bMouseOn;
    bool            m_bCmrAfctd;

public:
    virtual void tick();
    virtual void render(HDC _dc);

    void render_childUI(HDC _dc);


public:
    void SetIdleTex(CTexture* _pTex);
    void SetCameraAffected(bool _bSet) { m_bCmrAfctd = _bSet; }
    Vec2 GetFinalPos() { return m_vFinalPos; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }

    CUI* GetParentUI() { return m_pParentUI; }
    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

    CTexture* GetIdleTex() { return m_pIdleTex; }

    void AddChildUI(CUI* _pChildUI)
    {
        _pChildUI->m_pParentUI = this;
        m_vecChildUI.push_back(_pChildUI);
    }

    // UI 이벤트 함수
public:
    // 오버라이딩 할 경우 부모함수 호출할 것
    virtual void MouseLbtnDown() { m_bLbtnDown = true; };

    virtual void MouseLbtnClicked() {};

    virtual void MouseOn() {};


private:
    void MouseOnCheck();



public:
    CLONE(CUI);

public:
    CUI();
    CUI(const CUI& _other);
    ~CUI();

    friend class CUIMgr;
};

