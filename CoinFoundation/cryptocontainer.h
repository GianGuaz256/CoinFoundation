#ifndef MODELCONTAINER_H
#define MODELCONTAINER_H

#include <iostream>
#include <exception>

template <class T>
class ModelContainer
{
    class Node;

public:
    ModelContainer();
    ModelContainer(ModelContainer<T>&);
    ModelContainer& operator=(const ModelContainer&);

    virtual ~ModelContainer();

    void push(const T&);
    void remove(T&);
    bool empty() const;
    void clear();

    unsigned int size() const;
    T at(unsigned int) const;

    class iterator;
    class const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator c_begin() const;
    const_iterator c_end() const;

    class iterator
    {
        friend class ModelContainer<T>;

    public:
        iterator(Node* = nullptr);

        T& operator*() const;
        T* operator->() const;

        iterator& operator++();
        iterator operator++(int);

        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

    private:
        Node* p;
    };

    class const_iterator
    {
        friend class ModelContainer<T>;

    public:
        const_iterator(Node* = nullptr);

        const T& operator*() const;
        const T* operator->() const;

        const_iterator& operator++();
        const_iterator operator++(int);

        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

    private:
        const Node* c_p;
    };

private:
    Node* first;
    unsigned int elem;

    class Node
    {
    public:
        Node();
        Node(const T&, Node* = nullptr);
        ~Node();

        static Node* clone(Node*);
        static Node* last(Node*); // navigazione fino all'ultimo nodo

        T data;
        Node* next;
    };
};

template <class T>
ModelContainer<T>::ModelContainer()
    : first(nullptr)
    , elem(0)
{
}

template <class T>
ModelContainer<T>::ModelContainer(ModelContainer<T>& q)
{
    if (q.first) {
        first = Node::clone(q.first);
    }
}
template <class T>
ModelContainer<T>& ModelContainer<T>::operator=(const ModelContainer<T>& q)
{
    if (this == &q) {
        delete first;
        first = ModelContainer<T>::Node::clone(q.first);
    }
    return *this;
}

template <class T>
ModelContainer<T>::~ModelContainer()
{
    delete first;
}

template <class T>
void ModelContainer<T>::push(const T& data)
{
    first = new Node(data, first);
    elem++;
}

template <class T>
void ModelContainer<T>::remove(T& data)
{
    if (empty())
        return;

    if (data == first->data) {
        Node* tmp = first;
        first = first->next;

        if (!first) {
            elem = 0;
            return;
        }
        tmp->next = nullptr;
        delete tmp;
        elem--;

        return;
    }

    Node* nav = first;
    Node* prev = nullptr;

    while (nav && data != nav->data) {
        prev = nav;
        nav = nav->next;
    }

    if (nav) {
        prev->next = nav->next;
        nav->next = nullptr;
        delete nav;
        elem--;
    }
}

template <class T>
unsigned int ModelContainer<T>::size() const
{
    return elem;
}

template <class T> T ModelContainer<T>::at(unsigned int index) const
{
    if (index >= size())
    {
        throw std::invalid_argument("Index out of bounds.");
    }

    unsigned int counter = 0;
    for (auto itr = begin(); itr != end(); itr++, counter++)
    {
        if ( counter == index )
            return *itr;
    }

    throw std::invalid_argument("Index out of bounds.");
}

template <class T>
bool ModelContainer<T>::empty() const
{
    return elem == 0;
}

template <class T>
void
ModelContainer<T>::clear()
{
    elem = 0;
    delete first;
    first = nullptr;
}

template <class T>
typename ModelContainer<T>::iterator ModelContainer<T>::begin()
{
    return iterator(first);
}

template <class T>
typename ModelContainer<T>::const_iterator ModelContainer<T>::begin() const
{
    return const_iterator(first);
}

template <class T>
typename ModelContainer<T>::const_iterator ModelContainer<T>::c_begin() const
{
    return const_iterator(first);
}

template <class T>
typename ModelContainer<T>::iterator ModelContainer<T>::end()
{
    return iterator();
}

template <class T>
typename ModelContainer<T>::const_iterator ModelContainer<T>::end() const
{
    return const_iterator();
}

template <class T>
typename ModelContainer<T>::const_iterator ModelContainer<T>::c_end() const
{
    return const_iterator();
}

template <class T>
ModelContainer<T>::iterator::iterator(ModelContainer<T>::Node* n) : p(n)
{
}

template <class T>
T& ModelContainer<T>::iterator::operator*() const
{
    return p->data;
}

template <class T>
T* ModelContainer<T>::iterator::operator->() const
{
    return &(p->data);
}

template <class T>
typename ModelContainer<T>::iterator& ModelContainer<T>::iterator::operator++()
{
    if (p)
        p = p->next;
    return *this;
}

template <class T>
typename ModelContainer<T>::iterator ModelContainer<T>::iterator::operator++(int)
{
    iterator tmp = *this;
    if (p)
        p = p->next;
    return tmp;
}

template <class T>
bool ModelContainer<T>::iterator::operator==(const ModelContainer<T>::iterator& i) const
{
    return p == i.p;
}

template <class T>
bool ModelContainer<T>::iterator::operator!=(const ModelContainer<T>::iterator& i) const
{
    return p != i.p;
}

template <class T>
ModelContainer<T>::const_iterator::const_iterator(ModelContainer<T>::Node* n) : c_p(n)
{
}

template <class T>
const T& ModelContainer<T>::const_iterator::operator*() const
{
    return c_p->data;
}

template <class T>
const T* ModelContainer<T>::const_iterator::operator->() const
{
    return &(c_p->data);
}

template <class T>
typename ModelContainer<T>::const_iterator& ModelContainer<T>::const_iterator::operator++()
{
    if (c_p)
        c_p = c_p->next;
    return *this;
}

template <class T>
typename ModelContainer<T>::const_iterator ModelContainer<T>::const_iterator::operator++(
        int)
{
    const_iterator tmp = *this;
    if (c_p)
        c_p = c_p->next;
    return tmp;
}

template <class T>
bool ModelContainer<T>::const_iterator::operator==(const ModelContainer<T>::const_iterator& i) const
{
    return c_p == i.c_p;
}

template <class T>
bool ModelContainer<T>::const_iterator::operator!=(
        const ModelContainer<T>::const_iterator& i) const
{
    return c_p != i.c_p;
}

template <class T>
ModelContainer<T>::Node::Node() : next(nullptr)
{
}

template <class T>
ModelContainer<T>::Node::Node(const T& data, ModelContainer::Node* n)
    : data(data), next(n)
{
}

template <class T>
ModelContainer<T>::Node::~Node()
{
    delete next;
}

template <class T>
typename ModelContainer<T>::Node* ModelContainer<T>::Node::clone(ModelContainer<T>::Node* n)
{
    if (!n) {
        return nullptr;
    } else {
        auto nNode = new Node(n->data, Node::clone(n->next));
        nNode->elem = n->elem;
    }
}

template <class T>
typename ModelContainer<T>::Node* ModelContainer<T>::Node::last(ModelContainer<T>::Node* n)
{
    if (n) {
        auto nav = n;
        while (nav->next != nullptr) {
            nav = nav->next;
        }
        return nav;
    } else {
        return nullptr;
    }
}

#endif // MODELCONTAINER_H
