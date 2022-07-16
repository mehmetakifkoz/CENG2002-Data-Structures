// HW #2 Mehmet Akif KOZ 192010010023

#include "Stack.h"
#include <cassert>

// Singly linked list
template <typename E>
class Link
{
public:
    E element;  // Value for this node
    Link *next; // Pointer to next node in list
    // Constructors
    Link(const E &elemval, Link *nextval = NULL)
    {
        element = elemval;
        next = nextval;
    }
    Link(Link *nextval = NULL) { next = nextval; }
};

// Linked stack implementation
template <typename E>
class LStack : public Stack<E>
{
private:
    Link<E> *top; // Pointer to first element
    int size;     // Number of elements

public:
    LStack() // Constructor
    {
        top = NULL;
        size = 0;
    }

    ~LStack() { clear(); } // Destructor

    void clear() // Reinitialize
    {
        while (top != NULL) // Delete link nodes
        {
            Link<E> *temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }

    void push(const E &it) // Push "it" on stack
    {
        top = new Link<E>(it, top);
        size++;
    }

    E pop() // Remove "it" from stack
    {
        assert(top != NULL && "Stack is empty");
        E it = top->element;
        Link<E> *ltemp = top->next;
        delete top;
        top = ltemp;
        size--;
        return it;
    }

    const E &topValue() const // Return top value
    {
        assert(top != 0 && "Stack is empty");
        return top->element;
    }

    int length() const { return size; } // Return length
};
