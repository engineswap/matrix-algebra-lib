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
    m_data.resize(rows, vector<float>(cols, 0.0f));
}

Matrix::Matrix(const FloatMatrix &mat) { m_data = mat; }

void Matrix::random_init() {
    // Create a static random number generator once.
    static std::mt19937 rng(42);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (int r = 0; r < get_rows(); ++r) {
        // Use std::generate to fill each row
        std::generate(m_data[r].begin(), m_data[r].end(),
                      [&]() { return dist(rng); });
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

// naive
Matrix Matrix::naive_mult(const Matrix &m2_) const {
    const auto &m1_ = *this;
    const auto &m1 = this->get_matrix();
    const auto &m2 = m2_.get_matrix();

    // Is it possible?
    if (m1_.get_cols() != m2_.get_rows()) {
        throw invalid_argument("Matrix dimensions not compatable.");
    }

    return Matrix::multiply(m1, m2);
}

// Divide and conquor
FloatMatrix Matrix::multiply(const FloatMatrix &m1, const FloatMatrix &m2) {
    // Get dimensions:
    // m1 is of size (r x p)
    // m2 is of size (p x c)
    // Result will be (r x c)
    int r = m1.size();
    int p = m1[0].size(); // also, m2.size() should equal p
    int c = m2[0].size();

    // Allocate result matrix with dimensions r x c
    FloatMatrix result(r, std::vector<float>(c, 0.0f));

    // Naive triple nested loop
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // dot product
            float sum = 0;
            for (int k = 0; k < p; k++) {
                sum += m1[i][k] * m2[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

// function to break matrix into 4 quadrants
array<FloatMatrix, 4>
Matrix::break_matrix_into_quadrants(const FloatMatrix &mat) {
    int N = mat.size();
    int midRow = mat.size() / 2;
    int midCol = mat[0].size() / 2;

    FloatMatrix topLeft, topRight, bottomLeft, bottomRight;

    for (int i = 0; i < N; ++i) {
        const auto &row = mat[i];
        if (i < midRow) {
            topLeft.emplace_back(row.begin(), row.begin() + midCol);
            topRight.emplace_back(row.begin() + midCol, row.end());
        } else {
            bottomLeft.emplace_back(row.begin(), row.begin() + midCol);
            bottomRight.emplace_back(row.begin() + midCol, row.end());
        }
    }

    return {topLeft, topRight, bottomLeft, bottomRight};
}

FloatMatrix Matrix::add(const FloatMatrix &m1, const FloatMatrix &m2) {
    int r = m1.size();
    int c = m1[0].size();
    FloatMatrix result(r, vector<float>(c, 0.0f));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return result;
}

FloatMatrix Matrix::subtract(const FloatMatrix &m1, const FloatMatrix &m2) {
    int r = m1.size();
    int c = m1[0].size();
    FloatMatrix result(r, vector<float>(c, 0.0f));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }

    return result;
}

FloatMatrix Matrix::combine_quadrants(const FloatMatrix &topLeft,
                              const FloatMatrix &topRight,
                              const FloatMatrix &bottomLeft,
                              const FloatMatrix &bottomRight) {
    FloatMatrix combined;

    int numRows = topLeft.size();
    for (int i = 0; i < numRows; ++i) {
        vector<float> row;
        row.insert(row.end(), topLeft[i].begin(), topLeft[i].end());
        row.insert(row.end(), topRight[i].begin(), topRight[i].end());
        combined.push_back(row);
    }

    numRows = bottomLeft.size();
    for (int i = 0; i < numRows; ++i) {
        vector<float> row;
        row.insert(row.end(), bottomLeft[i].begin(), bottomLeft[i].end());
        row.insert(row.end(), bottomRight[i].begin(), bottomRight[i].end());
        combined.push_back(row);
    }

    return combined;
}

Matrix Matrix::divide_and_conquer_mult(const Matrix &m2_, bool strassen) const {
    const FloatMatrix &m1 = this->get_matrix();
    const FloatMatrix &m2 = m2_.get_matrix();
    
    if (strassen) return strassen_mult_helper(m1,m2);
    else return divide_and_conquer_mult_helper(m1, m2);
}

// only suitable for square matrices
FloatMatrix Matrix::divide_and_conquer_mult_helper(const FloatMatrix &m1,
                                                   const FloatMatrix &m2) {
    // find output dimensions
    int n = m1[0].size();
    FloatMatrix result;

    // base case
    if (n <= 64) {
        result = Matrix::multiply(m1, m2);
    } else {
        // step case (divide into 4 parts)
        auto [a, b, c, d] = break_matrix_into_quadrants(m1);
        auto [e, f, g, h] = break_matrix_into_quadrants(m2);

        FloatMatrix topLeft = add(divide_and_conquer_mult_helper(a, e),
                                  divide_and_conquer_mult_helper(b, g));
        FloatMatrix topRight = add(divide_and_conquer_mult_helper(a, f),
                                   divide_and_conquer_mult_helper(b, h));
        FloatMatrix bottomLeft = add(divide_and_conquer_mult_helper(c, e),
                                     divide_and_conquer_mult_helper(d, g));
        FloatMatrix bottomRight = add(divide_and_conquer_mult_helper(c, f),
                                      divide_and_conquer_mult_helper(d, h));

        // conquer (combine quadrants into 1 big matrix)
        result = combine_quadrants(topLeft, topRight, bottomLeft, bottomRight);
    }

    return result;
}
