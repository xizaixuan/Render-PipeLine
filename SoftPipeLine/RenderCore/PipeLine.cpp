#include "PipeLine.h"
#include "Camera.h"
#include "..\FrameWork\RenderDevice.h"

PipeLine::PipeLine()
	: mViewPortWidth(0)
	, mViewPortHeight(0)
{
}

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

		// 透视除法
		newFace.v0.homogenous();
		newFace.v1.homogenous();
		newFace.v2.homogenous();

		// 视口转换
		newFace.v0 = newFace.v0*mViewPortMatrix;
		newFace.v1 = newFace.v1*mViewPortMatrix;
		newFace.v2 = newFace.v2*mViewPortMatrix;

		Vector4 v0 = newFace.v0;
		Vector4 v1 = newFace.v1;
		Vector4 v2 = newFace.v2;

		// 光栅化三角形
		rasterizeFace(&newFace);

// 		drawLine(v0, v1);
// 		drawLine(v0, v2);
// 		drawLine(v1, v2);
	}
}

void PipeLine::setViewPortData(float width, float height)
{
	mViewPortWidth = width;
	mViewPortHeight= height;

	float alpha = (0.5f*mViewPortWidth - 0.5f);
	float beta  = (0.5f*mViewPortHeight- 0.5f);

	mViewPortMatrix.init(
		alpha,	0,		0, 0,
		0,	   -beta,	0, 0,
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

void PipeLine::splitTriangle(RenderFace* triOne, RenderFace* triTwo)
{
	float x0 = triOne->v0.x;
	float x1 = triOne->v1.x;
	float x2 = triOne->v2.x;
	float y0 = triOne->v0.y;
	float y1 = triOne->v1.y;
	float y2 = triOne->v2.y;

	// dx2x0/dy2y0 = dx1x0/dy1y0 => newX = x0+(dy1y0)*(dx2x0/dy2y0)
	float dy1y0 = y1 - y0;

	float dx2x0 = (x2 - x0);
	float dy2y0 = (y2 - y0);

	// 计算分割点坐标
	float newX = x0 + (dy1y0)*(dx2x0/dy2y0);

	//////////////////////////////////////////////////////////////////////////
	// 平底三角形
	triOne->v0 = Vector4(x0,	y0, 0.0f, 1);
	triOne->v1 = Vector4(newX,	y1, 0.0f, 1);
	triOne->v2 = Vector4(x1,	y1, 0.0f, 1);

	//////////////////////////////////////////////////////////////////////////
	// 平顶三角形
	triTwo->v0 = Vector4(x1,	y1, 0.0f, 1);
	triTwo->v1 = Vector4(newX,	y1, 0.0f, 1);
	triTwo->v2 = Vector4(x2,	y2, 0.0f, 1);
}

/// \brief 光栅三角形
void PipeLine::rasterizeFace(RenderFace* face)
{
	// 在 y 轴上 进行排序 使 v01 <= v1 < = v2
	if (face->v1.y < face->v0.y)
		std::swap(face->v1, face->v0);
	if (face->v2.y < face->v0.y)
		std::swap(face->v2, face->v0);
	if (face->v2.y < face->v1.y)
		std::swap(face->v2, face->v1);

	// y0 == y1 则是 平顶三角形
	if (isEqual(face->v0.y, face->v1.y))
	{
		if (face->v1.x < face->v0.x)
			std::swap(face->v1, face->v0);

		// 平顶三角形
		rasterizeTopFace(face);
	}

	// y1 == y2 则是平底三角形
	else if (isEqual(face->v1.y, face->v2.y))
	{
		if (face->v2.x < face->v1.x)
			std::swap(face->v2, face->v1);

		// 平底三角形
		rasterizeBottomFace(face);
	}

	// 任意三角形
	else
	{
		RenderFace topFace(*face);

		// 分裂三角形
		splitTriangle(face, &topFace);

		// 平底三角形
		if (face->v2.x < face->v1.x)
			std::swap(face->v1.x, face->v2.x);
		rasterizeBottomFace(face);

		// 平顶三角形
		if (topFace.v1.x < topFace.v0.x)
			std::swap(topFace.v1.x, topFace.v0.x);
		rasterizeTopFace(&topFace);
	}
}

void PipeLine::rasterizeTopFace(RenderFace* renderFace)
{
	float x0 = renderFace->v0.x;
	float y0 = renderFace->v0.y;

	float x1 = renderFace->v1.x;
	float y1 = renderFace->v1.y;

	float x2 = renderFace->v2.x;
	float y2 = renderFace->v2.y;

	// 检测三角形是否退出为直线
	if (((x0 == x1) && (x1 == x2)) || ((y0 == y1) && (y1 == y2)))
		return;

	// 计算三角形的高
	float dy = (y2 - y0);

	// 计算左斜边斜率
	float dxdyl = (x2 - x0) / dy;

	// 计算右斜边斜率
	float dxdyr = (x2 - x1) / dy;

	// 设置扫描线起点x及终点x
	float xstart = x0;
	float xend = x1;

	// 设置扫描线起始y及终点y
	float ystart = y0;
	float yend = y2;

	for (float yi = ystart; yi < yend; yi++)
	{
		// 绘制扫描线
		for (float xi = xstart; xi < xend; xi++)
		{
			// 绘制像素点
			RenderDevice::getSingletonPtr()->drawPixel((int)xi, (int)yi, RGB(255, 255, 255));
		}

		//计算下一条扫描线起点及终点
		xstart += dxdyl;
		xend += dxdyr;
	}
}

void PipeLine::rasterizeBottomFace(RenderFace* renderFace)
{
	float x0 = renderFace->v0.x;
	float y0 = renderFace->v0.y;

	float x1 = renderFace->v1.x;
	float y1 = renderFace->v1.y;

	float x2 = renderFace->v2.x;
	float y2 = renderFace->v2.y;

	// 检测三角形是否退出为直线
	if (((x0 == x1) && (x1 == x2)) || ((y0 == y1) && (y1 == y2)))
		return;

	// 计算三角形的高
	float dy = (y2 - y0);

	// 计算左斜边斜率
	float dxdyl = (x1 - x0) / dy;

	// 计算右斜边斜率
	float dxdyr = (x2 - x0) / dy;

	// 设置扫描线起点x及终点x
	float xstart = x0;
	float xend = x0;

	// 设置扫描线起始y及终点y
	float ystart = y0;
	float yend = y2;

	for (float yi = ystart; yi < yend; yi++)
	{
		// 绘制扫描线
		for (float xi = xstart; xi < xend; xi++)
		{
			// 绘制像素点
			RenderDevice::getSingletonPtr()->drawPixel((int)xi, (int)yi, RGB(255, 255, 255));
		}

		//计算下一条扫描线起点及终点
		xstart += dxdyl;
		xend += dxdyr;
	}
}