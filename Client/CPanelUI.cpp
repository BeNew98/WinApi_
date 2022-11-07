#include "pch.h"
#include "CPanelUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"

CPanelUI::CPanelUI()
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::tick()
{	
	if (IsLbtnDown())
	{
		Vec2 vMove = MOUSE_POS - m_vPressPos;

		Vec2 vPos = GetPos();
		vPos += vMove;
		SetPos(vPos);

		m_vPressPos = MOUSE_POS;
	}	

	CUI::tick();
}

void CPanelUI::render(HDC _dc)
{
	if (nullptr == GetIdleTex())
		return;

	Vec2 vPos = GetPos();

	TransparentBlt(_dc, vPos.x, vPos.y
		, GetIdleTex()->Width()
		, GetIdleTex()->Height()
		, GetIdleTex()->GetDC()
		, 0, 0
		, GetIdleTex()->Width()
		, GetIdleTex()->Height()
		, RGB(255, 0, 255));


	render_childUI(_dc);
}

void CPanelUI::MouseLbtnDown()
{
	CUI::MouseLbtnDown();

	m_vPressPos = MOUSE_POS;
}

void CPanelUI::MouseLbtnClicked()
{
	int a = 0;
}

