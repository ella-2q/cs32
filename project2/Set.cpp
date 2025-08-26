#include "Set.h"
#include <utility>
#include <iostream>


Set::Set() : m_size(0) // basic Constructor establishes head node and creates circular 
{
    head = new Node;
    head->m_next = head;
    head->m_prev = head;
}

int Set::size() const
{
    return m_size;
}

Set::~Set(){ //destructor

    Node* current = head->m_next;
    while (current != head){ //loops through linked list deleting previous Nodes.
        Node* deleting = current;
        current = current->m_next;
        delete deleting;
    }
    
    delete head;
}

Set::Set(const Set &other){ // copy constructor
    head = new Node;
    
    head->m_next = head;
    head->m_prev = head;
    
    Node* current = other.head->m_next;
        
    while (current != other.head){ //looping through other and assigning values.
            insert(current->value);
            current = current->m_next;
    }
}

Set &Set::operator=(const Set &rhs){ // assignment operator
    if (this == &rhs){
        return *this;
    }
        
    Node* current = this->head->m_next;
    while (current != head){ //loops through linked list deleting previous Nodes.
        Node* deleting = current;
        current = current->m_next;
        delete deleting;
    }
    
    this->head->m_next = head; //setting m_next and m_prev in case rhs is empty.
    this->head->m_prev = head;
    
    m_size = 0;
        
    current = rhs.head->m_next;
    
    while (current != rhs.head){ //looping through rhs and assigning values.
        insert(current->value);
        current = current->m_next;
    }
    return *this;
}

void Set::dump() const{
    int counter = 0;
    for (Node* current = this->head->m_next; current != head; current = current->m_next){
        std::cerr << current->value << " ... ";
        counter++;
    }
    std::cerr << std::endl;
}

bool Set::empty() const
{
    return size() == 0;
}

bool Set::contains(const ItemType& value) const
{
    Node* p = head->m_next;
    while (p != head) {
        if (p->value == value){
            return true;
        }
        p = p->m_next;
    }

    return false;
}

bool Set::insert(const ItemType& value)
{
    if (contains(value)) return false;
    
    for (Node* i = head->m_next; i != head; i = i->m_next){ // trying to make the linked list ordered
        if (value < i->value){
            Node* newNode = new Node;
            
            newNode->value = value;
            
            
            //setting the pointers of the new node
            newNode->m_next = i;
            newNode->m_prev = i->m_prev;
            
            //changing the old pointers of the head node.
            i->m_prev->m_next = newNode;
            i->m_prev = newNode;
            m_size++;
            return true;
        }
    }
    // this case is for empty lists and if the value is greater than all other values.
    Node* newNode = new Node;
    
    newNode->value = value;
    
    
    //setting the pointers of the new node
    newNode->m_next = head;
    newNode->m_prev = head->m_prev;
    
    //changing the old pointers of the head node.
    head->m_prev->m_next = newNode;
    head->m_prev = newNode;
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value)
{
    if (contains(value)){
        Node* p = head->m_next;
        
        do {
            if (p->value == value){
                break;
            }
            p = p-> m_next;
        } while (p != head); // do nothing
        
        
        //swapping m_next and prev
        p->m_prev->m_next = p->m_next;
        p->m_next->m_prev = p->m_prev;
        
        delete p; //remove node
 
        m_size--; //deincrement size
        return true;
    }
    else return false;
}

     
bool Set::get(int i, ItemType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;
    
    Node* current = head->m_next; //setting initial node to start after head node.
    
    int j = 0;
    while (j < i){ // looping through list to find value with 2 values less than it.
        current = current->m_next;
        j++;
    }
    value = current->value;
    return true;
}

void Set::swap(Set& other) //Another requirement is that as in Problem 5 of Homework 1, the number of statement executions when swapping two sets must be the same no matter how many items are in the sets.
{
    // Swap elements.  Since the only elements that matter are those up to
    // m_size and other.m_size, only they have to be moved.
    // If the sizes are different, assign the remaining elements from the
    // longer one to the shorter.
    
    std::swap(head, other.head);
    std::swap(m_size, other.m_size);
}

void unite(const Set& s1, const Set& s2, Set& result){ //  When this function returns, result must contain one copy of each of the values that appear in s1 or s2 or both, and must not contain any other values. (You must not assume result is empty when it is passed in to this function; it might not be.) Since result is a Set, it must, of course, not have any duplicates.
    
    ItemType valueToInsert;
    int total = s2.size();
    result = s1;
    
    for (int i = 0; i < total; i++){
        s2.get(i, valueToInsert);
        if (!result.contains(valueToInsert)){ //the contains and insert are redunandant, but I like it for clarity.
            result.insert(valueToInsert);
        }
    }
}

void excludeInclude(const Set& s1, const Set& s2, Set& result){ // When this function returns, result must contain one copy of each of the values that appear in s2 but not s1, and must not contain any other values — in other words, excluding values that appear in s1, result includes the values in s2. (You must not assume result is empty when it is passed in to this function; it might not be.) For example, if s1 and s2 were as in the example above, result must end up as a set containing one instance of each of these values and no others (not necessarily in this order): 10 6
    
    Set temp = s2; //added temporory Set to protect against aliasing.
    ItemType valueToCheck;
    int total = s1.size();
    
    for (int i = 0; i < total; i++){
        s1.get(i, valueToCheck);
        if (temp.contains(valueToCheck)){
            temp.erase(valueToCheck);
        }
    }
    result = temp;
}
