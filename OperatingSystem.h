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
		unsigned int time; //运行时间
		void pagedispatch(int n);
		void releaseMemory(PCB* pcb);	//释放占用内存
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
							
							pcb.frames->push(i);
							pcb.frames->push(i+1);
							pcb.frames->push(i+2);
							pcb.frames->push(i+3);
							//cout << pcb.frames->front() << endl;
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
		cout <<"当前时间"<< time << endl;
		if (!queue[0].empty())
		{
			cout << "进程" << queue[0].front().PID << "正在运行" <<",调用逻辑页："<<queue[0].front().page<< endl;
			queue[0].front().runtime++;

			pagedispatch(0);
			

			if (queue[0].front().needtime== queue[0].front().runtime)
			{
				PCB tmp = queue[0].front();
				queue[0].pop();
				tmp.endtime = tmp.runtime;
				cout << "进程" << tmp.PID << "结束，" << "运行时间" << tmp.runtime << "；从队列1中移除" << endl;
				return 1;
			}
			else if(queue[0].front().runtime==2)
			{
				PCB tmp = queue[0].front();
				queue[0].pop();
				queue[1].push(tmp);
				cout << "进程" << tmp.PID << "进入第2队列" << ",运行时间" << tmp.runtime<< endl;
			}
			
			return 0;
		}
		if (!queue[1].empty())
		{
			cout << "进程" << queue[1].front().PID << "正在运行" << ",调用逻辑页：" << queue[1].front().page << endl;
			queue[1].front().runtime++;
			//访问页面
			pagedispatch(1);
			
			if (queue[1].front().needtime == queue[1].front().runtime)
			{
				PCB tmp = queue[1].front();
				queue[1].pop();
				tmp.endtime = tmp.runtime;
				cout << "进程" << tmp.PID << "结束，" << "运行时间" << tmp.runtime << "；从队列2中移除" << endl;
				return 1;
			}
			else if (queue[1].front().runtime==6)
			{
				PCB tmp = queue[1].front();
				tmp.rrtmp = rrslice;
				queue[1].pop();
				queue[2].push(tmp);
				cout << "进程" << tmp.PID << "进入第3队列" << ",运行时间" << tmp.runtime << endl;
			}
			
			return 0;
		}
		if (!queue[2].empty())
		{
			cout << "进程" << queue[2].front().PID << "正在运行" << ",调用逻辑页：" << queue[2].front().page << endl;
			queue[2].front().runtime++;
			//访问页面
			pagedispatch(2);
			
			queue[2].front().rrtmp--;
			if (queue[2].front().needtime == queue[2].front().runtime)
			{
				PCB *tmp = &queue[2].front();
				
				queue[2].pop();
				
				tmp->endtime = tmp->runtime;

				cout << "进程" << tmp->PID << "结束，" << "运行时间" << tmp->runtime << "；从队列3中移除" << endl;

				
				//releaseMemory(tmp);
				
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

	inline void OperatingSystem::pagedispatch(int n)
	{
		//访问页面
		unsigned int framenumber;
		if (queue[n].front().pagetable->tryGet(queue[n].front().page, framenumber))
		{
			queue[n].front().page = memory.block[queue[n].front().pagetable->get(queue[n].front().page)];
		}
		else
		{
			if (queue[n].front().frames->empty())
			{
				queue[n].front().frames->push(queue[n].front().pagetable->returnHead());
			}
			queue[n].front().pagetable->insert(queue[n].front().page, queue[n].front().frames->front());
			queue[n].front().frames->pop();
			memory.block[queue[n].front().pagetable->get(queue[n].front().page)] = disk.disk[queue[n].front().physicalAddress + queue[n].front().page];
			queue[n].front().pagetable->dumpDebug(std::cout << "--> 缺页中断" << std::endl);
			queue[n].front().page = memory.block[queue[n].front().pagetable->get(queue[n].front().page)];
		}
	}

	inline void OperatingSystem::releaseMemory(PCB* pcb)
	{
		for (size_t i = 0; i < 4; i++)
		{
			memory.memory[pcb->frames->front()] = 0;
			cout << pcb->frames->front() << endl;
			pcb->frames->pop();
		}	
	}

}

#endif

