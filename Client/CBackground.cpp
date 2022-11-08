#include "pch.h"
#include "CBackground.h"

#include "CTexture.h"

CBackground::CBackground()
	:m_pTex(nullptr)
{
}

CBackground::~CBackground()
{
}

void CBackground::SetTex(CTexture* _pTex)
{	
	m_pTex = _pTex;

	if (nullptr != m_pTex)
	{
		Vec2 vScale = Vec2((float)m_pTex->Width(), (float)m_pTex->Height());
		SetScale(vScale);
	}	
}

void CBackground::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	Graphics g(_dc);
	//g.DrawImage((Bitmap*)m_pTex->GetBit()
	//	, (int)(vPos.x - m_pTex->GetBit()->GetWidth() / 2.f)
	//	, (int)(vPos.y - m_pTex->GetBit()->GetHeight() / 2.f)
	//	, m_pTex->GetBit()->GetWidth() 
	//	, m_pTex->GetBit()->GetHeight());

	g.DrawImage(m_pTex->GetBit()
		, 0
		, 0);
}
