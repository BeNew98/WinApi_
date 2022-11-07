#include "pch.h"
#include "CStartLevel.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CCamera.h"

#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CForce.h"
#include "CPlatform.h"

#include "CResMgr.h"
#include "CKeyMgr.h"


CStartLevel::CStartLevel()
{
}

CStartLevel::~CStartLevel()
{
}

void CStartLevel::init()
{
	// Texture 로딩
	CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\Fighter.bmp");
	CResMgr::GetInst()->LoadTexture(L"tPlane", L"texture\\testFighter.png");

	// Player 생성
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(500.f, 100.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);
		
	/*pObj = pObj->Clone();
	pObj->SetPos(Vec2(700.f, 100.f));
	AddObject(pObj, LAYER::PLAYER);*/

	// Monster 생성
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(Vec2(960.f, 200.f));
	pMonster->SetScale(Vec2(150.f, 150.f));
	pMonster->SetTarget((CPlayer*)pObj);
	AddObject(pMonster, LAYER::MONSTER);
		
	/*pMonster = pMonster->Clone();
	pMonster->SetPos(Vec2(500.f, 500.f));
	AddObject(pMonster, LAYER::MONSTER);*/


	// Level 의 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MONSTER, LAYER::MONSTER);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER_PROJECTILE, LAYER::MONSTER);

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLATFORM);

	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CStartLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		//CCamera::GetInst()->FadeOut(1.f);
		//CCamera::GetInst()->FadeIn(1.f);	
		//CCamera::GetInst()->CameraShake(15.f, 600.f, 0.3f);

		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	if (IsTap(KEY::LBTN))
	{
		//CForce* pForce = new CForce;
		//pForce->SetLifeTime(1.5f);
		//pForce->SetForceScale(200.f);
		//pForce->SetForceRadius(500.f);

		//Vec2 vMousePos = MOUSE_POS;
		//vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
		//Instantiate(pForce, vMousePos, LAYER::FORCE);
	}

	if (IsTap(KEY::RBTN))
	{
		CPlatform* pPlatform = new CPlatform;

		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		Instantiate(pPlatform, vMousePos, LAYER::PLATFORM);
	}
}

void CStartLevel::Enter()
{
	init();
}

void CStartLevel::Exit()
{
	DeleteAllObject();
}
