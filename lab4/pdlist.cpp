#include "Diary.hpp"
#include <iostream>
#include <string>


using namespace std;

/**
 * @brief pdlist: List entries in diary
 *
 * pdlist lists all entries in the diary or entries in a given range.
 *
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 * @return 0 if successful, -1 if not
 */
int main(int argc, char *argv[]) {
    Diary diary;
    if (!diary.load("diary.txt")) {
        cerr << "Failed to load diary." << endl;
        return -1;
    }

    vector<string> dates;
    if (argc == 1) {
        dates = diary.get_dates();
    } else if (argc == 3) {
        string start = argv[1], end = argv[2];
        if (!is_date(start) || !is_date(end)) {
            cerr << "Invalid date format." << endl;
            return -1;
        }
        dates = diary.get_dates_in_range(start, end);
    } else {
        cerr << "Usage: pdlist [start end]" << endl;
        return -1;
    }

    for (const auto &date : dates) {
        cout << date << endl;
        string content = diary.get_content(date);
        if (!content.empty()) cout << content << endl;
    }
    return 0;
}