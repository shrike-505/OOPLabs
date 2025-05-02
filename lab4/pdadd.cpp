#include "Diary.hpp"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief pdadd: Add entries to diary
 *
 * pdadd adds a new entry to diary.txt.
 *
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return 0 if successful, -1 if not
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: pdadd <YYYY-MM-DD>" << endl;
        return -1;
    }

    string date = argv[1];
    if (!is_date(date)) {
        cerr << "Invalid date format." << endl;
        return -1;
    }

    string content, line;
    while (getline(cin, line) && line != ".") {
        content += line + "\n";
    }
    if (!content.empty()) content.pop_back();

    Diary diary;
    diary.load("diary.txt");
    diary.add(date, content);
    return diary.save("diary.txt") ? 0 : -1;
}