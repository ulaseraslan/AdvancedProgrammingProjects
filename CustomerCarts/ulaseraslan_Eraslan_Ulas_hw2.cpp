//
//  ulaseraslan_eraslan_ulas_hw2.cpp
//  CS 204 HW2 Sabanci University Kamer Kaya
//
//  Created by Ulaş Eraslan on 29.09.2019.
//  Copyright © 2019 Ulaş Eraslan. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Product {                //This is a struct of a Product which has product id, product name, product amount and product's pointer.
    int prod_id;
    string prod_name;
    int amount;
    Product * next;
};

struct Customer{                //This is a struct of a Customer which has customer id, customer name, customer amount,customer's next pointer, previous pointer and product pointer.
    int cust_id;
    string cust_name;
    Customer * prev;
    Customer * next;
    Product * prod;
    
    Customer (int id,string name, Customer *prev, Customer *next, Product *prod)
    : cust_id(id),
    cust_name(name),
    prev(prev),                     //This struct has a constructor.
    next(next),
    prod(prod)
    {}
    
};
void addToProduct (int product_id, string product_name, int product_amount, Product *&head);
void addToCustomer(int Id, string name, Customer *&head, Customer *tail,Product *prod);

void print_customer_data(Customer *CustomerHead) {      //This functions prints the customer's data.
    
    Customer *ptr = CustomerHead;
    
    if (ptr == nullptr) {
        cout << "List is empty"<< endl;
    }
    else {
        
        while (ptr->next != nullptr) {
            cout << "ID: " << ptr ->next-> cust_id <<" "<<" Name: "<<ptr ->next-> cust_name<<endl;
            cout << "Items in the cart: "<< endl;
            
            Product* ptr2 = ptr->next->prod;
            
            while (ptr2 != nullptr && ptr2->next != nullptr) {
                
                if (ptr2->next->prod_id == -1) {
                    ptr2 = ptr2->next;
                    continue;
                }
                
                cout << "Item ID: " << ptr2->next->prod_id << " Item name: " << ptr2->next->prod_name << "." << " "<< " Amount: "<<ptr2->next->amount<< endl;
                ptr2 = ptr2->next;
                
            }
            
            ptr= ptr->next;
            cout << endl;
            
        }
    }
}

void find_customer(Customer *head) {            //This function finds the customer which is given by the user..
    
    Customer *ptr = head;
    string answer,cust_name;
    int id=0;
    
    cout << "Enter cutomer's ID or name and surname: ";
    cin.ignore();
    getline(cin,answer);
    bool a= false;
    
    
    if (answer.at(0)<48 || answer.at(0) >57) {      //If answer is not string program continue accordingly.
        
        while (ptr->next != nullptr) {
            
            if (ptr->next->cust_name == answer) {
                
                cout << "Customer found!"<< endl;
                cout << "ID: " << ptr ->next-> cust_id <<" "<<" Name:  "<<ptr ->next-> cust_name<<endl;
                cout << "Items in the cart:"<< endl;
                
                while (ptr->next->prod !=nullptr) {
                    
                    if (ptr->next->prod->prod_id == -1) {       //At this point function does not print the garbage node of the list.
                        ptr->next->prod = ptr ->next->prod->next;
                    }
                    
                    cout << "Item ID: " << ptr->next->prod->prod_id << " Item name: " << ptr->next->prod->prod_name << "." << " "<< " Amount: "<<
                    ptr->next->prod->amount<< endl;
                    ptr->next->prod = ptr ->next->prod->next;
                    a= true;
                }
                ptr = ptr->next; //To check the same name customer.
            }
            else {
                ptr = ptr->next; // If the corresponding node does not consist the given name, pointer will be the next to check.
            }
            
        }
        if (ptr->next == nullptr && a==false) {
            cout << "CUSTOMER DOESN'T EXIST. GOING BACK TO MENU"<< endl;
        }
    }
    
    else {
        id = stoi(answer);          //If the given input is name and surname program countinues accordingly.
        
        while (ptr->next != nullptr) {
            
            if (ptr->next->cust_id == id) {
                
                cout << "Customer found!"<< endl;
                cout << "ID: " << ptr ->next-> cust_id <<" "<<" Name:  "<<ptr ->next-> cust_name<<endl;
                cout << "Items in the cart:"<< endl;
                
                while (ptr->next->prod !=nullptr) {
                    
                    if (ptr->next->prod->prod_id == -1) {
                        ptr->next->prod = ptr ->next->prod->next;
                    }
                    
                    cout << "Item ID: " << ptr->next->prod->prod_id << " Item name: " << ptr->next->prod->prod_name << "." << " "<< " Amount: "<<
                    ptr->next->prod->amount<< endl;
                    ptr->next->prod = ptr ->next->prod->next;
                    
                }
                break;
            }
            else {
                ptr = ptr->next;
            }
        }
        
        if (ptr->next == nullptr) {
            cout << "CUSTOMER DOESN'T EXIST. GOING BACK TO MENU"<< endl;
        }
    }
    
}

