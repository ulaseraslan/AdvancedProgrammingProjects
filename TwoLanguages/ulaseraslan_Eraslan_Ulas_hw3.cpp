//Ulas Eraslan Homework3 22.10.19 CS204 Kamer Kaya
// Two Languages

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DynamicStrQueue.h"
#include "DynamicIntStack.h"
#include "DynamicStrStack.h"
#include "strutils.h"
#include <stack>

using namespace std;

int special_regs[5] = {0};// namely CSA CSB CSC CSP CST
int general_regs[20] = {0}; // namely CSG0 CSG1 CSG2 ... CSG19
string variables[20] = {""}; // to store the variable names defined by the user. (e.g. var1, var2)
DynamicStrQueue instruction_queue; // to store the instructions in the queue
int def_counter = 0; // counting the def statements so that general reg - variable match holds
DynamicIntStack memory_stack; // needed for debugger
int instr_counter = 1; // counter for printing the instruction counts in print remaining instructions

void executeCode(string word, stringstream &ss);
void operation (string value1, string value2 , int array[] , string valueType);
string operand1Index (string operand1);

bool check = true;


void clear_regs_vars() {
    def_counter = 0;
    for (int &i : special_regs) {
        i = 0;
    }
    for (int &i : general_regs) {
        i = 0;
    }
    for (string &i : variables) {
        i = "";
    }
    instruction_queue.clear();
    memory_stack.clear();
}

void push (string value, DynamicIntStack &memory_stack) {  //This function push the values to the memory stack.
    
    
    int pushedValue=0;
    
    if (value == "CSA") {
        
        pushedValue = special_regs[0];
        
    }
    
    else if (value == "CSB") {
        pushedValue = special_regs[1];
        
    }
    
    else if (value == "CSC") {
        pushedValue = special_regs[2];
        
    }
    
    else {
        
        pushedValue= general_regs[value.at(3) - 48];
        
    }
    
    memory_stack.push(pushedValue);
    
    
}

void mov (string value1, string value2) {   //This function assigns values to each other.
    
    
    int pushedValue=0;
    
    if (value1 == "CSA") {
        
        if (value2.at(0) >= 65 && value2.at(0) <= 95) {
            
            special_regs[0] = special_regs[value2.at(3)-48];
            
        }
        
        else {
            
            pushedValue = stoi(value2);
            special_regs[0] = pushedValue;
        }
        
    }
    
    
    else if (value1 == "CSB") {
        
        if (value2.at(0) >= 65 && value2.at(0) <= 95) {
            
            special_regs[1] = special_regs[value2.at(3)-48];
            
        }
        
        else {
            
            pushedValue = stoi(value2);
            special_regs[1] = pushedValue;
        }
        
    }
    
    
    else if (value1 == "CSC") {
        
        if (value2.at(0) >= 65 && value2.at(0) <= 95) {
            
            special_regs[2] = special_regs[value2.at(3)-48];
            
        }
        
        else {
            
            pushedValue = stoi(value2);
            special_regs[2] = pushedValue;
        }
        
    }
    
    else if (value1 == "CST") {
        
        if (value2 == "CSP") {
            special_regs[4] = special_regs[3];
        }
        
        else if (value2 == "CSC") {
            special_regs[4] = special_regs[2];
        }
        
        else if (value2 == "CSB") {
            special_regs[4] = special_regs[1];
        }
        
        else if (value2 == "CSA") {
            special_regs[4] = special_regs[0];
        }
        
        else {
            
            pushedValue = stoi(value2);
            special_regs[4] = pushedValue;
        }
        
    }
    
    
    
    else {      // mov CSG.. CS.. OR mov CSG.. 1,2,3,4
        
        if (value2 == "CST") {
            general_regs[value1.at(3)-48] = special_regs[4];
        }
        
        else if (value2 == "CSP") {
            general_regs[value1.at(3)-48] = special_regs[3];
        }
        
        else if (value2 == "CSC") {
            special_regs[value1.at(3)-48] = special_regs[2];
        }
        
        else if (value2 == "CSB") {
            general_regs[value1.at(3)-48] = special_regs[1];
        }
        
        else if (value2 == "CSA") {
            general_regs[value1.at(3)-48] = special_regs[0];
        }
        
        else if (value2.at(0) >= 65 && value2.at(0) <= 95) {    //CSG.. CGS..
            
            general_regs[value1.at(3)-48] = general_regs[value2.at(3)-48];
            
        }
        else {  //CSG.. 1,2,3
            
            pushedValue = stoi(value2);
            general_regs[value1.at(3)-48] = pushedValue;
        }
        
        
    }
    
    
}

void pop (DynamicIntStack &memory_stack,int array[]) {  //This function pops the value in the stack and store it in CSP (special reg. for popped values)
    
    IntStackNode *ptr;
    ptr = memory_stack.GetTopPointer();
    
    array[3] = ptr->value;
    
    memory_stack.pop(ptr->value);
}

void add (string add1, string add2, int array[] ) {     //This function add the given values by calling operation function which is defined below. Value stored in CSA
    
    string type = "add";
    
    operation(add1, add2, special_regs, type);
    
}

void sub (string sub1 , string sub2, int array[]) {     //This function substract the given values by calling operation function which is defined below.Value stored in CSA
    
    string type = "sub";
    
    operation(sub1, sub2, special_regs, type);
    
}

