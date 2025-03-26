#include "../include/matrix.hpp"
#include <cassert>

void printFloatMatrix(const FloatMatrix &matrix) {
    for (const auto &row : matrix) {
        for (const auto &val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int main() {
    Matrix m1("1 2 3 4; 5 6 7 8; 9 10 11 12; 13 14 15 16");
    Matrix m2("16 15 14 13; 12 11 10 9; 8 7 6 5; 4 3 2 1");
    Matrix answer(
        "80 70 60 50; 240 214 188 162; 400 358 316 274; 560 502 444 386");
    
    Matrix result = m1.divide_and_conquer_mult(m2, false);
    assert(result==answer);
    cout << result << endl;
}
