#pragma once
#include "CEntity.h"

#include "CFSM.h"
#include "CObj.h"

class CState :
    public CEntity
{
private:
    CFSM*    m_pOwnerAI; // State 를 소유하고 있는 AIComponent

public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    CFSM* GetOwnerAI() { return m_pOwnerAI; }
    CObj* GetOwnerObj() { return m_pOwnerAI->GetOwner(); }

    void ChangeState(const wchar_t* _strStateName);


public:
    CState* Clone() = 0;

public:
    CState();
    ~CState();

    friend class CFSM;
};

