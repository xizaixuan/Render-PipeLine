#include "MathUtil.h"


template<typename T>
float Length(const T& a)
{
	float length = 0.0f;
	for (auto data : a.M)
	{
		length += data*data;
	}

	return sqrt(length);
}
