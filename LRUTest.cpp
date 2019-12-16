#include "LRUCache.h"
#include "OperatingSystem.h"
using namespace std;
namespace OS
{
	typedef std::string String;
	void test()
	{
		OS::Cache<String, String> cache(3, 0);
		cache.insert("hello", "world");
		cache.insert("foo", "bar");
		cache.dumpDebug(std::cout << "--> After 2 inserts" << std::endl);

		std::cout << "checking refresh : " << cache.get("hello") << std::endl;
		cache.dumpDebug(std::cout << "--> After refeshing oldest key" << std::endl);

		cache.insert("hello1", "world1");
		cache.insert("foo1", "bar1");
		cache.dumpDebug(std::cout << "--> After adding two more" << std::endl);
	}
}

int main(int argc, char** argv)
{
	//OS::test();
	
	int temp = 0;
	OS::OperatingSystem os = OS::OperatingSystem();
	while (true)
	{
		if (os.time == 0) {
			os.CreateProcess(os.allocateMemory(1, os.time, 10, 5, 10));
		}
		if (os.time==1)
		{
			os.CreateProcess(os.allocateMemory(2, os.time, 10, 31, 10));
		}
		if (os.time == 1)
		{
			os.CreateProcess(os.allocateMemory(3, os.time, 10, 150, 10));
		}
		if (os.time == 6)
		{
			os.CreateProcess(os.allocateMemory(4, os.time, 10, 65, 10));
		}
		if (os.time == 10)
		{
			os.CreateProcess(os.allocateMemory(5, os.time, 10, 113, 10));
		}
		temp=os.RunATimeSlice();
		if (temp==1)
		{
			os.pf++;
			temp = 0;
		}

		if (os.pf==5)
		{
			break;
		}
		os.time++;
	}
	
	return 0;
}