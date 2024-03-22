#pragma once

//单例模式 只有一个全局访问点 保证一个类仅有一个实例

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