void add_customer(Customer *head) {     //This function add a new customer to the list.
    string name;
    int cust_id;
    bool check= false;
    Customer *ptr = head;
    Customer *ptr2 = head;
    
    cout << "Enter an ID for the user: ";
    cin >> cust_id;
    
    while (ptr->next != nullptr) {          //Checks until the pointer points null.
        
        if (ptr->next->cust_id == cust_id) {    //If the given ID is in the list already program  backs to menu.
            
            cout << "User with ID: " << cust_id<< " already exists. Going back to menu." <<endl;
            check = true;
            break;
        }
        else {
            ptr=ptr->next;
        }
    }
    
    if (check == false) { //If given ID is not in the list program asks the user's name and surname.
        cout << "Please enter the user's name and surname: ";
        cin.ignore();
        getline(cin,name);
        
        addToCustomer(cust_id, name, ptr2, nullptr, nullptr);    //Program adds the given user to the list by addToCustomer function.
        cout << "User with ID: "<< cust_id<< " is insterted to the list." << endl;
    }
    
    
}

void DeleteList (Product *head) {       //This is a recursive function which delete a linked list.
    if (head) {
        DeleteList(head->next);
        delete head;
    }
}


void delete_customer(Customer *head) {  //Given input by the user deleted by this function.
    int cust_id2=0;
    bool check = 0;
    Customer *ptr=head;
    Customer *ptr3=nullptr;
    
    cout << "Enter an ID for the customer to be deleted: ";
    cin >> cust_id2;
    
    while (ptr->next != nullptr) {      //Until pointer finds the null loop continues.
        
        if (ptr->next->cust_id == cust_id2 ) {
            Product* ptr2 = ptr->next->prod;
            while (head->next->prod->next !=nullptr) {
                
                DeleteList(ptr2); //Function calls the recursive delete funciton which is defined at the above to delete the customer's products.
                
                ptr3 = ptr->next;
                ptr->next = ptr->next->next;    //Then program delete customer's node.
                delete ptr3;
                
                cout << "Customer is deleted succesfully." << endl;
                check=1;
                break;
            }
            if (check == 1) {
                break;
            }
        }
        ptr = ptr->next;
        
    }
    
    if (check==0) {
        cout << "CUSTOMER DOESN'T EXIST. GOING BACK TO MENU"<< endl;
    }
}

