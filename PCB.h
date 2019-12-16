#ifndef _PCB_H_
#define _PCB_H_
#include "LRUCache.h"
#include <queue>
using namespace std;
namespace OS {
class PCB
{    
public:
    unsigned int PID;         //���̱�־��
    unsigned int starttime;   // ��ʼִ��ʱ��
    unsigned int endtime;    //����ʱ��
    unsigned int needtime;  // Ԥ��ִ��ʱ��
    unsigned int runtime;   //�Ѿ�����ʱ��
    //unsigned int count;    //������
    unsigned int page;         //�ֳ�������
    unsigned int rrtmp;			//RRʣ��ʱ��
    int physicalAddress;        //���̵�ַ
    int frameNum;               //���̿���
    Cache<int, int> *pagetable; //ҳ��
    queue<int> frames;          //����������ַ

    explicit PCB(unsigned int pid=1, unsigned int st=0,  unsigned int nt=0, int pa=0,int frameNum=0) :PID(pid),starttime(st),needtime(nt),physicalAddress(pa),frameNum(frameNum)
    {
        rrtmp = 0;
        pagetable = new Cache<int, int>(4, 0);
        runtime = 0;
        endtime = 0;
        page = 0;
    }

};
}



#endif