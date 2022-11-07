#include "pch.h"
#include "CTraceState.h"

#include "CTimeMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CMonster.h"

CTraceState::CTraceState()
{
}

CTraceState::~CTraceState()
{
}


void CTraceState::finaltick()
{
	// 상태 소유 오브젝트가 몬스터 종류가 아닌 경우
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	// Player 를 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	assert(pPlayer);

	Vec2 vMonPos = pMon->GetPos();
	Vec2 vPlayerPos =  pPlayer->GetPos();

	Vec2 vMonToPlayer = vPlayerPos - vMonPos;
	vMonToPlayer.Normalize();

	float fSpeed = pMon->GetMonInfo().m_fSpeed;

	vMonPos += vMonToPlayer * DT * fSpeed;

	pMon->SetPos(vMonPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
