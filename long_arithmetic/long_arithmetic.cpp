#include <ostream>
#include <cstring>
#include <iostream>
#include <cmath>
#include <climits>
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

        *(ptr++) = number % 10;
        number /= 10;
    }
    last_digit = ptr == digits ? ptr : ptr - 1;
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

long_arithmetic::long_arithmetic(const long_arithmetic &clone) {
    size = clone.size;
    __is_negative = clone.__is_negative;
    digits = new int[size];
    memcpy(digits,clone.digits,size * sizeof(int));
    last_digit = digits + clone.number_significant_digits() - 1;
}

long_arithmetic::~long_arithmetic() {
    //std::cout << "remove object is " << *this << std::endl;
    memset(digits, 0, size * sizeof(int));
    delete[] digits;
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

std::__cxx11::basic_string<char> long_arithmetic::toString() const{
    auto str = new char[number_significant_digits() + 1 + (__is_negative ? 1 : 0)];
    char* str_ptr = str;
    if(__is_negative) (*str = '-', str_ptr++);
    int* ptr = last_digit;
    while(ptr >= digits) *(str_ptr++) = '0' + (char)*(ptr--);
    *str_ptr = 0;
    return str;
}

std::basic_ostream<char> &operator<<(std::ostream & os, const long_arithmetic & number) {
    int* ptr = number.last_digit;
    if(number.__is_negative) os << '-';
    while(ptr + 1 - number.digits) os << *(ptr--);
    return os;
}

long_arithmetic::operator int() {
    long result = 0;
    for(int i = 0; i < number_significant_digits(); ++i) {
        result *= 10;
        result += digits[i];
        if(result > INT_MAX)
            throw "Нельзя привести большое число к типу int.";
    }
    if(__is_negative) result = -result;
    return static_cast<int>(result);
}

void long_arithmetic::sum_digits(const long_arithmetic& addend) {
    if(addend.number_significant_digits() == 1 && !*(addend.last_digit)) return;
    int tmp;
    int* ptr1 = digits;
    int* ptr2 = addend.digits;
    while(last_digit >= ptr1 || addend.last_digit >= ptr2) {
        tmp = *ptr1 + *ptr2;
        *ptr1 = tmp % 10;
        *(ptr1 + 1) += (tmp / 10);
        ptr1++;
        if (addend.last_digit >= ptr2) ptr2++;
    }
    last_digit = *ptr1 ? ptr1 : (ptr1 - 1);
}

void long_arithmetic::sum_digits(int addend) {
    if(!addend) return;
    int* ptr1 = digits;
    int tmp;
    while(ptr1 <= last_digit) {
        tmp = *ptr1 + addend;
        *ptr1 = tmp % 10;
        *(ptr1 + 1) += (tmp / 10);
        ptr1++;
    }
    while(!*ptr1) {
        *(ptr1 + 1) += (*(ptr1) / 10);
        *(ptr1) %= 10;
        ptr1++;
    }
    last_digit = ptr1 - 1;
}

void long_arithmetic::subtract_digits(const long_arithmetic& minuend, const long_arithmetic& subtrahend) {
    if(subtrahend.number_significant_digits() == 1 && !*(subtrahend.last_digit)) {
        if(minuend.digits == this->digits) return;
        memcpy(digits, minuend.digits, minuend.number_significant_digits() * sizeof(int));
        if(digits + minuend.number_significant_digits() < last_digit)
            memset(digits + minuend.number_significant_digits(), 0, (last_digit - digits - minuend.number_significant_digits() + 1) * sizeof(int));
        return;
    }
    int* minuend_ptr = minuend.digits;
    int* subtrahend_ptr = subtrahend.digits;
    int* result_ptr = digits;

    while(subtrahend_ptr <= subtrahend.last_digit) *(result_ptr++) = *(minuend_ptr++) - *(subtrahend_ptr++);
    memcpy(result_ptr, minuend_ptr, (minuend.last_digit - minuend_ptr + 1) * sizeof(int));
    if(digits + minuend.number_significant_digits() < last_digit)
        memset(digits + minuend.number_significant_digits(), 0, (last_digit - digits - minuend.number_significant_digits() + 1) * sizeof(int));
    result_ptr = digits;
    last_digit = digits + minuend.number_significant_digits() - 1;
    while(result_ptr < last_digit) {
        if(*result_ptr < 0) (*(result_ptr + 1) -= 1, *(result_ptr) += 10);
        result_ptr++;
    }
    while(!*last_digit) last_digit--;
}

void long_arithmetic::subtract_digits(const long_arithmetic& minuend, int subtrahend) {
    if(!subtrahend) {
        if(minuend.digits == this->digits) return;
        memcpy(digits, minuend.digits, minuend.number_significant_digits() * sizeof(int));
        if(digits + minuend.number_significant_digits() < last_digit)
            memset(digits + minuend.number_significant_digits(), 0, (last_digit - digits - minuend.number_significant_digits() + 1) * sizeof(int));
        return;
    }
    int* minuend_ptr = minuend.digits;
    int* result_ptr = digits;

    while(minuend_ptr <= minuend.last_digit) *(result_ptr++) = *(minuend_ptr++) - subtrahend;
    result_ptr = digits;
    while(result_ptr < last_digit) {
        if(*result_ptr < 0) (*(result_ptr + 1) -= 1, *(result_ptr) += 10);
        result_ptr++;
    }
    while(!last_digit) last_digit--;
}

void long_arithmetic::subtract_digits(int minuend, int subtrahend) {
    memset(digits, 0, number_significant_digits() * sizeof(int));
    int number = minuend - subtrahend;
    *digits = 0;
    int* ptr = digits;
    while(number) {
        *(ptr++) = number % 10;
        number /= 10;
    }
    last_digit = ptr == digits ? ptr : ptr - 1;
}

//subtraction operations
long_arithmetic long_arithmetic::operator-() const {
    auto *result = new long_arithmetic(*this);
    result->__is_negative = !__is_negative;
    return *result;
}
long_arithmetic long_arithmetic::operator-(const long_arithmetic& subtrahend) const {
    auto *result = new long_arithmetic(*this);
    *result -= subtrahend;
    return *result;
}
long_arithmetic long_arithmetic::operator-(int subtrahend) const{
    auto *result = new long_arithmetic(*this);
    size_t new_size = MAX(this->number_significant_digits(), 1 + (size_t)(log(subtrahend) / log(10)));
    if(result->size < new_size) result->resize(2 * new_size);
    *result -= subtrahend;
    return *result;
}
long_arithmetic operator-(int a, const long_arithmetic &subtrahend) {
    return -subtrahend + a;
}
long_arithmetic& long_arithmetic::operator-=(const long_arithmetic& subtrahend) {
    if(__is_negative ^ subtrahend.__is_negative) {
        sum_digits(subtrahend);
    } else {
        if(absolute_comparison(subtrahend) < 0) {
            subtract_digits(subtrahend, *this);
            __is_negative = !__is_negative;
        } else {
            subtract_digits(*this, subtrahend);
        }
    }
    return *this;
}
long_arithmetic& long_arithmetic::operator-=(int subtrahend) {
    if(__is_negative ^ subtrahend < 0) {
        sum_digits(abs(subtrahend));
    } else {
        if(absolute_comparison(abs(subtrahend)) < 0) {
            subtract_digits(abs(subtrahend), abs((int)*this));
            __is_negative = !__is_negative;
        } else {
            subtract_digits(*this, abs(subtrahend));
        }
    }
    return *this;
}

//operations of addition
long_arithmetic long_arithmetic::operator+(const long_arithmetic& addend) const {
    auto *result = new long_arithmetic(*this);
    *result += addend;
    return *result;
}
long_arithmetic long_arithmetic::operator+(int addend) const{
    auto *result = new long_arithmetic(*this);
    size_t new_size = MAX(this->size, 1 + (size_t)(log(addend) / log(10))) + 1;
    if(size < new_size) result->resize(2 * new_size);
    *result += addend;
    return *result;
}
long_arithmetic operator+(int int_addend, const long_arithmetic& addend) {
    return addend + int_addend;
}
long_arithmetic& long_arithmetic::operator+=(const long_arithmetic& addend) {
    if(__is_negative ^ addend.__is_negative) {
        if(absolute_comparison(addend) < 0) {
            subtract_digits(addend, *this);
            __is_negative = !__is_negative;
        } else {
            subtract_digits(*this, addend);
        }
    } else {
        sum_digits(addend);
    }
    return *this;
}
long_arithmetic& long_arithmetic::operator+=(int addend) {
    if(__is_negative ^ addend < 0) {
        if(absolute_comparison(abs(addend)) < 0) {
            subtract_digits(abs(addend), abs((int)*this));
            __is_negative = !__is_negative;
        } else {
            subtract_digits(*this, abs(addend));
        }
    } else {
        sum_digits(abs(addend));
    }
    return *this;
}

//multiplication operations
long_arithmetic long_arithmetic::operator*(const long_arithmetic &multiplier) const {
    int i, j;
    auto *result = new long_arithmetic(
            MAX(INITIAL_DIGITS_SIZE,2 * (number_significant_digits() + multiplier.number_significant_digits() + 1)), 0);
    result->last_digit = result->digits + number_significant_digits() + multiplier.number_significant_digits() - 1;
    for(i = 0; i < number_significant_digits(); ++i) {
        for(j = 0; j < multiplier.number_significant_digits(); ++j) {
            result->digits[i+j] += (this->digits[i] * multiplier.digits[j]);
        }
    };
    int* ptr = result->digits;
    while(ptr < result->last_digit + 1) (*(ptr + 1) += (*ptr / 10), *(ptr++) %= 10);
    while(!*ptr) ptr--;
    result->last_digit = ptr;
    result->__is_negative = this->__is_negative ^ multiplier.__is_negative;
    return *result;
}
long_arithmetic long_arithmetic::operator*(int multiplier) const {
    auto *result = new long_arithmetic(*this);
    *result *= multiplier;
    return *result;
}
long_arithmetic operator*(int int_multiplier, const long_arithmetic &multiplier) {
    return multiplier * int_multiplier;
}
long_arithmetic& long_arithmetic::operator*=(const long_arithmetic & multiplier) {
    int i, j;
    size_t new_size = number_significant_digits() + multiplier.number_significant_digits() + 1;
    auto* c = new int[new_size];
    memset(c,0, new_size * sizeof(int));
    for(i = 0; i < number_significant_digits(); ++i) {
        for(j = 0; j < multiplier.number_significant_digits(); ++j) {
            c[i+j] += (this->digits[i] * multiplier.digits[j]);
        }
    };
    i = 0;
    while(i < new_size) (c[i+1] += (c[i] / 10), c[i++] %= 10);
    last_digit = digits + new_size - 1;
    if(!*last_digit) last_digit--;
    __is_negative ^= multiplier.__is_negative;
    memcpy(digits,c,new_size * sizeof(int));
    delete[] c;
    return *this;
}
long_arithmetic& long_arithmetic::operator*=(int multiplier) {
    int i, j;
    if(multiplier == 0) {
        memset(digits, 0, number_significant_digits() * sizeof(int));
        last_digit = digits;
        return *this;
    }
    if(multiplier == 1)
        return *this;
    //if(result->size < number_significant_digits() + (int)(log(multiplier)/log(10)) + 2) result->resize(MAX(INITIAL_DIGITS_SIZE,2 * (number_significant_digits() + (int)(log(multiplier)/log(10)) + 1)));
    for(i = 0; i < number_significant_digits(); ++i) {
        digits[i] = this->digits[i] * multiplier;
    };
    int* ptr = digits;
    while(ptr <= last_digit) (*(ptr + 1) += (*ptr / 10), *(ptr++) %= 10);
    while(*ptr) (*(ptr + 1) += (*ptr / 10), *(ptr++) %= 10);
    while(!*ptr) ptr--;
    last_digit = ptr;
    __is_negative ^= multiplier < 0;
    return *this;
}

//division operations
long_arithmetic long_arithmetic::operator/(const long_arithmetic &b) const {
    //доделать!!!!
    if(*this < b) return long_arithmetic();
    int* ptr1 = this->last_digit;
    long_arithmetic digit = 0;
    auto *result = new long_arithmetic(0);
//    long_arithmetic remainder = 0;
//    while(ptr1 >= this->digits) {
//        remainder *= 10;
//        remainder += *ptr1;
//        for(; digit < 9; digit = digit + 1) {
//            if(remainder.absolute_comparison(b * (digit + 1)) < 0) break;
//        }
//        *result *= 10;
//        *result += digit;
//        remainder -= (b * digit);
//        ptr1--;
//        digit = 0;
//    }
    return *result;
}
long_arithmetic long_arithmetic::operator /(int b) const{
    auto *result = new long_arithmetic(*this);
    *result /= b;
    return *result;
}
int operator/(int a, const long_arithmetic &b ) {
    //доделать!!!
    return 0;
}
long_arithmetic& long_arithmetic::operator/=(const long_arithmetic & b) {
    return *this;//Доделать!!!!
}
long_arithmetic& long_arithmetic::operator/=(int b) {
    return *this;//Доделать!!!
}

long_arithmetic long_arithmetic::operator%(const long_arithmetic &b) const {
    //Доделать!!!
    return *this;
}
long_arithmetic long_arithmetic::operator%(int b) const{
    //Доделать!!!
    return *this;
}
int operator%(int a, const long_arithmetic &b ) {
    //Доделать!!!!!
    return 0;
}
long_arithmetic& long_arithmetic::operator%=(const long_arithmetic & b) {
    return *this;///Доделать!!!!
}
long_arithmetic& long_arithmetic::operator%=(int b) {
  return *this;//Доделать!!!
}

//comparison operations
int long_arithmetic::absolute_comparison(const long_arithmetic& number) const {
    if(number_significant_digits() != number.number_significant_digits())
        return static_cast<int>(number_significant_digits()) - static_cast<int>(number.number_significant_digits());
    else {
        int* ptr1 = last_digit;
        int* ptr2 = number.last_digit;
        while(!(*(ptr1--) - *(ptr2--)) && ptr1 >= digits);
        return *(ptr1 + 1) - *(ptr2 + 1);
    }
}
int long_arithmetic::absolute_comparison(int number) const {
//Доделать
    return 0;
}
bool long_arithmetic::operator<(const long_arithmetic &b) const {
    if(__is_negative ^ b.__is_negative) return __is_negative;
    else {
        bool result = absolute_comparison(b) < 0;
        return __is_negative == result;
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

