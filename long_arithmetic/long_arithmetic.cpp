#include <ostream>
#include <cstring>
#include <iostream>
#include <cmath>
#include "long_arithmetic.hpp"

size_t long_arithmetic::INITIAL_DIGITS_SIZE = 100;

long_arithmetic::long_arithmetic(size_t _size, int number) {
    size = _size;
    digits = new int[size];
    last_digit = digits;
    __is_negative = false;

    if(number < 0) (number = -number, __is_negative = true);
    *digits = 0;
    int* ptr = digits;
    while(number) {
        if(ptr > end_digits()) throw "Переполнение массива цифр.";

        last_digit = ptr;
        *(ptr++) = number % 10;
        number /= 10;
    }

    if(last_digit < end_digits()) memset(last_digit + 1, 0, end_digits() - last_digit + 1);
}

long_arithmetic::long_arithmetic() : long_arithmetic(INITIAL_DIGITS_SIZE, 0) {}

long_arithmetic::long_arithmetic(int number) : long_arithmetic(INITIAL_DIGITS_SIZE, number) {}

long_arithmetic::long_arithmetic(const char *number) : long_arithmetic(MAX(2 * strlen(number), INITIAL_DIGITS_SIZE), 0) {
    const char* str_ptr = number + strlen(number) - 1;
    const char* end = number;
    if('-' == *end) (end++, __is_negative = true);

    int* ptr = digits;
    while(str_ptr + 1 - end) {
        if(*str_ptr < '0' || *str_ptr > '9') throw "Строка не явлется представлением целого числа.";

        last_digit = ptr;
        *(ptr++) = *(str_ptr--) - '0';
    }
}

long_arithmetic::long_arithmetic(const long_arithmetic &b) {
    size = b.size;
    __is_negative = b.__is_negative;
    digits = new int[size];
    memcpy(digits,b.digits,size * sizeof(int));
    last_digit = digits + b.number_significant_digits() - 1;
}

long_arithmetic::~long_arithmetic() {
    //std::cout << "remove object is " << *this << std::endl;
    memset(digits, 0, size * sizeof(int));
    delete[] digits;
}

std::__cxx11::basic_string<char> long_arithmetic::toString() const{
    auto str = new char[number_significant_digits() + 1 + (__is_negative ? 1 : 0)];
    char* str_ptr = str;
    if(__is_negative) (*str = '-', str_ptr++);
    int* ptr = last_digit;
    while(ptr + 1 - digits) *(str_ptr++) = '0' + (char)*(ptr--);
    *str_ptr = 0;
    return str;
}

std::basic_ostream<char> &operator<<(std::ostream & os, const long_arithmetic & x) {
    int* ptr = x.last_digit;
    if(x.__is_negative) os << '-';
    while(ptr + 1 - x.digits) os << *(ptr--);
    return os;
}

long_arithmetic long_arithmetic::operator-() const {
    auto *result = new long_arithmetic(*this);
    result->__is_negative = !__is_negative;
    return *result;
}

void long_arithmetic::resize(size_t new_size) {
    if(new_size < number_significant_digits()) throw "Новый размер памяти меньше размера памяти, хранящей цифры.";
    auto new_digits = new int[new_size];
    memcpy(new_digits, digits, number_significant_digits());
    memset(digits, 0, number_significant_digits() * sizeof(int));
    last_digit = new_digits + number_significant_digits() - 1;
    memset(last_digit + 1, 0, (size - number_significant_digits()) * sizeof(int));
    delete[] digits;
    digits = new_digits;
}

long_arithmetic long_arithmetic::operator-(const long_arithmetic &b) const {
    auto *c = new long_arithmetic(*this);
    *c -= b;
    return *c;
}

long_arithmetic long_arithmetic::operator+(const long_arithmetic &b) const {
    auto *c = new long_arithmetic(*this);
    *c += b;
    return *c;
}

long_arithmetic long_arithmetic::operator*(const long_arithmetic &b) const {
    int i, j;
    auto *c = new long_arithmetic(
            MAX(INITIAL_DIGITS_SIZE,2 * (number_significant_digits() + b.number_significant_digits() + 1)), 0);
    c->last_digit = c->digits + number_significant_digits() + b.number_significant_digits() - 1;
    for(i = 0; i < number_significant_digits(); ++i) {
        for(j = 0; j < b.number_significant_digits(); ++j) {
            c->digits[i+j] += (this->digits[i] * b.digits[j]);
        }
    };
    int* ptr = c->digits;
    while(ptr < c->last_digit + 1) (*(ptr + 1) += (*ptr / 10), *(ptr++) %= 10);
    c->last_digit = *ptr ? ptr : ptr - 1;
    c->__is_negative = this->__is_negative ^ b.__is_negative;
    return *c;
}

long_arithmetic long_arithmetic::operator/(const long_arithmetic &b) const {
    if(*this < b) return 0;
    int* ptr1 = this->last_digit;
    int digit;
    auto *result = new long_arithmetic(0);
    long_arithmetic remainder = 0;
    while(ptr1 >= this->digits) {
        remainder *= 10;
        remainder += *ptr1;
        for(digit = 0; digit < 9; ++digit) {
            if(b * (digit + 1) > remainder) break;
        }
        *result *= 10;
        *result += digit;
        remainder -= (b * digit);
        ptr1--;
    }
    return *result;
}

