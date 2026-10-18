#include <iostream>

double average(int sum, int count) {
 if (count <= 0) {
 return 0.0;
 }
 return static_cast<double>(sum) / count;
}

int main() {
    double result = average (5, 2);

    std::cout << "Expected: 2.5\n";
    std::cout << "Actual: " << result << '\n';
    
    return 0;
}