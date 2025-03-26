#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <random>
using namespace std;

using FloatMatrix = vector<vector<float>>;

class Matrix {
  private:
    // data
    vector<vector<float>> m_data;

  public:
    Matrix(string str);
    Matrix(int rows, int cols);
    Matrix(const FloatMatrix& mat);

    void random_init();

    friend ostream &operator<<(ostream &os, const Matrix &obj);

    Matrix apply_scalar(float x, function<float(float, float)> op) const;

    // Scalar operations
    Matrix operator+(float x) const {
        auto lambda = [](float a, float b) { return a + b; };
        return apply_scalar(x, lambda);
    }

    Matrix operator-(float x) const {
        auto lambda = [](float a, float b) { return a - b; };
        return apply_scalar(x, lambda);
    }

    Matrix operator*(float x) const {
        auto lambda = [](float a, float b) { return a * b; };
        return apply_scalar(x, lambda);
    }

    Matrix operator/(float x) const {
        auto lambda = [](float a, float b) { return a / b; };
        return apply_scalar(x, lambda);
    }

    // matrix *
    Matrix naive_mult(const Matrix& m2) const;
    Matrix divide_and_conquer_mult(const Matrix& m2, bool strassen) const;
    
    static FloatMatrix divide_and_conquer_mult_helper(const FloatMatrix& m1, const FloatMatrix& m2);
    static FloatMatrix strassen_mult_helper(const FloatMatrix& m1, const FloatMatrix& m2);
    static FloatMatrix add(const FloatMatrix& m1, const FloatMatrix& m2);
    static FloatMatrix subtract(const FloatMatrix& m1, const FloatMatrix& m2);
    static FloatMatrix multiply(const FloatMatrix& m1, const FloatMatrix& m2); // naive n^3 loop
    static array<FloatMatrix, 4> break_matrix_into_quadrants(const FloatMatrix &mat);
    static FloatMatrix combine_quadrants(const FloatMatrix &topLeft,
                              const FloatMatrix &topRight,
                              const FloatMatrix &bottomLeft,
                              const FloatMatrix &bottomRight);



    // matrix +,-

    // index
    vector<float> &operator[](int r) { return m_data[r]; }
    const vector<float> operator[](int r) const { return m_data[r]; }

    // row len, col len
    int get_rows() const { return m_data.size(); }
    int get_cols() const { return m_data[0].size(); }

    // get 2d matrix
    const vector<vector<float>>& get_matrix() const { return m_data; }

    // transpose
    Matrix transpose();

    // comparison
    bool operator==(const Matrix &m2) const;
};
