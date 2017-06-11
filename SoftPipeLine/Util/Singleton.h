/////////////////////////////////////////////////////////////////////////////////
/// Copyright (C), 2017-2017, xizaixuan. All rights reserved.
/// \brief   ����ģʽ����
/// \author  xizaixuan
/// \date    2017-05
/////////////////////////////////////////////////////////////////////////////////

#ifndef Singleton_H_
#define Singleton_H_

/// \brief �������������е��øú�
#define SINGLETON_DEFINE(classname) friend class Singleton<classname>;

template<typename T>
class Singleton
{
public:
	/// brief ��ȡ����ָ��
	static T* getSingletonPtr()
	{
		static T mSingleton;
		return &mSingleton;
	}

protected:
	/// brief ���캯��
	Singleton(void){}

	/// brief ��������
	~Singleton(void){}
};

#endif