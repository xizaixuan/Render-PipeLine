#include "PipeLine.h"
#include "Camera.h"
#include "..\FrameWork\RenderDevice.h"
#include "Texture.h"

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

	mRasterizeList.clear();
	mRenderFace2List.clear();

	for (auto face:mRenderFaceList)
	{
		RenderFace newFace(face);
		newFace.v0 = face.v0*vp;
		newFace.v1 = face.v1*vp;
		newFace.v2 = face.v2*vp;

		mRenderFace2List.push_back(newFace);
	}

	clipFace(camera);

	for (auto& face: mRasterizeList)
	{
		// ͸�ӳ���
		face.v0.homogenous();
		face.v1.homogenous();
		face.v2.homogenous();

		// �ӿ�ת��
		face.v0 = face.v0*mViewPortMatrix;
		face.v1 = face.v1*mViewPortMatrix;
		face.v2 = face.v2*mViewPortMatrix;

		Vector4 v0 = face.v0;
		Vector4 v1 = face.v1;
		Vector4 v2 = face.v2;

		// ��դ��������
//		rasterizeFace(&face);

		DWORD color = RGB(255, 255, 255);

		if (face.color == 1)
		{
			color = RGB(0, 255, 255);
		}

 		drawLine(v0, v1, color);
		drawLine(v0, v2, color);
 		drawLine(v1, v2, color);
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

void PipeLine::drawLine(Vector4 ver0, Vector4 ver1, DWORD color)
{
	int x0 = ver0.x;
	int y0 = ver0.y;
	int x1 = ver1.x;
	int y1 = ver1.y;
	float z0 = 1.0f / (ver0.z + 0.5f);
	float z1 = 1.0f / (ver1.z + 0.5f);

	float dy = y1 - y0;

	//ʹ��DDA�㷨���л�ֱ��
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
		// �������ص�
		RenderDevice::getSingletonPtr()->drawPixel((int)xi, (int)yi, color);

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
	float z0 = triOne->v0.z;
	float z1 = triOne->v1.z;
	float z2 = triOne->v2.z;

	Vector2 uv0 = triOne->uv0;
	Vector2 uv1 = triOne->uv1;
	Vector2 uv2 = triOne->uv2;

	
	float dy1_0 = y1 - y0;
	float dy2_0 = y2 - y0;
	float dx2_0 = x2 - x0;
	float dz2_0 = z2 - z0;
	Vector2 duv2_0 = (uv2 - uv0);

	// dx(new-0)/dx(2-0) = dy(1-0)/dy(2-0) => newX = 0 + dy(1-0)/dy(2-0)*dx(2-0)
	float newX = x0 + (dy1_0 / dy2_0)*dx2_0;

	// dz(new-0)/dz(2-0) = dy(1-0)/dy(2-0) => newX = 0 + dy(1-0)/dy(2-0)*dz(2-0)
	float newZ = z0 + (dy1_0 / dy2_0)*dz2_0;

	// duv(new-0)/duv(2-0) = dy(1-0)/dy(2-0) => new = 0 + duv(2-0)*dy(1-0)/dy(2-0)
	Vector2 newUV = uv0 + duv2_0*(dy1_0 / dy2_0);

	//////////////////////////////////////////////////////////////////////////
	// ƽ��������
	triOne->v0 = Vector4(x0,	y0, z0, 1);
	triOne->v1 = Vector4(newX,	y1, newZ, 1);
	triOne->v2 = Vector4(x1,	y1, z1, 1);

	triOne->uv0 = uv0;
	triOne->uv1 = newUV;
	triOne->uv2 = uv1;

	//////////////////////////////////////////////////////////////////////////
	// ƽ��������
	triTwo->v0 = Vector4(x1,	y1, z1, 1);
	triTwo->v1 = Vector4(newX,	y1, newZ, 1);
	triTwo->v2 = Vector4(x2,	y2, z2, 1);

	triTwo->uv0 = uv1;
	triTwo->uv1 = newUV;
	triTwo->uv2 = uv2;
}

/// \brief ��դ������
void PipeLine::rasterizeFace(RenderFace* face)
{
	// �� y ���� �������� ʹ v01 <= v1 < = v2
	if (face->v1.y < face->v0.y)
	{
		std::swap(face->v1, face->v0);
		std::swap(face->uv1, face->uv0);
	}
		
	if (face->v2.y < face->v0.y)
	{
		std::swap(face->v2, face->v0);
		std::swap(face->uv2, face->uv0);
	}

	if (face->v2.y < face->v1.y)
	{
		std::swap(face->v2, face->v1);
		std::swap(face->uv2, face->uv1);
	}

	// y0 == y1 ���� ƽ��������
	if (isEqual(face->v0.y, face->v1.y))
	{
		if (face->v1.x < face->v0.x)
		{
			std::swap(face->v1, face->v0);
			std::swap(face->uv1, face->uv0);
		}

		// ƽ��������
		rasterizeTopFace(face);
	}

	// y1 == y2 ����ƽ��������
	else if (isEqual(face->v1.y, face->v2.y))
	{
		if (face->v2.x < face->v1.x)
		{
			std::swap(face->v2, face->v1);
			std::swap(face->uv2, face->uv1);
		}

		// ƽ��������
		rasterizeBottomFace(face);
	}

	// ����������
	else
	{
		RenderFace topFace(*face);

		// ����������
		splitTriangle(face, &topFace);

		// ƽ��������
		if (face->v2.x < face->v1.x)
		{
			std::swap(face->v1, face->v2);
			std::swap(face->uv1, face->uv2);
		}
		rasterizeBottomFace(face);

		// ƽ��������
		if (topFace.v1.x < topFace.v0.x)
		{
			std::swap(topFace.v1, topFace.v0);
			std::swap(topFace.uv1, topFace.uv0);
		}
		rasterizeTopFace(&topFace);
	}
}

void PipeLine::rasterizeTopFace(RenderFace* renderFace)
{
	float x0 = renderFace->v0.x;
	float y0 = renderFace->v0.y;
	float z0 = renderFace->v0.z;

	float x1 = renderFace->v1.x;
	float y1 = renderFace->v1.y;
	float z1 = renderFace->v1.z;

	float x2 = renderFace->v2.x;
	float y2 = renderFace->v2.y;
	float z2 = renderFace->v2.z;

	// ����������Ƿ��˳�Ϊֱ��
	if (((x0 == x1) && (x1 == x2)) || ((y0 == y1) && (y1 == y2)))
		return;

	// ���������εĸ�
	float dy = (y2 - y0);

	float inv_dy = 1.0f / dy;

	// ������б��x����
	float dxdyl = (x2 - x0) * inv_dy;

	// ������б��x����
	float dxdyr = (x2 - x1) * inv_dy;

	// ������б��z����
	float dzdyl = (z2 - z0) * inv_dy;

	// ������б��z����
	float dzdyr = (z2 - z1) * inv_dy;

	// ������б��uv����
	Vector2 duvdyl = (renderFace->uv2 - renderFace->uv0) * inv_dy;

	// ������б��uv����
	Vector2 duvdyr = (renderFace->uv2 - renderFace->uv1) * inv_dy;

	// ����ɨ�������x���յ�x
	float xstart = x0;
	float xend = x1;

	// ����ɨ������ʼy���յ�y
	float ystart = y0;
	float yend = y2;

	// ����ɨ������ʼz���յ�z
	float zstart = z0;
	float zend = z1;

	// ����ɨ����uv��ʼ�㼰�յ�
	Vector2 uvstart = renderFace->uv0;
	Vector2 uvend = renderFace->uv1;

	for (float yi = ystart; yi < yend; yi++)
	{
		float inv_dx = 1.0f / (xend - xstart);
		Vector2 duv = (uvend - uvstart) * inv_dx;
		float dz = (zend - zstart) * inv_dx;

		Vector2 uv = uvstart;

		float z = zstart;

		// ����ɨ����
		for (float xi = xstart; xi < xend; xi++)
		{
			extern Texture* texture;

			DWORD color = texture->getPixel(uv.x, uv.y);
			// �������ص�
			RenderDevice::getSingletonPtr()->drawPixel((int)xi, (int)yi, color, z);

			uv = uv + duv;
			z = z + dz;
		}

		//������һ��ɨ������㼰�յ�
		xstart += dxdyl;
		xend += dxdyr;

		uvstart = uvstart + duvdyl;
		uvend = uvend + duvdyr;

		zstart = zstart + dzdyl;
		zend = zend + dzdyr;
	}
}

void PipeLine::rasterizeBottomFace(RenderFace* renderFace)
{
	float x0 = renderFace->v0.x;
	float y0 = renderFace->v0.y;
	float z0 = renderFace->v0.z;

	float x1 = renderFace->v1.x;
	float y1 = renderFace->v1.y;
	float z1 = renderFace->v1.z;

	float x2 = renderFace->v2.x;
	float y2 = renderFace->v2.y;
	float z2 = renderFace->v2.z;

	// ����������Ƿ��˳�Ϊֱ��
	if (((x0 == x1) && (x1 == x2)) || ((y0 == y1) && (y1 == y2)))
		return;

	// ���������εĸ�
	float dy = (y2 - y0);

	float inv_dy = 1.0f / dy;

	// ������б��x����
	float dxdyl = (x1 - x0) * inv_dy;

	// ������б��x����
	float dxdyr = (x2 - x0) * inv_dy;

	// ������б��z����
	float dzdyl = (z1 - z0) * inv_dy;

	// ������б��z����
	float dzdyr = (z2 - z0) * inv_dy;

	// ������б��uv����
	Vector2 duvdyl = (renderFace->uv1 - renderFace->uv0) * inv_dy;

	// ������б��uv����
	Vector2 duvdyr = (renderFace->uv2 - renderFace->uv0) * inv_dy;

	// ����ɨ�������x���յ�x
	float xstart = x0;
	float xend = x0;

	// ����ɨ������ʼy���յ�y
	float ystart = y0;
	float yend = y2;

	// ����ɨ������ʼy���յ�y
	float zstart = z0;
	float zend = z0;

	// ����ɨ����uv��ʼ�㼰�յ�
	Vector2 uvstart = renderFace->uv0;
	Vector2 uvend = renderFace->uv0;

	for (float yi = ystart; yi < yend; yi++)
	{
		float inv_dx = 1.0f / (xend - xstart);
		Vector2 duv = (uvend - uvstart) * inv_dx;
		float dz = (zend - zstart) * inv_dx;

		Vector2 uv = uvstart;

		float z = zstart;

		// ����ɨ����
		for (float xi = xstart; xi < xend; xi++)
		{
			extern Texture* texture;

			DWORD color = texture->getPixel(uv.x, uv.y);
			// �������ص�
			RenderDevice::getSingletonPtr()->drawPixel((int)xi, (int)yi, color, z);

			uv = uv + duv;

			z = z + dz;
		}

		//������һ��ɨ������㼰�յ�
		xstart += dxdyl;
		xend += dxdyr;

		uvstart = uvstart + duvdyl;
		uvend = uvend + duvdyr;

		zstart = zstart + dzdyl;
		zend = zend + dzdyr;
	}
}

// �������Բ�ֵ
template<class T>
inline T SrFastLerp(const T& a, const T& b, float ratio, float inv_ratio)
{
	return (a * inv_ratio + b * ratio);
}


void PipeLine::clipFace(Camera* camera)
{
	// �ڲ��ü���
	const int CLIP_CODE_GZ = 0x0001;    // z > 1
	const int CLIP_CODE_LZ = 0x0002;    // z < 0
	const int CLIP_CODE_IZ = 0x0004;    // 0 < z < 1

	const int CLIP_CODE_GX = 0x0001;    // x > 1
	const int CLIP_CODE_LX = 0x0002;    // x < -1
	const int CLIP_CODE_IX = 0x0004;    // 1 < x < -1

	const int CLIP_CODE_GY = 0x0001;    // y > 1
	const int CLIP_CODE_LY = 0x0002;    // y < -1
	const int CLIP_CODE_IY = 0x0004;    // -1 < y < 1

	for (auto& face : mRenderFace2List)
	{
		// ���ڴ洢�ü����
		int vertexCode[3]; 

		int vertexCountInView = 0;

		// ����Զ���ü�������޳�
		for (int i = 0; i < 3; i++)
		{
			auto& vertex = face.vertex[i];

			if (vertex.w>=0)
			{
				if (vertex.z > vertex.w)
				{
					vertexCode[i] = CLIP_CODE_GZ;
				}
				else if (vertex.z < 0.0f)
				{
					vertexCode[i] = CLIP_CODE_LZ;
				}
				else
				{
					vertexCountInView++;
					vertexCode[i] = CLIP_CODE_IZ;
				}
			}
			else
			{
				if (vertex.z < vertex.w)
				{
					vertexCode[i] = CLIP_CODE_GZ;
				}
				else if (vertex.z > 0.0f)
				{
					vertexCode[i] = CLIP_CODE_LZ;
				}
				else
				{
					vertexCountInView++;
					vertexCode[i] = CLIP_CODE_IZ;
				}
			}
		}

		// �����Ƿ���ȫ��Զ���ü�����
		if ((vertexCode[0] == CLIP_CODE_GZ) &&
			(vertexCode[1] == CLIP_CODE_GZ) &&
			(vertexCode[2] == CLIP_CODE_GZ) ||

			(vertexCode[0] == CLIP_CODE_LZ) &&
			(vertexCode[1] == CLIP_CODE_LZ) &&
			(vertexCode[2] == CLIP_CODE_LZ))
		{
			continue;
		}

		// ���ݽ��ü�����вü�
		if (((vertexCode[0] | vertexCode[1] | vertexCode[2]) & CLIP_CODE_LZ))
		{
			int v0 = 0;
			int v1 = 0;
			int v2 = 0;

			float minZ = 0.1f;

			// ��������1�������ڽ��ü����ڲ�,2�����������
			if (vertexCountInView == 1)
			{
				// ��һ��:�ҳ�λ���ڲ�Ķ���
				if (vertexCode[0] == CLIP_CODE_IZ)
				{
					v0 = 0; v1 = 1; v2 = 2;
				}
				else if (vertexCode[1] == CLIP_CODE_IZ)
				{
					v0 = 1; v1 = 2; v2 = 0;
				}
				else
				{
					v0 = 2; v1 = 0; v2 = 1;
				}

				//float ratio1 = (face.vertex[v0].w - 0) / (face.vertex[v0].w - face.vertex[v1].w);
				//float ratio2 = (face.vertex[v0].w - 0) / (face.vertex[v0].w - face.vertex[v2].w);

				float ratio1 = (face.vertex[v1].z) / ((face.vertex[v1].z) - (face.vertex[v0].z));
				float ratio2 = (face.vertex[v2].z) / ((face.vertex[v2].z) - (face.vertex[v0].z));

				//float inv_ratio = 1.f - ratio1;
				//face.vertex[v1] = SrFastLerp(face.vertex[v1], face.vertex[v0], ratio1, inv_ratio);

				face.vertex[v1] = face.vertex[v1] + (face.vertex[v0] - face.vertex[v1])*ratio1;

				//inv_ratio = 1.f - ratio2;
				//face.vertex[v2] = SrFastLerp(face.vertex[v2], face.vertex[v0], ratio2, inv_ratio);
				face.vertex[v2] = face.vertex[v2] + (face.vertex[v0] - face.vertex[v2])*ratio2;
			}

			// ��������2�������ڽ��ü����ڲ�,1�����������
			else if (vertexCountInView == 2)
			{
				RenderFace newRenderFace(face);
				Vector4* newVertex = newRenderFace.vertex;

				// �ڶ���:�ҳ�λ�����Ķ���
				if (vertexCode[0] == CLIP_CODE_LZ)
				{
					v0 = 0; v1 = 1; v2 = 2;
				}
				else if (vertexCode[1] == CLIP_CODE_LZ)
				{
					v0 = 1; v1 = 2; v2 = 0;
				}
				else
				{
					v0 = 2; v1 = 0; v2 = 1;
				}

// 				float ratio1 = (0 - face.vertex[v0].w) / (face.vertex[v1].w - face.vertex[v0].w);
// 				float ratio2 = (0 - face.vertex[v0].w) / (face.vertex[v2].w - face.vertex[v0].w);

				float ratio1 = (face.vertex[v0].z) / ((face.vertex[v0].z) - (face.vertex[v1].z));
				float ratio2 = (face.vertex[v0].z) / ((face.vertex[v0].z) - (face.vertex[v2].z));

				//float ratio1 = (face.vertex[v0].w - face.vertex[v0].z) / ((face.vertex[v0].w - face.vertex[v0].z) - (face.vertex[v1].w - face.vertex[v1].z));
				//float ratio2 = (face.vertex[v0].w - face.vertex[v0].z) / ((face.vertex[v0].w - face.vertex[v0].z) - (face.vertex[v2].w - face.vertex[v2].z));
				//float ratio2 = (0 - face.vertex[v0].w) / (face.vertex[v2].w - face.vertex[v0].w);

				face.vertex[v0] = face.vertex[v0] + (face.vertex[v1] - face.vertex[v0])*ratio1;
				//float inv_ratio = 1.f - ratio1;
				//face.vertex[v0] = SrFastLerp(face.vertex[v0], face.vertex[v1], ratio1, inv_ratio);
				
				//inv_ratio = 1.f - ratio2;
				//newVertex[v0] = SrFastLerp(newVertex[v0], newVertex[v1], ratio2, inv_ratio);
				//newVertex[v1] = face.vertex[v0];

				newVertex[v0] = newVertex[v0] + (newVertex[v2] - newVertex[v0])*ratio2;
				newVertex[v1] = face.vertex[v0];

				newRenderFace.color = 1;
				mRasterizeList.push_back(newRenderFace);
			}
		}

		face.color = 0;
		mRasterizeList.push_back(face);
	}
}