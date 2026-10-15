
#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
#include <iostream>
#include <cstddef>

class BigInt {
public:
    // Constructors
    BigInt();
    BigInt(long long value);
    BigInt(const std::vector<int>& digits);
    BigInt(const std::vector<char>& digits);
    BigInt(const char* digits, std::size_t size);

    // Arithmetic operators
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;

    // Logical operators
    bool operator!() const;
    bool operator==(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;

    // Prefix
    BigInt& operator++();
    BigInt& operator--();
    // Postfix
    BigInt operator++(int);
    BigInt operator--(int);

    
    // Stream operators
    friend std::ostream& operator<<(
        std::ostream& os, const BigInt& value);

    friend std::istream& operator>>(
        std::istream& is, BigInt& value);


private:
    // Digits stored in reverse order: least significant first.
    std::vector<int> digits_;
    bool negative_;

    void normalize();
    static int compareMagnitude(
        const BigInt& a, const BigInt& b);

    static BigInt addMagnitude(
        const BigInt& a, const BigInt& b);

    // Constructs a BigInt from a string representation.
    void parse(const char* str, std::size_t size);


};

#endif
