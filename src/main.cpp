#include "../include/matrix.hpp"

int main(){
    Matrix m("2 3; 7 8; 1 1");

    cout << m << "\n\n";

    cout << m.transpose();

}
