#include "pch.h"
#include "CEditorLevel.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CEngine.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CTile.h"

#include "CUI.h"
#include "CPanelUI.h"
#include "CButton.h"
#include "CBackground.h"

#include "resource.h"

void CEditorLevel::init()
{
	// 카메라 시점
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);


	// UI 배치
	//CreateUI();

	// 타일이 사용할 아틀라스 이미지 로딩
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");
	//
	//// 타일 생성
	//CreateTile(10, 10);
	//
	//// 각 타일에다가 사용할 아틀라스 이미지와, 이미지 인덱스를 세팅해준다.
	//const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	//for (size_t i = 0; i < vecTile.size(); ++i)
	//{
	//	((CTile*)vecTile[i])->SetAtlas(pTex);
	//	((CTile*)vecTile[i])->SetImgIdx((int)0);
	//}
}


void CEditorLevel::CreateUI()
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// Button 이 사용할 텍스쳐
	CTexture* pButtonTex = CResMgr::GetInst()->LoadTexture(L"Button", L"texture\\button.bmp");
	CTexture* pButtonPressedTex = CResMgr::GetInst()->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
	CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"Panel", L"texture\\OakUI.bmp");

	// Panel UI
	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetIdleTex(pPanelTex);
	pPanelUI->SetPos(Vec2(vResolution.x - (pPanelTex->Width() + 20.f), 10.f));

	

	// Tile Save 버튼
	CButton* pSaveTileBtn = new CButton;
	pSaveTileBtn->SetScale(Vec2(100.f, 50.f));
	Vec2 vUIPos = Vec2(10.f, 20.f);
	pSaveTileBtn->SetPos(vUIPos);
	pSaveTileBtn->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTile);
	pSaveTileBtn->SetIdleTex(pButtonTex);
	pSaveTileBtn->SetPressedTex(pButtonPressedTex);
		

	// Tile Load 버튼
	CButton* pLoadTileBtn = pSaveTileBtn->Clone();
	pLoadTileBtn->SetPos(Vec2(150.f, 20.f));
	pLoadTileBtn->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTile);
	

	// Save, Load 버튼을 Panel 의 자식으로 추가
	pPanelUI->AddChildUI(pSaveTileBtn);
	pPanelUI->AddChildUI(pLoadTileBtn);

	AddObject(pPanelUI, LAYER::UI);


	CUI* pOtherPanelUI = pPanelUI->Clone();
	pOtherPanelUI->SetPos(Vec2(vResolution.x - (pPanelTex->Width() * 2.f + 20.f), 10.f));
	AddObject(pOtherPanelUI, LAYER::UI);
}