#pragma once


template <typename T>
T max_(T a, T b)
{
	return (a > b) ? a : b;
}

//�ػ�
template<> const char* max_(const char* a, const char* b)
{
	return strcmp(a,b) >= 0 ? a : b;
}

void template_spec()
{
	std::cout << "max: " << max_<int>(1, 3) << std::endl;
	std::cout << "max: " << max_<double>(1.0, 3.0) << std::endl;
	//std::cout << "max: " << max_<double>("aaa", "bbb") << std::endl;  //error ��Ҫ���ػ�
	std::cout << "max: " << max_("aaa", "bbb") << std::endl;
	char s1[] = "xyce", s2[] = "xbv";
	std::cout << "max: " << max_(s1, s2) << std::endl;
}