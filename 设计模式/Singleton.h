#pragma once

//����ģʽ ֻ��һ��ȫ�ַ��ʵ� ��֤һ�������һ��ʵ��

class Singleton
{
public:
	
	 virtual ~Singleton();

	 static Singleton* GetInstance();

	 void SingleOp();

	 static void Test();
private:
	Singleton();

	static Singleton *instance;

};

