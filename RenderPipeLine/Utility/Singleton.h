/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   单例模式基类
/// \author  xizaixuan
/// \date    2017-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef Singleton_H_
#define Singleton_H_

/// \brief 需在子类申明中调用该宏
#define SINGLETON_DEFINE(classname) friend class Singleton<classname>;

template<typename T>
class Singleton
{
public:
	/// brief 获取单例指针
	static T* getSingletonPtr()
	{
		static T m_Singleton;
		return &m_Singleton;
	}

protected:
	/// brief 构造函数
	Singleton(void){}

	/// brief 析构函数
	~Singleton(void){}
};

#endif