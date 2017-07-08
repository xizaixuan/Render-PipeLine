/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��Ⱦ����
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _PipeLine_H_
#define _PipeLine_H_

#include "../Math/MathUtil.h"
#include "../Util/Singleton.h"
#include <vector>
#include "RenderFace.h"
#include <windows.h>

class Camera;

class PipeLine : public Singleton<PipeLine>
{
	SINGLETON_DEFINE(PipeLine)
public:
	/// \brief ���캯��
	PipeLine();

	/// \brief ��������
	~PipeLine();

	/// \brief ���ӵ���Ⱦ�б�
	void addToRenderList(RenderFace& face);

	/// \brief ִ����Ⱦ��ˮ��
	void execute(Camera* camera);

	/// \brief �����ӿ���Ϣ
	void setViewPortData(float width, float height);

	/// \brief �����߶�
	void drawLine(Vector4 ver0, Vector4 ver1, DWORD color);

	/// \brief ���Ѳ�����������
	void splitTriangle(RenderFace* triOne, RenderFace* triTwo);

	/// \brief ��դ������
	void rasterizeFace(RenderFace* renderFace);

	/// \brief ��դƽ��������
	void rasterizeTopFace(RenderFace* renderFace);

	/// \brief ��դƽ��������
	void rasterizeBottomFace(RenderFace* renderFace);

	/// \brief �ü�
	void clipFace(Camera* camera);

private:

	/// �Ӵ���
	float mViewPortWidth;

	/// �Ӵ����
	float mViewPortHeight;

	/// �ӿ�ת������
	Matrix4 mViewPortMatrix;

	/// ��Ⱦ�б�
	std::vector<RenderFace> mRenderFaceList;
	std::vector<RenderFace> mRenderFace2List;
	std::vector<RenderFace> mRasterizeList;
};

#endif