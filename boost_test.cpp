#include <boost\version.hpp>
#include <boost\config.hpp>
#include <iostream>
using namespace std;

int main()
{
	cout << "boost �汾:" << BOOST_VERSION << endl;
	cout << "boost lib �汾:" << BOOST_LIB_VERSION << endl;
	cout << "����ϵͳ:" << BOOST_PLATFORM << endl;
	cout << "������:" << BOOST_COMPILER << endl;
	cout << "��׼��:" << BOOST_STDLIB << endl;
}