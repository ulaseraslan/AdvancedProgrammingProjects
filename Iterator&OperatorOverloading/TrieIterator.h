#ifndef _ITERATOR
#define _ITERATOR

#include "Stack.h"

class TrieIterator {
public:
	
    TrieIterator(const Trie & myTrie);
    
	void Init();
	bool HasMore() const;
	string Current() const;
	void Next();
    int sizeChecker;
    
    
private:
    
	const Trie & myTrie;
	TrieNode* currentNode;
	string currentWord;
    Stack stack;
};
#endif
