//using unsinged long


#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main(){
    Set s1;
    assert(s1.empty() == true);
    assert(s1.contains(4.888) == false);
    assert(s1.size() == 0);
    assert(s1.insert(2) == true);
    assert(s1.insert(2) == false); // does not insert twice
    assert(s1.insert(8) == true);
    assert(s1.insert(3) == true);
    assert(s1.insert(9) == true);
    assert(s1.insert(5) == true);
    assert(s1.size() == 5); // check size is correct
    unsigned long value = 0;
    assert(s1.get(0, value) == true); // check that get function operates correctly, even when scope of i is out of bounds.
    assert(value == 2);
    assert(s1.get(20, value) == false);
    assert(value == 2);

    Set s2; //initialize set 2
    
    assert(s2.insert(6) == true);
    assert(s2.insert(3) == true);
    assert(s2.insert(8) == true);
    assert(s2.insert(5) == true);
    assert(s2.insert(10) == true);

    Set s3;
    excludeInclude(s1, s2, s3);
    s3.dump(); // s3 should include 10 and 6, which is true;
    
    Set s4;
    s4.insert(6);
    s4.insert(5);
    s4.insert(4);
    
    excludeInclude(s4, s3, s2); // checking a situation where the results Set is not empty. s2 dumps just 10, which is correct.
    s2.dump();
}
