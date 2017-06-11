#include "PipeLine.h"
#include "Camera.h"
#include "..\FrameWork\RenderDevice.h"

/// \brief 构造函数
PipeLine::PipeLine()
	: mViewPortWidth(0)
	, mViewPortHeight(0)
{
}

/// \brief 析构函数
PipeLine::~PipeLine()
{

}

void PipeLine::addToRenderList(RenderFace& face)
{
	mRenderFaceList.push_back(face);
}

void PipeLine::execute(Camera* camera)
{
	Matrix4 viewMat = camera->GetViewMatrix();
	Matrix4 projMat = camera->GetPerspectiveMatrix();
	Matrix4 vp = viewMat*projMat;

	for (auto face:mRenderFaceList)
	{
		RenderFace newFace;
		newFace.v0 = face.v0*vp;
		newFace.v1 = face.v1*vp;
		newFace.v2 = face.v2*vp;

		newFace.v0.homogenous();
		newFace.v1.homogenous();
		newFace.v2.homogenous();

		newFace.v0 = newFace.v0*mViewPortMatrix;
		newFace.v1 = newFace.v1*mViewPortMatrix;
		newFace.v2 = newFace.v2*mViewPortMatrix;

		drawLine(newFace.v0, newFace.v1);
		drawLine(newFace.v0, newFace.v2);
		drawLine(newFace.v1, newFace.v2);
	}
}

void PipeLine::setViewPortData(float width, float height)
{
	mViewPortWidth = width;
	mViewPortHeight = height;

	float alpha = (0.5f*mViewPortWidth - 0.5f);
	float beta  = (0.5f*mViewPortHeight- 0.5f);

	mViewPortMatrix.init(
		alpha,	0,		0, 0,
		0,		beta,	0, 0,
		0,		0,		1, 0,
		alpha,	beta,	0, 1);
}

void PipeLine::drawLine(Vector4 ver0, Vector4 ver1)
{
	int x0 = ver0.x;
	int y0 = ver0.y;
	int x1 = ver1.x;
	int y1 = ver1.y;
	float z0 = 1.0f / (ver0.z + 0.5f);
	float z1 = 1.0f / (ver1.z + 0.5f);

	float dy = y1 - y0;

	//使用DDA算法进行画直线
	float steps;
	if (abs(x1 - x0) > abs(y1 - y0))
		steps = abs(x1 - x0);
	else
		steps = abs(y1 - y0);

	float increx = (float)(x1 - x0) / steps;
	float increy = (float)(y1 - y0) / steps;
	float dzds = (z1 - z0) / steps;

	float xi = x0;
	float yi = y0;
	float zi = z0;

	for (int i = 1; i <= steps; i++)
	{
		// 绘制像素点
		RenderDevice::getSingletonPtr()->drawPixel((int)xi, (int)yi, RGB(255, 255, 255));

		xi += increx;
		yi += increy;
		zi += dzds;
	}
}