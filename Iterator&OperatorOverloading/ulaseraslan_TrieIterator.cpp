#include "Stack.h"
#include "Trie.h"
#include "TrieIterator.h"


TrieIterator::TrieIterator(const Trie & myTrie)
	: myTrie(myTrie), currentNode(nullptr), currentWord("") {
}

// TODO: Implement this function
void TrieIterator::Init() {                                 //At this point program finds the first word in the trie.
    
    bool check = false;
    stack.push(myTrie.root, -1);
    currentNode = myTrie.root;
    
    while (myTrie.hasChildren(stack.top->node, 0)) {        //Program checks whether stack's top has children or not.
        
        for ( int i =0 ; i < ALPHABET_SIZE ; i++ ) {
            
            if (stack.top->node->children[i] != nullptr) {      //This loop searches all childrens of the stack'top node.
                
                check = true;   //If any non null ptr (letter) is found the found letter pushed to the stack.
                
                stack.push(stack.top->node->children[i], i); //push pointer to stack
                currentWord += i + 'a';     // update the word
                break;
            }
        }
        
        if (stack.top->node->isWord) {          //If word is found then program increase the counter.
            sizeChecker++;
            break;
            
            }

        }
    
    if (stack.top->indexOfChild == -1) {
        cout << "Trie is empty."<< endl;
        
    }
    
    else {
    
    if (check == false && myTrie.hasChildren(stack.top->node, 0)) {
        int i=0;
        TrieNode * temp;
        stack.pop(temp, i);
        currentNode = stack.top->node;
        }
    
    }
}


// TODO: Implement this function

void TrieIterator::Next() {
    
    bool check = false,poppedValue=false;
    int i=0,initialValue=0;
    
    while (myTrie.hasChildren(myTrie.root, initialValue)) {         //While there are trie nodes program searches words.
        
        while (stack.top->indexOfChild != -1) {                     //If node stack is not at the root node.
            
            while (myTrie.hasChildren(stack.top->node, 0)) {        //Program checks whether stack's top has children or not.
                
                if (poppedValue==true) {                            // If any node is popped from stack program increase i by one to find next letter.
                    i++;
                    poppedValue = false;
                }
                
                else {
                    i=0;                                            // If no popped i=0;
                }
                
                for ( ; i< ALPHABET_SIZE ; i++ ) {                  //This loop searches all childrens of the stack'top node.
                   
                    if (stack.top->node->children[i] != nullptr) {  //If any non null ptr (letter) is found the found letter pushed to the stack.
                        check = true;
                        
                        stack.push(stack.top->node->children[i], i); //push pointer to stack
                        currentWord +=  i + 'a';     // update the word
                        
                        if (stack.top->node->isWord) {  //If word is found then program increase the counter.
                            sizeChecker++;
                            
                            }
                        
                        if (!myTrie.hasChildren(stack.top->node, i)) {      //If there is no more children the program breaks the loop.
                            break;
                            }
                        
                        }
                    }
                
                
                if (check == false) {           //If there is no children loop is stopped.
                    break;
                }
                
                
                
            }
            
            
            if (stack.top->node->isWord && check == true) {     // If word is found.
                break;
            }
            

            //If node has no childeren, stack top is popped.
            TrieNode * temp;
            stack.pop(temp, i);
            poppedValue=true;
            currentWord = currentWord.substr(0,currentWord.length()-1);
            
        }
        
        if (stack.top->indexOfChild == -1) {            //If stack's top at the root, next first letter is found.
            
            for (int j=i+1; j<ALPHABET_SIZE; j++) {
                if (stack.top->node->children[j] != nullptr) {
                    check = true;
                    
                    stack.push(stack.top->node->children[j], j); //push pointer to stack
                    currentWord +=  j + 'a';     // update the word
                    
                    if (stack.top->node->isWord) {
                        sizeChecker++;
                    }
                    break;
                }
                
            }
            
            while (myTrie.hasChildren(stack.top->node, 0)) {        //Next first letter's word is found.
                
                for ( int i =0 ; i < ALPHABET_SIZE ; i++ ) {
                    
                    if (stack.top->node->children[i] != nullptr) {
                        
                        check = true;
                        
                        stack.push(stack.top->node->children[i], i); //push pointer to stack
                        currentWord += i + 'a';     // update the word
                        break;
                    }
                }
                
                if (stack.top->node->isWord) {
                    sizeChecker++;
                    break;
                    
                }
                
            }
            
        }
        
        if (stack.top->node->isWord) {
            break;
        }
        
        
    }
}

// TODO: Implement this function

bool TrieIterator::HasMore() const {
    
    bool check = false;
    
    if (sizeChecker <= myTrie.size ) {          //If size checker(number of the found words) smaller or equal to myTrie.size program continiues.
        
        check= true;
    }
    
    return check;
}

// TODO: Implement this function
string TrieIterator::Current() const {          //Return current word.
    
    return currentWord;
    
}
