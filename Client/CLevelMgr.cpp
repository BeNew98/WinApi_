#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CStartLevel.h"
#include "CStage01Level.h"
#include "CEditorLevel.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		DEL(m_arrLevel[i]);		
	}	
}

void CLevelMgr::init()
{
	// Level ����
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new CStartLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CStage01Level;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CEditorLevel;

	ChangeLevel(LEVEL_TYPE::EDITOR);
}

void CLevelMgr::tick()
{
	m_pCurLevel->tick();
	m_pCurLevel->final_tick();
}

void CLevelMgr::render(HDC _dc)
{
	m_pCurLevel->render(_dc);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _eNext)
{
	// ���� ������ �����Ϸ��� ������ ���� �� ���
	assert(m_pCurLevel != m_arrLevel[(UINT)_eNext]);

	// ���� ������ ���
	if(nullptr != m_pCurLevel)
		m_pCurLevel->Exit();

	m_pCurLevel = m_arrLevel[(UINT)_eNext];

	m_pCurLevel->Enter();
}
