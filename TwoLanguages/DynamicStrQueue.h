/*Author: Zeynep Dogmus
 *Date: March 2013
 *Operator Overloading with Queue

  *Modified by: M. Yusa Erguven
  *Date: 07.10.2019
  *Adjusted for string
*/
#ifndef DYNAMICSTRQUEUE_H
#define DYNAMICSTRQUEUE_H

#include <string>
using namespace std;

struct StrQueueNode
{
	string value;
	StrQueueNode *next;
	StrQueueNode(string str, StrQueueNode *ptr = NULL)
	{
		value = str;
		next = ptr;
	}
};

class DynamicStrQueue
{
	private:
		StrQueueNode *front;
		StrQueueNode *rear;

	public:
		DynamicStrQueue();
		~DynamicStrQueue();

		void enqueue(string);
		void dequeue(string &);
		bool isEmpty() const; 
		void clear(void);

		StrQueueNode* GetFront();
		StrQueueNode* GetRear();
};


#endif