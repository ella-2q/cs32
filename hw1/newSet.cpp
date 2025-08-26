#include "newSet.h"
#include <iostream>
#include <string>

//private items
//    int m_size;
//    int m_maximum;
//    ItemType *m_item;

Set::Set(int max){
    if (max >= 0){
        m_size = 0;
        m_maximum = max;
        m_item = new ItemType[max];
    }
    else {
        std::cerr << "Error: Set size cannot be negative." << std::endl;
        exit(1);
    }
} // Create an empty set (i.e., one whose size() is 0).

Set::Set(const Set &other){ // copy constructor
    m_size = other.m_size;
    m_maximum = other.m_maximum;
    m_item = new ItemType[m_maximum];
    for (int i = 0; i < m_size; i++){
        m_item[i] = other.m_item[i];
    }
    
}

Set &Set::operator=(const Set &rhs){ // assignment operator
    if (this != &rhs){
        delete[] m_item;
        m_size = rhs.m_size;
        m_maximum = rhs.m_maximum;
        m_item = new ItemType[m_maximum];
        for (int i = 0; i < m_size; i++){
            m_item[i] = rhs.m_item[i];
        }
    }
    return *this;
}

Set::~Set(){ // destructor
    delete[] m_item;
}

bool Set::empty() const{ // Return true if the set is empty, otherwise false.
    if (m_size == 0) return true;
    else return false;
}

int Set::size() const{ // Return the number of items in the set.
    return m_size;
}

bool Set::insert(const ItemType& value){
    // Insert value into the set if it is not already present.  Return
    // true if the value actually is inserted.  Leave the set unchanged
    // and return false if value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    if (m_size >= m_maximum){
        return false;
    }
    if (m_size == 0){
        m_item[0] = value;
        m_size = 1;
        return true;
    }
    for (int i=0; i < m_size; i++){
        if (m_item[i] == value) {
            return false;
        }
        
    }
    
    for (int i = 0; i < m_size; i++){
         if (m_item[i] > value){
             for (int j = m_size; j > i; j--){
                 m_item[j] = m_item[j - 1];
             }
             m_item[i] = value;
             m_size++;
             return true;
         }
     }
     m_item[m_size] = value;
     m_size++;
    return true;
}

bool Set::erase(const ItemType& value){
    // Remove the value from the set if present.  Return true if the
    // value was removed;  otherwise, leave the set unchanged and
    // return false.
    
    for (int i = 0; i < m_size; i++)
        if (m_item[i] == value){
            for (int j=i; j < m_size - 1; j++){
                m_item[j] = m_item[j+1];
            }
            m_size--;
            return true;
        }
    return false;
}


bool Set::contains(const ItemType& value) const{
    // Return true if the value is in the set, otherwise false.
    for (int i = 0; i < m_size; i++){
        if (m_item[i] == value){
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const{
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    if (0 <= i && i < size()){
        value = m_item[i];
        return true;
    }
    return false;
}

void Set::swap(Set& other){ // Exchange the contents of this set with the other one.
    Set temp(other);
    other = *this;
    *this = temp;
}

void Set::dump() const{
    std::cerr << "ORDERING..." << std::endl;
    for (int i = 0; i < m_size; i++){
        std::cerr << "#" << i << ":" << m_item[i] << std::endl;
    }
}
