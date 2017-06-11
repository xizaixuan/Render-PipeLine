/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   渲染管线
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
	/// \brief 构造函数
	PipeLine();

	/// \brief 析构函数
	~PipeLine();

	/// \brief 增加到渲染列表
	void addToRenderList(RenderFace& face);

	/// \brief 执行渲染流水线
	void execute(Camera* camera);

	/// \brief 设置视口信息
	void setViewPortData(float width, float height);

	/// \brief 绘制线段
	void drawLine(Vector4 ver0, Vector4 ver1);

private:

	/// 视窗宽
	float mViewPortWidth;

	/// 视窗宽高
	float mViewPortHeight;

	/// 视口转换矩阵
	Matrix4 mViewPortMatrix;

	/// 渲染列表
	std::vector<RenderFace> mRenderFaceList;
};

#endif