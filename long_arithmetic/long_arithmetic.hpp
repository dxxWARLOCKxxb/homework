#ifndef LONG_ARITHMETIC_HPP
#define LONG_ARITHMETIC_HPP
#include <string>
#include <vector>

#define MAX(x,y) ((x) < (y) ? (y) : (x))
/*!
 * @brief long_arithmetic - класс для работы с большими числами
 */
class long_arithmetic {
private:
    /*!
     * @brief Указатель на область памяти, в которой хранятся цифры.
     */
    int* digits;
    /*!
     * @brief Указаетль на последнюю значащую цифру.
     */
    int* last_digit;
    /*!
     * @brief Размер области памяти, в которой хранятся цифры.
     */
    size_t  size;
    /*!
     * @brief Флаг, принимающий значение <strong>true</strong> если число отрицательное и <strong>false</strong> иначе.
     */
    bool __is_negative;

    /*!
     * @brief
     * Приватный конструктор, выделяющий память под заданное количество цифр и задающий начальное значение большого числа.
     * @param [in] _size - количество цифр, для которых нужно зарезервировать память
     * @param [in] number - начальное значение большого числа
     * @throw Бросает исключение, если при записи начального значения выходит за пределы зарезервированной под цифры памяти.
     */
    long_arithmetic(size_t, int);
    /*!
     * @brief
     * Выделяет новую память под цифры указанного размера.
     * @param new_size - новый размер массива цифр.
     * @throw бросает исключение, если новый размер меньше количества значащих цифр.
     */
    void resize(size_t new_size);
    /*!
     * @brief
     * Количество значащих цифр числа.
     * @return Возвращает количество значащих цифр числа.
     */
    inline size_t number_significant_digits() const { return last_digit - digits + 1;}
    /*!
     * @brief Конец зарезервированной памяти
     * @return Возвращает указаетль на последнюю ячейку зарезервированной памяти
     */
    inline int* end_digits() const {return digits + size -1;}
    /*!
     * @brief
     * Сравнивает по модулю с числом <strong>number</strong>
     * @param [in] number - большое число, с котороым сравнивается текущее.
     * @return Возвращает <0, 0 или >0, если текущее число меньше, равно или больше number соотвественно.
     */
    int absolute_comparison(const long_arithmetic&) const;
    /*!
     * Прибавляет к текущему числу другое большое число без учета знака
     * @param [in] addend - второе слагаемое
     */
    void sum_digits(const long_arithmetic&);
    void sum_digits(int);
    /*!
     * Вычисляет разность minued и subtract без учета знака, значение разницы записывается объект, вызвавший метод
     * @param [in] minued - уменьшаемое
     * @param [in] subtract - вычитаемое
     */
    void subtract_digits(const long_arithmetic&, const long_arithmetic&);
    void subtract_digits(const long_arithmetic&, int);
    void subtract_digits(int, int);
    int operator int();

public:
    /*!
     * Начальный размер резервируемой под цифры памяти для новых объектов.
     */
    static size_t INITIAL_DIGITS_SIZE;
    /*!
     * @brief
     * Конструктор по умолчанию, создает большое число с резервированием памяти под INITIAL_DIGITS_SIZE цифр и задает начальное значение 0
     */
    long_arithmetic();
    /*!
     * @brief
     * Конструктор создает большое число из простого int с резервированием памяти под INITIAL_DIGITS_SIZE цифр и задает начальное значение number
     * @param [in] number - начальное значение большого числа.
     */
    long_arithmetic(int);
    /*!
     * @brief
     * Конструктор создает большое число по строковому представление number, если размер number меньше INITIAL_DIGITS_SIZE,
     * то выделяет память под INTITIAL_DIGITS_SIZE цифр,
     * иначе выделят память под удвоенный размер number, и задает начальное значение number.
     * @param [in] number - строковое представление начального значения большого числа.
     * @throw Бросает исключение, если строка не является строковым представлением числа
     */
    long_arithmetic(const char*);
    /*!
     * @brief
     * Конструктор копирования
     * @param [in] b - большое число, копия которого создается конструктором.
     */
    long_arithmetic(const long_arithmetic&);
    /*!
     * @brief
     * Деструктор класса, перед освобождением памяти, зануляет хранящиеся значения.
     */
    ~long_arithmetic();
    /*!
     * Преобразует большое число в строкове представление
     * @return строковое представление
     */
    std::string toString() const;
    friend std::ostream&operator<<(std::ostream&, const long_arithmetic&);

    long_arithmetic operator -() const;

    long_arithmetic&operator +=(const long_arithmetic &);
    long_arithmetic&operator -=(const long_arithmetic &);
    long_arithmetic&operator *=(const long_arithmetic &);
    long_arithmetic&operator /=(const long_arithmetic &);
    long_arithmetic&operator %=(const long_arithmetic &);

    long_arithmetic operator +(const long_arithmetic &) const;
    long_arithmetic operator -(const long_arithmetic &) const;
    long_arithmetic operator *(const long_arithmetic &) const;
    long_arithmetic operator /(const long_arithmetic &) const;
    long_arithmetic operator %(const long_arithmetic &) const;


    long_arithmetic&operator +=(int);
    long_arithmetic&operator -=(int);
    long_arithmetic&operator *=(int);
    long_arithmetic&operator /=(int);
    long_arithmetic&operator %=(int);

    long_arithmetic operator +(int) const;
    long_arithmetic operator -(int) const;
    long_arithmetic operator *(int) const;
    long_arithmetic operator /(int) const;
    long_arithmetic operator %(int) const;

    friend long_arithmetic operator +(int, const long_arithmetic &);
    friend long_arithmetic operator -(int, const long_arithmetic &);
    friend long_arithmetic operator *(int, const long_arithmetic &);
    friend int operator /(int, const long_arithmetic &);
    friend int operator %(int, const long_arithmetic &);

    bool operator<(const long_arithmetic &) const;
    bool operator>(const long_arithmetic &) const;
    bool operator<=(const long_arithmetic &) const;
    bool operator>=(const long_arithmetic &) const;
    bool operator==(const long_arithmetic &) const;
    bool operator!=(const long_arithmetic &) const;

    /*bool operator<(const int&) const;
    bool operator>(const int&) const;
    bool operator<=(const int&) const;
    bool operator>=(const int&) const;
    bool operator==(const int&) const;
    bool operator!=(const int&) const;
    friend bool operator<(const int&, const long_arithmetic &);
    friend bool operator>(const int&, const long_arithmetic &);
    friend bool operator<=(const int&, const long_arithmetic &);
    friend bool operator>=(const int&, const long_arithmetic &);
    friend bool operator==(const int&, const long_arithmetic &);
    friend bool operator!=(const int&, const long_arithmetic &);*/
};
#endif