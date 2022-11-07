#include "pch.h"
#include "CStage01Level.h"

#include "CKeyMgr.h"
#include "CPlayer.h"

CStage01Level::CStage01Level()
{
}

CStage01Level::~CStage01Level()
{
}


void CStage01Level::init()
{
	// Player »ý¼º
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(500.f, 100.f));
	pObj->SetScale(Vec2(100.f, 100.f));

	AddObject(pObj, LAYER::PLAYER);
}

void CStage01Level::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{		
		ChangeLevel(LEVEL_TYPE::START);
	}
}

void CStage01Level::Enter()
{
	init();
}

void CStage01Level::Exit()
{
	DeleteAllObject();
}
