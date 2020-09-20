//
//  ulaseraslan_Eraslan_Ulas_hw7.cpp
//  hw7
//
//  Created by Ulaş Eraslan on 23.11.2019.
//  Copyright © 2019 Ulaş Eraslan. All rights reserved.
//  CS204 Kamer Kaya Sabanci University

#include <iostream>
#include <string>

using namespace std;

class Human{        //Human base class.
    
public:
    
    Human () {};                            //Two constructors for the class first is default second is with parameters.
    Human (string name, int age) : name(name), age(age) {};
    virtual ~Human(){}  //Destructor for the class
    
    virtual void printInfo() {                      //printInfo function prints name and age information of the given object.
        cout << "Human informations" << endl;       //Since there are other printInfo functions this function is defined as virtual.
        cout << "Name: " << name<< endl;
        cout << "Age: " << age<< endl;
    }
    
protected:          //Since subclasses need to reach these variable protected is used.
    string name;
    int age;
};


class Muggle: public Human {        //Derived class from Human class.
    
public:
    
    Muggle(string name, int age , string job) : Human(name,age), job(job) {};       //Constructor takes 3 parameters and 2 of them used by subclass.
    ~Muggle () {}
    
    virtual void printInfo() {                      //Same as previous printInfo function this function prints informations muggle object.
        
        cout << "Muggle Informations"<< endl;
        cout << "Name: " << name<< endl;
        cout << "Age: " << age<< endl;
        cout << "Job: "<< job << endl;
    }
    
protected:
    string job;
    
};

class WizardKind: public Human {        //Derived class from Human.
    
public:
    WizardKind (string name, int age, string wand) : Human(name,age), wand(wand) {};    //Constructor takes 3 parameters and 2 of them used by subclass.
    ~WizardKind () {}
    
    virtual void printInfo() {              //Same as previous printInfo function this function prints informations muggle object.
        
        cout << "Wizardkind Informations"<< endl;
        cout << "Name: " << name<< endl;
        cout << "Age: " << age<< endl;
        cout << "Wand: "<< wand << endl;
    }
    
     virtual void doSpell (string spell) {               //doSpell function is used to print used spell by the given object.
        cout << name << " used spell: " << spell << endl;
    }
    
protected:
    string wand;
};

class Student: public WizardKind {  //Derived class from subclass WizardKind
    
public:
    
    Student (string name, int age, string wand, string pet, string houseName) : WizardKind(name,age,wand), pet(pet), houseName(houseName) {};
    ~Student () {}          //Constructor takes 5 parameters and 3 of them used by WizarKind (derived class from Human(Baseclass)).
    
    virtual void printInfo () {
        cout << "Student Wizardkind Informations"<< endl;        //Same as previous printInfo function this function prints informations student WizardK object.
        cout << "Name: " << name<< endl;
        cout << "Age: " << age<< endl;
        cout << "House: "<< houseName << endl;
        cout << "Wand: "<< wand << endl;
        cout << "Pet: " << pet << endl;
    }
    
    virtual void feedPet () {       //feedPet function is used to print fed pet by the object.
        
        cout << name << " fed " << pet << endl;
    }
    
protected:
    string pet;
    string houseName;
};


class GrownUp: public WizardKind {  //Derived class from subclass WizardKind
    
public:
    GrownUp (string name, int age, string wand, string job): WizardKind(name,age,wand), job(job) {};
    ~GrownUp () {}  //Constructor takes 5 parameters and 3 of them used by WizarKind (derived class from Human(Baseclass)).
    
    virtual void printInfo() {
        cout << "Grownup Wizardkind Informations"<< endl;
        cout << "Name: " << name<< endl;
        cout << "Age: " << age<< endl;
        cout << "Wand: " << wand<< endl;
        cout << "Job: "<< job << endl;
    }
    
protected:
    string job;
    
};



int main(){
    Muggle vernon("Vernon Dursley", 50, "Director at Grunnings");
    vernon.printInfo();
    cout << endl;
    Student Harry("Harry Potter", 16, "Phoenix Feather", "Hedwig", "Gryffindor");
    Harry.printInfo();
    cout << endl;
    GrownUp Dumbledore("Albus Dumbledore", 110, "Elder Wand", "Headmaster");
    Dumbledore.printInfo();
    cout << endl;
    Dumbledore.doSpell("Expecto Patronum");
    cout << endl;
    Harry.doSpell("Expelliarmus");
    cout << endl;
    Harry.feedPet();
    cout << endl;
    Student Ginny("Ginny Weasley", 15, "Yew wood", "Arnold", "Gryffindor");
    GrownUp Snape("Severus Snape", 35, "Dragon Heartstring", "Potion Master");
    Student Hermione("Hermione Granger", 16, "Vine", "Crookshanks", "Gryffindor");
    
    Human hArray[6];
    hArray[0] = vernon;
    hArray[1] = Harry;
    hArray[2] = Dumbledore;
    hArray[3] = Ginny;
    hArray[4] = Snape;
    hArray[5] = Hermione;
    Human * hPtr;
    for (int i = 0; i < 6; i++) {
        cout << endl;
        hPtr = &hArray[i];
        hPtr->printInfo();
        
    }
    
    cout << endl;
    system("pause");
    return 0;
}
