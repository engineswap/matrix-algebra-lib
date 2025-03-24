#include "../include/matrix.hpp"

// constructors
Matrix::Matrix(string str) {
    // "1 2 3; 1 2 3; 1 2 3"
    stringstream ss(str);
    string row_s;

    // Iterate rows
    while (getline(ss, row_s, ';')) {
        stringstream ss_2(row_s);

        vector<float> row;
        row.reserve(row.size() / 2);

        string number;
        // Iterate elements
        while (getline(ss_2, number, ' ')) {
            if (number.length() > 0) {
                row.push_back(stof(number));
            }
        }
        m_data.push_back(row);
    }
}

Matrix::Matrix(int rows, int cols) {
    m_data.reserve(rows);
    for (int i = 0; i < rows; i++) {
        vector<float> row(cols, 0);
        m_data.push_back(row);
    }
}

// print
std::ostream &operator<<(std::ostream &os, const Matrix &obj) {
    // iterate rows
    for (size_t i = 0; i < obj.m_data.size(); i++) {
        // iterate elements
        for (const float &f : obj.m_data[i]) {
            os << std::fixed << setprecision(2) << f << " ";
        }

        if (i != obj.m_data.size() - 1) {
            os << "\n";
        }
    }

    return os;
}

Matrix Matrix::apply_scalar(float x, function<float(float, float)> op) const {
    Matrix result = *this; // copy of present state
    for (auto &row : result.m_data) {
        for (float &f : row) {
            f = op(f, x);
        }
    }

    return result; // return copy
}

Matrix Matrix::transpose() {
    Matrix result(get_cols(), get_rows());
    Matrix &cur_mat = *this;

    for (int r = 0; r < get_rows(); r++) {
        for (int c = 0; c < get_cols(); c++) {
            result[c][r] = cur_mat[r][c];
        }
    }

    return result;
}

bool Matrix::operator==(const Matrix &m2) const {
    const Matrix &m1 = *this;
    if (m1.get_cols() != m2.get_cols())
        return false;
    if (m1.get_rows() != m2.get_rows())
        return false;

    // compare elements are equal
    float tolerance = 0.00000001;
    for (int r = 0; r < m1.get_rows(); r++) {
        for (int c = 0; c < m1.get_cols(); c++) {
            if (abs(m1[r][c] - m2[r][c]) > tolerance)
                return false;
        }
    }

    return true;
}

Matrix Matrix::operator*(Matrix m2) const {
    const auto& m1 = *this;
    // Is it possible?
    if (m1.get_cols() != m2.get_rows()) {
        throw invalid_argument("Matrix dimensions not compatable.");
    }

    // find output dimensions
    Matrix result(m1.get_rows(), m2.get_cols());

    // iterate rows of m1
    for (int r = 0; r < m1.get_rows(); r++) {
        for (int c = 0; c < m2.get_cols(); c++) {
            // find sum of r*c
            float sum = 0;
            for (int i = 0; i < m1.get_cols(); i++) {
                sum += m1[r][i] * m2[i][c];
            }

            result[r][c] = sum;
        }
    }

    return result;
}

