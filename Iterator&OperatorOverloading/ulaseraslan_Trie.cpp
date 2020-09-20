#include "Trie.h"
#include "TrieIterator.h"
#include <iostream>
#include <sstream>
#include <vector>

//ulaseraslan 15.11.2019 CS204 HW5

Trie::Trie(){
	this->root = new TrieNode();
	this->size = 0;
}

// TODO: Implement this function
Trie::Trie(const Trie & copy){

	cout << "Copy constructor called" << endl;
   this->root = copy.createClone();
    size = copy.size;
}

// TODO: Implement this function
Trie::Trie(Trie && move):root(nullptr), size(0){

	cout << "Move constructor called" << endl;
    
    std::swap(root,move.root);
    std::swap(size,move.size);
    
    
}

// TODO: Implement this function
Trie::~Trie(){
    
	cout << "Destructor called" << endl;
    
    deleteTrie();
}


// TODO: Implement this function
TrieNode * Trie::createClone() const {		//Copy root is created and "Create Clone" uses "CloneHelper" to copy source's info to the copyroot.

    TrieNode *copyRoot = new TrieNode;
    
    TrieNode *sourceNew = root;
    
    cloneHelper(sourceNew, copyRoot);
    
    
    
    return copyRoot;
}

// TODO: Implement this function
void Trie::cloneHelper(TrieNode* source, TrieNode* &destination) const {		//Clone helper recursively checks each nodes of the given sources and adds them to the destination trie.
    
    
    if (source == nullptr) {
        return;
    }
    
    else {
    for (int i=0; i<ALPHABET_SIZE ;i++) {
        
        if (source->children[i]) {
            
            destination->children[i] = new TrieNode();
            
            if (source->children[i]->isWord == true) {
                
                destination->children[i]->isWord = true;
            }
            
            else {
                destination->children[i]->isWord = false;
            }
            
            
            cloneHelper(source->children[i], destination->children[i]);
            
            }
        }
    }
}


/*******************************************************************/
/*                      DEFINE YOUR OPERATORS HERE                 */

ostream & operator << (ostream & obj,Trie &os) {		//This is << operator overloading.
    
    TrieIterator iter(os);
    
	iter.sizeChecker = 0;
    for (iter.Init(); iter.HasMore(); iter.Next()) {		//Function uses iterator and return ostream object.
        if (iter.Current() == "") {
            break;
        }
        obj << iter.Current() << endl ;
    }
    
    return obj;
}

bool Trie::operator == (const Trie & lhs) {		//This function uses iterator to find words of given parameter and current trie.
    
    vector<string> check;
    vector<string> check2;
    //Trie rooty(*this);
    

    TrieIterator iter1(lhs);
    TrieIterator iter2(*this);
    
	iter1.sizeChecker = 0;
	iter2.sizeChecker = 0;

    for (iter1.Init(); iter1.HasMore(); iter1.Next()) {		//Found words are pushed to vectors and compare each vector to find any differences.
       
        check.push_back(iter1.Current());
    }

    for (iter2.Init(); iter2.HasMore(); iter2.Next()) {
        check2.push_back(iter2.Current());
    }
    
    for (int i= 0; i<check2.size(); i++) {
        
        if (check[i] != check2[i]) {
            return false;
        }
    }
    
    return true;
}

bool Trie::operator != (const Trie & lhs) {			//This function is the opposite of the previous operator overloading.
    
    vector<string> check;
    vector<string> check2;
   
	//Trie rooty(*this);
    TrieIterator iter1(lhs);
    TrieIterator iter2(*this);

	iter1.sizeChecker = 0;
	iter2.sizeChecker = 0;
    
    
    for (iter1.Init(); iter1.HasMore(); iter1.Next()) {
        
        check.push_back(iter1.Current());
    }
    
    for (iter2.Init(); iter2.HasMore(); iter2.Next()) {
        check2.push_back(iter2.Current());
    }
    
    for (int i= 0; i<check2.size(); i++) {
        
        if (check[i] != check2[i]) {
            return true;
        }
    }
    
    return false;
    
}

const Trie &Trie :: operator = (const Trie & rhs) {			//This operator overloading equalize given parameter to the current.
    
    if (*this != rhs) {
        
        deleteTrie();
        root = rhs.createClone();
        size = rhs.size;
    }
    
    return *this;
    
}


const Trie &Trie :: operator += (const Trie & rhs) {		//Given parameter is added to the current trie.
    
    TrieIterator iter1(rhs);

	iter1.sizeChecker = 0;
    
    for (iter1.Init(); iter1.HasMore(); iter1.Next()) {
        
        this->insertWord(iter1.Current());
    }
    
    
    return *this;
}

