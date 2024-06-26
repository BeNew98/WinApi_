#pragma once

class CObj;
bool IsValid(CObj*& _pTarget);

void Instantiate(CObj* _pNewObj, Vec2 _vPos, LAYER _eLayer);
void ChangeLevel(LEVEL_TYPE _eNextLevel);
void Saturate(float& _float);

void SaveWString(const wstring& _str, FILE* _pFile);
void LoadWString(wstring& _str, FILE* _pFile);
