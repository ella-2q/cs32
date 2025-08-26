#include "SerialNumberSet.h"
#include <cassert>
 
int main(){
    SerialNumberSet SSN;
    SSN.add(123);
    SSN.add(12);
    assert(SSN.add(123) == false);
    SSN.add(12345);
    SSN.add(12345);
    assert(SSN.size() == 3);

    SSN.print();
    std::cerr << "all tests passed!" << std::endl;
}
