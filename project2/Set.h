// Set.h

#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

  // Later in the course, we'll see that templates provide a much nicer
  // way of enabling us to have Sets of different types.  For now,
  // we'll use a type alias.

using ItemType = std::string;

const int DEFAULT_MAX_ITEMS = 140;

class Set
{
  public:
    Set();               // Create an empty set (i.e., one whose size() is 0).
    
    ~Set();              // destructor
    
    Set(const Set &other); // copy constructor
    
    Set &operator=(const Set &rhs); // assignment constructor
    
    void dump() const; // dump function used for testing.
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    
    int size() const;    // Return the number of items in the set.

    bool insert(const ItemType& value);
      // Insert value into the set if it is not already present.  Return
      // true if the value actually is inserted.  Leave the set unchanged
      // and return false if value was not inserted (perhaps because it
      // was already in the set or because the set has a fixed capacity and
      // is full).

    bool erase(const ItemType& value);
      // Remove the value from the set if present.  Return true if the
      // value was removed;  otherwise, leave the set unchanged and
      // return false.

    bool contains(const ItemType& value) const;
      // Return true if the value is in the set, otherwise false.
     
    bool get(int i, ItemType& value) const;
      // If 0 <= i < size(), copy into value the item in the set that is
      // strictly greater than exactly i items in the set and return true.
      // Otherwise, leave value unchanged and return false.

    void swap(Set& other);
      // Exchange the contents of this set with the other one.


  private:
    struct Node{
        ItemType value;
        Node* m_next;
        Node* m_prev;
        // Node next; would be incorrect as there would be no way to figure out the size of a Node as each one includes an int and another node.
    };
    Node* head;
    int      m_size;                     // number of items in the set
};

void unite(const Set& s1, const Set& s2, Set& result);

void excludeInclude(const Set& s1, const Set& s2, Set& result);

#endif // SET_INCLUDED
