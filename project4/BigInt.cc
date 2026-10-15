#include "BigInt.h"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <limits>
#include <cstdlib>



// ====================================================================================
// CONSTRUCTORS AND DESTRUCTORS
// ====================================================================================

// default constructor
BigInt::BigInt() : digits_{0}, negative_(false) {}

// constructor, long long
BigInt::BigInt(long long value) : negative_(value < 0) {
    // avoid overflow when value is LLONG_MIN
    unsigned long long n = value < 0 ? 0ULL - static_cast<unsigned long long>(value) : static_cast<unsigned long long>(value);

    do {
        digits_.push_back(static_cast<int>(n % 10));
        n /= 10;
    } while (n > 0);

    normalize();
}

// constructor, int vector
BigInt::BigInt(const std::vector<int>& digits) : digits_{0}, negative_(false) {
    // ex: {-1, 2, 3} is -123
    if (digits.empty()) {
        return;
    }

    std::size_t start = 0;

    // first digit shows sign
    if (digits[0] < 0) {
        negative_ = true;
    }

    // makes sure every element is 1 digit
    for (std::size_t i = 0; i < digits.size(); ++i) {
        int digit = digits[i];

        if (i == 0 && digit < 0) {
            digit = -digit;
        }

        if (digit < 0 || digit > 9) {
            throw std::invalid_argument(
                "Each vector element must represent one digit");
        }
    }

    // store the input digits in reverse order
    digits_.clear();
    for (std::size_t i = digits.size(); i > start; --i) {
        digits_.push_back(
            std::abs(digits[i - 1]));
    }

    normalize();
}

// constructor, char vector to BigInt
BigInt::BigInt(const std::vector<char>& digits) : digits_{0}, negative_(false) {
    if (digits.empty()) {
        return;
    }

    std::string text(digits.begin(), digits.end());
    parse(text.c_str(), text.size());
}

// constructor, C char array to BigInt
BigInt::BigInt(const char* digits, std::size_t size) : digits_{0}, negative_(false) {
    // if anything is null, error
    if (digits == nullptr && size != 0) {
        throw std::invalid_argument("Null character array");
    }

    // 
    if (size == 0) {
        return;
    }

    parse(digits, size);
}

// destructor, but vector already cleans itself
BigInt::~BigInt() {}



// ====================================================================================
// MATH OVERLOADS
// ====================================================================================

// addition overload
BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result;

    // if same sign, add
    if (negative_ == other.negative_) {
        result.digits_.clear();

        int carry = 0;
        std::size_t i = 0;

        while (i < digits_.size() || i < other.digits_.size() || carry != 0) {
            int sum = carry;

            if (i < digits_.size()) {
                sum += digits_[i];
            }
            if (i < other.digits_.size()) {
                sum += other.digits_[i];
            }

            result.digits_.push_back(sum % 10);
            carry = sum / 10;
            ++i;
        }

        result.negative_ = negative_;
        result.normalize();
        return result;
    }

    // if different signs, find the bigger number
    int comparison = compare(*this, other);

    if (comparison == 0) {
        return BigInt(0);
    }

    const BigInt& bigger = (comparison > 0) ? *this : other;
    const BigInt& smaller = (comparison > 0) ? other : *this;

    result.digits_.clear();

    int borrow = 0;

    for (std::size_t i = 0; i < bigger.digits_.size(); ++i) {
        int difference = bigger.digits_[i] - borrow;

        if (i < smaller.digits_.size()) {
            difference -= smaller.digits_[i];
        }

        if (difference < 0) {
            difference += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits_.push_back(difference);
    }

    result.negative_ = bigger.negative_;
    result.normalize();

    return result;
}

// subtraction overload, convert to a BigInt to negative and then add
BigInt BigInt::operator-(const BigInt& other) const {
    BigInt negated = other;

    if (!(!negated)) {
        negated.negative_ = !negated.negative_;
    }

    return *this + negated;
}

// multiplication overload
BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.digits_.assign(
        digits_.size() + other.digits_.size(), 0);

    for (std::size_t i = 0; i < digits_.size(); ++i) {
        int carry = 0;

        for (std::size_t j = 0; j < other.digits_.size(); ++j) {
            int product =
                result.digits_[i + j]
                + digits_[i] * other.digits_[j]
                + carry;

            result.digits_[i + j] = product % 10;
            carry = product / 10;
        }

        std::size_t k = i + other.digits_.size();

        while (carry > 0) {
            if (k == result.digits_.size()) {
                result.digits_.push_back(0);
            }

            int sum = result.digits_[k] + carry;
            result.digits_[k] = sum % 10;
            carry = sum / 10;
            ++k;
        }
    }

    result.negative_ = (negative_ != other.negative_);
    result.normalize();
    return result;
}



