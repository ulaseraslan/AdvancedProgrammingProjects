/*Author: Zeynep Dogmus
 *Date: March 2013
 *Operator Overloading with Queue

  *Modified by: M. Yusa Erguven
  *Date: 07.10.2019
  *Adjusted for string
*/
#include <iostream>
#include "DynamicStrQueue.h"
using namespace std;

//********************************************
// Constructor. Generates an empty queue     *
//********************************************
DynamicStrQueue::DynamicStrQueue()
{
	front = NULL;
	rear = NULL;
}

StrQueueNode* DynamicStrQueue::GetFront()
{
	return front;
}

StrQueueNode* DynamicStrQueue::GetRear()
{
	return rear;
}


//********************************************
// Function enqueue inserts the value in elmt*
// at the rear of the queue.                 *
//********************************************
void DynamicStrQueue::enqueue(string elmt)
{
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new StrQueueNode(elmt);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new StrQueueNode(elmt);
		rear = rear->next;
	}
	#ifdef _DEBUG
		//cout << elmt << " enqueued\n";
	#endif
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into elmt.*
//**********************************************
void DynamicStrQueue::dequeue(string &elmt)
{
	StrQueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		elmt = front->value;
		temp = front;
		front = front->next;
		delete temp;      
	}
	#ifdef _DEBUG
		//cout << elmt << " dequeued\n";
	#endif
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynamicStrQueue::isEmpty() const
{
	if (front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void DynamicStrQueue::clear(void)
{
	string value;   // Dummy variable for dequeue

	while(!isEmpty())
	{
		dequeue(value); //delete all elements
	}
}

DynamicStrQueue::~DynamicStrQueue()
{
	clear();
	#ifdef _DEBUG
		//cout << "Destructor is invoked\n";
		//cout << endl;
	#endif
}