
#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include <iostream>

enum ClockDirection {
    ClockWise,
    CounterClockWise
};

class CircularLinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node* prev;

        Node(int i) : data(i), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    int size;

public:
    // Constructor
    CircularLinkedList();

    // Destructor
    ~CircularLinkedList();

    // Insert a node relative to head
    void push(int i, ClockDirection d);

    // Remove head and move head in specified direction
    int pop(int i, ClockDirection d);

    // Return head value without modifying the list
    int peek();

    // Rotate head n positions
    void rotate(unsigned int n, ClockDirection d);

    // Print list clockwise
    friend std::ostream& operator<<(std::ostream& os,
                                    const CircularLinkedList& list);
};

#endif
