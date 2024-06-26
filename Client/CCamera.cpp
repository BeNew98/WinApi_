#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CTexture.h"

CCamera::CCamera()
	: m_pBlindTex(nullptr)	
	, m_fRatio(0.f)
	, m_fAccTime(0.f)
	, m_fMaxTime(0.f)
	, m_fRange(0.f)
	, m_fShakeSpeed(0.f)
	, m_bCamShake(false)
{
	POINT ptResolution = CEngine::GetInst()->GetResolution();

	m_pBlindTex = CResMgr::GetInst()->CreateTexture( L"BlindTex", ptResolution.x, ptResolution.y);
}

CCamera::~CCamera()
{

}

void CCamera::tick()
{
	if (IsPressed(KEY::W))
		m_vLook.y -= 300.f * DT;
	if (IsPressed(KEY::S))
		m_vLook.y += 300.f * DT;
	if (IsPressed(KEY::A))
		m_vLook.x -= 300.f * DT;
	if (IsPressed(KEY::D))
		m_vLook.x += 300.f * DT;
	
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vResolution /= 2.f;
	m_vDiff = m_vLook + m_vOffset - vResolution;


	// 카메라 렌더링 효과
	CameraEffect();

	// 카메라 흔들림 효과
	CameraShake();
}

void CCamera::render(HDC _dc)
{
	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = 0;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * m_fRatio);

	if (m_fRatio < 0.001f)
		return;

	AlphaBlend(_dc
		, 0, 0
		, m_pBlindTex->Width()
		, m_pBlindTex->Height()
		, m_pBlindTex->GetDC()
		, 0, 0
		, m_pBlindTex->Width()
		, m_pBlindTex->Height()
		, tBlend);
}

void CCamera::FadeOut(float _fTerm)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_OUT;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;

	m_CamEffectList.push_back(effect);
}

void CCamera::FadeIn(float _fTerm)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_IN;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;

	m_CamEffectList.push_back(effect);
}

void CCamera::CameraShake(float _fRange, float _fShakeSpeed, float _fTerm)
{
	m_fAccTime = 0.f;
	m_fMaxTime = _fTerm;
	m_fRange = _fRange;
	m_fShakeSpeed = _fShakeSpeed;
	m_fShakeDir = 1.f;
	m_bCamShake = true;
}

void CCamera::CameraEffect()
{
	if (m_CamEffectList.empty())
		return;

	tCamEffect& effect = m_CamEffectList.front();

	effect.m_fAccTime += DT;

	if (effect.m_fMaxTime <= effect.m_fAccTime)
	{
		m_CamEffectList.pop_front();
		return;
	}

	m_fRatio = effect.m_fAccTime / effect.m_fMaxTime;
	if (CAMERA_EFFECT::FADE_IN == effect.m_eCurEffect)
		m_fRatio = 1.f - m_fRatio;
}

void CCamera::CameraShake()
{
	if (!m_bCamShake)
		return;

	m_fAccTime += DT;

	if (m_fMaxTime <= m_fAccTime)
	{
		m_bCamShake = false;
		m_vOffset = Vec2(0.f, 0.f);
	}

	m_vOffset.y += DT * m_fShakeSpeed * m_fShakeDir;
	
	if (m_fRange < fabsf(m_vOffset.y))
	{
		m_vOffset.y = m_fRange * m_fShakeDir;
		m_fShakeDir *= -1;		
	}
}
