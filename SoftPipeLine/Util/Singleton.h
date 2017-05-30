/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017, zhangxuan. All rights reserved.
/// \brief   单例模式基类
/// \author  zhangxuan
/// \version 0.1
/// \date    2017-05
/// \history v0.1 2017/05/28 zhangxuan 第一次添加Singleton
/////////////////////////////////////////////////////////////////////////////////

#ifndef Singleton_H_
#define Singleton_H_

/// \brief 需在子类申明中调用该宏
#define SINGLETON_DEFINE(classname) friend class Singleton<classname>;

template<typename T>
class Singleton
{
public:

	//************************************
	// Method:    getSingletonPtr
	// FullName:  Singleton<T>::getSingletonPtr
	// Access:    public static 
	// Returns:   T*
	// Qualifier:
	//************************************
	static T* getSingletonPtr()
	{
		static T mSingleton;
		return &mSingleton;
	}

protected:
	Singleton(void){}
	~Singleton(void){}
};

#endif