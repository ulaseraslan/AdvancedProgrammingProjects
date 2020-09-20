#include <iostream>
#include "SortedArray.h"


using namespace std;


int main() {

	SortedArray sortedArray;
	SortedArray sortedArray2;
	SortedArray sortedArray3;


	sortedArray.insert(5);
	sortedArray.insert(10);
	sortedArray.insert(7);
	sortedArray.insert(2);
	sortedArray.insert(4);

	sortedArray2.insert(2);
	sortedArray2.insert(0);
	sortedArray2.insert(10);
	sortedArray2.insert(8);
	sortedArray2.insert(9);

	sortedArray3.insert(20);
	sortedArray3.insert(30);
	sortedArray3.insert(40);
	sortedArray3.insert(50);
	sortedArray3.insert(70);
    


//	sortedArray.print();
//	sortedArray2.print();
//	sortedArray3.print();

//	sortedArray = sortedArray2 = sortedArray3;
	
	cout << "Array1: ";
	sortedArray.print();

	cout << endl << "Array1 = Array1 + 20" << endl;
	sortedArray = sortedArray + 20;
	cout << "Array1: ";
	sortedArray.print();

	cout << endl << "Array1 = 6 + Array1" << endl;
	sortedArray = 6 + sortedArray;
	cout << "Array1: ";
	sortedArray.print();


	cout << endl << "Array2: ";
	sortedArray2.print();

	SortedArray sumOfTwo = sortedArray + sortedArray2;
	cout << endl << "Array1 + Array2 = ";
	sumOfTwo.print();

	cout << endl << "Array3: ";
	sortedArray3.print();

	SortedArray sumOfAllThree = sortedArray + sortedArray2 + sortedArray3;
	cout << endl << "Array1 + Array2 + Array3 = ";
	sumOfAllThree.print();

	SortedArray example1 = 1 + sortedArray + 56;
	cout << endl << "1 + Array1 + 56 = ";
	example1.print();



	sortedArray = sortedArray2 = sortedArray3;
	cout << endl << "After => Array1 = Array2 = Array3" << endl;
	cout << "Array1: ";
	sortedArray.print();
	cout << "Array2: ";
	sortedArray2.print();
	cout << "Array3: ";
	sortedArray3.print();

    SortedArray sortedArray4(sortedArray3);
    cout << endl << "Array4 is generated with copy constructor of Array3" << endl;
    cout << "Array4: ";
    sortedArray4.print();
    cout << endl;
    
	system("pause");
	return 0;
}
