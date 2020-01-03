#include "LRUCache.h"
#include "OperatingSystem.h"
using namespace std;

int main(int argc, char** argv)
{

	int temp = 0;
	OS::OperatingSystem os = OS::OperatingSystem();
	while (true)
	{
		if (os.time == 0) {
			os.CreateProcess(os.allocateMemory(1, os.time, 6, 5, 10));
		}
		if (os.time==1)
		{
			os.CreateProcess(os.allocateMemory(2, os.time, 25, 31, 10));
		}
		if (os.time == 15)
		{
			os.CreateProcess(os.allocateMemory(3, os.time, 20, 150, 10));
		}
		if (os.time == 6)
		{
			os.CreateProcess(os.allocateMemory(4, os.time, 16, 65, 10));
		}
		if (os.time == 10)
		{
			os.CreateProcess(os.allocateMemory(5, os.time, 10, 113, 10));
		}
		temp=os.RunATimeSlice();
		if (temp==1)
		{
			os.pf++;
			cout << "当前时间" << os.time << endl;
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