void long_arithmetic::sum_digits(const long_arithmetic& addend) {
    int tmp;
    int* ptr1 = digits;
    int* ptr2 = addend.digits;
    while(last_digit >= ptr1 || addend.last_digit >= ptr2) {
        tmp = *ptr1 + *ptr2;
        *ptr1 = tmp % 10;
        *(ptr1 + 1) += (tmp / 10);
        ptr1++, ptr2++;
    }
    last_digit = *ptr1 ? ptr1 : (ptr1 - 1);
}

void long_arithmetic::subtract_digits(const long_arithmetic& minuend, const long_arithmetic& subtrahend) {
    int* ptr1 = minuend.digits;
    int* ptr2 = subtrahend.digits;
    int* ptr = digits;
    while(ptr1 < minuend.last_digit + 1) *(ptr++) = *(ptr1++) - *(ptr2++);
    ptr = digits;
    while(ptr < last_digit) {
        if(*ptr < 0) (*(ptr + 1) -= 1, *(ptr) += 10);
        ptr++;
    }
    while(!last_digit) last_digit--;
}

int long_arithmetic::absolute_comparison(const long_arithmetic& number) const {
    if(number_significant_digits() != number.number_significant_digits())
        return static_cast<int>(number_significant_digits()) - static_cast<int>(number.number_significant_digits());
    else {
        int* ptr1 = digits;
        int* ptr2 = number.digits;
        while(!(*(ptr1++) - *(ptr2++)) && ptr1 < last_digit + 1);
        return *(ptr1-1) - *(ptr2 - 1);
    }
}

long_arithmetic &long_arithmetic::operator+=(const long_arithmetic& b) {
    if(__is_negative ^ b.__is_negative) {
        if(absolute_comparison(b) < 0) {
            subtract_digits(b, *this);
            __is_negative = !__is_negative;
        } else {
            subtract_digits(*this, b);
        }
    } else {
        sum_digits(b);
    }
    return *this;
}

long_arithmetic &long_arithmetic::operator-=(const long_arithmetic &b) {
    if(__is_negative ^ b.__is_negative) {
        sum_digits(b);
    } else {
        if(absolute_comparison(b) < 0) {
            subtract_digits(b, *this);
            __is_negative = !__is_negative;
        } else {
            subtract_digits(*this, b);
        }
    }
    return *this;
}

long_arithmetic &long_arithmetic::operator*=(const long_arithmetic & b) {
    int i, j;
    size_t new_size = number_significant_digits() + b.number_significant_digits() + 1;
    auto* c = new int[new_size];
    memset(c,0, new_size * sizeof(int));
    for(i = 0; i < number_significant_digits(); ++i) {
        for(j = 0; j < b.number_significant_digits(); ++j) {
            c[i+j] += (this->digits[i] * b.digits[j]);
        }
    };
    i = 0;
    while(i < new_size) (c[i+1] += (c[i] / 10), c[i++] %= 10);
    last_digit = digits + new_size - 1;
    if(!*last_digit) last_digit--;
    __is_negative ^= b.__is_negative;
    memcpy(digits,c,new_size * sizeof(int));
    delete[] c;
    return *this;
}

long_arithmetic &long_arithmetic::operator/=(const long_arithmetic & b) {

    return *this;///!!!!
}

long_arithmetic operator+(const int & a, const long_arithmetic & b) {
    return b + a;//!!!!!
}

long_arithmetic operator-(const int & a, const long_arithmetic & b) {
    return -b + a;//!!!!!
}

long_arithmetic operator*(const int & a, const long_arithmetic & b) {
    long_arithmetic c = b;//!!!!!
    return c;
}

long_arithmetic operator/(const int &a, const long_arithmetic &b ) {
    long_arithmetic c = b;//!!!!!
    return c;
}

bool long_arithmetic::operator<(const long_arithmetic &b) const {
    if(__is_negative ^ b.__is_negative) return __is_negative;
    else {
        bool result = absolute_comparison(b) < 0;
        return __is_negative == !result;
    }
}

bool long_arithmetic::operator>(const long_arithmetic &b) const {
    return b < *this;
}

bool long_arithmetic::operator<=(const long_arithmetic &b) const {
    return *this < b || *this == b;
}

bool long_arithmetic::operator>=(const long_arithmetic &b) const {
    return *this > b || *this == b;
}

bool long_arithmetic::operator==(const long_arithmetic &b) const {
    return __is_negative == b.__is_negative && absolute_comparison(b) == 0;
}

bool long_arithmetic::operator!=(const long_arithmetic &b) const {
    return !(*this == b);
}

long_arithmetic long_arithmetic::operator*(const int &b) const {
    int i, j;
    if(b == 0)
        return long_arithmetic(0);
    auto *c = new long_arithmetic(*this);
    //if(c->size < number_significant_digits() + (int)(log(b)/log(10)) + 2) c->resize(MAX(INITIAL_DIGITS_SIZE,2 * (number_significant_digits() + (int)(log(b)/log(10)) + 1)));
    for(i = 0; i < number_significant_digits(); ++i) {
        c->digits[i] = this->digits[i] * b;
    };
    int* ptr = c->digits;
    while(ptr < c->last_digit + 1) (*(ptr + 1) += (*ptr / 10), *(ptr++) %= 10);
    c->last_digit = *ptr ? ptr : ptr - 1;
    c->__is_negative = this->__is_negative ^ b < 0;
    return *c;
}

