#include "CycleList.hpp"

CycleList::CycleList() : first(0), last(0), len(0) {}
CycleList::~CycleList()
{
	while (first != last)
	{
		item *p = first->next;
		delete first;
		first = p;
	}
	delete last;
}

void CycleList::Push(int val)
{
	item *tmp = new item;
	if (!last)
		last = tmp;
	if (!first)
		first = tmp;
	tmp->val = val;
	tmp->next = first;
	tmp->prev = last;
	first->prev = tmp;
	last->next = tmp;
	first = tmp;
	len++;
}

void CycleList::Pop()
{
	item *tmp = first->next;
	delete first;
	first = tmp;
	first->prev = last;
	last->next = first;
	len--;
}

CycleListCursor CycleList::operator[](int idx)
{
	item **p = &first;
	if (idx > 0)
	{
		while (idx)
		{	
			p = &((*p)->next);
			idx--;
		}
	}	
	else if (idx < 0)
	{
		while (idx)
		{
			p = &((*p)->prev);
			idx++;
		}
	}
	return CycleListCursor(this, p);
}

void CycleList::InsertTo(CycleListCursor *a, int val)
{
	item *p = new item;
	item **tmp = a->itm;
	p->val = val;
	p->next = *tmp;
	p->prev = (*tmp)->prev;
	p->prev->next = p;
	p->next->prev = p;
	if (first == *tmp)
		first = p;
	if (last == *tmp)
		last = p;
}

void CycleList::RemoveAt(CycleListCursor *a)
{
	item *tmp = *(a->itm);
	if (first == tmp)
		first = tmp->next;
	if (last == tmp)
		last = tmp->prev;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	delete tmp;
}

///////////////////////////////////////////

bool CycleList::Iterator::More() { return end; }

CycleListCursor CycleList::Iterator::Next()
{
	CycleListCursor tmp(the_master, first);
	if (*first == *last)
		end = false;
	first = &((*first)->next);
	return tmp;
}

CycleListCursor CycleList::Iterator::Prev()
{
	CycleListCursor tmp(the_master, first);
	if (*first == *last)
		end = false;
	first = &((*first)->prev);
	return tmp;
}
