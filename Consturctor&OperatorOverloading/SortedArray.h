#ifndef _SORTEDARRAY
#define _SORTEDARRAY

#include <iostream>

using namespace std;

class ArrayNode {
public:
	int val;
	ArrayNode *right;
	ArrayNode() {};
	ArrayNode(int val) :val(val), right(nullptr) {};
};


class SortedArray {
public:
	SortedArray();

	//we need deep copy implementation for copy constructor
	//createClone and cloneHelper will do the real work
    
	SortedArray(const SortedArray &);

	//we need to destruct all the nodes in the linkedlist
	//complete the implementation of this
	~SortedArray();

	bool search(int Value);
	void insert(int Value);
	void deleteSortedArray();
	void print();
	ArrayNode * getFront()const;
	void SetFront(ArrayNode * newFront);

	//implement this function in the cpp file
	ArrayNode* createClone() const;

	//Define and implement = operator for assignments and cascading assignment
    
    const SortedArray & (operator = (const SortedArray &rhs));

private:
	
	//complete the implementation of this function in cpp file
	void cloneHelper(ArrayNode* source, ArrayNode*& destination) const;

	ArrayNode *front;

};

//Define and implement + operators

SortedArray operator+ (const SortedArray &lhs , int rhs);                       //These are + operators
SortedArray operator+ (int rhs,const SortedArray &lhs);                         // operations may be array + array or array+int or int + array
SortedArray operator+ (const SortedArray &lhs , const SortedArray &rhs);        //cascading operations are also fixed by these operators


#endif
