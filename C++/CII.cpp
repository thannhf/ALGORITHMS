#include <cstdlib>
#include <cstring>
#include <iostream>
#ifndef CLL_H
#define CLL_H
struct node {
	int data;
	node* next;
};
class cll{
	public:
		cll();
		~cll();
		void display();
		void insert_front(int new_data);
		void insert_tail(int new_data);
		int get_size();
		bool find_item(int item_to_find);
		
		int operator*();
		void operator++();
	protected:
		node* head;
		int total;
};
#endif