#include "countHits.h"
#include <stack>

int countHits(std::vector<Asteroid> a) {
    // function takes vector of multiple asteroids each with size and direction
    // returns total hits as size of a stack of right moving asteroids
    std::stack<Asteroid> asteright;

    // loop through every asteroid in vector
    for (const Asteroid& current : a) {
        // if asteroid is heading right, push into asteright
        if (current.d == right) {
            asteright.push(current);
        }

        // if heading left, compare to top of asteright stack
        else {

            // work through asteright stack until all gone
            while (!asteright.empty()) {
                int topMass = asteright.top().m;

                // mass of right vs left, destroy right asteroid if left bigger
                if (topMass < current.m){
                asteright.pop();
                }

                // if same mass, destroy both
                else if (topMass == current.m) {
                    asteright.pop();
                    break;
                }

                // if right bigger, destroy left and move on to next asteroid
                else {
                    break;
                }
            }
        }
    }

    return static_cast<int>(asteright.size());
};

/*
time and space complexity is both o(n),
each asteroid is touched once, there's no nested for loops

tests used in my main.cc file:

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

*/