void add_product(Customer *head) {  //This function adds a new product to Customer.
    int cust_id,item_id,prod_amount;
    string answ,prod_name;
    bool name_exist=false;
    
    Customer *ptr = head;
    
    cout << "Enter an ID for the Customer to add product: ";
    cin>> cust_id;
    
    while (ptr->next != nullptr) {
        
        if (ptr->next->cust_id == cust_id) {    //Program checks the list if the given customer id in the list or not.
            name_exist=true;
            cout <<"Would you like to add item to cart(Y/y): ";
            cin>> answ;
            while (answ == "Y" || answ == "y") {
                
                cout << "ID of the item to add to cart: ";
                cin>>item_id;
                bool product_exist=false;
                if(ptr->next->prod != nullptr){
                    Product* ptr2 = ptr->next->prod;
                    
                    while (ptr2->next != nullptr) { //Program checks the item id given by user if it is in the list or not.
                        
                        if (ptr2->next->prod_id == item_id) { //If given item id is in the list.
                            product_exist = true;
                            cout << "Product aldready exists. How many would you like to add more: ";
                            cin>>prod_amount;
                            
                            ptr2->next->amount +=prod_amount;   //Exsisted item is increased.
                            
                            cout <<"Product's amount in the cart increased to: "<< ptr2->next->amount<< endl;
                            cout <<"Would you like to add item to cart(Y/y): ";
                            cin>> answ;
                            break;
                            
                        }
                        
                        else {
                            ptr2 = ptr2->next;
                        }
                    }
                }
                if(product_exist == false) { //If given item id is not in the list.
                    Product* ptr2 = ptr->next->prod;
                    
                    if (ptr2 == nullptr) {  //New product is created.
                        Product *prod = new Product;
                        prod->prod_id = -1;
                        prod->prod_name = "temp";
                        prod->amount = -1;
                        prod->next=nullptr;
                    }
                    
                    cout << "Name of the product: ";
                    cin.ignore();
                    getline(cin,prod_name);
                    
                    cout << "Amount: ";
                    cin>>prod_amount;
                    addToProduct(item_id,prod_name,prod_amount,ptr->next->prod); //Given information by the user such as id of the item,amount and name is added to the corresponded customer's product list.
                    cout <<"Would you like to add item to cart(Y/y): ";
                    cin>> answ;
                    
                    
                }
                
            }
            
            if (answ!= "Y" ||answ != "y") {
                cout << "Going back to menu." << endl;
                break;
            }
        }
        
        else {
            ptr=ptr->next;
            
        }
        
    }
    
    if (name_exist==0){
        cout <<"CUSTOMER DOESN'T EXIST. GOING BACK TO MENU" << endl;
    }
    
}


void delete_product(Customer *head) { //This function delete a product of given customer.
    int customer_id,prod_id;
    Customer *ptr = head;
    bool check1= false,check2=false;
    cout << "Enter an ID for the Customer to delete product: " ;
    cin>> customer_id;
    
    while (ptr->next != nullptr) {
        if (ptr->next->cust_id == customer_id) {    //If customer id is found program continues.
            cout << "ID of the item to delete from cart: ";
            cin >> prod_id;
            check1=true;
            Product *ptr2= ptr->next->prod;
            while (ptr2 != nullptr) {
                if (ptr2->next->prod_id == prod_id) {   //If the product is in the list program deletes it.
                    
                    Product *ptr3 = ptr2->next;
                    ptr2->next=ptr3->next;
                    delete ptr3;
                    cout << "Product has been deleted." << endl;
                    cout << "Current items in the cart: " << endl;
                    
                    cout << "ID: " << ptr->next->cust_id << " Name: "<<ptr->next->cust_name <<endl;
                    
                    if (ptr->next->prod->next != nullptr ) {
                        while (ptr->next->prod != nullptr) {
                            
                            if (ptr->next->prod->prod_id == -1) {       //Program skips the node which consists garbage value in it.
                                ptr->next->prod=ptr->next->prod->next;
                            }
                            
                            cout << "ID: " << ptr->next->prod->prod_id << " Item name: " << ptr->next->prod->prod_name << " Amounts: " << ptr->next->prod->amount << endl;          //Print condition of the customer after deleting the item.
                            ptr->next->prod=ptr->next->prod->next;
                            
                            
                        }
                    }
                    check2=true;
                    break;
                }
                else {
                    ptr2=ptr2->next;
                }
            }
            if (check2== false){
                cout << "Product doesn't exists. Going back to main menu. " << endl;
                break;
            }
            
        }
        else {
            ptr = ptr->next;
        }
        
        if (check2==true) {
            break;
        }
    }
    
    if (check1 == false) {
        cout << "Customer with ID: " << customer_id << " doesn't exists. Going back to menu." << endl;
    }
    
}

void list_product_owners(Customer *head) {      //This function lists the customers who have the given item.
    int prod_id;
    
    cout << "ID of the product to search buyers: ";
    cin>> prod_id;
    bool check = false;
    Customer *ptr = head->next;
    Customer *lptr = nullptr;
    
    while (ptr->next!=nullptr) {        //Program go to the end of the list.
        ptr=ptr->next;
    }
    
    lptr = ptr;
    
    while (lptr->prev != nullptr) {      //By starting at the end of the list, program search the customers who have the given item.
        
        while (lptr->prod != nullptr) {  //Program search the each customer's product list.
            
            if (lptr->prod->prod_id == prod_id) {    //If id is found customer informations are printed.
                
                cout << "Customer ID: " << lptr->cust_id << " Customer name: " << lptr->cust_name << " and Amount: " << lptr->prod->amount << endl;
                check=true;
                break;
            }
            else {
                lptr->prod=lptr->prod->next;
            }
            
        }
        
        lptr=lptr->prev;
        
    }
    
    if (check==false) {
        cout <<"Product doesn't exists. Going back to main menu. " << endl;
    }
    
    
}

