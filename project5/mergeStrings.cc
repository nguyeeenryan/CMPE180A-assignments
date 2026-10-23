#include "mergeStrings.h"

string mergeStrings( const vector<string> &a) {
    string result;

    // find max length so you don't go out of bounds
    size_t maxLength = 0;
    for (const string &s : a) { 
        if (s.length() > maxLength){
            maxLength = s.length();
        }
    }

    // loop over every string and add a single character to result
    for (size_t i = 0; i < maxLength; i++) {
        for (const string &s : a) {
            // if within range, add to result
            // if not, skip
            if (i < s.length()) {
                result += s[i];
            }
        }
    }

    return result;
}