#pragma once

struct Vec2
{
	float x;
	float y;


public:
	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}

	void Normalize() // 정규화
	{
		float fDist = sqrtf(x * x + y * y);
		x /= fDist;
		y /= fDist;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}



	Vec2 operator +(Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vec2 operator -(Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	void operator -= (Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}




	Vec2 operator / (float _f)
	{
		return Vec2(x / _f, y / _f);
	}

	void operator /= (float _f)
	{
		x /= _f;
		y /= _f;
	}



	Vec2 operator / (Vec2 _vOther)
	{
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	void operator /= (Vec2 _vOther)
	{
		x /= _vOther.x;
		y /= _vOther.y;
	}

	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}



public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec2(UINT _x, UINT _y)
		: x((float)_x), y((float)_y)
	{}

	Vec2(POINT _pt)
		: x ((float)_pt.x)
		, y ((float)_pt.y)
	{

	}

	~Vec2()
	{}
};

struct tEvent
{
	EVENT_TYPE	eType;
	DWORD_PTR	wParam;
	DWORD_PTR	lParam;
};

struct tAnimFrm
{
	Vec2	vLeftTop;	// 이미지 내에서 프레임의 좌상단 위치
	Vec2	vSize;		// 프레임 사이즈
	Vec2	vOffset;	// 추가 이동
	float	fDuration;	// 해당 프레임 노출 시간
};


struct tMonsterInfo
{
	UINT	m_iHP;
	UINT	m_iMaxHP;

	float	m_fAtt;
	float	m_fDef;
	float	m_fAgi;

	float	m_fSpeed;
	float	m_fDetectRange;
	float	m_fAttRange;
};