void addToCustomer(int Id, string name, Customer *&head, Customer *tail,Product *prod) { //This function is add product linked lists to customers and create doubly linked of customers
    
    Customer *heady = new Customer(-1,"temp",nullptr,nullptr,nullptr); //Heady is a node which consists garbage value.
    Customer *temp = new Customer(Id,name,nullptr,nullptr,nullptr);         //These pointers used to create new customers.
    Customer *temp2 = head;
    
    if(head == nullptr) {   //If there is nothing in the list, node which consists garbage value added to the list.
        
        head= heady;
        temp2 = head;
        
        while (temp2->next != tail && temp2->cust_id < temp->cust_id) {     //This is a sorting step.
            if(temp2->next->cust_id < temp->cust_id)
                temp2 = temp2->next;
            else
                break;
        }
        
        temp->next = temp2->next;
        temp->prev = temp2;                 //At this point node is inserted to the list.
        temp2->next= temp;
        
        temp->prod= prod;
    }
    
    
    else {
        
        while (temp2->next != tail && temp2->cust_id < temp->cust_id) {     //At this point program creates new nodes and add to the lists as a sorted order.
            if(temp2->next->cust_id < temp->cust_id)
                temp2 = temp2->next;
            else
                break;
        }
        
        temp->next = temp2->next;
        temp->prev = temp2;             //Created node is inserted to the lists.
        temp2->next= temp;
        
        temp->prod= prod;
    }
}

void addToProduct (int product_id, string product_name, int product_amount, Product *&head) { //This function creates a list of products which are owned by the customer.
    
    Product *prody = new Product;
    prody->prod_id=-1;
    prody->prod_name= "temp";
    prody->amount = -1;                     //Firs of all a node which has garbage values inserted at the beginning of the list.
    prody-> next = nullptr;
    
    Product *temp;
    Product *temp2=head;
    
    temp= new Product;
    
    temp->prod_id=product_id;                   //Secondyl a new node is created which has the product informations.
    temp->prod_name = product_name;
    temp->amount= product_amount;
    temp->next = nullptr;
    
    if(head == nullptr) {   //If there is nothing in the list garbage node is added to the list.
        
        head= prody;
        temp2 = head;
        
        while (temp2->next != nullptr && temp2->prod_id < temp->prod_id) {  //Created node is inserted to the lists as a sorted order.
            if(temp2->next->prod_id < temp->prod_id)
                temp2 = temp2->next;
            else
                break;
        }
        
        temp->next = temp2->next; //temp taila eşitlendi
        temp2->next= temp;
        
    }
    
    else {
        
        while (temp2->next != nullptr && temp2->prod_id < temp->prod_id) {  //If there is a node, new node is added to the list.
            
            if(temp2->next->prod_id < temp->prod_id)
                temp2 = temp2->next;                    //Program finds the sorted order.
            else
                break;
        }
        
        temp->next= temp2->next; //temp taila eşitlendi     //Then put the product to the correct place.
        temp2->next= temp;
        
    }
    
}

