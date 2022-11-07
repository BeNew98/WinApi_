#pragma once
#include "CLevel.h"

class CTexture; 

enum class EDITOR_MODE
{
    TILE,
    ANIMATION,
    OBJECT,

    NONE,
};

class CEditorLevel :
    public CLevel
{
private:
    HMENU           m_hMenu;
    EDITOR_MODE     m_eMode;
    CTexture*       m_pTex;


public:
    virtual void init() override;
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void render(HDC _dc)override;

private:
    void update();
    void tile_update();
    void animation_update();
    void object_update();
    void CreateUI();

public:
    void SaveTile();
    void LoadTile();

    void LoadAtlas();

public:
    CEditorLevel();
    ~CEditorLevel();
};

