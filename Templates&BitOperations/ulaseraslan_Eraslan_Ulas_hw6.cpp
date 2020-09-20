#include <iostream>
#include <vector>
#include <cmath>

// 19.11.2019 CS204 Sabanci University
//Template Class & Bitwise Operations
// template class editions and bitwise operations are made by ulaseraslan

using namespace std;

template <typename T>
T Xor (T decrypted, T key);

template <typename T>
void CycleLeft(T & num, int shiftV);                    //Template class functions prototypes.

template <typename T>
void CycleRight(T & num, int shiftV);

template <typename T>
T flipper (vector<int> &listFlip, T code);


template <typename T>
class Encrypter {
private:
    const T key;
    const int nShifts;
    
public:
    vector<int> listFlips;
    Encrypter(T, int, vector<int>);
    T encrypt(const T decrypted);
    T decrypt(const T encrypted);
};

template <typename T>       //Encrypter class constructor.
Encrypter <T> :: Encrypter(T keyT,int shiftV ,vector<int> listFlipT ): key(keyT),nShifts(shiftV),listFlips(listFlipT) {}

template <typename T>
T Encrypter<T> :: encrypt(T decrypted) {        //Encrypt function uses 3 functions (Xor, CycleLeft , flipper) to encrypt the given variable.
    
    T num = Xor(decrypted, key);
    
    CycleLeft(num, nShifts);
    
    num = flipper(listFlips, num);
    
    return num;
}

template <typename T>
T Encrypter<T> :: decrypt(T encrypted) {     //Encrypt function uses 3 functions (Xor, CycleLeft , flipper) in the reverse order to decrypt the given variable.
    T var;
    
    var = flipper(listFlips, encrypted);
    CycleRight(var, nShifts);
    var = Xor(var, key);
    
    return var;
}


int main() {
    
    int nShifts = 12;
    vector<int> listFlips = { 0,1,2,3,4,9,15,30,35 };
    
    unsigned char key1 = 101;
    unsigned char chClear = 'b';
    Encrypter<unsigned char> encrypterChar(key1, nShifts, listFlips);
    
    cout << "Char to encrypt: " << chClear << endl;
    cout << "Xor result: " << Xor(chClear, key1) << endl;
    unsigned char encryptedCh = encrypterChar.encrypt(chClear);
    unsigned char decryptedCh = encrypterChar.decrypt(encryptedCh);
    
    cout << "Char encrypted: " << encryptedCh << endl;
    cout << "Char decrypted: " << decryptedCh << endl;
    cout << "List of flipped bits: ";
    for (int i : encrypterChar.listFlips) {
        cout << i << " ";
    }
    cout << endl << endl;
    
    unsigned short int key2 = 101;
    unsigned short int intShortClear = 500;
    Encrypter<unsigned short int> encrypterShortInt(key2, nShifts, listFlips);
    
    cout << "Short Int to encrypt: " << intShortClear << endl;
    cout << "Xor result: " << Xor(intShortClear, key2) << endl;
    unsigned short int encryptedShortInt = encrypterShortInt.encrypt(intShortClear);
    unsigned short int decryptedShortInt = encrypterShortInt.decrypt(encryptedShortInt);
    
    cout << "Short Int encrypted: " << encryptedShortInt << endl;
    cout << "Short Int decrypted: " << decryptedShortInt << endl;
    cout << "List of flipped bits: ";
    for (int i : encrypterShortInt.listFlips) {
        cout << i << " ";
    }
    cout << endl << endl;
    
    unsigned int key3 = 101;
    unsigned int intClear = 32800;
    Encrypter<unsigned int> encrypterInt(key3, nShifts, listFlips);
    
    cout << "Int to encrypt: " << intClear << endl;
    cout << "Xor result: " << Xor(intClear, key3) << endl;
    unsigned int encryptedInt = encrypterInt.encrypt(intClear);
    unsigned int decryptedInt = encrypterInt.decrypt(encryptedInt);
    
    cout << "Int encrypted: " << encryptedInt << endl;
    cout << "Int decrypted: " << decryptedInt << endl;
    cout << "List of flipped bits: ";
    for (int i : encrypterInt.listFlips) {
        cout << i << " ";
    }
    cout << endl << endl;
    
    unsigned long long int key4 = 101;
    unsigned long long int intLLClear = 34359738368;
    Encrypter<unsigned long long int> encrypterLLInt(key4, nShifts, listFlips);
    
    cout << "Long Long Int to encrypt: " << intLLClear << endl;
    cout << "Xor result: " << Xor(intLLClear, key4) << endl;
    unsigned long long int encryptedLLInt = encrypterLLInt.encrypt(intLLClear);
    unsigned long long int decryptedLLInt = encrypterLLInt.decrypt(encryptedLLInt);
    
    cout << "Long Long Int encrypted: " << encryptedLLInt << endl;
    cout << "Long Long Int decrypted: " << decryptedLLInt << endl;
    cout << "List of flipped bits: ";
    for (int i : encrypterLLInt.listFlips) {
        cout << i << " ";
    }
    cout << endl << endl;
    
    
    system("pause");
    return 0;
}

template <typename T>
T Xor (T decrypted, T key) {        //Xor function uses XOR operation to find the xor result with given key and given variable.
    T xOr;
    xOr = decrypted ^ key;
    
    return xOr;
}

template <typename T>
void CycleLeft(T & num, int shiftV) {       //CycleLeft function shifts the given variable shiftV many times to the left.
    
    T one = 1;
    T shift=0;                            // The important point is by using cycle left most bit does not dissapear.
    shift= shiftV % (sizeof(num)*8);
    T size = sizeof(num)*8-1;
    
    for (int a=0; a<shift; a++) {
        
        
        T leftBitOne = one << size;
        T left = leftBitOne & num;
        
        num = num<< 1;
        num = num | left>>size;
        
    }
    
    cout << "Shift result: "<< num << endl;
    
}

template <typename T>
void CycleRight(T & num, int shiftV) {      //CycleRight function shifts the given variable shiftV many times to the right.
    
    T one = 1;
    T shift=0;
    shift = shiftV % (sizeof(num)*8);
    T size = sizeof(num)*8-1;

    for (int a=0; a<shift; a++) {
        
        T rightBitOne = 1;
        T right = rightBitOne & num;
        num = num >> one;
        
        num = num | right<<size;
        
    }
}

template <typename T>
T flipper (vector<int> &listFlip, T code) {         //Flip function flips the given bits in the given indices.
    
    vector<int> newFlipper;
    
    for (int i=0; i<listFlip.size() ; i++ ) {
        
        if (listFlip[i] < (sizeof(code)*8)) {       //If the given index is greater then the size of the variable small indexex are considered.
            
            newFlipper.push_back(listFlip[i]);      //Valid indices are push backed to new vector.
        }
    }
    
    listFlip.clear();
    
    for (int k=0; k<newFlipper.size(); k++) {       // To update the listFlip found indexes are push backed to listFlip.
        listFlip.push_back(newFlipper[k]);
    }
    
    T a = 1;
    for (int j=0; j<newFlipper.size(); j++) {       //Indices are changed by using same method in the shifting.
        
        T bitChange;
        if (newFlipper[j] == 0) {
            bitChange = 1;
        }
        
        else {
            
            bitChange = a << newFlipper[j];
        }
        code = code ^ bitChange;
    }
    
    return code;
}