const Trie Trie :: operator+ (const Trie & rhs) {			//Given parameter's nodes and current trie's nodes are summed up.
    
    Trie newTrie;
    TrieIterator iter1(rhs);
    TrieIterator iter2 (*this);

	iter1.sizeChecker = 0;
	iter2.sizeChecker = 0;
    
    for (iter1.Init(); iter1.HasMore(); iter1.Next()) {
        
        newTrie.insertWord(iter1.Current());
    }
    
    for (iter2.Init(); iter2.HasMore(); iter2.Next()) {
        
        newTrie.insertWord(iter2.Current());
    }
    
    return newTrie;
    
}

const Trie &Trie ::  operator += (string word){		//Given string is added to the trie.
    
    this->insertWord(word);
    
    return *this;
}

Trie operator + (const Trie &obj ,string word) {	//Trie object and string is added up.
 
    Trie newOb;
    TrieIterator iter1(obj);

	iter1.sizeChecker = 0;
 
    for (iter1.Init(); iter1.HasMore(); iter1.Next()) {
 
        newOb.insertWord(iter1.Current());
    }
 
    newOb.insertWord(word);
 
    return newOb;
}

Trie  operator + (string word,  Trie &obj ) {		//Trie object and string is added up (Same as previous overloading.)
    
    Trie newOb;
    TrieIterator iter1(obj);

	iter1.sizeChecker = 0;
    
    for (iter1.Init(); iter1.HasMore(); iter1.Next()) {
        
        newOb.insertWord(iter1.Current());
    }
    
    newOb.insertWord(word);
    
    return newOb;
}




/*******************************************************************/



bool Trie::searchWord(string word) {
	lower(word);
	TrieNode * ptr = root;
	int len = word.length();
	for (int i = 0; i < len; i++) {
		int targetIndex = word.at(i) - 'a';
		if (!ptr->children[targetIndex]) {
			return false;
		}
		ptr = ptr->children[targetIndex];
	}
	if (ptr->isWord) {
		return true;
	}
	return false;
}

void Trie::lower(string & word) {
	string res;
	for (char c : word) {
		if (c >= 'A' && c < 'a') {
			res += (c - 'A' + 'a');
		}
		else {
			res += c;
		}
	}
	word = res;
}


void Trie::insertWord(string word) {
	lower(word);
	if (!searchWord(word)) {
		TrieNode * ptr = root;
		int len = word.length();
		for (int i = 0; i < len; i++) {
			int targetIndex = word.at(i) - 'a';
			if (!ptr->children[targetIndex]) {
				ptr->children[targetIndex] = new TrieNode();
			}
			//			ptr->isLeaf = false;
			ptr = ptr->children[targetIndex];
		}
		ptr->isWord = true;
		size += 1;
	}
}

bool Trie::hasChildren(TrieNode * node, int i = 0) const {
	if (node) {
		for (i; i < ALPHABET_SIZE; i++) {
			if (node->children[i]) {
				return true;
			}
		}
	}
	return false;
}

void Trie::deleteWord(string word) {
	lower(word);
	if (searchWord(word)) {
		if (deleteWordHelper(root, word)) {
			size--;
		}
	}
}

bool Trie::isEmpty() const {
	return !(this->hasChildren(root));
}

bool Trie::deleteWordHelper(TrieNode *& node, string word) {
	if (word.length()) {
		if (node != nullptr &&
			node->children[word[0] - 'a'] != nullptr &&
			deleteWordHelper(node->children[word[0] - 'a'], word.substr(1)) &&
			!node->isWord
			) {
			if (!hasChildren(node)) {
				delete node;
				node = nullptr;
				return true;
			}
			else {
				node->isWord = false;
				return true;
			}

		}
	}
	if (word.length() == 0 && node->isWord) {
		if (!hasChildren(node)) {
			delete node;
			node = nullptr;
			return true;
		}
		else {
			node->isWord = false;
			return false;
		}
	}
    return false;
}

void Trie::printHelper(ostream & os, TrieNode * node, string & word) const {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->children[i]) {
			word += char(i + 'a');
			if (node->children[i]->isWord) {
				os << word << endl;
				printHelper(os, node->children[i], word);
			}
			else {
				printHelper(os, node->children[i], word);
			}
		}
		else if (i == 26) {
			word = word.substr(0, word.length() - 1);
		}
	}
	word = word.substr(0, word.length() - 1);
}

void Trie::deleteTrie() {
	if (root) {
		deleteTrieHelper(root);
		root = nullptr;
		size = 0;
	}
}

void Trie::deleteTrieHelper(TrieNode * node) {
	if (hasChildren(node)) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (node->children[i]) {
				deleteTrieHelper(node->children[i]);
			}
		}
	}
	delete node;
}

int Trie::length() {
	return size;
}
