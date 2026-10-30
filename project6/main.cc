#include <iostream>
#include <vector>
#include "asteroid.h"
#include "countHits.h"

using namespace std;

void testCase(const vector<Asteroid>& a, int expected, const string& name){
    int result = countHits(a);

    cout << name << ": " << result << " (expected " << ")";

    if (result == expected) {
        cout << " PASS";
    }
    else {
        cout << "FAIL";
    }

    cout << endl;
};

int main(){
    // example 1, expected 1
    vector<Asteroid> test1 = {
        {10, Direction::right},
        {11, Direction::left},
        {11, Direction::right},
        {5, Direction::left}
    };

    // test for all asteroids moving right, expected 4
    vector<Asteroid> test2a = {
        {10, Direction::right},
        {11, Direction::right},
        {11, Direction::right},
        {5, Direction::right}
    };
    // test for all asteroids moving left, expected 0
    vector<Asteroid> test2b = {
        {10, Direction::left},
        {11, Direction::left},
        {11, Direction::left},
        {5, Direction::left}
    };

    // test for same mass, expected 0
    vector<Asteroid> test3 = {
        {10, Direction::right},
        {10, Direction::left}
    };

    // multiple pairs of same mass, expected 0
    vector<Asteroid> test4 = {
        {10, Direction::right},
        {10, Direction::left},
        {11, Direction::right},
        {11, Direction::left}
    };

    // one fat l-asteroid eats all the right asteroids, expected 0
    vector<Asteroid> test5 = {
        {10, Direction::right},
        {20, Direction::right},
        {30, Direction::right},
        {40, Direction::left}
    };

    // no asteroids at all, expected 0
    vector<Asteroid> test6 = {};

    testCase(test1, 1, "test 1");
    testCase(test2a, 4, "test 2a");
    testCase(test2b, 0, "test 2b");
    testCase(test3, 0, "test 3");
    testCase(test4, 0, "test 4");
    testCase(test5, 0, "test 5");
    testCase(test6, 0, "test 6");
}