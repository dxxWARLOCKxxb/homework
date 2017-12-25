#include <iostream>
#include "long_arithmetic.hpp"

using namespace std;

int  main(int argc, char* argv[]) {
    switch (*argv[1]) {
        case '+':
            cout << long_arithmetic(argv[2]) + long_arithmetic(argv[3]);
            break;
        case '-':
            cout << long_arithmetic(argv[2]) - long_arithmetic(argv[3]);
            break;
        case '*':
            cout << long_arithmetic(argv[2]) * long_arithmetic(argv[3]);
            break;
        case '/':
            cout << long_arithmetic(argv[2]) / long_arithmetic(argv[3]);
            break;
        default:
            cout << 0;
            break;
    }
    return 0;
}