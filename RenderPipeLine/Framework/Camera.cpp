#include "Camera.h"
#include "..\Mathematics\MathUtil.h"

Camera::Camera()
	: m_Fov(0.0f)
	, m_Aspect(0.0f)
	, m_ZNear(0.0f)
	, m_ZFar(0.0f)
	, m_Position(0.0f, 0.0f, 0.0f)
	, m_Target(0.0f, 0.0f, 0.0f)
	, m_Forward(0.0f, 0.0f, 0.0f)
	, m_Up(0.0f, 0.0f, 0.0f)
	, m_Right(0.0f, 0.0f, 0.0f)
{
	m_View.identity();
	m_Proj.identity();
}

Camera::~Camera()
{
}

void Camera::setParams(float lfov, float laspect, float lznear, float lzfar)
{
	m_Fov	= lfov;
	m_Aspect= laspect;
	m_ZNear	= lznear;
	m_ZFar	= lzfar;

	buildPerspectiveMatrix();
}

void Camera::setParams(float3 position, float3 target)
{
	this->m_Position = position;
	this->m_Target = target;

	buildViewMatrix();
}

void Camera::buildViewMatrix()
{
	// Transform Mat = (MatR * MatT)-1
	float3 dir = m_Target - m_Position;

	if (MathUtil::Length(dir) <= MathUtil::EPSILON && MathUtil::Length(dir) >= -MathUtil::EPSILON)
	{

	}
	else
	{
		m_Forward = MathUtil::Normalize(m_Target - m_Position);
	}

	m_Right = MathUtil::Normalize(MathUtil::Cross(float3(0.0f, 1.0f, 0.0f), m_Forward));
	m_Up = MathUtil::Normalize(MathUtil::Cross(m_Forward, m_Right));

	Matrix matT;
	matT.identity();
	//matT.setTranslate(m_Position);

	Matrix matR(
		m_Right.x,	m_Right.y,	m_Right.z,	0.0f,
		m_Up.x,		m_Up.y,		m_Up.z,		0.0f,
		m_Forward.x,	m_Forward.y,	m_Forward.z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f);

	Matrix invView = matR*matT;
	m_View = MathUtil::inverse(invView);
}

void Camera::buildPerspectiveMatrix()
{
	float N = m_ZNear;
	float F = m_ZFar;

	float cotFov2 = 1.0f / (std::tan(MathUtil::AngelToRadian(m_Fov / 2.0f)));
	float W = 2.0f * N / cotFov2;
	float H = W/m_Aspect;

	float a = F / (F - N);
	float b = -N*F / (F - N);

	m_Proj.set(
		2.0f*N/W,	0.0f,		0.0f,	0.0f,
		0.0f,		2.0f*N/H,	0.0f,	0.0f,
		0.0f,		0.0f,		a,		1.0f,
		0.0f,		0.0f,	    b,		0.0f);
}

Matrix Camera::GetViewMatrix()
{
	return m_View;
}

Matrix Camera::GetPerspectiveMatrix()
{
	return m_Proj;
}