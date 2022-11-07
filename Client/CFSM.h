#pragma once
#include "CComponent.h"


class CState;

class CFSM :
    public CComponent
{
private:
    map<wstring, CState*>   m_mapState;
    CState*                 m_pCurState;

public:
    virtual void tick() override {}
    virtual void final_tick() override;
    virtual void render(HDC _dc) override {}

public:
    void AddState(const wstring& _strKey, CState* _pState);
    CState* FindState(const wstring& _strKey)
    {
        map<wstring, CState*>::iterator iter = m_mapState.find(_strKey);
        if (iter != m_mapState.end())
            return iter->second;
        return nullptr;
    }

    void ChangeState(const wstring& _strStateName);



    CLONE(CFSM);

public:
    CFSM(CObj* _pObj);
    ~CFSM();
};

