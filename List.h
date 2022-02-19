#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#define LOX printf("%d\n", __LINE__);

static const int START_LIST_CAPACITY = 10;

namespace lst
{
	using namespace std;

	template <typename T> class List
	{
	public:
		List(size_t _capacity = START_LIST_CAPACITY);
		~List();
		void Dump();
		void GraphDump(const char * const graphname = "graph");
		int PushBack(const T& value);
		int PushFront(const T& value);
		int Insert(int index, const T& value);
		T Delete(int index);
		T Show(int index);
		T PopFront();
		T PopBack();
		void Sorting();
		int TranslateIndex(int logic_index);

	private:
		int* Prev;
		T* Data;
		int* Next;
		int free;
		int head;
		int tail;
		size_t size;
		size_t capacity;
		void ListResize();
		inline int CheckValidInsertIndex(int index);
		inline int CheckValidDeleteIndex(int index);
	};

	template <typename T>			 List<typename T>::List					(size_t _capacity)
	{
		Prev = (int*)malloc(_capacity * sizeof(int));
		Data =   (T*)calloc(_capacity,  sizeof(T));
		Next = (int*)malloc(_capacity * sizeof(int));

		assert(Prev);
		assert(Data);
		assert(Next);

		free = 1;
		head = 0;
		tail = 0;
		size = 0;
		capacity = _capacity;

		Prev[0] = 0;
		Prev[1] = -1;
		Next[0] = 0;
		Next[1] = -2;
		for (int i = 2; i < capacity; i++)
		{
			Prev[i] = -1;
			Next[i] = Next[i - 1] - 1;

		}
	}

	template <typename T>			 List<typename T>::~List				()
	{
		std::free(Prev);
		std::free(Data);
		std::free(Next);
	}

	template <typename T> void		 List<typename T>::Dump					()
	{
		cout << "free: " << free << endl;
		cout << "head: " << head << endl;
		cout << "tail: " << tail << endl;
		cout << "size: " << size << endl;
		cout << "capacity: " << capacity << endl;

		cout << "Prev:\n";
		for (int i = 0; i < capacity; i++) cout << Prev[i] << " ";
		cout << endl;
		cout << "Data:\n";
		for (int i = 0; i < capacity; i++) cout << Data[i] << " ";
		cout << endl;
		cout << "Next:\n";
		for (int i = 0; i < capacity; i++) cout << Next[i] << " ";
		cout << "\n\n";
	}

	template <typename T> int		 List<typename T>::Insert				(int index, const T& value)
	{
		bool status = CheckValidInsertIndex(index);
		if (!status) return -1;
		
		if (size == capacity or index >= capacity)
			ListResize();

		int RealIndex = free;
		int next_free = -Next[free];
		
		if (size == 0)
		{
			head = free;
			tail = free;
			Data[free] = value;
			Next[free] = 0;
			Prev[free] = 0;
			Next[0] = free;
		}
		else
		{
			Data[free] = value;
			Prev[free] = index;
			Next[free] = Next[index];
			Prev[Next[index]] = free;
			Next[index] = free;
			if (index == tail)
				tail = free;
			if (index == 0)
				head = free;
		}

		free = next_free;
		size += 1;

		return RealIndex;
	}

	template <typename T> int		 List<typename T>::PushBack				(const T& value)
	{
		return Insert(tail, value);
	}

	template <typename T> int		 List<typename T>::PushFront			(const T& value)
	{
		return Insert(0, value);
	}

	template <typename T> T			 List<typename T>::Delete				(int index)
	{
		bool status = CheckValidDeleteIndex(index);
		if (!status) return -1;
		
		T data = Data[index];
		if (index == head)
			head = Next[head];
		if (index == tail)
			tail = Prev[tail];
		Next[Prev[index]] = Next[index];
		Prev[Next[index]] = Prev[index];
		Next[index] = -free;
		Prev[index] = -1;
		free = index;
		Data[index] = 0;
		size--;
		return data;
	}

	template <typename T> T			 List<typename T>::PopBack				()
	{
		return Delete(tail);
	}

	template <typename T> T			 List<typename T>::PopFront				()
	{
		return Delete(head);
	}

