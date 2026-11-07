#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cassert>
#include <limits>
#include <utility>
using namespace std;

std::string trim(const std::string& text) {
    const std::size_t first = text.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = text.find_last_not_of(' ');
    return text.substr(first, (last - first + 1));
}

bool readMovie(std::vector<std::string>& names, std::vector<int>& durations) {
    assert(names.size() == durations.size());
    if (names.size() >= 30) {
        std::cerr << "Error: Threshold reached: 30 movies." << endl;
        return false;
    }

    std::string name;

    while (true) {
        std::cout << "Movie`s name (not more than 60 bytes): ";
        if (!std::getline(std::cin, name)) {
            return false;
        }
        name = trim(name);
        if (name.empty()) {
            std::cout << "Name cannot be empty. Enter a valid name." << endl;
        }
        else if (name.size() > 60) {
            std::cout << "Name is too long. Enter a name with 60 bytes or less." << endl;
        }
        else {
            break;
        }
    }

    int duration;
    while (true) {
        std::cout << "Movies duration (in minutes: 1-25): ";
        if (!(std::cin >> duration)) {
            return false;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (duration >= 1 && duration <= 25) {
            break;
        }
        else {
            std::cout << "Invalid duration. Duration must be between 1 and 25 minutes." << endl;
        }
    }

    names.push_back(name);
    durations.push_back(duration);
    assert(names.size() == durations.size());
    return true;
}

void printMovies(const std::vector<std::string>& names, const std::vector<int>& durations) {
    assert(names.size() == durations.size());
    if (names.empty()) {
        std::cout << "Catalog is empty." << endl;
        return;
    }
    for (std::size_t i = 0; i < names.size(); ++i) {
        std::cout << i + 1 << ". " << names[i] << " (" << durations[i] << " min)" << endl;
    }
}

void searchMovies(const std::vector<std::string>& names, const std::vector<int>& durations, const std::string& query) {
    assert(names.size() == durations.size());
    bool found = false;
    for (std::size_t i = 0; i < names.size(); ++i) {
        if (names[i].find(query) != std::string::npos) {
            std::cout << "Found: " << names[i] << " (" << durations[i] << " min)" << endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "There`s no matches" << endl;
    }
}

void filterMovies(const std::vector<std::string>& names, const std::vector<int>& durations) {
    assert(names.size() == durations.size());
    bool found = false;
    for (std::size_t i = 0; i < names.size(); ++i) {
        if (durations[i] < 12) {
            std::cout << "Found: " << names[i] << " (" << durations[i] << " min)" << endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "There`s no movies shorter than 12 min`s" << endl;
    }
}

void printStatistics(const std::vector<int>& durations) {
    std::cout << "Count: " << durations.size() << endl;
    int sum = 0;
    for (std::size_t i = 0; i < durations.size(); ++i) {
        sum += durations[i];
    }

    std::cout << "Sum: " << sum << " min" << endl;

    if (durations.empty()) {
        std::cout << "Average: " << "catalog is empty" << endl;
        return;
    }

    int minDuration = durations[0];
    int maxDuration = durations[0];

    for (std::size_t i = 1; i < durations.size(); ++i) {
        if (durations[i] < minDuration) {
            minDuration = durations[i];
        }
        if (durations[i] > maxDuration) {
            maxDuration = durations[i];
        }
    }

    double average = static_cast<double>(sum) / durations.size();
    std::cout << fixed << std::setprecision(2);
    std::cout << "Average: " << average << " min" << endl;
    std::cout << "Min: " << minDuration << " min" << endl;
    std::cout << "Max: " << maxDuration << " min" << endl;
}

void sortMovies(std::vector<std::string>& names, std::vector<int>& durations) {
    assert(names.size() == durations.size());
    for (std::size_t i = 0; i < durations.size(); ++i) {
        std::size_t maxIndex = i;
        for (std::size_t j = i + 1; j < durations.size(); ++j) {
            if (durations[j] > durations[maxIndex]) {
                maxIndex = j;
            }
        }
    std::swap(durations[i], durations[maxIndex]);
    std::swap(names[i], names[maxIndex]);
    }
}

int main() {
    assert(trim(" short Comedy ") == "short Comedy");
    assert(trim("  ").empty());
    std::vector<std::string> names;
    std::vector<int> durations;
    
    int count;

    while(true) {
        std::cout << "Enter the number of movies to add (0-20): ";
        if (!(std::cin >> count)) {
            std::cerr << "Invalid input or end of input." << endl;
            return 1;
        }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (count >= 0 && count <= 20) {
            break;
        }

        std::cout << "Invalid number. Enter a number between 0 and 20." << endl;
    }

    for (int i = 0; i < count; ++i) {
        std::cout << "Movie: " << i + 1 << endl;
        if (!readMovie(names, durations)) {
            std::cerr << "Movie name enter is not ended" << endl;
            return 1;
        }
    }

    std::cout <<"\nCatalog: \n";
    printMovies(names, durations);
    std::string query;

    while (true) {
        std::cout << "Enter a movie name to search: ";
        if (!std::getline(std::cin, query)) {
            std::cerr << "Invalid input or end of the input." << endl;
            return 1;
        }
        query = trim(query);
        if (!query.empty()) {
            break;
        }
        std::cout << "Search query cannot be empty. Enter a valid movie name." << std::endl;
    }

    std::cout << "\nSearch results: \n";
    searchMovies(names, durations, query);
    std::cout << "\nMovies shorter than 12 minutes: \n";
    filterMovies(names, durations);
    std::cout << "\nStatistics: \n";
    printStatistics(durations);
    sortMovies(names, durations);
    std::cout << "\nSorted by duration, descending: \n";
    printMovies(names, durations);
}