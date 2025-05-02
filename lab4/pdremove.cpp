#include "Diary.hpp"
#include <iostream>
#include <string>


using namespace std;

/**
 * @brief pdremove: Remove entries from diary
 *
 * pdremove removes the entries with the given date from the diary.
 *
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return 0 if successful, -1 if not
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: pdremove <YYYY-MM-DD>" << endl;
        return -1;
    }

    string date = argv[1];
    if (!is_date(date)) return -1;

    Diary diary;
    if (!diary.load("diary.txt")) return -1;
    if (!diary.remove(date)) return -1;
    return diary.save("diary.txt") ? 0 : -1;
}