	template <typename T> T			 List<typename T>::Show					(int index)
	{
		return data[index];
	}

	template <typename T> void		 List<typename T>::GraphDump			(const char * const graphname)
	{
		size_t length = strlen(graphname) + 40;
		char* command = (char*)calloc(length, sizeof(char));
		strcpy_s(command, length, graphname);
		strcat_s(command, length, ".dot");
		
		ofstream dumpfile;
		dumpfile.open(command);

		dumpfile << "digraph G{\n";
		dumpfile << "rankdir=LR\n";
		dumpfile << "edge[color=white]\n";

		size_t index = 0;
		while (index != capacity)
		{
			dumpfile << "Node" << index << "[shape = record, label = \" <index" << index << "> index " << index;
			dumpfile << " | { Prev " << Prev[index] << " | Data " << Data[index];
			dumpfile << " | <next" << index << "> Next " << Next[index] << " } \" ];\n";

			if (index + 1 != capacity)
				dumpfile << "Node" << index << "->Node" << index + 1 << ";\n";
			index++;
		}

		dumpfile << "edge[color=black]\n";

		index = head;
		while (Next[index] != 0)
		{
			dumpfile << "Node" << index << ":<next" << index << "> -> Node" << Next[index] << ":<index" << Next[index] << ">;\n";
			index = Next[index];
		}

		dumpfile << "\"head: " << head << "\" -> Node" << head << ":<index" << head << ">\n";
		dumpfile << "Node" << tail << ":<index" << tail << "> -> \"tail: " << tail << "\"\n";
		dumpfile << "\"free: " << free << "\" -> Node" << free << ":<index" << free << ">\n";


		dumpfile << "}";
		dumpfile.close();

		strcpy_s(command, length, "dot -Tpng ");
		strcat_s(command, length, graphname);
		strcat_s(command, length, ".dot");
		strcat_s(command, length, " -o ");
		strcat_s(command, length, graphname);
		strcat_s(command, length, ".png");
		system(command);
	}

	template <typename T> void		 List<typename T>::Sorting				()
	{
		T* SortList = (T*)calloc(capacity, sizeof(T));
		int SortIndex = 1, DataIndex = head;
		for (SortIndex, DataIndex; DataIndex != Next[tail]; SortIndex++, DataIndex = Next[DataIndex])
		{
			SortList[SortIndex] = Data[DataIndex];
			Next[SortIndex] = SortIndex + 1;
			Prev[SortIndex] = SortIndex - 1;
		}

		head = 1;
		tail = SortIndex - 1;
		Next[tail] = 0;
		free = SortIndex;
		for (int i = free, k = 1; i < capacity; i++, k++)
		{
			Prev[i] = -1;
			Next[i] = -free - k;
		}
		std::free(Data);
		Data = SortList;
	}

	template <typename T> int		 List<typename T>::TranslateIndex		(int logic_index)
	{		
		int real_index = head;
		for (int i = 1; i < logic_index; i++)
			real_index = Next[real_index];
		return real_index;
	}

	template <typename T> void		 List<typename T>::ListResize			()
	{
		int* NewPrev = (int*)realloc(Prev, 2 * capacity * sizeof(int));
		T* NewData   = (T*)_recalloc(Data, 2 * capacity, sizeof(T));
		int* NewNext = (int*)realloc(Next, 2 * capacity * sizeof(int));

		if (NewData and NewPrev and NewNext)
		{
			Prev = NewPrev;
			Data = NewData;
			Next = NewNext;
		}

		Prev[capacity] = -1;
		Next[capacity] = -int(capacity) - 1;
		for (size_t i = capacity + 1; i < 2 * capacity; i++)
		{
			Prev[i] = -1;
			Next[i] = Next[i - 1] - 1;

		}
		capacity = 2 * capacity;

	}

	template <typename T> inline int List<typename T>::CheckValidDeleteIndex(int index)
	{
		return index != 0 and Prev[index] != -1;
	}	
	
	template <typename T> inline int List<typename T>::CheckValidInsertIndex(int index)
	{
		return Prev[index] != -1;
	}
}



