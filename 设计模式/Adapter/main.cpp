#include <iostream>
#include "Adapter.h"
#include "Adaptee.h"
#include "Target.h"

using namespace std;

int main(int argc, char *argv[])
{
	//适配者
	Adaptee * adaptee  = new Adaptee();
	//目标类添加适配器
	Target * tar = new Adapter(adaptee);
	tar->request();
	
	return 0;
}
