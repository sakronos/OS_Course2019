#ifndef _PHSICALMEMORY_H_


class Memory
{
public:
	Memory();
	~Memory();
	unsigned int memory[80] = {0};
	
private:

};

Memory::Memory()
{
	/*
	模拟内存中已被占用的块
	*/
	for (size_t i = 0; i < 20; i++)
	{
		memory[i] = 1;
	}
	memory[23] = 1;
	memory[33] = 1;
	memory[37] = 1;
	memory[50] = 1;

	
}

Memory::~Memory()
{
}

#endif // !_PHSICALMEMORY_H_