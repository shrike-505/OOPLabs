#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <cstdlib>
#include <string>
#include <map>
// student class, with name, scores, and average score
class student
{
private:
    std::string name;
    std::map<std::string, int> score; // string for course name, int for score
    float average;
    int id;
public:
    student(long long id = 1, std::string name = "", std::map<std::string, int> score = {}, float average = 0);
    void setname(std::string n);
    void setid(long long i);
    void SetScoreByName(std::string CourseName, int s);
    void setaverage();
    std::string getname();
    int getid();
    // Return the score of the product
    int GetScoreByName(std::string CourseName);
    // Return the average score of the product
    float getaverage();
};



#endif