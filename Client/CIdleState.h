#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
private:

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CIdleState);

public:
    CIdleState();
    ~CIdleState();
};

