#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"

#include "CMissile.h"
#include "CCollider.h"
#include "CResMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidbody.h"


CPlayer::CPlayer()
	: m_fSpeed(100.f)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidbody();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(80.f, 80.f));

	// Animator 에서 사용할 Image 로딩, // 120, 130	
	CTexture* pLinkTex = CResMgr::GetInst()->LoadTexture(L"LINK", L"texture\\link.bmp");
			
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pLinkTex, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(0.f, -20.f), 10, 0.1f);	
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pLinkTex, Vec2(0.f, 650.f), Vec2(120.f, 130.f), Vec2(0.f, -20.f), 10, 0.1f);
	GetAnimator()->CreateAnimation(L"WALK_UP", pLinkTex, Vec2(0.f, 780.f), Vec2(120.f, 130.f), Vec2(0.f, -20.f), 10, 0.1f);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pLinkTex, Vec2(0.f, 910.f), Vec2(120.f, 130.f), Vec2(0.f, -20.f), 10, 0.1f);

	GetAnimator()->FindAnimation(L"WALK_DOWN")->Save(L"animation\\WALK_DOWN.anim");
	GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\WALK_LEFT.anim");
	GetAnimator()->FindAnimation(L"WALK_UP")->Save(L"animation\\WALK_UP.anim");
	GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\WALK_RIGHT.anim");
		
	/*GetAnimator()->LoadAnimation(L"animation\\WALK_DOWN.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_UP.anim");
	GetAnimator()->LoadAnimation(L"animation\\WALK_RIGHT.anim");*/

	// Rigidbody 설정	
	GetRigidbody()->SetFriction(100.f);
	GetRigidbody()->SetGravity(true);
	GetRigidbody()->SetGravityAccel(800.f);

	GetRigidbody()->SetVelocityLimit(200.f);
	GetRigidbody()->SetGravityVelocityLimit(700.f);

}

CPlayer::CPlayer(const CPlayer& _other)
	: CObj(_other)
	, m_fSpeed(_other.m_fSpeed)
{
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::tick()
{
	if (IsPressed(KEY::LEFT))
	{
		GetRigidbody()->AddForce(Vec2(-300.f, 0.f));		
	}

	if (IsPressed(KEY::RIGHT))
	{
		GetRigidbody()->AddForce(Vec2(300.f, 0.f));
	}

	/*if (IsPressed(KEY::UP))
	{
		GetRigidbody()->AddForce(Vec2(0., -300.f));
	}

	if (IsPressed(KEY::DOWN))
	{
		GetRigidbody()->AddForce(Vec2(0.f, 300.f));
	}*/

	/*if (IsTap(KEY::UP))	
		GetAnimator()->Play(L"WALK_UP", true);
	if (IsTap(KEY::DOWN))
		GetAnimator()->Play(L"WALK_DOWN", true);*/
	if (IsTap(KEY::LEFT))
		GetAnimator()->Play(L"WALK_LEFT", true);
	if (IsTap(KEY::RIGHT))
		GetAnimator()->Play(L"WALK_RIGHT", true);
	

	if (IsTap(KEY::SPACE))
	{
		// 미사일 생성
		/*for (int i = 0; i < 3; ++i)
		{
			CMissile* pMissile = new CMissile;			
			pMissile->SetScale(Vec2(20.f, 20.f));
			pMissile->SetSpeed(400.f);
			pMissile->SetDir(75.f + 15.f * (float)i);

			Instantiate(pMissile, GetPos(), LAYER::PLAYER_PROJECTILE);			
		}*/

		Vec2 V = GetRigidbody()->GetVelocity();

		if (0.f < V.y)
		{
			GetRigidbody()->AddVelocity(Vec2(0.f, -(V.y + 400.f)));
		}		
		else
		{
			GetRigidbody()->AddVelocity(Vec2(0.f, -400.f));
		}
	}


	// 부모 오브젝트의 Tick 도 실행시킨다(Component Tick 호출)
	CObj::tick();
}

void CPlayer::render(HDC _dc)
{
	CObj::render(_dc);
}


void CPlayer::BeginOverlap(CCollider* _pOther)
{
	int a = 0;
}

void CPlayer::OnOverlap(CCollider* _pOther)
{
	int a = 0;
}

void CPlayer::EndOverlap(CCollider* _pOther)
{
	int a = 0;
}
