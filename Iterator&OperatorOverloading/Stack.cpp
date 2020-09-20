#include <iostream>
#include "Stack.h"
#include "Trie.h"
using namespace std;

Stack::Stack() {
  top = nullptr; 
}

void Stack::push(TrieNode* node, int i) {
  StackNode *newNode;
  
  newNode = new StackNode;
  newNode->node = node;
  newNode->indexOfChild = i;
  // If there are no nodes in the list
  // make newNode the first node
  if (isEmpty())
    {
      top = newNode;
      newNode->next = nullptr;
    }
  else	// Otherwise, insert NewNode before top
    {
      newNode->next = top;
      top = newNode;
    }
    
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void Stack::pop(TrieNode* &node, int & i) {
  StackNode *temp;
  
  if (isEmpty()) {
    cout << "The stack is empty.\n";
    node = nullptr;
  }
  else {
    node = top->node;
	i = top->indexOfChild;
    temp = top->next;
    delete top;
    top = temp;
  }
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool Stack::isEmpty(void) const {
  bool status;
  
  if (top == NULL)
    status = true;
  else
    status = false;
  
  return status;
}

