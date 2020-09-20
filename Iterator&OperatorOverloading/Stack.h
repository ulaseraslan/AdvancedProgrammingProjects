#ifndef _STACK
#define _STACK

#include "Trie.h"

struct StackNode {
	int indexOfChild;
	TrieNode *node;
	StackNode *next;
    
};

class Stack {
 private:
  
  
 public:
    Stack();
    void push(TrieNode*, int);
    void pop(TrieNode* &, int &);
    bool isEmpty(void) const;
    StackNode *top;
    
};
#endif
