#include <boost\version.hpp>
#include <boost\config.hpp>
#include <iostream>
using namespace std;

int main()
{
	cout << "boost 版本:" << BOOST_VERSION << endl;
	cout << "boost lib 版本:" << BOOST_LIB_VERSION << endl;
	cout << "操作系统:" << BOOST_PLATFORM << endl;
	cout << "编译器:" << BOOST_COMPILER << endl;
	cout << "标准库:" << BOOST_STDLIB << endl;
}