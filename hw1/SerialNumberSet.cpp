#include "SerialNumberSet.h"
    
SerialNumberSet::SerialNumberSet(){
    
}  // Create an empty serial number set.
    
bool SerialNumberSet::add(unsigned long serialNum){
    // If specified serial number is not currently in this SerialNumberSet
    // and there is room in the SerialNumberSet, add that serial number to
    // the SerialNumberSet and return true.  Otherwise, make no change to
    // this SerialNumberSet and return false.
    return SSN.insert(serialNum);
}
    
int SerialNumberSet::size() const{
    // Return the number of serial numbers in this SerialNumberSet.
    return SSN.size();
}
    
void SerialNumberSet::print() const{
    // Write to cout every serial number in this SerialNumberSet exactly
    // once, one per line.  Write no other text.  The lines need
    // not be in any particular order.
    unsigned long x;
    for (int i = 0; i < SSN.size(); i++){
        SSN.get(i, x);
        std::cout << x << std::endl;
    }
}
