#include <ostream>
#include <cstring>
#include "long_arithmetic.hpp"

int long_arithmetic::INITIAL_DIGITS_SIZE = 100;

long_arithmetic::long_arithmetic(int _size, int number) {
    size = _size;
    digits = new int[size];
    last_digit = digits;
    __is_negative = false;

    if(number < 0) {
        number = -number;
        __is_negative = true;
    }

    int* ptr = digits;
    while(number) {
        if(ptr >= digits + size) throw "Переполнение массива цифр.";

        last_digit = ptr;
        *(ptr++) = number % 10;
        number /= 10;
    }

    if(last_digit < digits + size)
        memset(last_digit + 1, 0, digits + size - last_digit); //check!
}

long_arithmetic::long_arithmetic() : long_arithmetic(INITIAL_DIGITS_SIZE, 0) {}

long_arithmetic::long_arithmetic(int number) : long_arithmetic(INITIAL_DIGITS_SIZE, number) {}

long_arithmetic::long_arithmetic(const char *number) : long_arithmetic(MAX(2 * strlen(number), INITIAL_DIGITS_SIZE), 0) {
    const char* str_ptr = number + strlen(number) - 1;
    const char* end = number;
    if('-' == *end) {
        end++;
        __is_negative = true;
    }

    int* ptr = digits;
    while(str_ptr + 1 - end) {
        if(*str_ptr < '0' || *str_ptr > '9') throw "Строка не явлется представлением целого числа.";

        last_digit = ptr;
        *(ptr++) = *(str_ptr--) - '0';
    }
}

long_arithmetic::~long_arithmetic() {
    memset(digits, 0, size * sizeof(int));
    delete[] digits;
}

std::__cxx11::basic_string<char> long_arithmetic::toString() {
    return std::__cxx11::basic_string<char>();
}

std::basic_ostream<char> &operator<<(std::ostream & os, const long_arithmetic & x) {
    int* ptr = x.last_digit;
    if(x.__is_negative) os << '-';
    while(ptr + 1 - x.digits) os << *(ptr--);
    return os;
}

long_arithmetic &long_arithmetic::operator+=(const long_arithmetic &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator-=(const long_arithmetic &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator*=(const long_arithmetic &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator/=(const long_arithmetic &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator+(const long_arithmetic &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator-(const long_arithmetic &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator*(const long_arithmetic &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator/(const long_arithmetic &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator+=(const int &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator-=(const int &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator*=(const int &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator/=(const int &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator+(const int &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator-(const int &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator*(const int &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator/(const int &) {
    return *this;
}

long_arithmetic &long_arithmetic::operator-() {
    return *this;
}

bool long_arithmetic::operator<(const long_arithmetic &) {
    return false;
}

bool long_arithmetic::operator>(const long_arithmetic &) {
    return false;
}

bool long_arithmetic::operator<=(const long_arithmetic &) {
    return false;
}

bool long_arithmetic::operator>=(const long_arithmetic &) {
    return false;
}

bool long_arithmetic::operator==(const long_arithmetic &) {
    return false;
}

bool long_arithmetic::operator!=(const long_arithmetic &) {
    return false;
}

bool long_arithmetic::operator<(const int &) {
    return false;
}

bool long_arithmetic::operator>(const int &) {
    return false;
}

bool long_arithmetic::operator<=(const int &) {
    return false;
}

bool long_arithmetic::operator>=(const int &) {
    return false;
}

bool long_arithmetic::operator==(const int &) {
    return false;
}

bool long_arithmetic::operator!=(const int &) {
    return false;
}
