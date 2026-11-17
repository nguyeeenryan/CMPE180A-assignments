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

}

int CircularLinkedList::peek() {

}

void CircularLinkedList::rotate(unsigned int n, ClockDirection d) {

}

std::ostream& operator<<(std::ostream& os, const CircularLinkedList& list) {
    
}
