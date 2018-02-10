#include "matrix.h"

std::queue<task> task_manager;
pthread_mutex_t manager_mutex;
bool stop_flag = false;
size_t BLOCK_SIZE;
size_t PROCESSOR_COUNT;
pthread_t* workers;

block::block() {
    pthread_mutex_init(&mutex, NULL);
    __elements = new long long* [BLOCK_SIZE];
    for(size_t i = 0; i < BLOCK_SIZE; ++i) {
        __elements[i] = new long long[BLOCK_SIZE];
        for(size_t j = 0; j < BLOCK_SIZE; ++j)
            __elements[i][j] = 0;
    }
}
block::block(const block& copy) : block() {
    for(size_t i = 0; i < BLOCK_SIZE; ++i)
        for(size_t j = 0; j < BLOCK_SIZE; ++j)
            __elements[i][j] = copy.__elements[i][j];
}
block::~block() {
    pthread_mutex_destroy(&mutex);
    for(size_t i = 0; i < BLOCK_SIZE; ++i)
        delete[] __elements[i];
    delete[] __elements;
}
long long* block::operator[](size_t index) { return  __elements[index]; }
long long* block::operator[](size_t index) const { return  __elements[index]; }

block block::operator*(const block& b) const {
    auto result = block();
    for(size_t i = 0; i < BLOCK_SIZE; ++i)
        for(size_t j = 0; j < BLOCK_SIZE; ++j)
            for(size_t k = 0; k < BLOCK_SIZE; ++k)
                result[i][j] += (*this)[i][k] * b[k][j];
    return result;
}

block& block::operator+=(const block& b) {
    pthread_mutex_lock(&mutex); //операция изменяет текущую матрицу, поэтому заблокируем ее для других.
    for(size_t i = 0; i < BLOCK_SIZE; ++i)
        for(size_t j = 0; j < BLOCK_SIZE; ++j)
            (*this)[i][j] += b[i][j];
    pthread_mutex_unlock(&mutex);
    return *this;
}

task::task(block& res, block& a, block& b) : result(res), A(a), B(b) {}

matrix_row::matrix_row(block* arr, size_t row) : __blocks(arr), __row(row) {};
long long& matrix_row::operator[](size_t index) const {
    //index / BLOCK_SIZE - номер столбца (матрицы блока)
    //[__row % BLOCK_SIZE][index % BLOCK_SIZE] - номер столбца и строки элемента
    return __blocks[index / BLOCK_SIZE][__row % BLOCK_SIZE][index % BLOCK_SIZE];
}

size_t matrix::__row_block() const {
    return  __row / BLOCK_SIZE + (__row % BLOCK_SIZE ? 1 : 0);
}
size_t matrix::__col_block() const {
    return  __col / BLOCK_SIZE + (__col % BLOCK_SIZE ? 1 : 0);
}

matrix::matrix(size_t row, size_t col) : __row(row), __col(col) {
    __blocks = new block*[__row_block()];
    for(size_t i = 0; i < __row_block(); ++i) {
        __blocks[i] = new block[__col_block()];
    }
}
matrix::matrix(const matrix& copy) : matrix(copy.__row, copy.__col) {
    for(size_t i = 0; i < __row_block(); ++i)
        for(size_t j = 0; j < __col_block(); ++j)
            (*this).__blocks[i][j] = copy.__blocks[i][j];
}
matrix::matrix(size_t row, size_t col, int flag) : matrix(row, col) {
    for(size_t i = 0; i < __row; ++i)
        for(size_t j = 0; j < __col; ++j) {
            (*this)[i][j] = rand() % 100;
        }
}
matrix::~matrix() {
    for(size_t i = 0; i < __row_block(); ++i)
        delete[] __blocks[i];
    delete[] __blocks;
}
matrix_row matrix::operator[](size_t index) const {
    //auto result = new
            return matrix_row(__blocks[index / BLOCK_SIZE], index);
    //return *result;
}
matrix matrix::operator*(const matrix& b) const {
    if((*this).__col != b.__row)
        throw ERROR;
    auto result = matrix((*this).__row, b.__col);
    for(size_t i = 0; i < result.__row_block(); ++i)
        for(size_t j = 0; j < result.__col_block(); ++j)
            for(size_t k = 0; k < (*this).__col_block(); ++k) {
                pthread_mutex_lock(&manager_mutex); //блокируем очередь заданий
                task_manager.push(task(result.__blocks[i][j], (*this).__blocks[i][k], b.__blocks[k][j])); //помещаем задание
                pthread_mutex_unlock(&manager_mutex); //разблокируем задание
            }
    return result;
}

std::ostream& operator<<(std::ostream& os, const matrix& value) {
    for(size_t i = 0; i < value.__row; ++i)
        for(size_t j = 0; j < value.__col; ++j)
            os << value[i][j] << " ";
    return os;
}