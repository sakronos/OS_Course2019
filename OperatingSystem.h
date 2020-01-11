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
		unsigned int rrslice;		//RRʱ��Ƭ
			
	public:
		OperatingSystem();
		~OperatingSystem();
		bool CreateProcess(PCB process);
		PCB allocateMemory(unsigned int pid = 1,		//����ID
			unsigned int st = 0, unsigned int nt = 0, int pa = 0, int frameNum = 0);
		int RunATimeSlice();
		std::queue<PCB> queue[3];
		Memory memory;
		Disk disk;
		unsigned int pf;			//����ɽ�����
		unsigned int time; //����ʱ��
		void pagedispatch(int n);
		void releaseMemory(PCB* pcb);	//�ͷ�ռ���ڴ�
		PCB* currentProcess;
		PCB cP;
		int currentQueueNum = 3;		//�����޽���ʱ��ǰ���к�Ϊ�������ڵģ���4����
	};

	OperatingSystem::OperatingSystem()
	{
		cout << "ϵͳ��ʼ����"<<endl;
		pf = 0;
		rrslice = 10;
		memory = Memory();
		disk = Disk();
		time = 0;
		currentProcess = nullptr;
	}

	OperatingSystem::~OperatingSystem()
	{
	}
	inline bool OperatingSystem::CreateProcess(PCB process)
	{
		queue[0].push(process);
		cout<<"����"<<process.PID<<"�����ɹ��������1����"<<endl;
		return true;
	}

	inline PCB OperatingSystem::allocateMemory(unsigned int pid,	//����ID
		unsigned int st, unsigned int nt, int pa,int frameNum)
	{
		PCB pcb = PCB(pid, st, nt, pa, frameNum);
		for (size_t i = 0; i < 80; i++)			//���������ڴ�
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
							cout << i << "," << i + 1 << "," << i + 2 << "," << i + 3 << "�ѱ�����" << endl;
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
		cout <<"��ǰʱ��"<< time << endl;
		



		//if (!currentProcess)
		//{
		//	if (!queue[0].empty())
		//	{
		//		currentProcess = &queue[0].front();

		//		currentQueueNum = 0;
		//		queue[0].pop();
		//	}
		//	else if (!queue[1].empty())
		//	{
		//		currentProcess = &queue[1].front();

		//		currentQueueNum = 1;
		//		queue[1].pop();
		//	}
		//	else if(!queue[2].empty())
		//	{
		//		currentProcess = &queue[2].front();

		//		currentQueueNum = 2;
		//		queue[2].pop();
		//	}
		//}

		////
		//if (currentQueueNum == 0) {
		//	//No Operation
		//}
		//else if (currentQueueNum == 1) {
		//	if (!queue[0].empty())
		//	{

		//		queue[1].push(*currentProcess);
		//		currentProcess = &queue[0].front();


		//		currentQueueNum = 0;
		//		queue[0].pop();
		//	}
		//}
		//else if (currentQueueNum == 2) {
		//	
		//	if (!queue[0].empty())
		//	{
		//		queue[2].push(*currentProcess);
		//		currentProcess = &queue[0].front();

		//	

		//		currentQueueNum = 0;
		//		queue[0].pop();
		//	}
		//	else if(!queue[1].empty())
		//	{
		//		queue[2].push(*currentProcess);
		//		currentProcess = &queue[1].front();


		//		currentQueueNum = 1;
		//		queue[1].pop();
		//	}

		//}
		//cout << "����" << currentProcess->PID << "��������" << ",�����߼�ҳ��" << currentProcess->page << endl;
		//currentProcess->runtime++;
		//pagedispatch(currentQueueNum);
		//if (currentQueueNum == 2) {
		//	currentProcess->rrtmp--;
		//}
		//if (currentProcess->needtime==currentProcess->runtime)
		//{
		//	currentProcess->endtime = currentProcess->runtime;
		//	cout << "����" << currentProcess->PID << "������" << "����ʱ��" << currentProcess->runtime << "���Ӷ���" << currentQueueNum << "���Ƴ�" << endl;
		//	//Mark
		//	queue[currentQueueNum].pop();
		//	//
		//	releaseMemory(currentProcess);
		//	currentProcess = nullptr;
		//	currentQueueNum = 3;
		//	return 1;
		//}
		//else if (currentQueueNum == 0) {
		//	if (currentProcess->runtime==2)
		//	{
		//		queue[1].push(*currentProcess);
		//		cout << "����" << currentProcess->PID << "�����2����" << ",����ʱ��" << currentProcess->runtime << endl;
		//		currentProcess = nullptr;
		//		currentQueueNum = 3;
		//	}
		//}
		//else if (currentQueueNum==1)
		//{
		//	if (currentProcess->runtime == 6) {
		//		queue[2].push(*currentProcess);
		//		cout << "����" << currentProcess->PID << "�����3����" << ",����ʱ��" << currentProcess->runtime << endl;
		//		currentProcess = nullptr;
		//		currentQueueNum = 3;
		//	}
		//}
		//else if (currentQueueNum == 2) {
		//	if (currentProcess->rrtmp==0)
		//	{
		//		currentProcess->rrtmp = rrslice;
		//		queue[2].push(*currentProcess);
		//		cout << "����" << currentProcess->PID << "��תʱ��Ƭӿ�������²�ص�3����" << endl;
		//		currentProcess = nullptr;
		//		currentQueueNum = 3;
		//	}
		//}





		if (!queue[0].empty())
		{
			cout << "����" << queue[0].front().PID << "��������" <<",�����߼�ҳ��"<<queue[0].front().page<< endl;
			queue[0].front().runtime++;

			pagedispatch(0);
			cout << "�´η���ҳ��" << queue[0].front().page << endl;

			if (queue[0].front().needtime== queue[0].front().runtime)
			{
				PCB tmp = queue[0].front();
				queue[0].pop();
				tmp.endtime = tmp.runtime;
				cout << "����" << tmp.PID << "������" << "����ʱ��" << tmp.runtime << "���Ӷ���1���Ƴ�" << endl;
				releaseMemory(&tmp);
				return 1;
			}
			else if(queue[0].front().runtime==2)
			{
				PCB tmp = queue[0].front();
				queue[0].pop();
				queue[1].push(tmp);
				cout << "����" << tmp.PID << "�����2����" << ",����ʱ��" << tmp.runtime<< endl;
			}
			
			return 0;
		}
		if (!queue[1].empty())
		{
			cout << "����" << queue[1].front().PID << "��������" << ",�����߼�ҳ��" << queue[1].front().page << endl;
			queue[1].front().runtime++;
			//����ҳ��
			pagedispatch(1);
			cout << "�´η���ҳ��" << queue[1].front().page << endl;
			if (queue[1].front().needtime == queue[1].front().runtime)
			{
				PCB tmp = queue[1].front();
				queue[1].pop();
				tmp.endtime = tmp.runtime;
				cout << "����" << tmp.PID << "������" << "����ʱ��" << tmp.runtime << "���Ӷ���2���Ƴ�" << endl;
				releaseMemory(&tmp);
				return 1;
			}
			else if (queue[1].front().runtime==6)
			{
				PCB tmp = queue[1].front();
				//tmp.rrtmp = rrslice;
				queue[1].pop();
				queue[2].push(tmp);
				cout << "����" << tmp.PID << "�����3����" << ",����ʱ��" << tmp.runtime << endl;
				
			}
			
			return 0;
		}
		if (!queue[2].empty())
		{
			cout << "����" << queue[2].front().PID << "��������" << ",�����߼�ҳ��" << queue[2].front().page << endl;
			queue[2].front().runtime++;
			//����ҳ��
			pagedispatch(2);
			cout << "�´η���ҳ��" << queue[2].front().page << endl;
			queue[2].front().rrtmp--;
			if (queue[2].front().needtime == queue[2].front().runtime)
			{
				PCB *tmp = &queue[2].front();
				
				queue[2].pop();
				
				tmp->endtime = tmp->runtime;

				cout << "����" << tmp->PID << "������" << "����ʱ��" << tmp->runtime << "���Ӷ���3���Ƴ�" << endl;

				
				releaseMemory(tmp);
				
				return 1;
			}
			if (queue[2].front().rrtmp==0)
			{
				PCB tmp = queue[2].front();
				tmp.rrtmp = rrslice;
				cout << "����" << tmp.PID << "��תʱ��Ƭӿ�������²����3����" << endl;
				queue[2].pop();
				queue[2].push(tmp);
			}
			return 0;
		}

		return 0;
	}

	inline void OperatingSystem::pagedispatch(int n)
	{
		//����ҳ��
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
			queue[n].front().pagetable->dumpDebug(std::cout << "--> ȱҳ�ж�" << std::endl);
			queue[n].front().page = memory.block[queue[n].front().pagetable->get(queue[n].front().page)];
		}
	}

	inline void OperatingSystem::releaseMemory(PCB* pcb)
	{
		unsigned int blocks[4] = { -1,-1,-1,-1 };
		pcb->pagetable->ClearPageTable(blocks);
		for (size_t i = 0; i < 4; i++)
		{
			if (blocks[i]!=-1)
			{
				memory.memory[blocks[i]] = 0;
				cout << "�ͷŵ�" << blocks[i] << "���ڴ�" << endl;
			}
		}
	}

}

#endif