int main() {
    
    Customer *head= nullptr;
    Customer *tail= nullptr;
    Product *product_head = nullptr;
    
    char chr;
    bool a = true;
    string line,id;
    string name,itemId,itemName,itemAmount,customer_name="";
    int cust_id = 0,prod_id = 0,prod_amount;
    ifstream FileStr;
    
    string file = "input.txt";
    
    FileStr.open(file.c_str());
    
    while (getline(FileStr,line)) {     //This point program get the each line of the given file.
        
        stringstream ss(line);          //Given line is converted to stringstream so that program checks the first char of the line.
        
        ss.get(chr);
        
        if (chr == '#') {               //If the first char is # then it means there is a customer.
            
            ss>>id;
            
            cust_id = stoi(id.substr(0,id.length()-1));     //Program finds the customer's id.
            
            while (a) {
                
                ss>>name;
                
                if (":" == name.substr(name.length()-1)) {
                    customer_name += name;                      //Program finds the customer's name.
                    customer_name = customer_name.substr(0,customer_name.length()-1);
                    break;
                }
                
                else {
                    customer_name+= name;
                    customer_name+= " ";
                    
                }
            }
            
            while (a) {     //At this point program reads the file and take the products.
                
                ss>>itemId;     //Program finds the product's id.
                
                prod_id = stoi(itemId);
                break;
            }
            string prod_name="";
            int count =0;
            while(a) {
                
                if  (count !=0) {
                    prod_name+= " ";
                }
                ss>>itemName;
                
                if ("(" == itemName.substr(0,1)) {                               //Program finds the product's name,amount.
                    prod_name = prod_name.substr(0,customer_name.length()-1);
                    itemAmount = itemName.substr(1,itemName.length()-3);
                    prod_amount = stoi(itemAmount);
                    
                    if (itemName.substr(itemName.length()-1) == ".") {
                        
                        addToProduct(prod_id, prod_name, prod_amount, product_head);        //At this point found prodcut informations added to new node the new created node is inserted to customer (This is for the last line of the file.).
                        addToCustomer(cust_id,customer_name, head, tail, product_head);
                        customer_name="";
                        
                        a=false;
                        break;
                    }
                    
                    else {
                        addToProduct(prod_id, prod_name, prod_amount, product_head);        //At this point new product node is created.
                        break;
                    }
                }
                else {
                    
                    prod_name+= itemName;
                    count ++;
                    
                }
            }
            
        }
        
        else if (line != "\r") {
            
            if (a==0) {
                break;
            }
            
            string product_name = "",name1="";;
            ss>>itemId;
            prod_id = stoi(itemId);     //Product id is converted to int from string.
            
            
            while (a) {
                
                ss>>itemName;
                
                if ("(" == itemName.substr(0,1)) {
                    //Program finds the product's name,amount.
                    product_name = product_name.substr(0,name1.length()-2);
                    itemAmount = itemName.substr(1,itemName.length()-3);
                    
                    prod_amount = stoi(itemAmount);
                    
                    if (line != "\r") {
                        addToProduct(prod_id, product_name, prod_amount, product_head);     //At this point new product node is created.
                        
                        break;
                    }
                    
                    break;
                }
                
                else {
                    product_name+= itemName;
                    product_name+= " ";
                }
            }
            
            if (itemName.substr(itemName.length()-1)== ".") {
                addToCustomer(cust_id, customer_name, head, tail, product_head);        //At this point found prodcut informations added to new node the new created node is inserted to customer (This is for the last line of the file.).
                customer_name="";
                product_head = nullptr;
            }
        }
        
        
    }
    
    
    while (true){
        
        
        cout << endl;
        cout << "***********************************************************************" << endl;
        cout << "**************** 0 - EXIT PROGRAM"<<endl;
        cout << "**************** 1 - PRINT ALL CUSTOMER DATA"<< endl;
        cout << "**************** 2 - FIND A CUSTOMER" << endl;
        cout << "**************** 3 - ADD A CUSTOMER" << endl;
        cout << "**************** 4 - DELETE A CUSTOMER" << endl;
        cout << "**************** 5 - ADD A PRODUCT TO A CUSTOMER" << endl;
        cout << "**************** 6 - DELETE A PRODUCT FROM A CUSTOMER" << endl;
        cout << "**************** 7 - LIST THE BUYERS OF A PRODUCT" << endl;
        cout << "***********************************************************************" << endl;
        cout << endl;
        int option;
        cout << "Pick an option from above (int number from 0 to 7): ";
        cin >> option;
        switch (option)
        {
            case 0:
                cout << "PROGRAM EXITING ... " << endl; system("pause");
                exit(0);
            case 1:
                print_customer_data(head);
                break;
            case 2:
                find_customer(head);
                break;
            case 3:
                add_customer(head);
                break;
            case 4:
                delete_customer(head);
                break;
            case 5:
                add_product(head);
                break;
            case 6:
                delete_product(head);
                break;
            case 7:
                list_product_owners(head);
                break;
            default:
                cout << "INVALID OPTION!!! Try again" << endl;
        } }
    
    return 0;
}
