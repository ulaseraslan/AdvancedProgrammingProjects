#include "SortedArray.h"

//Edited by ulaseraslan
// 28.10.19 Sabanci Univ. CS 204


SortedArray::SortedArray() {
	front = nullptr;
}

//impelent copy constructor
SortedArray::SortedArray(const SortedArray & copy) {            //This function creates a new SortedArray object by deep-copying given array as "copy" parameter.
    
    front = copy.createClone();             //CreateClone is used to copy each node of the given parameter.
    
}

//implement destructor
SortedArray::~SortedArray() {               // This function destruct each node of the array.

    ArrayNode * ptr = front;
    
    while (ptr!= NULL) {
        
        ArrayNode *temp = ptr->right;
        delete ptr;
        ptr = temp;
        
    }
}

ArrayNode * SortedArray::getFront() const{
	return front;
}

void SortedArray::SetFront(ArrayNode * newFront){
	front = newFront;
}

// implement this function
ArrayNode * SortedArray::createClone() const{           //This function copy the sorted array and return the new array's head.

    if (front == nullptr)               //If given array's front is null then it means array is empty.
        return nullptr;
    
    ArrayNode * headClone = new ArrayNode(front->val);      //If array is not empty, clone's head is assign to orginal array's front value
    ArrayNode * ptr = front->right;                         // ptr is eqaul to orginal array's head's next node. So ptr can traverse between nodes.
    ArrayNode *ptrClone = headClone;
    
    while (ptr) {                                           // While ptr is not null, orginal array's info. are copied to clone.
        
        ptrClone->right = new ArrayNode(ptr->val);
        ptr = ptr->right;
        ptrClone = ptrClone->right;
    }
    
    return headClone;           //At the end copy clone's head is returned.
}


bool SortedArray::search(int Value)
{
	ArrayNode * tmp = front;
	while (tmp) {
		if (tmp->val == Value) {
			return true;
		}
		tmp = tmp->right;
	}
	return false;
}

void SortedArray::insert(int Value) {
	if (!search(Value)) {
		ArrayNode * tmp = front;

		ArrayNode * newNode = new ArrayNode(Value);
		if (!front) {
			front = newNode;
		}
		else if (front && Value < front->val) {
			newNode->right = front;
			front = newNode;
		}
		else {
			while (tmp->right && tmp->right->val < Value) {
				tmp = tmp->right;
			}
			newNode->right = tmp->right;
			tmp->right = newNode;
		}
	}
}

void SortedArray::deleteSortedArray() {
	ArrayNode * current = front, *next = front;
	while (current) {
		next = current->right;
		delete current;
		current = next;
	}
	front = nullptr;
}

void SortedArray::print() {
	if (!front) {
		cout << "Array is empty" << endl;
	}
	ArrayNode * tmp = front;
	while (tmp) {
		cout << tmp->val << " ";
		tmp = tmp->right;
	}
	cout << endl;
}

//implement assignment (=) and plus (+) operators

const SortedArray &SortedArray :: operator = (const SortedArray &rhs) {     //This is assignment operator overload implemantation.
                                                                            //If right-hand-side operand is not equal to the left-hand-side (this)
    if (this != &rhs) {                                                     // rhs' copy is generated and assinged to the this (lhs).
        
        deleteSortedArray();
        front = rhs.createClone();
        
    }
    
    return *this;
}
                                                                                    //This is + operator overload process.

SortedArray operator+ (const SortedArray &lhs , const SortedArray &rhs) {               // If both sides of operator is array.
    
    SortedArray result(lhs);                        //Copy of the left-hand-side is constructed.
    ArrayNode *opr= nullptr;                        // opr is assinged to the right-hand-side's front.
    
    opr=rhs.getFront();
    
    while (opr) {                                   //while opr is not null ptr, rhs' values are copied to the lhs.
        result.insert(opr->val);
        
        opr = opr->right;
    }
    
    
    return result;
    
}


SortedArray operator+ (const SortedArray &lhs , int rhs) {                          // If one side of operator is array and other side is int.
    
    SortedArray result (lhs);                                   //Given int is insterted to the array.
    
    result.insert(rhs);
    
    return result;
}

SortedArray operator+ (int rhs,const SortedArray &lhs) {                            // If one side of operator is int and other side is array.
    
    SortedArray result (lhs);                                   //Given int is insterted to the array.
    
    result.insert(rhs);
    
    return result;
}

