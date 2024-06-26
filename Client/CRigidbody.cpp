#include "pch.h"
#include "CRigidbody.h"

#include "CTimeMgr.h"
#include "CObj.h"


CRigidbody::CRigidbody(CObj* _pOwner)
	: CComponent(_pOwner)
	, m_fMass(1.f)
	, m_fFriction(100.f)
	, m_fFrictionScale(1.f)
	, m_fVelocityLimit(10000.f)
	, m_fGravityVLimit(10000.f)
	, m_bGravityUse(false)
	, m_bGround(false)
{
}

CRigidbody::CRigidbody(const CRigidbody& _other)
	: CComponent(_other)
	, m_vForce(_other.m_vForce)
	, m_vVelocity(_other.m_vVelocity)
	, m_fMass(_other.m_fMass)
	, m_fFriction(_other.m_fFriction)
	, m_fFrictionScale(_other.m_fFrictionScale)
	, m_fVelocityLimit(_other.m_fVelocityLimit)
	, m_fGravityVLimit(_other.m_fGravityVLimit)
	, m_fGravityAccel(_other.m_fGravityAccel)
	, m_bGravityUse(_other.m_bGravityUse)
	, m_bGround(false)
{
}

CRigidbody::~CRigidbody()
{
}

void CRigidbody::tick()	
{	

}

void CRigidbody::final_tick()
{
	// F = M x A
	// 가속도 구하기
	Vec2 vAccel = m_vForce / m_fMass; 

	// 가속도를 이용해서 속도를 증가시킴
	m_vVelocity += vAccel * DT;

	// 중력을 사용하는 경우는, 땅에 있어야 마찰력 적용
	// 중력을 쓰지 않으면 마찰력 바로 적용
	if(m_bGravityUse && m_bGround || !m_bGravityUse)
	{
		// 마찰 가속도
		Vec2 vFriction = -m_vVelocity;
		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT);
		}

		// 속도 감소량(마찰력에 의한) 이 기존 속도를 넘어 설 경우, 완전 제로로 만든다.
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// 현재 속도 반대방향으로 마찰의 의한 속도 감소
			m_vVelocity += vFriction;
		}
	}	

	// 중력 적용 + 공중 상태 ==> 중력
	if (m_bGravityUse && !m_bGround)
	{
		Vec2 vGravityAccel = Vec2(0.f, m_fGravityAccel);
		m_vVelocity += vGravityAccel * DT;
	}


	// 속도 제한 설정(좌, 우)
	// 중력을 사용하는 경우, 좌우 이동과 중력방향(아래) 에 속도제한을 따로 설정한다.
	if (m_bGravityUse)
	{
		if (m_fVelocityLimit < fabsf(m_vVelocity.x))
		{
			m_vVelocity.x = (m_vVelocity.x / fabsf(m_vVelocity.x)) * m_fVelocityLimit;
		}

		if (m_fGravityVLimit < fabsf(m_vVelocity.y))
		{
			m_vVelocity.y = (m_vVelocity.y / fabsf(m_vVelocity.y)) * m_fGravityVLimit;
		}		
	}

	// 중력을 사용하지 않으면, 어느 방향으로든 속도 제한을 건다.
	else
	{
		if (m_fVelocityLimit < m_vVelocity.Length())
		{
			// 제한 속도를 넘겼을 경우
			m_vVelocity.Normalize();
			m_vVelocity *= m_fVelocityLimit;
		}
	}

	// 오브젝트의 위치
	Vec2 vPos = GetOwner()->GetPos();

	// 속도(속력 + 방향) 에 맞게 물체를 이동시킴
	vPos.x += m_vVelocity.x * DT;
	vPos.y += m_vVelocity.y * DT;

	GetOwner()->SetPos(vPos);

	m_vForce = Vec2(0.f, 0.f);
}

void CRigidbody::render(HDC _dc)
{
}

void CRigidbody::SetGround(bool _bGround)
{
	m_bGround = _bGround;

	if (m_bGround)
	{
		m_vVelocity.y = 0.f;
	}
}