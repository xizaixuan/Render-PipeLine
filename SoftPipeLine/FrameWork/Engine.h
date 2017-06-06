/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   N维向量，向量的基类
/// \author  xizaixuan
/// \date    2017-05
/////////////////////////////////////////////////////////////////////////////////
#ifndef Engine_H_
#define Engine_H_

#include <Windows.h>
#include "../Util/Singleton.h"

class Engine : public Singleton<Engine>
{
	SINGLETON_DEFINE(Engine)
private:
	Engine(void);
	~Engine(void);

public:
	/// \brief 初始化
	void init(HINSTANCE hInstance, int nCmdShow);

	/// \brief 资源销毁
	void destroy();

	/// \brief 更新
	void update(float dt);
};


#endif