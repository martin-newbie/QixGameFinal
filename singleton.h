#pragma once
template <typename T>
class singleton
{
public:
	singleton() {}
	virtual ~singleton() {}

	static T* p;
	static T* Get()
	{
	if (!p) p = new T();
		return p;
	}
	static void Del()
	{
		if (p) delete p;
		p = nullptr;
	}
};

template<typename T>
T* singleton<T>::p = nullptr;