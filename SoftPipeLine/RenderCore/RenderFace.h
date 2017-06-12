/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ��Ⱦ��Ƭ
/// \author  xizaixuan
/// \date    2017-06
/////////////////////////////////////////////////////////////////////////////////
#ifndef _RenderFace_H_
#define _RenderFace_H_

#include "../Math/MathUtil.h"

class RenderFace
{
public:
	/// \brief ���캯��
	RenderFace();

	/// \brief ���ƹ��캯��
	RenderFace(const RenderFace& face);

	/// \brief ��������
	~RenderFace();

public:
	/// ��Ƭ����������
	Vector4 v0;
	Vector4 v1;
	Vector4 v2;
};

#endif