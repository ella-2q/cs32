#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

template<typename ItemType>
class Set
{
  public:
    Set();
    bool empty() const;
    int size() const;

    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int i, ItemType& value) const;
    void swap(Set& other);

    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& rhs);

  private:
    struct Node
    {
        ItemType m_value;
        Node*    m_next;
        Node*    m_prev;
    };

    Node* m_head;
    int   m_size;

    void createEmpty();
    void insertBefore(Node* p, const ItemType& value);
    void doErase(Node* p);
    Node* findFirstAtLeast(const ItemType& value) const;
};

template<typename ItemType>
void unite(const Set<ItemType>& s1, const Set<ItemType>& s2, Set<ItemType>& result);
template<typename ItemType>
void excludeInclude(const Set<ItemType>& s1, const Set<ItemType>& s2, Set<ItemType>& result);

template<typename ItemType>
inline
int Set<ItemType>::size() const
{
    return m_size;
}

template<typename ItemType>
inline
bool Set<ItemType>::empty() const
{
    return size() == 0;
}

template<typename ItemType>
inline
bool Set<ItemType>::contains(const ItemType& value) const
{
    Node* p = findFirstAtLeast(value);
    return p != m_head  &&  p->m_value == value;
}

template<typename ItemType>
Set<ItemType>::Set()
{
    createEmpty();
}

template<typename ItemType>
bool Set<ItemType>::insert(const ItemType& value)
{
    Node* p = findFirstAtLeast(value);
    if (p != m_head  &&  p->m_value == value)
        return false;

    insertBefore(p, value);
    return true;
}

template<typename ItemType>
bool Set<ItemType>::erase(const ItemType& value)
{
    Node* p = findFirstAtLeast(value);
    if (p == m_head  ||  p->m_value != value)
        return false;

    doErase(p);
    return true;
}

template<typename ItemType>
bool Set<ItemType>::get(int i, ItemType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;

    Node* p;
    if (i < m_size / 2)
    {
        p = m_head->m_next;
        for (int k = 0; k != i; k++)
            p = p->m_next;
    }
    else
    {
        p = m_head->m_prev;
        for (int k = m_size-1; k != i; k--)
            p = p->m_prev;
    }

    value = p->m_value;
    return true;
}

template<typename ItemType>
void Set<ItemType>::swap(Set& other)
{
    Node* p = other.m_head;
    other.m_head = m_head;
    m_head = p;

    int s = other.m_size;
    other.m_size = m_size;
    m_size = s;
}

template<typename ItemType>
Set<ItemType>::~Set()
{
    while (m_head->m_prev != m_head)
        doErase(m_head->m_prev);

    delete m_head;
}

template<typename ItemType>
Set<ItemType>::Set(const Set& other)
{
    createEmpty();

    for (Node* p = other.m_head->m_next; p != other.m_head; p = p->m_next)
        insertBefore(m_head, p->m_value);
}

template<typename ItemType>
Set<ItemType>& Set<ItemType>::operator=(const Set<ItemType>& rhs)
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

template<typename ItemType>
void Set<ItemType>::createEmpty()
{
    m_size = 0;

    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}

template<typename ItemType>
void Set<ItemType>::insertBefore(Node* p, const ItemType& value)
{
    Node* newp = new Node;
    newp->m_value = value;

    newp->m_prev = p->m_prev;
    newp->m_next = p;
    newp->m_prev->m_next = newp;
    newp->m_next->m_prev = newp;

    m_size++;
}

template<typename ItemType>
void Set<ItemType>::doErase(Node* p)
{
    p->m_prev->m_next = p->m_next;
    p->m_next->m_prev = p->m_prev;
    delete p;

    m_size--;
}

template<typename ItemType>
typename Set<ItemType>::Node* Set<ItemType>::findFirstAtLeast(const ItemType& value) const
{
    Node* p = m_head->m_next;
    for ( ; p != m_head  &&  p->m_value < value; p = p->m_next)
        ;
    return p;
}

template<typename ItemType>
void unite(const Set<ItemType>& s1, const Set<ItemType>& s2, Set<ItemType>& result)
{
    const Set<ItemType>* sp = &s2;
    if (&result == &s1)
    {
        if (&result == &s2)
            return;
    }
    else if (&result == &s2)
        sp = &s1;
    else
    {
        result = s1;
        if (&s1 == &s2)
            return;
    }
    for (int k = 0; k < sp->size(); k++)
    {
        ItemType v;
        sp->get(k, v);
        result.insert(v);
    }
}

template<typename ItemType>
void excludeInclude(const Set<ItemType>& s1, const Set<ItemType>& s2, Set<ItemType>& result)
{
    Set<ItemType> s1copy(s1);
    result = s2;
    for (int k = 0; k < s1copy.size(); k++)
    {
        ItemType v;
        s1copy.get(k, v);
        result.erase(v);
    }
}

#endif // SET_INCLUDED
