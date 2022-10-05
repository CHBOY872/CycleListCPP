#include <stdio.h>
#include <stdlib.h>
#include "CycleList/CycleList.hpp"

int main() 
{
	CycleList a;
	a.Push(25);
	a.Push(60);
	a.Push(90);
	a.Push(100);
	CycleList::Iterator *it = a.Iterate();
	while(it->More())
		a.InsertTo(&(it->Next()), 42);
	delete it;
	it = a.Iterate();
	while(it->More())
		printf("%d\n", *(it->Next()));
	delete it;
	return 0;
}
