/*
Modified by Gizem Gezici
Date: 13.03.2012
Print member function was added
The name of the public clear function was modified
(in order to prevent function overloading)
 
*Modified by: M. Yusa Erguven
*Date: 07.10.2019
*Adjusted for int
*/


#ifndef DYNAMICINTSTACK_H
#define DYNAMICINTSTACK_H

using namespace std;

struct IntStackNode
{
	int value;
	IntStackNode *next;
};


class DynamicIntStack
{
	private:
		IntStackNode *top;

	public:
		DynamicIntStack(void);
		void push(int);
		void pop(int &);
		bool isEmpty(void);
		IntStackNode* GetTopPointer();
		void clear(void);

};


#endif