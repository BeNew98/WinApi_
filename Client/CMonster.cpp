#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CFSM.h"
#include "CIdleState.h"
#include "CTraceState.h"

CMonster::CMonster()
	: m_iHP(3)
	, m_pTarget(nullptr)
	, m_pTex(nullptr)
	, m_tInfo{}
{
	CreateCollider();
	CreateAI();

	// 충돌체 설정
	GetCollider()->SetScale(Vec2(100.f, 100.f));
	m_pTex = CResMgr::GetInst()->LoadTexture(L"tPlane",L"testFighter.png");


	m_tInfo.m_fSpeed = 100.f;
	m_tInfo.m_fDetectRange = 300.f;

	// AI 설정
	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);

	GetAI()->ChangeState(L"Idle");
}

CMonster::~CMonster()
{
}

void CMonster::tick()
{	
	/*if (IsValid(m_pTarget))
	{
		Vec2 vTargetPos = m_pTarget->GetPos();
		m_pTarget->SetName(L"Player");
		Vec2 vPos = GetPos();

		Vec2 vDir = vTargetPos - vPos;
		vDir.Normalize();

		vPos.x += vDir.x * 100.f * DT;
		vPos.y += vDir.y * 100.f * DT;

		SetPos(vPos);
	}*/

	CObj::tick();
}

void CMonster::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vSize = GetScale();
	

	static float fRatio = 0.f;
	static float Dir = 1.f;
	fRatio += DT * Dir * 8.f;

	if (1.f < fRatio)
	{
		fRatio = 1.f;
		Dir = -1.f;		
	}
	else if (fRatio < 0.f)
	{
		fRatio = 0.f;
		Dir = 1;
	}

	BLENDFUNCTION tBlend = {};
	
	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * fRatio);
	
	AlphaBlend(_dc
		, (int)(vPos.x - m_pTex->Width() / 2.f)
		, (int)(vPos.y - m_pTex->Height() / 2.f)
		, m_pTex->Width()
		, m_pTex->Height()
		, m_pTex->GetDC()
		, 0, 0	  
		, m_pTex->Width()
		, m_pTex->Height()
		, tBlend);

	Graphics g(_dc);
	//g.DrawImage((Bitmap*)m_pTex->GetBit()
	//	, (int)(vPos.x - m_pTex->GetBit()->GetWidth() / 2.f)
	//	, (int)(vPos.y - m_pTex->GetBit()->GetHeight() / 2.f)
	//	, m_pTex->GetBit()->GetWidth() 
	//	, m_pTex->GetBit()->GetHeight());

	g.DrawImage(m_pTex->GetBit()
		, (int)(vPos.x - m_pTex->Width() / 2.f)
		, (int)(vPos.y - m_pTex->Height() / 2.f));

	CObj::render(_dc);
}

void CMonster::BeginOverlap(CCollider* _pOther)
{
	SetDead();
}
