
#include "student.hpp"
#include <numeric>

student::student(long long id, std::string name, std::map<std::string, int> score, float average){
    id = id;
    name = name;
    score = score;
    average = average;
}

void student::setname(std::string n){
    name = n;
}
void student::SetScoreByName(std::string CourseName, int s){
    score[CourseName] = s;
}
void student::setaverage(){
    if (!score.empty()) {
        average = std::accumulate(score.begin(), score.end(), 0,
                                  [](int sum, const std::pair<std::string, int>& pair) {
                                      return sum + pair.second;
                                  }) / static_cast<float>(score.size());
    } else {
        average = 0;
    }
}

void student::setid(long long i){
    id = i;
}

std::string student::getname(){
    return name;
}
int student::getid(){
    return id;
}
// Return score of course i
int student::GetScoreByName(std::string CourseName){
    return score[CourseName];   
}
// Return average score of this student
float student::getaverage(){
    return average;
}