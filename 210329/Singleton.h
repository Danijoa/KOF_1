#pragma once

template<typename T> 
class Singleton
{
protected:	//�ڽ��� ���� �� �� �ְ�
	static T* instance;	//������ ������ ����~

	Singleton() {};		//private�� �����ڿ� �Ҹ��ڸ� �־�����ν�
	~Singleton() {};	//�ܺο��� �Ҵ� �Ұ��ϰ� ��
public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

template<typename T>
T* Singleton<T>::instance = nullptr;	//�ʱ�ȭ ���� �־�� ��

template<typename T>
inline T* Singleton<T>::GetSingleton()
{
	if (instance == nullptr)	//���� �ѹ��� ����
		instance = new T;
	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	if (instance)	//���� �ѹ��� ����
	{
		delete instance;
		instance = nullptr;
	}
}