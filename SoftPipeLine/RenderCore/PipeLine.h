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
	void drawLine(Vector4 ver0, Vector4 ver1);

private:

	/// �Ӵ���
	float mViewPortWidth;

	/// �Ӵ����
	float mViewPortHeight;

	/// �ӿ�ת������
	Matrix4 mViewPortMatrix;

	/// ��Ⱦ�б�
	std::vector<RenderFace> mRenderFaceList;
};

#endif