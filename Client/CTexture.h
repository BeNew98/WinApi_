#pragma once
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HBITMAP         m_hBit;
    HDC             m_hDC;
    BITMAP          m_tBitmapInfo;

    Bitmap* m_pBit;

public:
    //UINT Width() {  return m_tBitmapInfo.bmWidth; }
    //UINT Height() { return m_tBitmapInfo.bmHeight;}
    HDC GetDC() { return m_hDC; }

    void Resize(UINT _iWidth, UINT _iHeight);

    Bitmap* GetBit() { return m_pBit; }
    UINT Width()  { return m_pBit->GetWidth(); }
    UINT Height() { return m_pBit->GetHeight(); }

private:
    virtual int Load(const wstring& _strFilePath) override;
    void Create(UINT _iWidth, UINT _iHeight);


public:
    CTexture();
    ~CTexture();

    friend class CResMgr;
};

