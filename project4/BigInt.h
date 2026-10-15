
#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
#include <iostream>
#include <cstddef>

class BigInt {
public:
    // constructors
    BigInt();
    BigInt(long long value);
    BigInt(const std::vector<int>& digits);
    BigInt(const std::vector<char>& digits);
    BigInt(const char* digits, std::size_t size);

    // destructor
    ~BigInt();

    // math overloads
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;

    // logical overloads
    bool operator!() const;
    bool operator==(const BigInt& other) const;

    // comparison overloads
    bool operator>=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;

    // prefix increment
    BigInt& operator++();
    BigInt& operator--();
    // postfix increment
    BigInt operator++(int);
    BigInt operator--(int);


    // stream overloads
    friend std::ostream& operator<<(std::ostream& os, const BigInt& value);
    friend std::istream& operator>>(std::istream& is, BigInt& value);

private:
    // digits stored in reverse order, but first digit in vector shows sign
    std::vector<int> digits_;

    //keep track if negative
    bool negative_;

    // helper function to reformat BigInt into the right form after operations
    void normalize();

    // helper function for comparing two BigInts
    static int compare(const BigInt& a, const BigInt& b);

    // constructs a BigInt from a string
    void parse(const char* str, std::size_t size);


};

#endif
