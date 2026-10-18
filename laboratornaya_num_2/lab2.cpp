#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std;

double calculateAttendance(int totalClasses, int attendedClasses) {
    return 100.0 * attendedClasses / totalClasses;
}

bool isSearchMatch(double attendance, int score) {
    return attendance >= 60.0 && score >= 50;
}

void printStatus(double attendance, int score) {
    if (attendance < 60.0) {
        std::cout <<"Not allowed" << endl;
    }
    else if (score < 50) {
        std::cout <<"Allowed, but the result threshold is not met" << endl;
    }
    else {
        std::cout << "Conditional pass" << endl;
    }
}

bool readValidRecord(int number, int& totalClasses, int& attendedClasses, int& score) {
    while (true) {
        std::cout << "Students number" << number << endl;
    
        if (!(std::cin >> totalClasses >> attendedClasses >> score)) {
            std::cout <<"Input error or end of input. Try again." << endl;
            return false; 
        }

        if (totalClasses < 1 || totalClasses > 100 || attendedClasses < 0 || attendedClasses > totalClasses || score < 0 || score > 100) {
            std::cout <<"Error: Invalid values" << endl;
            continue;
        }

        return true;
    }
}

int main() {
    assert(calculateAttendance(8, 7) == 87.5);
    assert(calculateAttendance(20, 12) == 60.0);
    assert(calculateAttendance(20, 15) == 75.0);
    assert(calculateAttendance(1, 0) == 0.0);
    assert(calculateAttendance(94, 94) == 100.0);
    assert(isSearchMatch(60.0, 50));
    assert(!isSearchMatch(59.0, 50));
    assert(!isSearchMatch(60.0, 49));

    int N = 0;

    while(true) {
        if (!(std::cin >> N)) {
            std::cout <<"Input error or end of input. Try again." << endl;
            return 1;
        }
        if (N >= 1 && N <= 30) {
            break;
        }
        std::cout << "N must be in range from 1 to 30. Try again" << endl;
    }

    int accepted = 0;
    double sum = 0.0;

    double min = 0.0;
    double max = 0.0;
    int minNum = 0;
    int maxNum = 0;

    int matchCount = 0;
    int firstMatch = 0;

    std::cout << std::fixed << std::setprecision(2);

    while (accepted < N) {
        int totalClasses = 0;
        int attendedClasses = 0;
        int score = 0;
        int number = accepted + 1;
        
        if (!readValidRecord(number, totalClasses, attendedClasses, score)) {
            return 1;
        }

        double m = calculateAttendance(totalClasses, attendedClasses);
        bool match = isSearchMatch(m,score);

        std::cout <<"Attendance: " << m << "%\n";
        printStatus(m, score);

        sum += m;

        if (accepted == 0) {
            min = m;
            max = m;
            minNum = number;
            maxNum = number;
        }
        else {
            if(m < min) {
                min = m;
                minNum = number;
            }
            if(m > max) {
                max = m;
                maxNum = number;
            }
        }

        if (match) {
            ++matchCount;

            if(firstMatch == 0) {
                firstMatch = number;
            }
        }

        ++accepted;
    }

    double average = sum / N;

    std::cout << "Summary" << endl;
    std::cout << "Accepted entries: " << accepted << endl;
    std::cout << "Sum of indicators: " << sum << endl;
    std::cout << "Average attendance: " << average << "%\n";
    std::cout << "Min: " << min << "% (student number" << minNum << ")\n";
    std::cout << "Max: " << max << "% (student number" << maxNum << ")\n";
    std::cout << "Match count: " << matchCount << endl;

    if (firstMatch == 0) {
        std::cout << "First match: none" << endl;
    }
    else {
        std::cout << "First match: student number" << firstMatch << endl;
    }

    return 0;
}