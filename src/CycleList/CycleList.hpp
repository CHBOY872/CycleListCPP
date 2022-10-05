#ifndef CYCLELIST_HPP_SENTRY
#define CYCLELIST_HPP_SENTRY 

class CycleListCursor;

class CycleList {
	friend class CycleListCursor;

	struct item {
		int val;
		item* next;
		item* prev;
	};
	item *first;
	item *last;
	int len;

public:
	CycleList();
	~CycleList();
	void Push(int val);
	void Pop();
	int GetLen() { return len; }
	class Iterator {
		friend class CycleList;
		CycleList *the_master;
		CycleList::item **first;
		CycleList::item **last;
		bool end;
		Iterator(CycleList *_the_master, 
				 CycleList::item **_first, 
				 CycleList::item **_last)
			: the_master(_the_master), first(_first), last(_last), end(true)
		{}
	
	public:
		~Iterator() {}
		bool More();
		CycleListCursor Next();
		CycleListCursor Prev();	
	};

	Iterator* Iterate() { return new Iterator(this, &first, &last); }
	Iterator* Iterate(int) { return new Iterator(this, &last, &first); }

	CycleListCursor operator[](int idx);
	void InsertTo(CycleListCursor *a, int val);
	void RemoveAt(CycleListCursor *a);

private:
	CycleList(const CycleList&);
};

class CycleListCursor {
	friend class CycleList;
	CycleList* the_master;
	CycleList::item** itm;

public:
	CycleListCursor(CycleList* _the_master, CycleList::item** _itm)
		: the_master(_the_master), itm(_itm) {}
	~CycleListCursor() {}

	operator int*() { return &((*itm)->val); }
	CycleListCursor& operator=(const int &a)
	{
		(*itm)->val = a;
		return *this;
	}
	CycleListCursor* operator&() { return this; }
};

#endif
