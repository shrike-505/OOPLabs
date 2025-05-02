#include "Diary.hpp"
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

/**
 * @brief Checks if a string is a valid date in the form of "yyyy-mm-dd"
 *
 * @param s The string to be checked
 * @return true if the string is a valid date, false otherwise
 */
bool is_date(const std::string &s) {
    if (s.length() != 10) return false;
    if (s[4] != '-' || s[7] != '-') return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(s[i])) return false;
    }
    return true;
}

/**
 * @brief Loads a diary from a file
 *
 * The file should contain each date followed by the content of the
 * diary entry on that date, separated by a line containing a dot
 * (".") followed by another line containing the next date. If a date
 * is missing, the content of the previous entry is used.
 *
 * @param filename The name of the file to load from
 * @return true if the file was loaded successfully, false otherwise
 */
bool Diary::load(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) return true;

    entries.clear();
    string current_date, line;
    vector<string> content_lines;

    while (getline(file, line)) {
        if (is_date(line)) {
            if (!current_date.empty()) {
                entries[current_date] = "";
                content_lines.clear();
            }
            current_date = line;
        } else if (line == ".") {
            if (!current_date.empty()) {
                string content;
                for (const auto &l : content_lines) {
                    content += l + "\n";
                }
                if (!content.empty()) content.pop_back();
                entries[current_date] = content;
                current_date.clear();
                content_lines.clear();
            }
        } else {
            content_lines.push_back(line);
        }
    }
    return true;
}

/**
 * @brief Save the diary to a file
 *
 * Writes the diary entries to the given file, with each entry on its
 * own line, separated by a line containing a dot (".") followed by
 * another line containing the next date. If the file cannot be opened,
 * returns false.
 *
 * @param filename The name of the file to save to
 * @return true if the file was saved successfully, false otherwise
 */
bool Diary::save(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto &entry : entries) {
        file << entry.first << "\n";
        istringstream content_stream(entry.second);
        string line;
        while (getline(content_stream, line)) {
            file << line << "\n";
        }
        file << ".\n";
    }
    return true;
}


/**
 * @brief Add a new entry to the diary
 *
 * Adds a new entry to the diary for the given date. If an entry already
 * exists for the given date, it will be overwritten.
 *
 * @param date The date of the entry
 * @param content The content of the entry
 */
void Diary::add(const string &date, const string &content) {
    entries[date] = content;

}

/**
 * @brief Remove an entry from the diary
 *
 * Removes the entry with the given date from the diary. If no such
 * entry exists, returns false.
 *
 * @param date The date of the entry to remove
 * @return true if the entry was found and removed, false otherwise
 */
bool Diary::remove(const string &date) {
    return entries.erase(date) > 0;
}

/**
 * @brief Get the content of an entry
 *
 * Returns the content of the entry with the given date, or an empty
 * string if no such entry exists.
 *
 * @param date The date of the entry to look up
 * @return The content of the entry, or "" if no such entry exists
 */
string Diary::get_content(const string &date) const {
    auto it = entries.find(date);
    return it != entries.end() ? it->second : "";
}

/**
 * @brief Get all dates in the diary
 *
 * Returns a vector of all dates in the diary
 *
 * @return A vector of all dates in the diary
 */
vector<string> Diary::get_dates() const {
    vector<string> dates;
    for (const auto &entry : entries) dates.push_back(entry.first);
    return dates;
}

/**
 * @brief Get all dates in a given range
 *
 * Returns a vector of all dates in the diary that are within the
 * given range. The range is inclusive.
 *
 * @param start The start of the range
 * @param end The end of the range
 * @return A vector of all dates within the range
 */
vector<string> Diary::get_dates_in_range(const string &start, const string &end) const {
    vector<string> dates;
    for (auto it = entries.lower_bound(start); it != entries.end() && it->first <= end; ++it)
        dates.push_back(it->first);
    return dates;
}