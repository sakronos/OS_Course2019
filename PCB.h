#ifndef _PCB_H_
#define _PCB_H_
#include "LRUCache.h"
#include <queue>
using namespace std;
namespace OS {
class PCB
{    
public:
    unsigned int PID;         //进程标志号
    unsigned int starttime;   // 开始执行时间
    unsigned int endtime;    //结束时间
    unsigned int needtime;  // 预计执行时间
    unsigned int runtime;   //已经运行时间
    //unsigned int count;    //计数器
    unsigned int page;         //现场保护区
    unsigned int rrtmp;			//RR剩余时间
    int physicalAddress;        //磁盘地址
    int frameNum;               //磁盘块数
    Cache<int, int> *pagetable; //页表
    queue<int> frames;          //分配的物理地址

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