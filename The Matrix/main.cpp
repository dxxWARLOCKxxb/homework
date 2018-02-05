#include <iostream>
#include "matrix.h"

using namespace std;

int main(int argc, char** argv) {
    srand(time(0));
    init(8, 10);
    matrix a(599,478, RANDOM), b(478,505, RANDOM);
    ofstream file;
    file.open("/tmp/matrix_input.txt");
    file << 599 << ' ' << 478 << endl << a << endl;
    file << 478 << ' ' << 505 << endl << b << endl;
    file.close();
    file.open("/tmp/matrix_output.txt");
    try {
        matrix c = a * b;
        destroy();
        file << 599 << ' ' << 505 << endl << c << endl;
    } catch(const char* e) {
        destroy();
        file << e << endl;
    }
    file.close();
    return 0;
}