void mul (string mul1 , string mul2, int array[]) {     //This function multiplies the given values by calling operation function which is defined below.Value stored in CSA
    
    string type = "mul";
    
    operation(mul1, mul2, special_regs, type);
    
}

void division (string div1, string div2,int array[],int array2[]) { //This function divides given variables and store values in CSB or CSC
    
    int divValue= 0,divOne,divTwo = 0;
    int reminderValue=0;
    
    if (div1 == "CSA") {
        
        divOne = special_regs[0];
        
        if (div2 != "CSA" && div2 != "CSB" && div2 != "CSC" && div2 != "CSP" && div2 != "CST")  {
            
            divTwo = general_regs[div2.at(3)-48];
            
        }
        
        else {
            if (div2 == "CSA")
                divTwo = special_regs[0];
            else if (div2 == "CSB")
                divTwo = special_regs[1];
            else if (div2 == "CSC")
                divTwo = special_regs[2];
            else if (div2 == "CSP")
                divTwo = special_regs[3];
            else if (div2 == "CST")
                divTwo = special_regs[4];
            
        }
    }
    
    else if (div1 == "CSB") {
        
        divOne = special_regs[1];
        
        if (div2 != "CSA" && div2 != "CSB" && div2 != "CSC" && div2 != "CSP" && div2 != "CST")  {
            
            divTwo = general_regs[div2.at(3)-48];
            
        }
        
        else {
            if (div2 == "CSA")
                divTwo = special_regs[0];
            else if (div2 == "CSB")
                divTwo = special_regs[1];
            else if (div2 == "CSC")
                divTwo = special_regs[2];
            else if (div2 == "CSP")
                divTwo = special_regs[3];
            else if (div2 == "CST")
                divTwo = special_regs[4];
            
        }
        
    }
    
    else if (div1 == "CSC") {
        
        divOne = special_regs[2];
        
        if (div2 != "CSA" && div2 != "CSB" && div2 != "CSC" && div2 != "CSP" && div2 != "CST")  {
            
            divTwo = general_regs[div2.at(3)-48];
            
        }
        
        else {
            if (div2 == "CSA")
                divTwo = special_regs[0];
            else if (div2 == "CSB")
                divTwo = special_regs[1];
            else if (div2 == "CSC")
                divTwo = special_regs[2];
            else if (div2 == "CSP")
                divTwo = special_regs[3];
            else if (div2 == "CST")
                divTwo = special_regs[4];
            
        }
    }
    
    else if (div1 == "CSP") {
        divOne = special_regs[3];
        
        if (div2 != "CSA" && div2 != "CSB" && div2 != "CSC" && div2 != "CSP" && div2 != "CST")  {
            
            divTwo = general_regs[div2.at(3)-48];
            
        }
        
        else {
            if (div2 == "CSA")
                divTwo = special_regs[0];
            else if (div2 == "CSB")
                divTwo = special_regs[1];
            else if (div2 == "CSC")
                divTwo = special_regs[2];
            else if (div2 == "CSP")
                divTwo = special_regs[3];
            else if (div2 == "CST")
                divTwo = special_regs[4];
            
        }
        
    }
    
    else if (div1 == "CST") {
        divOne = special_regs[4];
        
        if (div2 != "CSA" && div2 != "CSB" && div2 != "CSC" && div2 != "CSP" && div2 != "CST")  {
            
            divTwo = general_regs[div2.at(3)-48];
            
        }
        
        else {
            if (div2 == "CSA")
                divTwo = special_regs[0];
            else if (div2 == "CSB")
                divTwo = special_regs[1];
            else if (div2 == "CSC")
                divTwo = special_regs[2];
            else if (div2 == "CSP")
                divTwo = special_regs[3];
            else if (div2 == "CST")
                divTwo = special_regs[4];
            
        }
        
    }
    
    else {
        
        divOne = general_regs[div1.at(3)-48];
        
        if (div2 == "CSA")
            divTwo = special_regs[0];
        else if (div2 == "CSB")
            divTwo = special_regs[1];
        else if (div2 == "CSC")
            divTwo = special_regs[2];
        else if (div2 == "CSP")
            divTwo = special_regs[3];
        else if (div2 == "CST")
            divTwo = special_regs[4];
        
        else
            divTwo = general_regs[div2.at(3)-48];
        
    }
    
    divValue = divOne / divTwo;
    
    reminderValue = divOne % divTwo;
    
    array[1] = divValue;
    array2[2] = reminderValue;
    
}

void print ( DynamicIntStack &memory_stack) {   //This function print the value at the top of the memory stack.
    
    IntStackNode *ptr;
    
    ptr = memory_stack.GetTopPointer();
    
    cout << "Print Output: "<<ptr->value << endl;
    
    memory_stack.pop(ptr->value);
}


string operand1Index (string operand1) {        //This function is used for to find the index of operands which are used during calculation.
    
    string operand1Num;
    for (int i =0; i<sizeof(variables); i++) {
        
        if (variables[i] == operand1) {
            operand1Num= itoa (i);
            break;
        }
    }
    
    return operand1Num;
}


