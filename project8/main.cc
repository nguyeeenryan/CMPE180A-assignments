
#include <iostream>
#include "CircularLinkedList.h"

using namespace std;

int main() {

    CircularLinkedList list;

    // Insert into an empty list
    cout << "Test 1: Push into empty list" << endl;

    list.push(10, ClockWise);
    cout << "Expected: {10}" << endl;
    cout << "Actual:   " << list << endl << endl;


    // Push clockwise
    cout << "Test 2: Push clockwise" << endl;

    list.push(20, ClockWise);
    list.push(30, ClockWise);

    cout << "Expected: {10, 30, 20}" << endl;
    cout << "Actual:   " << list << endl << endl;


    // Push counter-clockwise
    cout << "Test 3: Push counter-clockwise" << endl;

    list.push(40, CounterClockWise);

    cout << "Expected: {10, 30, 20, 40}" << endl;
    cout << "Actual:   " << list << endl << endl;


    // Peek
    cout << "Test 4: Peek" << endl;

    cout << "Expected: 10" << endl;
    cout << "Actual:   " << list.peek() << endl << endl;


    // Rotate clockwise
    cout << "Test 5: Rotate clockwise" << endl;

    list.rotate(2, ClockWise);

    cout << "Expected: {20, 40, 10, 30}" << endl;
    cout << "Actual:   " << list << endl << endl;


    // Rotate counter-clockwise
    cout << "Test 6: Rotate counter-clockwise" << endl;

    list.rotate(1, CounterClockWise);

    cout << "Expected: {30, 20, 40, 10}" << endl;
    cout << "Actual:   " << list << endl << endl;


    // Pop clockwise
    cout << "Test 7: Pop clockwise" << endl;

    int removed = list.pop(ClockWise);

    cout << "Expected removed value: 30" << endl;
    cout << "Actual removed value:   " << removed << endl;

    cout << "Expected list: {20, 40, 10}" << endl;
    cout << "Actual list:   " << list << endl << endl;


    // Pop counter-clockwise
    cout << "Test 8: Pop counter-clockwise" << endl;

    removed = list.pop(CounterClockWise);

    cout << "Expected removed value: 20" << endl;
    cout << "Actual removed value:   " << removed << endl;

    cout << "Expected list: {10, 40}" << endl;
    cout << "Actual list:   " << list << endl << endl;


    // Rotate more than list size
    cout << "Test 9: Rotate more than list size" << endl;

    list.rotate(5, ClockWise);

    cout << "Expected: {40, 10}" << endl;
    cout << "Actual:   " << list << endl << endl;


    // Remove until empty
    cout << "Test 10: Remove all nodes" << endl;

    list.pop(ClockWise);
    list.pop(ClockWise);

    cout << "Expected: {}" << endl;
    cout << "Actual:   " << list << endl << endl;


    // Insert after becoming empty
    cout << "Test 11: Insert after becoming empty" << endl;

    list.push(100, ClockWise);

    cout << "Expected: {100}" << endl;
    cout << "Actual:   " << list << endl << endl;


    cout << "done..." << endl;

    return 0;
}
