#include "Diary.hpp"
#include <iostream>
#include <string>


using namespace std;

/**
 * @brief pdshow: Show a diary
 *
 * pdshow shows the diary with the given date.
 *
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return 0 if successful, -1 if not
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: pdshow <YYYY-MM-DD>" << endl;
        return -1;
    }

    string date = argv[1];
    if (!is_date(date)) {
        cerr << "Invalid date format." << endl;
        return -1;
    }

    Diary diary;
    if (!diary.load("diary.txt")) return -1;

    string content = diary.get_content(date);
    if (content.empty()) return -1;

    cout << content;
    return 0;
}