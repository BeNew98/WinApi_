#include "pch.h"
#include "CObj.h"

#include "CEventMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidbody.h"
#include "CFSM.h"

CObj::CObj()
	: m_vPos{}
	, m_vScale{}	
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidbody(nullptr)
	, m_pAI(nullptr)
	, m_bDead(false)
{

}

CObj::CObj(const CObj& _other)
	: CEntity(_other)
	, m_vPos(_other.m_vPos)
	, m_vScale(_other.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidbody(nullptr)
	, m_pAI(nullptr)
	, m_bDead(false)
{
	if (nullptr != _other.m_pCollider)
	{
		m_pCollider = _other.m_pCollider->Clone();
		m_pCollider->SetOwner(this);
	}	

	if (nullptr != _other.m_pAnimator)
	{
		m_pAnimator = _other.m_pAnimator->Clone();
		m_pAnimator->SetOwner(this);
	}	

	if (nullptr != _other.m_pRigidbody)
	{
		m_pRigidbody = _other.m_pRigidbody->Clone();
		m_pRigidbody->SetOwner(this);
	}	

	if (nullptr != _other.m_pAI)
	{
		m_pAI = _other.m_pAI->Clone();
		m_pAI->SetOwner(this);
	}
}

CObj::~CObj()
{
	DEL(m_pCollider);
	DEL(m_pAnimator);
	DEL(m_pRigidbody);
	DEL(m_pAI);
}


void CObj::tick()
{
	if (nullptr != m_pCollider)
		m_pCollider->tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->tick();

	if (nullptr != m_pAI)
		m_pAI->tick();

	if (nullptr != m_pRigidbody)
		m_pRigidbody->tick();
}

void CObj::final_tick()
{
	if (nullptr != m_pRigidbody)
		m_pRigidbody->final_tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->final_tick();

	if (nullptr != m_pAI)
		m_pAI->final_tick();

	if (nullptr != m_pCollider)
		m_pCollider->final_tick();
}

void CObj::render(HDC _dc)
{
	if (nullptr != m_pCollider)
		m_pCollider->render(_dc);

	if (nullptr != m_pAnimator)
		m_pAnimator->render(_dc);	
}


void CObj::CreateCollider()
{
	m_pCollider = new CCollider(this);
}

void CObj::CreateAnimator()
{
	m_pAnimator = new CAnimator(this);
}

void CObj::CreateRigidbody()
{
	m_pRigidbody = new CRigidbody(this);
}

void CObj::CreateAI()
{
	m_pAI = new CFSM(this);
}




void CObj::SetDead()
{
	tEvent evn = {};
	evn.eType = EVENT_TYPE::DELETE_OBJECT;
	evn.wParam = (DWORD_PTR)this;
	CEventMgr::GetInst()->AddEvent(evn);
}