bool transform_source() {
    //It requests an input file and if it cannot be opened returns false
    //If the input file correctly opened, reads the file and
    //transform CS++ to Machine Language and stores the Machine Code instructions in `instruction_queue`
    
    string fileName,line,word;
    int top = -1;
    ifstream FileStr;
    
    stack<string> operation;
    stack <string> operation2;
    
    cout << "Please give me the input file name: ";                 //At this point program opens the given file.
    cin>> fileName;
    
    FileStr.open(fileName.c_str());
    
    if (FileStr.fail()) {
        return false;               //If it fails returns the menu.
        
    }
    
    else {
        
        getline(FileStr,line);
        
        while (getline(FileStr,line)) {             //Program first get line and by using stringstream pars the each given word.
            stringstream ss(line);
            ss >> word;
            
            if (word == "return") {         //If the CS++ Code is "return" then program put the command as "ret" to the command queue.
                
                string command= "ret";
                instruction_queue.enqueue(command);
                //cout << command << endl;
            }
            
            else if (word == "print") {     //If the CS++ Code is "print" then program push the printed value to the stack then print. (These are all command and stored in the command queue.)
                string value,last_digit;
                int a=0;
                ss >> value;
                
                for (int i =0; i< sizeof(variables); i++) {
                    
                    if (variables[i] == value) {
                        last_digit = value.at(value.length()-1);
                        a = stoi(last_digit)-1;
                        last_digit = itoa(a);
                        break;
                    }
                    
                }
                string command1= "push CSG" + last_digit;
                instruction_queue.enqueue(command1);
                //cout << command1 << endl;
                string command= "print";
                instruction_queue.enqueue(command);
                //cout << command << endl;
            }
            
            
            else if (word == "int") {       //If the word is "int" it means new variable is defining
                
                string var,sign;
                int bracketNum =0;
                ss>>var>>sign;
                
                top++;                      //DefCounter(for reg-var match) and top(for variable array) is incremented by one.
                def_counter++;
                variables[top]= var;
                
                
                if (sign == "=") {          //If sign is "=" it means there will be an assign operation.
                    string opp,chr;
                    ss>>opp;
                    
                    if (opp == "(" ) {      //If opp is "(" it means there will be an calculation.
                        
                        
                        operation.push(opp);
                        string command,command1,command2;
                        
                        while (ss>>opp) {       //Program reads the whole operation one by one.
                            
                            if (opp == ")") {   // If opp is ")" then it means a calculation is finished.
                                
                                
                                string var="",var2,sign,command,command2;
                                
                                
                                while (operation.top() != "(") {        //At this point program takes the variable in the calculation and put them to a stack.
                                    
                                    var = operation.top() + " ";
                                    operation2.push(var);
                                    operation.pop();
                                    
                                }
                                
                                
                                while (!operation2.empty() ) {         //At this to change the order of the variables, program put the variable to another stack.
                                    //Therefore, operation order does not change.
                                    var2 += operation2.top();
                                    operation2.pop();
                                    
                                    
                                }
                                
                                stringstream cc(var2);                  //At this point each calculation is read by the program.
                                string operand1,oprt,operand2;
                                
                                cc>>operand1>>oprt>>operand2;
                                
                                
                                if ( bracketNum == 0) {                 // If bracketNumber is 0 it means there are no any calculation left.
                                    // Therefore program do operation accordingly.
                                    string command = "pop";
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                    string command2 = "mov CST CSP";
                                    instruction_queue.enqueue(command2);
                                    //cout << command2 << endl;
                                    instruction_queue.enqueue(command); //pop again
                                    //cout << command << endl;
                                    
                                    operand1 = "CSP";
                                    operand2= "CST";
                                    
                                }
                                
                                if (oprt == "+") {                          //adding operation
                                    
                                    operation.pop();
                                    
                                    string command = "";
                                    command = "add " + operand1 + " "+operand2;
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                    command2 = "push CSA";
                                    instruction_queue.enqueue(command2);
                                    //cout << command2 << endl;
                                    
                                    
                                    operation.push("CSA");
                                    bracketNum --;
                                    
                                    
                                }
                                
                                else if (oprt == "-") {                     //substracting operation
                                    
                                    operation.pop();
                                    string command = "";
                                    
                                    command = "sub " + operand1 + " " + operand2;
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                    command2 = "push CSA";
                                    instruction_queue.enqueue(command2);
                                    //cout << command2 << endl;
                                    
                                    
                                    operation.push("CSA");
                                    bracketNum --;
                                }
                                
                                else if (oprt == "*") {                         //mul operation
                                    
                                    operation.pop();
                                    string command = "";
                                    
                                    
                                    command = "mul " + operand1 + " " + operand2;
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                    command2 = "push CSA";
                                    instruction_queue.enqueue(command2);
                                    //cout << command2 << endl;
                                    
                                    
                                    operation.push("CSA");
                                    bracketNum --;
                                }
                                
                                else if (oprt == "/") {                             //div operation
                                    
                                    operation.pop();
                                    string command = "";
                                    
                                    command = "div " + operand1 + " " + operand2;
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                    command2 = "push CSB";
                                    instruction_queue.enqueue(command2);
                                    //cout << command2 << endl;
                                    
                                    operation.push("CSB");
                                    bracketNum --;
                                }
                                
                                else if (oprt == "%") {                         //mod operation
                                    
                                    operation.pop();
                                    string command = "";
                                    
                                    command = "div " + operand1 + " " + operand2;
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                    command2 = "push CSC";
                                    instruction_queue.enqueue(command2);
                                    //cout << command2 << endl;
                                    
                                    operation.push("CSC");
                                    bracketNum --;
                                }
                                
                                
                            }
                            
                            
                            else if (opp == "(" ) {     //If program finds "(" sign is added to calculation stack.
                                operation.push(opp);
                                bracketNum ++;
                                //cout << operation.top()<< endl;
                                
                            }
                            
                            else if (opp.at(0) >= 48 && opp.at(0) <=57) {       //If program finds a variable (a1,etc), it is added to calculation stack.
                                
                                
                                operation.push(opp);
                                //cout << operation.top()<< endl;
                                
                                
                            }
                            
                            else if (opp == "+" ||opp == "-" || opp == "/" || opp == "*" || opp == "%" ) {  //If program finds an operation sign, it is added to calculation stack.
                                
                                
                                operation.push(opp);
                                //cout << operation.top()<< endl;
                                
                            }
                            
                            else if ((opp.at(0)>= 97 && opp.at(0) <=122) || (opp.at(0)>= 65 && opp.at(0) <=90)) {   //If program finds CSA,CSB etc. (a1,etc), it is added to calculation stack.
                                
                                operation.push(opp);
                                //cout << operation.top()<< endl;
                                
                                
                            }
                            
                        }
                        
                        string command3 = "pop";
                        instruction_queue.enqueue(command3);
                        //cout << command3 << endl;
                        
                        string command4 = "mov CSG"+ itoa(top) + " CSP";
                        instruction_queue.enqueue(command4);
                        //cout << command4 << endl;
                        
                        
                        
                    }
                    
                    else if (opp.at(0) >= 48 && opp.at(0) <=57) {           //mov CSG.. 1,2,3 etc.
                        
                        string name = itoa(top);
                        string command = "mov CGS" + name + " " + opp;
                        instruction_queue.enqueue(command);
                        //cout << command << endl;
                        
                    }
                    
                    else {          // mov CSG.. CSG..
                        
                        for (int i=0; i<sizeof(variables); i++) {
                            
                            if (variables[i]==opp) {
                                
                                string name = itoa(i);
                                string name2 = itoa(top);
                                string command = "mov CGS" + name2 + " " + "CGS" + name;
                                
                                instruction_queue.enqueue(command);
                                //cout << command << endl;
                                
                                break;
                            }
                            
                        }
                        
                    }
                    
                }
                
            }
            
            else {                                          //At this point, program is working with already defined variables. Following calculations and other            operations are same with the upside.
                string var,sign,opp;
                int bracketNum=0;
                ss >> sign >> opp;
                
                if (opp.at(0) >= 48 && opp.at(0) <=57) {
                    
                    char number = word.at(1);
                    int number1 = number - 48 ;
                    
                    string name = itoa(number1-1);
                    string command = "mov CSG" + name + " " + opp;
                    
                    
                    instruction_queue.enqueue(command);
                    //cout << command << endl;
                    
                }
                
                else if (opp == "(") {
                    
                    operation.push(opp);
                    
                    
                    while (ss>>opp) {
                        
                        if (opp == ")") {
                            
                            string var="",var2,sign,command,command2;
                            
                            
                            while (operation.top() != "(") {
                                
                                var = operation.top() + " ";
                                operation2.push(var);
                                operation.pop();
                                
                            }
                            
                            
                            
                            while (!operation2.empty() ) {
                                
                                var2 += operation2.top();
                                operation2.pop();
                                
                                
                            }
                            
                            stringstream cc(var2);
                            string operand1,oprt,operand2;
                            
                            cc>>operand1>>oprt>>operand2;
                            
                            if (operand1 == "CSA") {
                                operand1 = "CSP";
                            }
                            
                            else if (operand2 == "CSA") {
                                operand2= "CSP";
                            }
                            
                            
                            
                            
                            if ( bracketNum ==0 && oprt == "/") {
                                string command = "pop";
                                string command2 = "mov CST CSP";
                                instruction_queue.enqueue(command2);
                                //cout << command2 << endl;
                                instruction_queue.enqueue(command); //pop again
                                //cout << command << endl;
                                
                                operand1 = "CSP";
                                operand2= "CST";
                                
                            }
                            
                            if (oprt == "+") { //adding operation
                                
                                operation.pop();
                                
                                string operand1Num,operand2Num;
                                string command = "";
                                
                                if (operand1 != "CSA") {
                                    operand1Num = operand1Index(operand1);
                                    
                                }
                                
                                if (operand2 != "CSA") {
                                    operand2Num = operand1Index(operand2);
                                }
                                
                                
                                
                                if ( (operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0)>= 97 && operand2.at(0) <=122) ) {
                                    command = "add CSG" + operand1Num + " "+ "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0) >= 48 && operand2.at(0) <=57)) {
                                    command = "add CSG" + operand1Num + " " + operand2;
                                    
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0) >= 48 && operand1.at(0) <=57)) {
                                    command = "add " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 65 && operand1.at(0) <=90) && (operand2.at(0)>= 97 && operand2.at(0) <=122)) {
                                    
                                    command = "add " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0)>= 65 && operand1.at(0) <=90) ) {
                                    
                                    command = "add " + operand2 + " " + "CSG" + operand1Num;
                                }
                                
                                else { //add num CSP
                                    
                                    command = "add CSG" + operand1Num + " " + operand2;
                                }
                                
                                instruction_queue.enqueue(command);
                                //cout << command << endl;
                                command2 = "push CSA";
                                instruction_queue.enqueue(command2);
                                //cout << command2 << endl;
                                
                                operation.push("CSA");
                                
                                bracketNum --;
                                if (bracketNum > 0) {
                                    command = "pop";
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                }
                                
                                
                            }
                            
                            else if (oprt == "-") { //substracting operation
                                
                                operation.pop();
                                
                                string command = "";
                                string operand1Num,operand2Num;
                                
                                
                                if (operand1 != "CSA") {
                                    operand1Num = operand1Index(operand1);
                                    
                                }
                                
                                if (operand2 != "CSA") {
                                    operand2Num = operand1Index(operand2);
                                }
                                
                                
                                if ( (operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0)>= 97 && operand2.at(0) <=122) ) {
                                    command = "sub CSG" + operand1Num + " "+ "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0) >= 48 && operand2.at(0) <=57)) {
                                    command = "sub CSG" + operand1Num + " " + operand2;
                                    
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0) >= 48 && operand1.at(0) <=57)) {
                                    command = "sub " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 65 && operand1.at(0) <=90) && (operand2.at(0)>= 97 && operand2.at(0) <=122)) {
                                    
                                    command = "sub " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0)>= 65 && operand1.at(0) <=90) ) {
                                    
                                    command = "sub " + operand2 + " " + "CSG" + operand1Num;
                                }
                                
                                
                                else { //mul num CSP
                                    
                                    command = "sub CSG" + operand1Num + " " + operand2;
                                }
                                
                                instruction_queue.enqueue(command);
                                //cout << command << endl;
                                command2 = "push CSA";
                                instruction_queue.enqueue(command2);
                                //cout << command2 << endl;
                                
                                operation.push("CSA");
                                
                                bracketNum--;
                                if (bracketNum >0) {
                                    command = "pop";
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                }
                                
                                
                                
                            }
                            
                            else if (oprt == "*") { //mul operation
                                
                                operation.pop();
                                
                                string command = "";
                                
                                string operand1Num,operand2Num;
                                
                                if (operand1 != "CSA") {
                                    operand1Num = operand1Index(operand1);
                                    
                                }
                                
                                if (operand2 != "CSA") {
                                    operand2Num = operand1Index(operand2);
                                }
                                
                                
                                if ( (operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0)>= 97 && operand2.at(0) <=122) ) { //mul CSG.. CSG..
                                    command = "mul CSG" + operand1Num + " "+ "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0) >= 48 && operand2.at(0) <=57)) { //mul CSG.. 1,2,3
                                    command = "mul CSG" + operand1Num + " " + operand2;
                                    
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0) >= 48 && operand1.at(0) <=57)) { //mul a.. CSG..
                                    command = "mul " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 65 && operand1.at(0) <=90) && (operand2.at(0)>= 97 && operand2.at(0) <=122)) {
                                    
                                    command = "mul " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0)>= 65 && operand1.at(0) <=90) ) {
                                    
                                    command = "mul " + operand2 + " " + "CSG" + operand1Num;
                                }
                                
                                else { //mul num CSP
                                    
                                    command = "mul CSG" + operand1Num + " " + operand2;
                                }
                                
                                instruction_queue.enqueue(command);
                                //cout << command << endl;
                                command2 = "push CSA";
                                instruction_queue.enqueue(command2);
                                //cout << command2 << endl;
                                
                                operation.push("CSA");
                                
                                bracketNum--;
                                if (bracketNum >0) {
                                    command = "pop";
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                }
                                
                                
                                
                            }
                            
                            else if (oprt == "/") { //substracting operation
                                
                                operation.pop();
                                
                                string command = "";
                                
                                string operand1Num,operand2Num;
                                
                                
                                if (operand1 != "CSA") {
                                    operand1Num = operand1Index(operand1);
                                    
                                }
                                
                                if (operand2 != "CSA") {
                                    operand2Num = operand1Index(operand2);
                                }
                                
                                
                                
                                if ( (operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0)>= 97 && operand2.at(0) <=122) ) {
                                    command = "div CSG" + operand1Num + " "+ "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0) >= 48 && operand2.at(0) <=57)) {
                                    command = "div CSG" + operand1Num + " " + operand2;
                                    
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0) >= 48 && operand1.at(0) <=57)) {
                                    command = "div " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 65 && operand1.at(0) <=90) && (operand2.at(0)>= 97 && operand2.at(0) <=122)) {
                                    
                                    command = "div " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0)>= 65 && operand1.at(0) <=90) ) {
                                    
                                    command = "div " + operand2 + " " + "CSG" + operand1Num;
                                }
                                
                                else if ((operand1.at(0)>= 65 && operand1.at(0) <=90) && (operand2.at(0)>= 65 && operand2.at(0) <=90)) {
                                    command = "div " + operand1 + " " + operand2;
                                    
                                }
                                
                                else { //mul num CSP
                                    
                                    command = "div CSG" + operand1Num + " " + operand2;
                                }
                                
                                instruction_queue.enqueue(command);
                                //cout << command << endl;
                                command2 = "push CSB";
                                instruction_queue.enqueue(command2);
                                //cout << command2 << endl;
                                
                                operation.push("CSB");
                                
                                bracketNum --;
                                if (bracketNum >0) {
                                    command = "pop";
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                }
                                
                                
                                
                                //int b = stoi(operand1) % stoi(operand2);
                                //special_regs[2] = b;
                                
                                
                            }
                            else if (oprt == "%") { //mod operation
                                
                                operation.pop();
                                
                                string command = "";
                                
                                string operand1Num,operand2Num;
                                
                                
                                if (operand1 != "CSA") {
                                    operand1Num = operand1Index(operand1);
                                    
                                }
                                
                                if (operand2 != "CSA") {
                                    operand2Num = operand1Index(operand2);
                                }
                                
                                
                                
                                if ( (operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0)>= 97 && operand2.at(0) <=122) ) {
                                    command = "div CSG" + operand1Num + " "+ "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 97 && operand1.at(0) <=122) && (operand2.at(0) >= 48 && operand2.at(0) <=57)) {
                                    command = "div CSG" + operand1Num + " " + operand2;
                                    
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0) >= 48 && operand1.at(0) <=57)) {
                                    command = "div " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand1.at(0)>= 65 && operand1.at(0) <=90) && (operand2.at(0)>= 97 && operand2.at(0) <=122)) {
                                    
                                    command = "div " + operand1 + " " + "CSG" + operand2Num;
                                }
                                
                                else if ((operand2.at(0)>= 97 && operand2.at(0) <=122) && (operand1.at(0)>= 65 && operand1.at(0) <=90) ) {
                                    
                                    command = "div " + operand2 + " " + "CSG" + operand1Num;
                                }
                                
                                else { //mul num CSP
                                    
                                    command = "div CSG" + operand1Num + " " + operand2;
                                }
                                
                                instruction_queue.enqueue(command);
                                //cout << command << endl;
                                command2 = "push CSC";
                                instruction_queue.enqueue(command2);
                                //cout << command2 << endl;
                                
                                
                                //int b = stoi(operand1) % stoi(operand2);
                                //special_regs[2] = b;
                                
                                operation.push("CSC");
                                
                                bracketNum --;
                                if (bracketNum >=0) {
                                    command = "pop";
                                    instruction_queue.enqueue(command);
                                    //cout << command << endl;
                                }
                                
                                
                                
                            }
                            
                            
                        }
                        
                        
                        else if (opp == "(" ) {
                            bracketNum++;
                            operation.push(opp);
                            
                            //cout << operation.top()<< endl;
                            
                        }
                        
                        else if (opp.at(0) >= 48 && opp.at(0) <=57) {
                            
                            
                            operation.push(opp);
                            //cout << operation.top()<< endl;
                            
                            
                        }
                        
                        else if (opp == "+" ||opp == "-" || opp == "/" || opp == "*" || opp == "%" ) {
                            
                            
                            operation.push(opp);
                            //cout << operation.top()<< endl;
                            
                        }
                        
                        else if ((opp.at(0)>= 97 && opp.at(0) <=122) || (opp.at(0)>= 65 && opp.at(0) <=90)) {
                            
                            operation.push(opp);
                            //cout << operation.top()<< endl;
                            
                            
                        }
                        
                    }
                    
                    string command3 = "pop";
                    instruction_queue.enqueue(command3);
                    //cout << command3 << endl;
                    
                    string command4 = "mov CSG"+ itoa(top) + " CSP";
                    instruction_queue.enqueue(command4);
                    //cout << command4 << endl;
                    
                    
                    
                }
                
                
                
                else {
                    
                    for (int i=0; i<sizeof(variables); i++) {
                        
                        if (variables[i]==opp) {
                            
                            
                            string name = itoa(top);
                            string name2 = itoa(i);
                            
                            
                            string command = "mov CGS" + name + " " + "CGS" + name2;
                            
                            instruction_queue.enqueue(command);
                            //cout << command << endl;
                            
                            break;
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    
    return true;
    
}

void print_next_instruction();

void run_one_instruction() {
    //dequeue one instruction from `instruction_queue` and run it accordingly
    
    if (instruction_queue.isEmpty()) {
        
        cout << "There is no instruction left." << endl;
        check = false;
        
        
    }
    
    else {          //If queue is not empty, program run commands one-by-one
        
        string word,command;
        instruction_queue.dequeue(command);
        
        stringstream ss(command);
        
        ss>>word;
        
        executeCode(word,ss);                                       //This function is defined below, it reads each command and do the operations accordingly.
        cout << "Executed instruction: "<< command << endl;
    }
}

void run_until_end() {
    //run all the instructions in the queue
    
    if (instruction_queue.isEmpty()) {
        
        cout << "There is no instruction left." << endl;
        
    }
    
    while (!instruction_queue.isEmpty()) {                  //If queue is not empty, program run commands until the end.
        
        string command,word;
        instruction_queue.dequeue(command);
        
        stringstream ss(command);
        while (ss>>word) {
            
            executeCode(word,ss);       //This function is defined below, it reads each command and do the operations accordingly.
            
            
        }
        
    }
    
}

void print_stack() {
    //print the values in the `memory_stack`
    
    if (memory_stack.isEmpty()) {
        
        cout << "Current stack is empty" << endl;
        
    }
    
    else {                                                                //Current stack is printed by this function.
        IntStackNode *ptr;
        
        ptr = memory_stack.GetTopPointer();
        
        cout << "Current Stack" << endl;
        cout << endl;
        cout << " "<< " "<< " " << " "<<ptr->value<< endl;
        
    }
}


void print_registers() {
    //print the registers
    
    cout <<" " <<" "<<" "<<" "<<"SPECIAL REGISTERS" << endl;
    
    cout << endl;
    
    cout << " " <<" "<<" "<<" "<< " "<< "CSA: "<<special_regs[0] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSB: "<<special_regs[1] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSC: "<<special_regs[2] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSP: "<<special_regs[3] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CST: "<<special_regs[4] << endl;
    
    cout << endl;
    cout << " " <<" "<<" "<<" "<<"GENERAL USE REGISTERS" << endl;
    cout << endl;
    
    cout << " " <<" "<<" "<<" "<< " "<< "CSG0: "<<general_regs[0] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG1: "<<general_regs[1] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG2: "<<general_regs[2] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG3: "<<general_regs[3] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG4: "<<general_regs[4] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG5: "<<general_regs[5] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG6: "<<general_regs[6] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG7: "<<general_regs[7] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG8: "<<general_regs[8] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG9: "<<general_regs[9] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG10: "<<general_regs[10] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG11: "<<general_regs[11] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG12: "<<general_regs[12] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG13: "<<general_regs[13] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG14: "<<general_regs[14] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG15: "<<general_regs[15] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG16: "<<general_regs[16] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG17: "<<general_regs[17] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG18: "<<general_regs[18] << endl;
    cout << " " <<" "<<" "<<" "<< " "<< "CSG19: "<<general_regs[19] << endl;
    
    
}


void print_next_instruction() {
    //This function is called after using "run one-by-one" operation and also user can call this function seperately.
    //print the next Machine Code instruction to be executed
    
    if (check != false) {       //check false means if "there is no any instruction" warning given by the one-by-one execution option, no needed to repeat it again.
        StrQueueNode *ptr;
        
        if (instruction_queue.isEmpty()) {
            cout << "There is no instruction left."<< endl;
        }
        
        else {
            ptr = instruction_queue.GetFront();
            
            if (ptr->value == "" ) {
                
                cout << "There is no instruction left." << endl;
                
            }
            
            else {
                
                cout << "Next instruction is: "<<ptr->value<< endl;
            }
            
        }
        
    }
}


void print_remaining_instructions(int instr_counter) {
    //print the remaining instructions to execute in the `instruction_queue`
    
    StrQueueNode *ptr = nullptr;
    
    if (instruction_queue.isEmpty()) {
        cout << "There is no instruction left." << endl;
    }
    
    else {
        
        string command;
        ptr=instruction_queue.GetFront();
        
        while (!(ptr->value == "ret")) {
            
            cout << "["<< instr_counter<<"]"<< ptr->value << endl;
            ptr = ptr->next;
            instr_counter++;
            
        }
        
        cout << "["<< instr_counter<<"]"<< "ret" << endl;
        
        
    }
    
}


void print_variables() {
    //print the defined variables and their values
    
    cout << "******** DEFINED VARIABLES ********" << endl;
    
    for (int i = 0; i< def_counter ; i++) {
        
        cout << variables[i] <<": " <<general_regs[i] << endl;
        
    }
    
    
    
}


int main() {
    bool input_OK = false;
    while (true) {
        cout << endl;
        cout << "***********************************************************************" << endl
        << "**************** 0 - EXIT PROGRAM                          ************" << endl
        << "**************** 1 - GIVE INPUT FILE                       ************" << endl
        << "**************** 2 - RUN UNTIL THE END                     ************" << endl
        << "**************** 3 - RUN ONE INSTRUCTION                   ************" << endl
        << "**************** 4 - PRINT CURRENT STACK                   ************" << endl
        << "**************** 5 - PRINT REGISTER VALUES                 ************" << endl
        << "**************** 6 - PRINT NEXT INSTRUCTION                ************" << endl
        << "**************** 7 - PRINT REMAINING INSTRUCTIONS          ************" << endl
        << "**************** 8 - PRINT DEFINED VARIABLES               ************" << endl
        << "***********************************************************************" << endl;
        cout << endl;
        int option;
        cout << "Pick an option from above (int number from 0 to 8): ";
        cin >> option;
        switch (option)
        {
            case 0:
                cout << "PROGRAM EXITING ... " << endl;
                system("pause");
                exit(0);
            case 1:
                clear_regs_vars();
                if (transform_source()) {
                    input_OK = true;
                }
                else {
                    cout << "There is a problem with the input file." << endl;
                }
                break;
            case 2:
                if (input_OK) {
                    run_until_end();
                }
                else {
                    cout << "First give an input file." << endl;
                }
                break;
            case 3:
                if (input_OK) {
                    run_one_instruction();
                    print_next_instruction();
                }
                else {
                    cout << "First give an input file." << endl;
                }
                break;
            case 4:
                if (input_OK) {
                    print_stack();
                }
                else {
                    cout << "First give an input file." << endl;
                }
                break;
            case 5:
                if (input_OK) {
                    print_registers();
                }
                else {
                    cout << "First give an input file." << endl;
                }
                break;
            case 6:
                if (input_OK) {
                    print_next_instruction();
                }
                else {
                    cout << "First give an input file." << endl;
                }
                break;
            case 7:
                if (input_OK) {
                    print_remaining_instructions(instr_counter);
                }
                else {
                    cout << "First give an input file." << endl;
                }
                break;
            case 8:
                if (input_OK) {
                    print_variables();
                }
                else {
                    cout << "First give an input file." << endl;
                }
                break;
            default:
                cout << "INVALID OPTION!!! Try again" << endl;
        }
    }
    
    return 0;
}



void operation (string value1, string value2 , int array[] , string valueType) {        //This function is for add,sub and mul operations.
    
    
    int value=0;
    int valOne=0, valTwo=0;
    
    if (value1 == "CSA") {
        
        valOne = special_regs[0];
        
        if (value2 != "CSA" && value2 != "CSB" && value2 != "CSC" && value2 != "CSP" && value2 != "CST")  {
            
            valTwo = general_regs[value2.at(3)-48];
            
        }
        
        else {
            if (value2 == "CSA")
                valTwo = special_regs[0];
            else if (value2 == "CSB")
                valTwo = special_regs[1];
            else if (value2 == "CSC")
                valTwo = special_regs[2];
            else if (value2 == "CSP")
                valTwo = special_regs[3];
            else if (value2 == "CST")
                valTwo = special_regs[4];
            
        }
    }
    
    else if (value1 == "CSB") {
        
        valOne = special_regs[1];
        
        if (value2 != "CSA" && value2 != "CSB" && value2 != "CSC" && value2 != "CSP" && value2 != "CST")  {
            
            valTwo = general_regs[value2.at(3)-48];
            
        }
        
        else {
            if (value2 == "CSA")
                valTwo = special_regs[0];
            else if (value2 == "CSB")
                valTwo = special_regs[1];
            else if (value2 == "CSC")
                valTwo = special_regs[2];
            else if (value2 == "CSP")
                valTwo = special_regs[3];
            else if (value2 == "CST")
                valTwo = special_regs[4];
            
        }
        
    }
    
    else if (value1 == "CSC") {
        
        value1 = special_regs[2];
        
        if (value2 != "CSA" && value2 != "CSB" && value2 != "CSC" && value2 != "CSP" && value2 != "CST")  {
            
            valTwo = general_regs[value2.at(3)-48];
            
        }
        
        else {
            if (value2 == "CSA")
                valTwo = special_regs[0];
            else if (value2 == "CSB")
                valTwo = special_regs[1];
            else if (value2 == "CSC")
                valTwo = special_regs[2];
            else if (value2 == "CSP")
                valTwo = special_regs[3];
            else if (value2 == "CST")
                valTwo = special_regs[4];
            
        }
    }
    
    else if (value1 == "CSP") {
        valOne = special_regs[3];
        
        if (value2 != "CSA" && value2 != "CSB" && value2 != "CSC" && value2 != "CSP" && value2 != "CST")  {
            
            valTwo = general_regs[value2.at(3)-48];
            
        }
        
        else {
            if (value2 == "CSA")
                valTwo = special_regs[0];
            else if (value2 == "CSB")
                valTwo = special_regs[1];
            else if (value2 == "CSC")
                valTwo = special_regs[2];
            else if (value2 == "CSP")
                valTwo = special_regs[3];
            else if (value2 == "CST")
                valTwo = special_regs[4];
            
        }
        
    }
    
    else if (value1 == "CST") {
        valOne = special_regs[4];
        
        if (value2 != "CSA" && value2 != "CSB" && value2 != "CSC" && value2 != "CSP" && value2 != "CST")  {
            
            valTwo = general_regs[value2.at(3)-48];
            
        }
        
        else {
            if (value2 == "CSA")
                valTwo = special_regs[0];
            else if (value2 == "CSB")
                valTwo = special_regs[1];
            else if (value2 == "CSC")
                valTwo = special_regs[2];
            else if (value2 == "CSP")
                valTwo = special_regs[3];
            else if (value2 == "CST")
                valTwo = special_regs[4];
            
        }
        
    }
    
    else {
        
        if (value1.at(0)>=65 && value1.at(0) <=95) {
            valOne = general_regs[value1.at(3)-48];
        }
        
        else {
            
            valOne = stoi(value1);
        }
        
        if (value2 == "CSA")
            valTwo = special_regs[0];
        else if (value2 == "CSB")
            valTwo = special_regs[1];
        else if (value2 == "CSC")
            valTwo = special_regs[2];
        else if (value2 == "CSP")
            valTwo = special_regs[3];
        else if (value2 == "CST")
            valTwo = special_regs[4];
        
        else
            
            if (value2.at(0)>=65 && value2.at(0) <=95)
                valTwo = general_regs[value2.at(3)-48];
            else
                valTwo = stoi(value2);
        
    }
    
    if (valueType == "add") {
        
        value = valOne + valTwo;
        
        array[0] = value;
    }
    
    else if (valueType == "sub") {
        
        value = valOne - valTwo;
        
        array[0] = value;
        
    }
    
    else if (valueType == "mul") {
        value = valOne * valTwo;
        
        array[0] = value;
        
    }
    
}

void executeCode(string word, stringstream &ss) {   //This function is determine the commands and do the operations accordingly.
    
    
    if (word == "push") {
        
        string var;
        ss>>var;
        
        push(var, memory_stack);
        
    }
    
    else if (word == "mov") {
        
        string var1,var2;
        ss>>var1>>var2;
        
        mov(var1, var2);
        
    }
    
    else if (word == "pop") {
        
        pop(memory_stack, special_regs);
        
        
    }
    
    else if (word == "add") {
        
        string var1,var2;
        ss>>var1>>var2;
        
        add(var1, var2, special_regs);
        
        
    }
    
    else if (word == "sub") {
        
        string var1,var2;
        ss>>var1>>var2;
        
        
        sub(var1, var2, special_regs);
        
        
    }
    
    else if (word == "mul") {
        
        string var1,var2;
        ss>>var1>>var2;
        
        mul(var1, var2, special_regs);
        
    }
    
    else if (word == "div") {
        
        string var1,var2;
        ss>>var1>>var2;
        
        division(var1, var2, special_regs,special_regs);
        
    }
    
    else if (word == "print") {
        
        print(memory_stack);
        
    }
    
    else if (word == "ret") {
        
        
    }
    
}
