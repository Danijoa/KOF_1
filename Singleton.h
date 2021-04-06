#pragma once

template<typename T> 
class Singleton
{
protected:	//자식은 접근 할 수 있게
	static T* instance;	//데이터 영역에 저장~

	Singleton() {};		//private에 생성자와 소멸자를 넣어둠으로써
	~Singleton() {};	//외부에서 할당 불가하게 함
public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

template<typename T>
T* Singleton<T>::instance = nullptr;	//초기화 시켜 주어야 함

template<typename T>
inline T* Singleton<T>::GetSingleton()
{
	if (instance == nullptr)	//최초 한번만 생성
		instance = new T;
	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	if (instance)	//최초 한번만 생성
	{
		delete instance;
		instance = nullptr;
	}
}