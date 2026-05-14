#include <iostream>
//#include "非类型模板参数/notypepara.h"
#include "模板中的友元/friendtest.h"

int main()
{
	using namespace std;
	cout << "test template..." << endl;

//	cout << add(10) << endl;
	B<int> b;
	b.callBAF();

	getchar();
	return 0;
}