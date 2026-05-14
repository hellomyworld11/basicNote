#pragma once

template <typename U> class B;
template<typename T>
class A {
	template<typename> friend class B;
private:
	int data;
};

template<typename U>
class B {
public:
	void callBAF()
	{
		A<int> atempobj;
		atempobj.data = 5;
		std::cout << atempobj.data << std::endl;
	}
};
