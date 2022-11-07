#pragma once
#include "CUI.h"

class CEditorLevel;
class CTexture;

typedef void(*TestFuncType)(void);

typedef void(CEntity::*DELEGATE)(void);




class CButton :
    public CUI
{
private:   
    CTexture*       m_pPressedTex;
    CTexture*       m_pHighlightTex;

    // Call Back
    TestFuncType    m_pFunc;

    // Delegate
    CEntity*        m_pInst;
    DELEGATE        m_pDelegateFunc;



public:
    void SetCallBack(TestFuncType _pCallBack) { m_pFunc = _pCallBack; }
    void SetDelegate(CEntity* _pInst, DELEGATE _Func)
    {
        m_pInst = _pInst;
        m_pDelegateFunc = _Func;
    }

public:  
    void SetHighlightTex(CTexture* _pTex) { m_pHighlightTex = _pTex;}
    void SetPressedTex(CTexture* _pTex) { m_pPressedTex = _pTex; }

    virtual void render(HDC _dc);


private:
    virtual void MouseLbtnClicked();

public:
    CLONE(CButton);

public:
    CButton();
    ~CButton();
};

