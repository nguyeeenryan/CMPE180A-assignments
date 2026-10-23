#include "mergeStrings.h"

string mergeStrings( const vector<string> &a) {
    string result;

    size_t maxLength = 0;
    for (const string &s : a) {
        if (s.length() > maxLength){
            maxLength = s.length();
        }
    }

    for (size_t i = 0; i < maxLength; i++) {
        for (const string &s : a) {
            if (i < s.length()) {
                result += s[i];
            }
        }
    }

    return result;
}