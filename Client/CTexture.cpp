#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"

CTexture::CTexture()
    : m_hBit(nullptr)
    , m_hDC(nullptr)
    , m_tBitmapInfo {}
{
}

CTexture::~CTexture()
{
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);

    //delete m_iImage;
    //ReleaseDC(CEngine::GetInst()->GetMainWnd(), m_hDC);
}


int CTexture::Load(const wstring& _strFilePath)
{
    // Bitmap 로딩
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
    
    // Bitmap 과 연결 시킬 DC 생성
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    m_pBit = (Bitmap*)Image::FromFile(_strFilePath.c_str());   
    return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
    // 별도의 비트맵을 윈도우와 동일한 해상도로 생성시킴    
    m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);

    // 생성시킨 비트맵을 목적지로 하는 DC 를 생성함
    m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

    HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBit);

    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}

void CTexture::Resize(UINT _iWidth, UINT _iHeight)
{
    // 새로운 비트맵과 새로운 DC 를 생성
    HBITMAP hNewBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);    
    HDC hNewDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
    HBITMAP hPrevBit = (HBITMAP)SelectObject(hNewDC, hNewBit);
    DeleteObject(hPrevBit);

    // 기존에 있던 그림을 새로운 곳으로 복사
    BitBlt(hNewDC, 0, 0, m_tBitmapInfo.bmWidth, m_tBitmapInfo.bmHeight, m_hDC, 0, 0, SRCCOPY);

    // 기존 비트맵, DC 를 삭제
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);

    // 새로운 비트맵으로 아이디 대체
    m_hBit = hNewBit;
    m_hDC = hNewDC;

    // 비트맵 정보 갱신
    GetObject(m_hBit, sizeof(BITMAP), &m_tBitmapInfo);
}