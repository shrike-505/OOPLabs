#include "student.hpp"
#include "student.cpp"
#include <iomanip>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <limits>

// frequently used operators
using std::cin;
using std::cout;
using std::endl;
using std::cerr;

int main(int argc, char* argv[])
{
    std::string line; // read one line
    std::vector<std::string> temp_line; // split one line into mutiple strings(id, course name - score, etc..)
    std::vector<student> stus; // store all students
    std::set<std::string> courses; // store all courses
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <testcase>" << endl;
        return 1;
    }
    std::string filename = argv[1]; // ./testcases/testx.in
    std::ifstream input(filename);
    if(!input){
        cerr << "Error: Cannot open file" << argv[1] << endl;
        return 1;
    }

    int id = 1;
    
    // Read student records and collect all courses
    // Get one line
    while (std::getline(input, line))
    {
        // Split one line
        std::istringstream ss(line);
        std::string name;
        std::string score_str;
        std::string course_name;
        
        // Get name
        std::getline(ss, name, ',');
        student stu(id, name, {}, 0);

        // Get each course
        while (std::getline(ss, course_name, ',')){
            // And score of which
            std::getline(ss, score_str, ',');
            int score = std::stoi(score_str);
            stu.SetScoreByName(course_name, score);
            courses.insert(course_name);

        }
        stu.setname(name);
        stu.setid(id);
        stu.setaverage();
        stus.push_back(stu);
        id++;
    }

    
    // Output student sheet
    cout << "no      name    ";
    for(auto it = courses.begin(); it != courses.end(); it++){
        cout << std::left << std::setw(8) << *it;
    }
    cout << "average ";
    cout << std::endl;
    for(auto it = stus.begin(); it != stus.end(); it++){
        cout << std::left << std::setw(8) << it->getid() << std::left << std::setw(8) << it->getname();
        for(auto it2 = courses.begin(); it2 != courses.end(); it2++){
            if (it->GetScoreByName(*it2) > 0){
                cout << std::left << std::setw(8) << it->GetScoreByName(*it2);
            } else {
                // Replace 0 with "NA", everyone gets scores more than 0 by default
                cout << std::left << std::setw(8) << "NA";
            }
        }
        cout << std::left << std::setw(8) << it->getaverage() << std::setprecision(7) << std::endl;
    }
    
    // Calculate and output course average, max, min
    cout << "        average ";
    for (auto it = courses.begin(); it != courses.end(); it++) {
        float sum = 0;
        int count = 0;
        for (auto it2 = stus.begin(); it2 != stus.end(); it2++) {
            int score = it2->GetScoreByName(*it);
            if (score > 0) {
                sum += score;
                count++;
            }
        }
        float avg = (count > 0) ? sum / count : 0;
        cout << std::left << std::setw(8) << std::setprecision(6) << avg;
    }
    cout << std::endl;

    cout << "        max     ";
    for (auto it = courses.begin(); it != courses.end(); it++) {
        int max = std::numeric_limits<int>::min();
        for (auto it2 = stus.begin(); it2 != stus.end(); it2++) {
            int score = it2->GetScoreByName(*it);
            if (score > max) {
                max = score;
            }
        }
        cout << std::left << std::setw(8) << max;
    }
    cout << std::endl;

    cout << "        min     ";
    for (auto it = courses.begin(); it != courses.end(); it++) {
        int min = std::numeric_limits<int>::max();
        for (auto it2 = stus.begin(); it2 != stus.end(); it2++) {
            int score = it2->GetScoreByName(*it);
            if (score > 0 && score < min) {
                min = score;
            }
        }

        if (min != std::numeric_limits<int>::max()) {
            cout << std::left << std::setw(8) << min;
        } else {
            cout << std::left << std::setw(8) << "NA";
        }
    }
    cout << std::endl;
    return 0;
}