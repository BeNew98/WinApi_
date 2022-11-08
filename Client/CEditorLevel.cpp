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
	// �޴��� ����
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
	}
	
	// �޴��� �߰��� ���� �ػ� �� ����
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, m_hMenu);

	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);


	// �ʱ� ������Ʈ ����
	init();
}

void CEditorLevel::Exit()
{
	// �޴��� ����
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);

	// ���� ������ ũ�� ������
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
		// ���콺 ��ġ�� �޾ƿͼ� ������ǥ�� ��ȯ	
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

	// Ÿ�� ���� ���� ���� ����
	UINT iTileXCount = GetTileXCount();
	UINT iTileYCount = GetTileYCount();

	fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
	fwrite(&iTileYCount, sizeof(UINT), 1, pFile);



	// ������ Ÿ�� ���� ����
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

	// Ÿ�� ���� ���� ���� �б�
	UINT iTileXCount = 0, iTileYCount = 0;

	fread(&iTileXCount, sizeof(UINT), 1, pFile);
	fread(&iTileYCount, sizeof(UINT), 1, pFile);

	// ���� ������ �°� �ٽ� Ÿ�� ��ġ
	CreateTile(iTileXCount, iTileYCount);

	// ��ġ�� ������ Ÿ�ϵ��� ������ �е���
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
			// Edit Control �� �Էµ� ���ڸ� �޾ƿ´�.
			int iTileXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			if (!(iTileXCount && iTileYCount))
			{
				MessageBox(nullptr, L"Ÿ�� ������ �����ϼ���", L"Ÿ�� ���� ����", MB_OK);
				return (INT_PTR)TRUE;
			}

			// ������ ��ġ�� Ÿ���� ���� ������Ų��.
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			pCurLevel->CreateTile(iTileXCount, iTileYCount);

			// �� Ÿ�Ͽ��ٰ� ����� ��Ʋ�� �̹�����, �̹��� �ε����� �������ش�.
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