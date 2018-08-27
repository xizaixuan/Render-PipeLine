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
	m_View.Identity();
	m_Proj.Identity();
}

Camera::~Camera()
{
}

void Camera::SetParams(float fov, float aspect, float znear, float zfar)
{
	m_Fov	= fov;
	m_Aspect= aspect;
	m_ZNear	= znear;
	m_ZFar	= zfar;

	BuildPerspectiveMatrix();
}

void Camera::SetParams(float3 position, float3 target)
{
	this->m_Position = position;
	this->m_Target = target;

	BuildViewMatrix();
}

void Camera::BuildViewMatrix()
{
	//Transform Mat = (MatR * MatT)-1
	float3 dir = m_Target - m_Position;

	if (MathUtil::Length(dir) <= MathUtil::epsilon && MathUtil::Length(dir) >= -MathUtil::epsilon)
	{

	}
	else
	{
		m_Forward = MathUtil::Normalize(m_Target - m_Position);
	}

	m_Right = MathUtil::Normalize(MathUtil::Cross(float3(0.0f, 1.0f, 0.0f), m_Forward));
	m_Up = MathUtil::Normalize(MathUtil::Cross(m_Forward, m_Right));

	Matrix matT;
	matT.Identity();
	matT.Position(m_Position);

	Matrix matR(
		float4(m_Right.x,	m_Right.y,		m_Right.z,		0.0f), 
		float4(m_Up.x,		m_Up.y,			m_Up.z,			0.0f),
		float4(m_Forward.x, m_Forward.y,	m_Forward.z,	0.0f),
		float4(0.0f,		0.0f,			0.0f,			1.0f));

	Matrix invView = matR*matT;
	m_View = MathUtil::Inverse(invView);
}

void Camera::BuildPerspectiveMatrix()
{
	float N = m_ZNear;
	float F = m_ZFar;

	float cotFov2 = 1.0f / (std::tan(MathUtil::AngelToRadian(m_Fov / 2.0f)));
	float W = 2.0f * N / cotFov2;
	float H = W/m_Aspect;

	float a = F / (F - N);
	float b = -N*F / (F - N);

	m_Proj = Matrix(
		float4(2.0f*N / W,	0.0f,		0.0f,	0.0f),
		float4(0.0f,		2.0f*N / H, 0.0f,	0.0f),
		float4(0.0f,		0.0f,		a,		1.0f),
		float4(0.0f,		0.0f,		b,		0.0f));
}

Matrix Camera::GetViewMatrix()
{
	return m_View;
}

Matrix Camera::GetPerspectiveMatrix()
{
	return m_Proj;
}