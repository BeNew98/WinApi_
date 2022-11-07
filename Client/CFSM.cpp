#include "pch.h"
#include "CFSM.h"

#include "CState.h"


CFSM::CFSM(CObj* _pOwner)
	: CComponent(_pOwner)
	, m_pCurState(nullptr)
{
}

CFSM::~CFSM()
{
	map<wstring, CState*>::iterator iter =  m_mapState.begin();
	for (; iter != m_mapState.end(); ++iter)
	{
		DEL(iter->second);
	}
	m_mapState.clear();
}

void CFSM::final_tick()
{
	if (nullptr == m_pCurState)
		return;

	m_pCurState->finaltick();
}

void CFSM::AddState(const wstring& _strKey, CState* _pState)
{
	m_mapState.insert(make_pair(_strKey, _pState));
	_pState->m_pOwnerAI = this;
}


void CFSM::ChangeState(const wstring& _strStateName)
{
	CState* pNextState = FindState(_strStateName);
	assert(pNextState);

	if (nullptr != m_pCurState)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}