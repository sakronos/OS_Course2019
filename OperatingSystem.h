#ifndef _OPERATINGSYSTEM_H_
#define _OPERATINGSYSTEM_H_

#include<queue>
#include "PCB.h"
#include "PhysicalMemory.h"
#include "PhysicalDisk.h"
namespace OS {
	
	class OperatingSystem
	{
	private:
		unsigned int rrslice;		//RR时间片
		
		
	public:
		OperatingSystem();
		~OperatingSystem();
		bool CreateProcess(PCB process);
		PCB allocateMemory(unsigned int pid = 1,		//进程ID
			unsigned int st = 0, unsigned int nt = 0, int pa = 0, int frameNum = 0);
		int RunATimeSlice();
		std::queue<PCB> queue[3];
		Memory memory;
		Disk disk;
		unsigned int pf;			//已完成进程数
		unsigned int time; ;//运行时间
	};

	OperatingSystem::OperatingSystem()
	{
		cout << "系统开始运行"<<endl;
		pf = 0;
		rrslice = 10;
		memory = Memory();
		disk = Disk();
		time = 0;
	}

	OperatingSystem::~OperatingSystem()
	{
	}
	inline bool OperatingSystem::CreateProcess(PCB process)
	{
		queue[0].push(process);
		cout<<"进程"<<process.PID<<"创建成功，进入第1队列"<<endl;
		return true;
	}

	inline PCB OperatingSystem::allocateMemory(unsigned int pid,	//进程ID
		unsigned int st, unsigned int nt, int pa,int frameNum)
	{
		PCB pcb = PCB(pid, st, nt, pa, frameNum);
		for (size_t i = 0; i < 80; i++)			//分配物理内存
		{
			if (memory.memory[i]==0)
			{
				if (memory.memory[i+1]==0)
				{
					if (memory.memory[i + 2] == 0)
					{
						if (memory.memory[i + 3] == 0)
						{
							pcb.frames.push(i);
							pcb.frames.push(i+1);
							pcb.frames.push(i+2);
							pcb.frames.push(i+3);
							memory.memory[i] = 1;
							memory.memory[i + 1] = 1;
							memory.memory[i+2] = 1;
							memory.memory[i+3] = 1;
							break;
						}
					}
				}
			}
		}
		return pcb;
	}

	inline int OperatingSystem::RunATimeSlice()
	{
		//cout <<"当前时间"<< time << endl;
		if (!queue[0].empty())
		{
			
			
			queue[0].front().runtime++;
			
			
			
			if (queue[0].front().needtime== queue[0].front().runtime)
			{
				PCB tmp = queue[0].front();
				queue[0].pop();
				tmp.endtime = tmp.runtime;
				cout << "进程" << tmp.PID << "结束，" << "运行时间" << tmp.runtime << endl;
				return 1;
			}
			else if(queue[0].front().runtime==2)
			{
				PCB tmp = queue[0].front();
				queue[0].pop();
				queue[1].push(tmp);
				cout << "进程" << tmp.PID << "进入第2队列" << endl;
			}
			
			return 0;
		}
		if (!queue[1].empty())
		{
			
			queue[1].front().runtime++;
			//tmp.needtime--;
			
			if (queue[1].front().needtime == queue[1].front().runtime)
			{
				PCB tmp = queue[1].front();
				queue[1].pop();
				tmp.endtime = tmp.runtime;
				cout << "进程" << tmp.PID << "结束，" << "运行时间" << tmp.runtime << endl;
				return 1;
			}
			else if (queue[1].front().runtime==6)
			{
				PCB tmp = queue[1].front();
				tmp.rrtmp = rrslice;
				queue[1].pop();
				queue[2].push(tmp);
				cout << "进程" << tmp.PID << "进入第3队列" << endl;
			}
			
			return 0;
		}
		if (!queue[2].empty())
		{
			
			queue[2].front().runtime++;
			//tmp.needtime--;
			
			queue[2].front().rrtmp--;
			if (queue[2].front().needtime == queue[2].front().runtime)
			{
				PCB tmp = queue[2].front();
				queue[2].pop();
				tmp.endtime = tmp.runtime;
				cout << "进程" << tmp.PID << "结束，" << "运行时间" << tmp.runtime << endl;
				return 1;
			}
			if (queue[2].front().rrtmp==0)
			{
				PCB tmp = queue[2].front();
				tmp.rrtmp = rrslice;
				queue[2].pop();
				queue[2].push(tmp);
			}
			return 0;
		}

		return 0;
	}

}

#endif

