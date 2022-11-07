#pragma once
#include "CState.h"
class CTraceState :
    public CState
{

private:

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CTraceState);

public:
    CTraceState();
    ~CTraceState();
};

