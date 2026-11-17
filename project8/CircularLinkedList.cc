#include "CircularLinkedList.h"

// constructor
CircularLinkedList::CircularLinkedList() {
    head = nullptr;
    size = 0;
}

// destructor
CircularLinkedList::~CircularLinkedList() {
    if (head == nullptr) {
        return;
    }
    
    // delete nodes starting from the head
    Node* current = head;
    for (int i = 0; i < size; i++){
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    
    head = nullptr;
    size = 0;
}

void CircularLinkedList::push(int i, ClockDirection d) {
    Node* newNode = new Node(i);

    // if empty list
    if (head == nullptr){
        head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
        size++;
        return;
    }

    if (d == ClockWise){
        // CW, after head
        newNode->next = head->next;
        newNode->prev = head;

        head->next->prev = newNode;
        head->next = newNode;
    } else {
        // CCW, before head
        newNode->prev = head->prev;
        newNode->next = head;

        head->prev->next = newNode;
        head->prev = newNode;
    }

    size ++;
}

int CircularLinkedList::pop(ClockDirection d) {
    // check if empty
    if (head == nullptr) {
        std::cerr << "cannot pop from an empty list" << std::endl;
        return -1;
    }

    int value = head->data;

    // if only 1 node
    if (size == 1){
        delete head;
        head = nullptr;
        size = 0;
        return value;
    }

    // make next/prev node head
    Node* oldHead = head;
    if (d == ClockWise) {
        head = head->next;
    } else {
        // CCW
        head = head->prev;
    }

    // remove old head
    oldHead->prev->next = oldHead->next;
    oldHead->next->prev = oldHead->prev;
    delete oldHead;
    size --;

    return value;
    
}

int CircularLinkedList::peek() {
    // same as before, check if empty
    if (head == nullptr) {
        std::cerr << "cannot peek from an empty list" << std::endl;
        return -1;
    }

    return head->data;
}

void CircularLinkedList::rotate(unsigned int n, ClockDirection d) {
    // if empty list
    if (head == nullptr) {
        return;
    }

    // if n bigger than list size
    n = n % size;

    // rotate head forward or backward n times
    for (unsigned int i = 0; i < n; i++) {
        if (d == ClockWise) {
            head = head->next;
        } else {
            // CCW
            head = head->prev;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const CircularLinkedList& list) {
    // again, if empty list
    if (list.head == nullptr) {
        os << "{}";
        return os;
    }

    CircularLinkedList::Node* current = list.head;
    
    os << "{";
    for (int i = 0; i < list.size; i++) {
        os << current->data;

        if (i < list.size - 1) {
            os << ", ";
        }

        current = current->next;
    }
    os << "}";

    return os;
}
