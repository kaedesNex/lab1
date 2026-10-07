#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

int main() {
    int totalClasses;
    int attendedClasses;
    int score;

    std::cin >> totalClasses;
    std::cin >> attendedClasses;
    std::cin >> score;
    const double attendancePercent = 100.0 * attendedClasses / totalClasses;

    if (totalClasses < 1||totalClasses > 100||attendedClasses < 0||attendedClasses > totalClasses||score < 0||score > 100) {
        std::cerr << "Error: Invalid input";
        return 1;
    }
    std::cout << std::fixed << std::setprecision(2) << "attendancePercent: " << attendancePercent << "%, ";
    if (attendancePercent < 60) {
        std::cout << "Not allowed"; 
    }
    else if (score < 50) {
        std::cout << "Accepted, but the result threshold in not met";
    }
    else {
        std::cout << "Conditional pass";
    }
    
}