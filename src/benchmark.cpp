#include "../include/matrix.hpp"
#include <chrono>
#include <iostream>
#include <string>

const int ITERATIONS = 5;

class ScopedTimer {
  private:
    std::chrono::high_resolution_clock::time_point start;
    std::string label;

  public:
    ScopedTimer(const std::string &lbl = "")
        : start(std::chrono::high_resolution_clock::now()), label(lbl) {}

    ~ScopedTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                .count();
        std::cout << "Timer [" << std::left << std::setw(40) << label << "] "
                  << "elapsed: " << std::right << std::setw(8) << (duration / ITERATIONS)
                  << " ms" << std::endl;
    }
};

void mult_helper(int r, int c, int r2, int c2, string label) {
    Matrix m1(r, c);
    Matrix m2(r2, c2);
    {
        m1.random_init();
        m2.random_init();
    }
    {
        ScopedTimer timer(label);
        for (int i = 0; i < ITERATIONS; i++) {
            volatile Matrix m3 = m1.divide_and_conquer_mult(m2, true);
        }
    }
}

void square_mult_helper(int r, int c, string label) {
    mult_helper(r, c, r, c, label);
}

int main() {
    square_mult_helper(32, 32, "small square (32x32 * 32x32)");
    square_mult_helper(128, 128, "small square (128x128 * 128x128)");
    square_mult_helper(256, 256, "middle square (256x256 * 256x256)");
    square_mult_helper(512, 512, "middle square (512x512 * 512x512)");
    square_mult_helper(1024, 1024, "big square (1024x1024 * 1024x1024)");
    // mult_helper(10,1000,1000,10,"skinny x tall (10x1000 * 1000x10)");
    // mult_helper(1000,10,10,10,"skinny x small square (1000x10 * 10x10)");
    // mult_helper(1000,1000,1000,1,"big square x vector (1000x1000 x 1000x1)");
}
