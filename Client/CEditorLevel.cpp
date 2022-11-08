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
#include "CButton.h"
#include "CObj.h"

#include "resource.h"


CEditorLevel::CEditorLevel()
	: m_hMenu(nullptr)
	, m_eMode(EDITOR_MODE::ANIMATION)
{
}

CEditorLevel::~CEditorLevel()
{
	if(nullptr != m_hMenu)
		DestroyMenu(m_hMenu);
}


void CEditorLevel::tick()
{
	CLevel::tick();

	if (IsTap(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}

	if (IsTap(KEY::_1))
		m_eMode = EDITOR_MODE::TILE;
	if (IsTap(KEY::_2))
		m_eMode = EDITOR_MODE::ANIMATION;
	if (IsTap(KEY::_3))
		m_eMode = EDITOR_MODE::OBJECT;
	if (IsTap(KEY::_0))
		m_eMode = EDITOR_MODE::NONE;

	update();
}

void CEditorLevel::render(HDC _dc)
{

	if (m_pTex!=nullptr)
	{
		Graphics g(_dc);
		g.DrawImage(m_pTex->GetBit(), 0, 0);
	}	
}

void CEditorLevel::Enter()
{
	// 메뉴바 생성
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
	}
	
	// 메뉴바 추가로 인한 해상도 재 설정
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, m_hMenu);

	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);


	// 초기 오브젝트 설정
	init();
}

void CEditorLevel::Exit()
{
	// 메뉴바 제거
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);

	// 메인 윈도우 크기 재조정
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
}

void CEditorLevel::update()
{
	switch (m_eMode)
	{
	case EDITOR_MODE::TILE:
		tile_update();
		break;
	case EDITOR_MODE::ANIMATION:
		animation_update();
		break;
	case EDITOR_MODE::OBJECT:
		object_update();
		break;
	case EDITOR_MODE::NONE:
		return;
	}
}

void CEditorLevel::tile_update()
{
	if (IsTap(KEY::LBTN))
	{
		// 마우스 위치를 받아와서 실제좌표로 변환	
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f <= vMousePos.x && iCol < (int)GetTileXCount()
			&& 0.f <= vMousePos.y && iRow < (int)GetTileYCount())
		{
			int iIdx = iRow * GetTileXCount() + iCol;
			const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
			((CTile*)vecTile[iIdx])->AddImgIdx();
		}
	}

	if (IsTap(KEY::_8))
	{
		SaveTile();
	}
	else if (IsTap(KEY::_9))
	{
		LoadTile();
	}
}

void CEditorLevel::animation_update()
{
	if (IsTap(KEY::_7))
	{
		LoadAtlas();
	}
	
}

void CEditorLevel::object_update()
{
}

void CEditorLevel::SaveTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";


	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	// 타일 개로 세로 개수 저장
	UINT iTileXCount = GetTileXCount();
	UINT iTileYCount = GetTileYCount();

	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);



	// 각각의 타일 정보 저장
	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadTile()
{	
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;
	

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	// 타일 개로 세로 개수 읽기
	UINT iTileXCount = 0, iTileYCount = 0;

	fread(&iTileXCount, sizeof(UINT), 1, pFile);
	fread(&iTileYCount, sizeof(UINT), 1, pFile);

	// 읽은 개수에 맞게 다시 타일 배치
	CreateTile(iTileXCount, iTileYCount);

	// 배치한 각각의 타일들을 데이터 읽도록
	const vector<CObj*>& vecTile = GetLayer(LAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}

void CEditorLevel::LoadAtlas()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	wstring FinalFileName;
	strTileFolderPath += L"texture\\";
	
	wchar_t FileName[256] = {};

	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = L"ALL\0*.*";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = (LPWSTR)FileName;
	ofn.nMaxFileTitle = 256;
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	FinalFileName += L"texture\\";
	FinalFileName +=FileName;

	m_pTex = CResMgr::GetInst()->LoadTexture(FileName, FinalFileName);

}




// ======================
// Tile Count Dialog Proc
// ======================
INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		if (LOWORD(wParam) == IDOK)
		{
			// Edit Control 에 입력된 숫자를 받아온다.
			int iTileXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			if (!(iTileXCount && iTileYCount))
			{
				MessageBox(nullptr, L"타일 개수를 지정하세요", L"타일 생성 오류", MB_OK);
				return (INT_PTR)TRUE;
			}

			// 지정된 수치로 타일을 새로 생성시킨다.
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			pCurLevel->CreateTile(iTileXCount, iTileYCount);

			// 각 타일에다가 사용할 아틀라스 이미지와, 이미지 인덱스를 세팅해준다.
			CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

			const vector<CObj*>& vecTile = pCurLevel->GetLayer(LAYER::TILE);
			for (size_t i = 0; i < vecTile.size(); ++i)
			{
				((CTile*)vecTile[i])->SetAtlas(pTex);
				((CTile*)vecTile[i])->SetImgIdx(0);
			}


			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}

// ======================
// Anim Tool Dialog Proc
// ======================
INT_PTR CALLBACK Anim_Tool(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		if (LOWORD(wParam) == IDOK|| LOWORD(wParam) == IDCANCEL)
		{
			
			DestroyWindow(hDlg);
			hDlg = NULL;
			return (INT_PTR)TRUE;
		}
		else if(LOWORD(wParam)== IDD_Texture_Key)
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			((CEditorLevel*)pCurLevel)->LoadAtlas();
		}
		break;
	
	}
	return (INT_PTR)FALSE;
}