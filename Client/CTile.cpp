#include "pch.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CTexture.h"

CTile::CTile()
	: m_pAtlas(nullptr)
	, m_iImgIdx(-1)
{

}

CTile::~CTile()
{
}

void CTile::tick()
{

}

void CTile::render(HDC _dc)
{
	if (-1 == m_iImgIdx || m_pAtlas == nullptr)
		return;

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	int iMaxCol = m_pAtlas->Width() / TILE_SIZE;

	int iCurRow = m_iImgIdx / iMaxCol;
	int iCurCol = m_iImgIdx % iMaxCol;

	BitBlt(_dc
		, (int)vPos.x
		, (int)vPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pAtlas->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);

}


void CTile::SetImgIdx(int _imgidx)
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->Width() / TILE_SIZE;
	int iRow = m_pAtlas->Height() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	assert(!(iImgMaxCount <= _imgidx));

	m_iImgIdx = _imgidx;
}

void CTile::AddImgIdx()
{
	assert(m_pAtlas);

	int iCol = m_pAtlas->Width() / TILE_SIZE;
	int iRow = m_pAtlas->Height() / TILE_SIZE;
	int iImgMaxCount = iCol * iRow;

	++m_iImgIdx;

	// 최대 이미지 초과하는 경우, 다시 처음으로...
	if (iImgMaxCount <= m_iImgIdx)
	{
		m_iImgIdx = 0;
	}
}


void CTile::Save(FILE* _pFile)
{
	// 위치
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, _pFile);

	// 아틀라스 이미지 정보
	bool bAtlas = m_pAtlas;
	fwrite(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		// 키값 저장,
		wstring strKey = m_pAtlas->GetKey();
		SaveWString(strKey, _pFile);		

		// 상대경로 저장,
		wstring strRelativePath = m_pAtlas->GetRelativePath();
		SaveWString(strRelativePath, _pFile);
	}

	// 이미지 인덱스
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	// 위치
	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, _pFile);
	SetPos(vPos);

	// 아틀라스 이미지 정보
	bool bAtlas = false;
	fread(&bAtlas, sizeof(bool), 1, _pFile);

	if (bAtlas)
	{
		wstring strKey, strRelativePath;
		LoadWString(strKey, _pFile);
		LoadWString(strRelativePath, _pFile);
		m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	// 이미지 인덱스
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}