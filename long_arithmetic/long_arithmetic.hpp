#ifndef LONG_ARITHMETIC_HPP
#define LONG_ARITHMETIC_HPP
#include <string>
#include <vector>

#define MAX(x,y) ((x) < (y) ? (y) : (x))
/*!
 * @brief long_arithmetic - класс для работы с большими числами
 * @private
 * <strong>int*</strong> digits - указатель на область памяти, хранящую цифры большого числа.<br>
 * <strong>int*</strong> last_digit - указатель на последнюю значащую цифру.<br>
 * <strong>int</strong> size - количество цифр, под которые зарезервирована память.<br>
 * <strong>bool</strong> __is_negative - флаг отрицательности числа, <strong>true</strong> - если число отрицательное.<br>
 * @static
 * <strong>int</strong> INITIAL_DIGITS_SIZE - статическое поле задающая начальный size для конструктора всех новых больших чисел.
 */
class long_arithmetic {
private:
    int* digits;
    int* last_digit;
    int  size;
    bool __is_negative;

    /*!
     * @brief
     * Приватный конструктор, выделяющий память под заданное количество цифр и задающий начальное значение большого числа.
     * @param [in] _size - количество цифр, для которых нужно зарезервировать память
     * @param [in] number - начальное значение большого числа
     * @throw Бросает исключение, если при записи начального значения выходит за пределы зарезервированной под цифры памяти.
     */
    long_arithmetic(int, int);

public:
    static int INITIAL_DIGITS_SIZE;
    /*!
     * @brief
     * Конструктор по умолчанию, создает большое число с резервированием памяти под INITIAL_DIGITS_SIZE цифр и задает начальное значение 0
     */
    long_arithmetic();
    /*!
     * @brief
     * Конструктор создает большое число из простого int с резервированием памяти под INITIAL_DIGITS_SIZE цифр и задает начальное значение number
     * @param [in] int number - начальное значение большого числа.
     */
    long_arithmetic(int);
    /*!
     * @brief
     * Конструктор создает большое число по строковому представление number, если размер number меньше INITIAL_DIGITS_SIZE,
     * то выделяет память под INTITIAL_DIGITS_SIZE цифр,
     * иначе выделят память под удвоенный размер number, и задает начальное значение number.
     * @param [in] const char* number - строковое представление начального значения большого числа.
     * @throw Бросает исключение, если строка не является строковым представлением числа
     */
    long_arithmetic(const char*);
    /*!
     * @brief
     * Деструктор класса, перед освобождением памяти, зануляет хранящиеся значения.
     */
    ~long_arithmetic();

    std::string toString();
    friend std::ostream&operator<<(std::ostream&, const long_arithmetic&);

    long_arithmetic&operator +=(const long_arithmetic&);
    long_arithmetic&operator -=(const long_arithmetic&);
    long_arithmetic&operator *=(const long_arithmetic&);
    long_arithmetic&operator /=(const long_arithmetic&);

    long_arithmetic&operator +(const long_arithmetic&);
    long_arithmetic&operator -(const long_arithmetic&);
    long_arithmetic&operator *(const long_arithmetic&);
    long_arithmetic&operator /(const long_arithmetic&);

    long_arithmetic&operator +=(const int&);
    long_arithmetic&operator -=(const int&);
    long_arithmetic&operator *=(const int&);
    long_arithmetic&operator /=(const int&);

    long_arithmetic&operator +(const int&);
    long_arithmetic&operator -(const int&);
    long_arithmetic&operator *(const int&);
    long_arithmetic&operator /(const int&);

    long_arithmetic&operator -();

    bool operator<(const long_arithmetic&);
    bool operator>(const long_arithmetic&);
    bool operator<=(const long_arithmetic&);
    bool operator>=(const long_arithmetic&);
    bool operator==(const long_arithmetic&);
    bool operator!=(const long_arithmetic&);

    bool operator<(const int&);
    bool operator>(const int&);
    bool operator<=(const int&);
    bool operator>=(const int&);
    bool operator==(const int&);
    bool operator!=(const int&);
};
#endif