// ====================================================================================
// LOGIC OVERLOADS
// ====================================================================================

// NOT overload, if singleton 0, then returns true
bool BigInt::operator!() const {
    return digits_.size() == 1 && digits_[0] == 0;
}

// equals overload, if same sign and same value, returns true
bool BigInt::operator==(const BigInt& other) const {
    return negative_ == other.negative_
        && digits_ == other.digits_;
}



// ====================================================================================
// COMPARISON OVERLOADS
// ====================================================================================

// greater than overload
bool BigInt::operator>(const BigInt& other) const {
    // checks if one is larger because of the sign
    if (negative_ != other.negative_) {
        return !negative_;
    }

    // compare the absolute value if they have the same sign
    int cmp = compare(*this, other);

    return negative_ ? (cmp < 0) : (cmp > 0);
}

// less than overload
bool BigInt::operator<(const BigInt& other) const {
    return other > *this;
}

// greater/equal overload
bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}
// lesser/equal overload
bool BigInt::operator<=(const BigInt& other) const {
    return !(*this > other);
}



// ====================================================================================
// INCREMENT OVERLOADS
// ====================================================================================

// pre increment overloads
BigInt& BigInt::operator++() {
    *this = *this + BigInt(1);
    return *this;
}
BigInt& BigInt::operator--() {
    *this = *this - BigInt(1);
    return *this;
}

// post increment overloads
BigInt BigInt::operator++(int) {
    BigInt old = *this;
    ++(*this);
    return old;
}
BigInt BigInt::operator--(int) {
    BigInt old = *this;
    --(*this);
    return old;
}



// ====================================================================================
// stream overloads
// ====================================================================================

// outstream
std::ostream& operator<<(
    std::ostream& os, const BigInt& value) {

    if (value.negative_) {
        os << '-';
    }

    for (std::size_t i = value.digits_.size(); i > 0; --i) {
        os << value.digits_[i - 1];
    }

    return os;
}

// instream
std::istream& operator>>(
    std::istream& is, BigInt& value) {

    std::string text;

    if (is >> text) {
        try {
            BigInt temp(text.c_str(), text.size());
            value = temp;
        } catch (const std::invalid_argument&) {
            is.setstate(std::ios::failbit);
        }
    }

    return is;
}



// ====================================================================================
// HELPER FUNCTIONS
// ====================================================================================

// helper function, convert characters into digits
void BigInt::parse(const char* str, std::size_t size) {
    digits_.clear();
    negative_ = false;

    std::size_t i = 0;

    if (size > 0 && (str[0] == '-' || str[0] == '+')) {
        negative_ = (str[0] == '-');
        i = 1;
    }

    if (i == size) {
        throw std::invalid_argument("No digits provided");
    }

    for (std::size_t j = i; j < size; ++j) {
        if (str[j] < '0' || str[j] > '9') {
            throw std::invalid_argument(
                "Input contains a non-digit character");
        }
    }

    // read from right to left for internal storage
    for (std::size_t j = size; j > i; --j) {
        digits_.push_back(str[j - 1] - '0');
    }

    normalize();
}

// helper function, cleans up BigInt
// removes leading zeros and makes sure a singleton BigInt of 0 doesn't have negative set to true
void BigInt::normalize() {
    while (digits_.size() > 1 && digits_.back() == 0) {
        digits_.pop_back();
    }

    if (digits_.empty()) {
        digits_.push_back(0);
    }

    // sets negative value for BigInt to false if the only digit is 0
    if (digits_.size() == 1 && digits_[0] == 0) {
        negative_ = false;
    }
}

//helper function, find larger BigInt
int BigInt::compare(
    const BigInt& a, const BigInt& b) {

    if (a.digits_.size() < b.digits_.size()) return -1;
    if (a.digits_.size() > b.digits_.size()) return 1;

    for (std::size_t i = a.digits_.size(); i > 0; --i) {
        if (a.digits_[i - 1] < b.digits_[i - 1])
            return -1;

        if (a.digits_[i - 1] > b.digits_[i - 1])
            return 1;
    }

    return 0;
}

