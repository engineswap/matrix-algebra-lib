#include "../include/matrix.hpp"

// only suitable for square matrices
FloatMatrix Matrix::strassen_mult_helper(const FloatMatrix &m1,
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

        FloatMatrix p1 = strassen_mult_helper(a, (subtract(f,h)));
        FloatMatrix p2 = strassen_mult_helper(add(a,b), h);
        FloatMatrix p3 = strassen_mult_helper(add(c,d), e);
        FloatMatrix p4 = strassen_mult_helper(d, subtract(g,e));
        FloatMatrix p5 = strassen_mult_helper(add(a,d), add(e,h));
        FloatMatrix p6 = strassen_mult_helper(subtract(b,d), add(g,h));
        FloatMatrix p7 = strassen_mult_helper(subtract(a,c), add(e,f));

        FloatMatrix topLeft = add(subtract(add(p5,p4), p2), p6);
        FloatMatrix topRight = add(p1,p2);
        FloatMatrix bottomLeft = add(p3,p4);
        FloatMatrix bottomRight = subtract(subtract(add(p1,p5), p3), p7);

        // conquer (combine quadrants into 1 big matrix)
        result = combine_quadrants(topLeft, topRight, bottomLeft, bottomRight);
    }

    return result;
}
