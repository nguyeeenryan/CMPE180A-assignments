
#include "BigInt.h"
#include <iostream>
#include <vector>

int main() {
    BigInt a("12345678901234567890", 20);
    BigInt b("-9876543210987654321", 20);

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    std::cout << "a + b = " << a + b << '\n';
    std::cout << "a - b = " << a - b << '\n';
    std::cout << "a * b = " << a * b << '\n';

    std::cout << "a == b: " << (a == b) << '\n';
    std::cout << "a > b: " << (a > b) << '\n';
    std::cout << "a >= b: " << (a >= b) << '\n';
    std::cout << "a < b: " << (a < b) << '\n';
    std::cout << "a <= b: " << (a <= b) << '\n';

    BigInt c(999);
    std::cout << "c = " << c << '\n';
    std::cout << "c++ = " << c++ << '\n';
    std::cout << "After c++: " << c << '\n';
    std::cout << "++c = " << ++c << '\n';

    std::cout << "c-- = " << c-- << '\n';
    std::cout << "After c--: " << c << '\n';
    std::cout << "--c = " << --c << '\n';

    BigInt zero(0);
    BigInt uno(1);
    std::cout << "!zero = " << !zero << '\n';
    std::cout << "!uno = " << !uno << '\n';

    BigInt fromInts(std::vector<int>{-1, 2, 3});
    BigInt fromChars(std::vector<char>{
        '-', '4', '5', '6'
    });

    std::cout << "From int vector: " << fromInts << '\n';
    std::cout << "From char vector: " << fromChars << '\n';

    BigInt input;
    std::cout << "Enter a big integer: ";

    if (std::cin >> input) {
        std::cout << "You entered: " << input << '\n';
    } else {
        std::cout << "Invalid integer input.\n";
    }

    return 0;
}
