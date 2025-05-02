#ifndef DIARY_HPP
#define DIARY_HPP

#include <string>
#include <map>
#include <vector>

class Diary {
public:
    bool load(const std::string &filename);
    bool save(const std::string &filename);
    void add(const std::string &date, const std::string &content);
    bool remove(const std::string &date);
    std::string get_content(const std::string &date) const;
    std::vector<std::string> get_dates() const;
    std::vector<std::string> get_dates_in_range(const std::string &start, const std::string &end) const;

private:
    std::map<std::string, std::string> entries;
};

bool is_date(const std::string &s);
#endif // DIARY_HPP