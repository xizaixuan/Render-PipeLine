#include "Camera.h"

Camera::Camera()
	: mFov(0.0f)
	, mAspect(0.0f)
	, mZNear(0.0f)
	, mZFar(0.0f)
	, mPosition(0.0f, 0.0f, 0.0f)
	, mTarget(0.0f, 0.0f, 0.0f)
	, mForward(0.0f, 0.0f, 0.0f)
	, mUp(0.0f, 0.0f, 0.0f)
	, mRight(0.0f, 0.0f, 0.0f)
{
	mView.identity();
	mProj.identity();
}

Camera::~Camera()
{
}

void Camera::update(float lfov, float laspect, float lznear, float lzfar)
{
	mFov	= lfov;
	mAspect	= laspect;
	mZNear	= lznear;
	mZFar	= lzfar;
}

void Camera::update(Vector3 position, Vector3 target)
{
	this->mPosition = position;
	this->mTarget = target;

	buildViewMatrix();

	buildPerspectiveMatrix();
}

void Camera::buildViewMatrix()
{
	// Transform Mat = (MatR * MatT)-1
	Vector3 dir = mTarget - mPosition;

	if (Length(dir) <= epsilon_e3 && Length(dir) >= -epsilon_e3)
	{
	}
	else
	{
		mForward = Normalize(mTarget - mPosition);
	}

	mRight = Normalize(Cross(Vector3(0,1,0), mForward));
	mUp = Normalize(Cross(mForward, mRight));

	Matrix4 matT;
	matT.identity();
	matT.setTranslate(mPosition);

	Matrix4 matR(
		mRight.x,	mRight.y,	mRight.z,	0.0f,
		mUp.x,		mUp.y,		mUp.z,		0.0f,
		mForward.x,	mForward.y,	mForward.z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f);

	Matrix4 invView = matR*matT;
	mView = invView.inverse();
}

void Camera::buildPerspectiveMatrix()
{
	float N = mZNear;
	float F = mZFar;

	float cotFov2 = 1.0f / (tan(AngelToRadian(mFov / 2.0f)));
	float W = 2.0f * N / cotFov2;
	float H = W/mAspect;

	float a = F / (F - N);
	float b = -N*F / (F - N);

	mProj.init(
		2.0f*N/W,	0.0f,		0.0f,	0.0f,
		0.0f,		2.0f*N/H,	0.0f,	0.0f,
		0.0f,		0.0f,		a,		1.0f,
		0.0f,		0.0f,	    b,		0.0f);
}

Matrix4 Camera::GetViewMatrix()
{
	return mView;
}

Matrix4 Camera::GetPerspectiveMatrix()
{
	return mProj;
}