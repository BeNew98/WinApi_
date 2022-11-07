#include "pch.h"
#include "CIdleState.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CMonster.h"

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::finaltick()
{
	// 상태 소유 오브젝트가 몬스터 종류가 아닌 경우
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	// Player 를 알아낸다.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCurLevel->GetLayer(LAYER::PLAYER)[0]);

	assert(pPlayer);	

	// Player 와 Monster 의 거리값을 계산
	float fDetectRange = pMon->GetMonInfo().m_fDetectRange;

	// Player 가 탐지범위 이내에 들어오면 추적상태로 전환
	Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
	if (vDir.Length() < fDetectRange)
	{
 		ChangeState(L"Trace");
	}
}

void CIdleState::Enter()
{

}

void CIdleState::Exit()
{

}