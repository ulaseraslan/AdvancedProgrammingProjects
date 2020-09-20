//
//  ulaseraslan_Eraslan_Ulas_hw1.cpp
//  hw1 Matrix Operations ** CS204 Sabancı University ** Kamer Kaya
//
//  Created by Ulaş Eraslan on 18.09.2019.
//  Copyright © 2019 Ulaş Eraslan. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct words {                  //This struct stores the datas(the word and the occurance of the word) which are found in matrix.
    
    string word;
    int occurance =0;
};

void check (int i, int j,string word, vector<vector<char>> matrix1, vector<vector<int>> matrix2, int wordLenght, int columnN,vector<words> &wordStruct) {
    //This function is the main algorithm of this program. It gets some parameters (x and y axis of the matrix, word to be created, given matrix from the user, second matrix which is same as the first matrix but full of zeros, word lenght which is given by user, wordStruct vector which stores found words' datas.
    char c;
    if (i>=0 && i<columnN && j>=0 && j<columnN && word.length()<wordLenght && matrix2[i][j] == 0) {     //This is a checkpoint. If all conditions are provided then program continues. (Conditions are : check the matrix's boundries, check lenght of the word and check the second matrix which is full of 0.)
        
        c = matrix1[i][j]; //Take the char in the cell.
        word +=c; // Add it to the word.
        matrix2[i][j] = 1; //Change the corresponded cell in the matrix2 as 1. It means the program visited this cell so program will not visit this cell again.
        
        
        if (word.length() == wordLenght) {  // At this point program checks the word length. If it is same as the given (wordLenght) then program apply the next protocol.
            
            bool occuranceW= false;
            
            for (int y=0; y<wordStruct.size() ; y++) {  //Program chekcs the wordStruct vector to seek the word. If the word in the vector, program increment the number of occurance of the word.
                
                if (wordStruct[y].word == word) {
                    
                    wordStruct[y].occurance ++;
                    occuranceW= true;
                    
                }
                
            }
            
            if (occuranceW == false)  { //If the word is not in the wordStruct vector, program add it into the vector and increment the number of occurance of word.
                
                wordStruct.push_back(words());
                wordStruct[wordStruct.size()-1].word = word;
                wordStruct[wordStruct.size()-1].occurance ++;
                
            }
    
        }
    //This part of the program is the recursive part. At this point each function get different x and y indexes to check the up-down-right-left cells.
    // Each function works until check point is not valid.
        
        check(i,j-1,word,matrix1,matrix2,wordLenght,columnN,wordStruct); // Left
        check(i,j+1,word,matrix1,matrix2,wordLenght,columnN,wordStruct); // Right
        check(i-1,j,word,matrix1,matrix2,wordLenght,columnN,wordStruct); // Up
        check(i+1,j,word,matrix1,matrix2,wordLenght,columnN,wordStruct); // Down
        
        
        return;
        
    }
    
    else {
        return;
    }
}

int main() {
    
    string fileName,line,line2,wordy = "";
    char chr;
    int column,stringN,lineC=0;
    
    cout << "Please enter the input file name: ";
    cin >> fileName;
    
    ifstream input;                         // Program reads the input file.
    
    input.open(fileName);
    
    while (input.fail()) { //If file can not open then programs asks again until the correct form is entered.
        
        cout << "Couldn’t open file. Please enter again: ";
        cin>> fileName;
        
    }
    
    getline(input,line); //Program reads the first line
    
    column = stoi(line); //Then the first line is converted to string to store as "column number"

    
    if (column>20 || column <=0) {
        cout << "Input file is not as expected." << endl;   //This part checks the boundires of the column. If it is less then 0 or greater then 20 program ends.
        return 0;
        
        }
    
    vector<vector<char>> matrix; //This 2D vector is store the chars which are given by the user file.
    vector <vector<int>> matrix2 (column,vector<int>(column)); //This vector is full of 0 which is the same as the char vector. Program use this vector to check the direction. E.g. If a cell is 1 it means program visited this cell before.
    vector <words> wordStruct;  //This is the vector of struct which stores the words' datas which are found in the matrix.
    vector <char> charV; //This vector is used to store each characters which are found in the given file. Then this vector pushed back to matrix.
    
    while (!input.eof()) {              // At this point program reads the whole file line by line.
        
        getline(input,line);
        
        lineC++;
        
        if (line != "") {               // Until program finds a space in the file it reads.
            
            stringstream ss1(line);     // By using stringstream program checks the lenght of the string.
            
            string a;
            
            ss1>>a;
            
            stringstream ss(a);
            
            if (a.length() != column) {                             //If the lenght of the string is not equal the column number program ends.
                cout << "Input file is not as expected." << endl;
                return 0;
            }
            
            while (ss.get(chr)) {       //At this point program gets the each character of the string.
                
                if (isupper(chr) &&  chr >= 'A' && chr <= 'Z' ) {       //These chars must be uppercase letters.
                    
                    charV.push_back(chr);   // If all conditions are provided, each char pushback to the char vector.
                        
                    if (charV.size() == column) {   //To create a 2D matrix in every column size char vector is pushed back to matrix.
                        matrix.push_back(charV);
                        charV.clear();
                    }
                    
                }
                
                else {
                    
                    cout << "Input file is not as expected." << endl;
                    return 0;
                }
                
            }
            
        }
        
        else {
            break;
        }
        
    }
    
    if (lineC!= column+1) {
        cout << "Input file is not as expected." << endl;
        return 0;
    }
    else {
    getline(input,line);    //After reading all characters program reads the last number which represent the lenght of the words.
    stringN = stoi(line);
    
    if (stringN>20 || stringN <=0) {    //At this point program check the interval of the lengnth of the word.
        cout << "Input file is not as expected." << endl;
        return 0;
    }
        
    
    for (int k=0; k<column; k++) {      //After all, program starts to read each letters in the matrix to create the words.
        for(int l=0; l<column; l++) {
            
            check(k, l, wordy, matrix, matrix2, stringN, column,wordStruct);
        }
    }
    
    for (int q=0; q < wordStruct.size() ; q++ ) {       //At this point program prints the outputs.
        
        cout << "[+] "<<wordStruct[q].word<< " exists "<< wordStruct[q].occurance<< " many times." <<endl;
        
    }
    
    return 0;
}
    }
