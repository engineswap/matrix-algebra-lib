#include "../include/matrix.hpp"
#include <cassert>

void test_dimensions() {
    cout << "Running test_dimensions\n";
    Matrix m1(2, 3);

    assert(m1.get_rows() == 2);
    assert(m1.get_cols() == 3);

    Matrix m2("1 2 3 4 5; 1 2 3 4 5");

    assert(m2.get_rows() == 2);
    assert(m2.get_cols() == 5);
}

void test_comparison() {
    cout << "Running test_comparison\n";
    Matrix m1(2, 3);
    Matrix m2(2, 3);

    Matrix m3("1 2; 1 2");
    Matrix m4("1 2 3 4; 1 2 3 4");
    assert(m1 == m2);
    assert(!(m1 == m3));
    assert(!(m2 == m3));
    assert(!(m3 == m4));
}

void test_index() {
    cout << "Running test_index\n";

    Matrix m1("1 2 3; 4 5 6; 7 8 9");
    assert(m1[0][0] == 1);
    assert(m1[1][0] == 4);
    assert(m1[0][1] == 2);
}

void test_transpose() {
    cout << "Running test_transpose\n";

    // non square matrix
    Matrix m1("2 3; 7 8; 1 1");
    Matrix m1_t("2 7 1; 3 8 1");

    assert(m1.transpose() == m1_t);

    // square matrix
    Matrix m2("1 2 3; 4 5 6; 7 8 9");
    Matrix m2_t("1 4 7; 2 5 8; 3 6 9");

    assert(m2.transpose() == m2_t);
}

void test_scalar_add() {
    cout << "Running test_scalar_add\n";

    Matrix m1(3, 3);
    m1 = m1 + 7;
    Matrix m1_("7 7 7; 7 7 7; 7 7 7");

    assert(m1 == m1_);
}

void test_scalar_subtract() {
    cout << "Running test_scalar_subtract\n";

    Matrix m1(3, 3);
    m1 = m1 - 7;
    Matrix m1_("-7 -7 -7; -7 -7 -7; -7 -7 -7");

    assert(m1 == m1_);
}

void test_scalar_mult() {
    cout << "Running test_scalar_mult\n";

    Matrix m1(3, 3);
    m1 = m1 + 2;
    m1 = m1 * 3;
    Matrix m1_("6 6 6; 6 6 6; 6 6 6");

    assert(m1 == m1_);
}

void test_scalar_divide() {
    cout << "Running test_scalar_divide\n";

    Matrix m1(3, 3);
    m1 = m1 + 18;
    m1 = m1 / 3;
    Matrix m1_("6 6 6; 6 6 6; 6 6 6");

    assert(m1 == m1_);
}

void test_matrix_mult() {
    cout << "Running test_matrix_mult\n";

    Matrix m1("1 2;3 4");
    Matrix m2("5 6;0 7");
    Matrix answer("5 20;15 46");

    assert(m1 * m2 == answer);

    Matrix m3("1 2 3; 4 5 6");         // 2x3 matrix
    Matrix m4("7 8; 9 10; 11 12");     // 3x2 matrix
    Matrix answer_2("58 64; 139 154"); // Expected 2x2 result

    assert(m3 * m4 == answer_2);
}

int main() {
    test_dimensions();
    test_comparison();
    test_index();
    test_transpose();
    test_scalar_add();
    test_scalar_subtract();
    test_scalar_mult();
    test_scalar_divide();
    test_matrix_mult();

    cout << "All tests passed!\n";
}
