#ifndef _PHYSICALDISK_H_


#include<string>
using namespace std;


	class Disk
	{
		
	public:
		Disk();
		~Disk();
		int disk[200] = { 0 };
	private:

	};

	Disk::Disk()
	{
		int process1[] = { 1,5,9,5,6,4,2,1,4,6 };
		int process2[] = { 1,5,9,5,6,4,2,1,4,6 };
		int process3[] = { 1,5,9,5,6,4,2,1,4,6 };
		int process4[] = { 1,5,9,5,6,4,2,1,4,6 };
		int process5[] = { 1,5,9,5,6,4,2,1,4,6 };
		memcpy(&disk[5], process1, sizeof(process1));
		memcpy(&disk[31], process2, sizeof(process2));
		memcpy(&disk[150], process3, sizeof(process3));
		memcpy(&disk[65], process4, sizeof(process4));
		memcpy(&disk[113], process5, sizeof(process5));
	}

	Disk::~Disk()
	{
	}
	


#endif

