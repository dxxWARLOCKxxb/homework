#ifndef THE_MATRIX_MATRIX_H
#define THE_MATRIX_MATRIX_H

#include <pthread.h>
#include <queue>
#include <fstream>

#define RANDOM true

static const char* ERROR =  "Данные матрицы нельзя перемножить, размерности не подходят";

class matrix;
class block;
class matrix_row;
class task;

/**
 * Очередь с заданиями на умножение матриц.
 */
extern std::queue<task> task_manager;
/**
 * Мьютекс доступа к очереди с заданиями.
 */
extern pthread_mutex_t manager_mutex;
/**
 * Флаг остановки всех потоков.
 */
extern bool stop_flag;
/**
 * Массив потоков.
 */
extern pthread_t* workers;
/**
 * Размер одного блока (квадратной матрицы).
 */
extern size_t BLOCK_SIZE;
/**
 * Количество потоков, выполняющих умножения.
 */
extern size_t PROCESSOR_COUNT;

/**
 * Класс матрицы-блока, представляет собой квадратную матрицу размера BLOCK_SIZE
 */
class block {
private:
    /**
     * Массив значений матрицы.
     */
    long long **__elements;
    /**
     * Мьютекс блокировки записи матрицы-блока.
     */
    pthread_mutex_t mutex;
public:
    /**
     * Конструктор по умолчанию, создает матрицу-блок и заполняет нулями
     */
    block();
    /**
     * Конструктор копирования
     * @param copy - копируемая матрица
     */
    block(const block& copy);
    ~block();
    /**
     * Оператор индексации.
     * @param index - номер строки. Индексация начинается с 0.
     * @return - Возвращает строку матрицы-блока.
     */
    long long*operator[](size_t index);
    /**
     * Оператор индексации с доступом только на чтение.
     * @param index - номер строки. Индексация начинается с 0.
     * @return - Возвращает строку матрицы-блока.
     */
    long long*operator[](size_t index) const;

    /**
     * Оператор умножения матрицы. Умножение классическое, со сложностью O(n<sup>3</sup>).
     * @param b - второй множитель.
     * @return - возвращает новую матрицу-блок.
     */
    block operator*(const block& b) const;
    /**
     * Прибавляет к текущей матрице матицу b
     * @param b - прибавляемая матрица.
     * @return Возвращает увеличенную матрицу.
     */
    block& operator+=(const block& b);
};

/**
 * Класс задача, используется для передачи данных потокам.
 */
class task {
private:
    /**
     * Матрица-блок, в которую записывается результат.
     */
    block& result;
    /**
     * Левый множитель.
     */
    block& A;
    /**
     * Правый множитель.
     */
    block& B;

public:
    /**
     * Конструктор задания умножения.
     * @param res - ссылка на результирую матрицу-блок, в которую заносится результат.
     * @param a - ссылка на левый множитель.
     * @param b - ссылка на правый множитель.
     */
    task(block& res, block& a, block& b);
    /**
     * Функция умножения двух матриц-блоков и записи результата в третью.
     * @param prm  - параметр неиспользуется, можно передавать NULL.
     * @return
     */
    static void* compute(void* prm) {
        bool empty = false;  //флаг проверки очереди
        while(!(stop_flag && empty)) { //"бесконечный цикл", прекращающий работу, когда stop_flag будет true и очередь с заданиями будет пуста.
            pthread_mutex_lock(&manager_mutex); //блокируем очередь
            empty = task_manager.empty(); //проверяем есть ли в ней что-нибудь
            if(empty) {
                pthread_mutex_unlock(&manager_mutex);
                continue;
            }
            auto tmp = task_manager.front(); //достаем первую задачу
            task_manager.pop();
            pthread_mutex_unlock(&manager_mutex); //разблокируем очередь
            tmp.result += tmp.A * tmp.B; //выполняем умножение
        }
        return EXIT_SUCCESS;
    }
};
/**
 * Вспомогательный класс, строка составной матрицы, нужен для индексации.
 */
class matrix_row {
private:
    /**
     * Массив - строка составноей матрицы.
     */
    block* __blocks;
    /**
     * Количество строк составной матрицы.
     */
    size_t __row;
public:
    /**
     * Конструктор строки матрицы.
     * @param arr - массив - стрка составной матрицы.
     * @param row - количество строк составной матрицы.
     */
    matrix_row(block* arr, size_t row);
    /**
     * Оператор индексации, возвращает элемент составной матрицы.
     * @param index - индекс-столбец.
     * @return - возвращает элемент матрицы.
     */
    long long& operator[](size_t index) const;
};

/**
 * Класс составной матрицы. Основной класс.
 */
class matrix {
private:
    /**
     * Массив матриц-блоков, из который состоит составная матрица.
     */
    block **__blocks;
    /**
     * Количество строк (общий индекс).
     */
    size_t __row;
    /**
     * Количество столбцов (общий индекс).
     */
    size_t __col;
    /**
     * Количество строк (индекс матриц-блоков).
     * @return
     */
    size_t __row_block() const;
    /**
     * Количество столбцов (индекс матриц-блоков).
     * @return
     */
    size_t __col_block() const;
public:
    /**
     * Стандартный коснтруктор.
     * @param row - количество строк.
     * @param col - количество столбцов.
     */
    matrix(size_t row, size_t col);
    /**
     * Конструктор копирования.
     * @param copy - копируемая матрица.
     */
    matrix(const matrix& copy);
    /**
     * Конструктор с рандомным заполнением
     * @param row - количество строк.
     * @param col - количество столбцов.
     * @param flag - RANDOM для заполнения случайными числами [0,100)
     */
    matrix(size_t row, size_t col, int flag);
    ~matrix();
    /**
     * Оператор индексации.
     * @param index - номер строки.
     * @return Возвращает строку составной матрицы.
     */
    matrix_row operator[](size_t index) const;
    /**
     * Оператор умножения матриц. Матрицы умножаются многопоточно, но классическим алгоритмом O(n<sup>3</sup>).
     * @param b - второй множитель.
     * @return Возвращает новую матрицу - результат умножения.
     */
    matrix operator*(const matrix& b) const;
    /**
     * Оператор вывода матрицы, выводит все элементы в одну строку (для python).
     * @param os - поток вывода.
     * @param value - выводимая матрица.
     * @return Возвращает поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const matrix& value);
};
/**
 * Функция инициализирующая настройки и создающая потоки.
 * @param processor_count - количество потоков, которые будут умножать матрицы.
 * @param block_size - размер матриц-блока, из которых будет состоять составная матрица.
 */
static void init(size_t processor_count = 8, size_t block_size = 10) {
    PROCESSOR_COUNT = processor_count;
    BLOCK_SIZE = block_size;
    stop_flag = false;
    pthread_mutex_init(&manager_mutex, nullptr);
    workers = new pthread_t[PROCESSOR_COUNT];
    for (size_t i = 0; i < PROCESSOR_COUNT; ++i)
        pthread_create(&workers[i], nullptr, task::compute, nullptr);
}
/**
 * Функция завершающая работу виех потоков.
 */
static void destroy() {
    stop_flag = true; //ставим флаг завершения
    for (size_t i = 0; i < PROCESSOR_COUNT; ++i)
        pthread_join(workers[i], EXIT_SUCCESS); //ждем выполнения оставшихся заданий
    delete[] workers;
    pthread_mutex_destroy(&manager_mutex);
}
#endif