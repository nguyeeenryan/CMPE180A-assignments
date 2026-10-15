
#include "BigInt.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <limits>
#include <cstdlib>

BigInt::BigInt() : digits_{0}, negative_(false) {}

BigInt::BigInt(long long value) : negative_(value < 0) {
    // Avoid overflow when value is LLONG_MIN.
    unsigned long long n =
        value < 0
        ? 0ULL - static_cast<unsigned long long>(value)
        : static_cast<unsigned long long>(value);

    do {
        digits_.push_back(static_cast<int>(n % 10));
        n /= 10;
    } while (n > 0);

    normalize();
}

BigInt::BigInt(const std::vector<int>& digits)
    : digits_{0}, negative_(false) {

    if (digits.empty()) {
        return;
    }

    std::size_t start = 0;

    // A negative first element indicates a negative number.
    // Example: {-1, 2, 3} represents -123.
    if (digits[0] < 0) {
        negative_ = true;
    }

    for (std::size_t i = 0; i < digits.size(); ++i) {
        int digit = digits[i];

        if (i == 0 && digit < 0) {
            digit = -digit;
        }

        if (digit < 0 || digit > 9) {
            throw std::invalid_argument(
                "Each vector element must represent one digit.");
        }
    }

    // Store the input digits in reverse order.
    digits_.clear();

    for (std::size_t i = digits.size(); i > start; --i) {
        digits_.push_back(
            std::abs(digits[i - 1]));
    }

    normalize();
}

BigInt::BigInt(const std::vector<char>& digits)
    : digits_{0}, negative_(false) {

    if (digits.empty()) {
        return;
    }

    std::string text(digits.begin(), digits.end());
    parse(text.c_str(), text.size());
}

BigInt::BigInt(const char* digits, std::size_t size)
    : digits_{0}, negative_(false) {

    if (digits == nullptr && size != 0) {
        throw std::invalid_argument("Null character array.");
    }

    if (size == 0) {
        return;
    }

    parse(digits, size);
}

void BigInt::parse(const char* str, std::size_t size) {
    digits_.clear();
    negative_ = false;

    std::size_t i = 0;

    if (size > 0 && (str[0] == '-' || str[0] == '+')) {
        negative_ = (str[0] == '-');
        i = 1;
    }

    if (i == size) {
        throw std::invalid_argument("No digits provided.");
    }

    for (std::size_t j = i; j < size; ++j) {
        if (str[j] < '0' || str[j] > '9') {
            throw std::invalid_argument(
                "Input contains a non-digit character.");
        }
    }

    // Read from right to left for internal storage.
    for (std::size_t j = size; j > i; --j) {
        digits_.push_back(str[j - 1] - '0');
    }

    normalize();
}

void BigInt::normalize() {
    while (digits_.size() > 1 && digits_.back() == 0) {
        digits_.pop_back();
    }

    if (digits_.empty()) {
        digits_.push_back(0);
    }

    // Zero must never be negative.
    if (digits_.size() == 1 && digits_[0] == 0) {
        negative_ = false;
    }
}

int BigInt::compareMagnitude(
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

// Adds absolute values, ignoring signs.
BigInt BigInt::addMagnitude(
    const BigInt& a, const BigInt& b) {

    BigInt result;
    result.digits_.clear();

    int carry = 0;
    std::size_t n =
        std::max(a.digits_.size(), b.digits_.size());

    for (std::size_t i = 0; i < n || carry; ++i) {
        int sum = carry;

        if (i < a.digits_.size())
            sum += a.digits_[i];

        if (i < b.digits_.size())
            sum += b.digits_[i];

        result.digits_.push_back(sum % 10);
        carry = sum / 10;
    }

    result.negative_ = false;
    result.normalize();
    return result;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (negative_ == other.negative_) {
        BigInt result = addMagnitude(*this, other);
        result.negative_ = negative_;
        result.normalize();
        return result;
    }

    int cmp = compareMagnitude(*this, other);

    if (cmp == 0) {
        return BigInt(0);
    }

    const BigInt& larger = (cmp > 0) ? *this : other;
    const BigInt& smaller = (cmp > 0) ? other : *this;

    BigInt result;
    result.digits_.clear();

    int borrow = 0;

    for (std::size_t i = 0; i < larger.digits_.size(); ++i) {
        int digit = larger.digits_[i] - borrow;

        if (i < smaller.digits_.size()) {
            digit -= smaller.digits_[i];
        }

        if (digit < 0) {
            digit += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits_.push_back(digit);
    }

    result.negative_ = larger.negative_;
    result.normalize();
    return result;
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt negated = other;

    if (!(!negated)) {
        negated.negative_ = !negated.negative_;
    }

    return *this + negated;
}

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

bool BigInt::operator!() const {
    return digits_.size() == 1 && digits_[0] == 0;
}

bool BigInt::operator==(const BigInt& other) const {
    return negative_ == other.negative_
        && digits_ == other.digits_;
}

bool BigInt::operator>(const BigInt& other) const {
    if (negative_ != other.negative_) {
        return !negative_;
    }

    int cmp = compareMagnitude(*this, other);

    return negative_ ? (cmp < 0) : (cmp > 0);
}

bool BigInt::operator<(const BigInt& other) const {
    return other > *this;
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(*this > other);
}

BigInt& BigInt::operator++() {
    *this = *this + BigInt(1);
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt old = *this;
    ++(*this);
    return old;
}

BigInt& BigInt::operator--() {
    *this = *this - BigInt(1);
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt old = *this;
    --(*this);
    return old;
}

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
