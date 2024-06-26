#include "pch.h"
#include "func.h"

#include "CEventMgr.h"
#include "CObj.h"

bool IsValid(CObj*& _pTarget)
{
    if (nullptr == _pTarget)
    {
        return false;
    }
    else if (_pTarget->IsDead())
    {
        _pTarget = nullptr;
        return false;
    }    

    return true;
}

void Instantiate(CObj* _pNewObj, Vec2 _vPos, LAYER _eLayer)
{
    _pNewObj->SetPos(_vPos);

    tEvent _evn = {};
    _evn.eType = EVENT_TYPE::CREATE_OBJECT;
    _evn.wParam = (DWORD_PTR)_pNewObj;
    _evn.lParam = (DWORD_PTR)_eLayer;

    CEventMgr::GetInst()->AddEvent(_evn);
}

void ChangeLevel(LEVEL_TYPE _eNextLevel)
{  
    tEvent _evn = {};
    _evn.eType = EVENT_TYPE::LEVEL_CHANGE;
    _evn.wParam = (DWORD_PTR)_eNextLevel;
    CEventMgr::GetInst()->AddEvent(_evn);
}

void Saturate(float& _float)
{
    if (1.f < _float)
        _float = 1.f;
    if (_float < 0.f)
        _float = 0.f;
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
    size_t iLen = _str.length();
    fwrite(&iLen, sizeof(size_t), 1, _pFile);
    fwrite(_str.c_str(), sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
    size_t iLen = 0;
    fread(&iLen, sizeof(size_t), 1, _pFile);

    wchar_t szBuff[256] = {};
    fread(szBuff, sizeof(wchar_t), iLen, _pFile);
    _str = szBuff;
}
