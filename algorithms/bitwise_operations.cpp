#include <iostream>

using namespace std;

int getNext(int m) {
    
    //find first trailing zero after 1s and flip it
    int firstOne = 0;
    for (firstOne=0; firstOne<32; ++firstOne) {
        if (m  & (1 << firstOne)) {
            break;
        }
    }
    
    if (firstOne == 32) {
        return -1;
    }
    
    int firstZero = firstOne;
    for ( ; firstZero < 32; ++firstZero) {
        if ((m & (1 << firstZero)) == 0) {
            break;
        }
    }
    
    if (firstZero == 32) {
        return -1;
    }
    
    // swap firstZero to one and swap firstOne to zero
    int mask = (1 << firstZero);
    m = m | mask;
    
    mask = ~(1 << firstOne);
    
    m = m & mask;
    
    return m;
}

int getPrevious(int m) {
    // set first occuring one to zero and first occuring zero to one
    
    int firstZero = 0;
    for (; firstZero < 32; ++firstZero) {
        if ( (m & ( 1 << firstZero)) == 0) {
            break;
        }
    }
    
    if (firstZero == 32) {
        return -1;
    }
    
    int firstOne = firstZero;
    for (; firstOne < 32; ++firstOne) {
        if ( (m & ( 1 << firstOne))) {
            break;
        }
    }
    
    if (firstOne == 32) {
        return -1;
    }
    
    cout << "firstOne " << firstOne << endl;
    
    int mask = (1 << (firstOne - 1));
    m = m | mask;
    
    mask = ~(1 << firstOne);
    m = m & mask;

    return m;
}

int main() {
    //cout << getNext(40) << endl;
    //cout << getNext(33) << endl;
    //cout << getNext(67) << endl;
    //cout << getNext(83) << endl;
    
    
    cout << getPrevious(20) << endl;
    cout << getPrevious(40) << endl;
    cout << getPrevious(87) << endl;
    cout << getPrevious(43) << endl;
    cout << getPrevious(77) << endl;
    cout << getPrevious(7) << endl;
}