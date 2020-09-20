#include <iostream>
#include "Trie.h"
#include "TrieIterator.h"

using namespace std;


int main() {

	Trie tr1;
    
    tr1.insertWord("uni");
    tr1.insertWord("unido");
    tr1.insertWord("process");
    tr1.insertWord("computer");
    tr1.insertWord("compute");
    tr1.insertWord("program");
    tr1.insertWord("progress");
    tr1.insertWord("universe");
    tr1.insertWord("university");
    

	cout << "Content of tr1: " << endl << tr1 << endl;

	cout << endl << "Creating tr2 with: tr2(tr1)" << endl;
	Trie tr2(tr1);
	cout << "Content of tr1: " << endl << tr1 << endl;
	cout << "Content of tr2: " << endl << tr2 << endl;

	cout << endl << "Creating tr3 with: tr3 = tr1" << endl;
	Trie tr3 = tr1;
	cout << "Content of tr3: " << endl << tr3 << endl;
    
	Trie tr4;

	tr4.insertWord("saramago");
	tr4.insertWord("computing");
	tr4.insertWord("zapatista");
	tr4.insertWord("headphone");
	tr4.insertWord("header");

	cout << "Content of tr4: " << endl << tr4 << endl;

	cout << endl << "Creating tr5 with: tr5(tr1 + tr4)" << endl;
	Trie tr5(tr1 + tr4);
	cout << "Content of tr5: " << endl << tr5 << endl;


	cout << endl << "Deleting the tr1" << endl;
	tr1.deleteTrie();
	cout << "Content of tr1: " << endl << tr1 << endl;

	cout << "Iterator for tr5 is starting: " << endl;
	TrieIterator iter1(tr5);
	int i = 1;
    
	for (iter1.Init(); iter1.HasMore(); iter1.Next()) {
		cout << "[" << i << "] " << iter1.Current() << endl;
		i++;
	}

	cout << endl << "tr2 += tr4" << endl;
	tr2 += tr4;
	cout << "Content of tr2: " << endl << tr2 << endl;

	cout << "Content of tr5: " << endl << tr5 << endl;
	if (tr5 == tr2) {
		cout << "tr5 and tr2 are equal." << endl;
	}
	else {
		cout << "tr5 and tr2 are not equal." << endl;
	}

	cout << endl << "tr4 += \"gloves\"" << endl;
	tr4 += "gloves";
	cout << "Content of tr4: " << endl << tr4 << endl;

	cout << endl << "tr3 = tr3 + tr4" << endl;
	tr3 = tr3 + tr4;
	cout << "Content of tr3: " << endl << tr3 << endl;
	cout << "Content of tr5: " << endl << tr5 << endl;
	if (tr5 != tr3) {
		cout << "tr5 and tr3 are not equal." << endl;
	}
	else {
		cout << "tr5 and tr3 are equal." << endl;
	}

	cout << endl << "tr4 = tr4 + \"helmet\"" << endl;
	tr4 = tr4 + "helmet";
	cout << "Content of tr4: " << endl << tr4 << endl;

	cout << endl << "tr4 = \"jacket\" + tr4 " << endl;
	tr4 = "jacket" + tr4;
	cout << "Content of tr4: " << endl << tr4 << endl;


	//system("pause");*/
	return 0;
}
