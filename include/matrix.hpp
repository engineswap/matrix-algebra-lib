#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

class Matrix {
  private:
    // data
    vector<vector<float>> m_data;

  public:
    Matrix(string str);
    Matrix(int rows, int cols);

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
    Matrix operator*(Matrix m2) const;

    // matrix +,-

    // index
    vector<float> &operator[](int r) { return m_data[r]; }
    const vector<float> operator[](int r) const { return m_data[r]; }

    // row len, col len
    int get_rows() const { return m_data.size(); }
    int get_cols() const { return m_data[0].size(); }

    // transpose
    Matrix transpose();

    // comparison
    bool operator==(const Matrix &m2) const;
};
