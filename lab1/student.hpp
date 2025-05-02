#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <cstdlib>
#include <string>

// student class, with name, 3 scores, and average score
class student
{
private:
    std::string name;
    int score[3];
    float average;
public:
    // student();
    // ~student();
    void setname(std::string n){
        name = n;
    }
    void setscorei(int i, int s){
        if (s < 0 || s > 5) exit(0);
        score[i] = s;
    }
    void setaverage(){
        average = float(score[1] + score[2] + score[0]) / 3;
    }
    std::string getname(){
        return name;
    }
    // Return score of course i
    int getscorei(int i){
        return score[i];
    }
    // Return average score of this student
    float getaverage(){
        return average;
    }
};

// Sum up scores of course i, upon students s
float sumup(int i, student s[]);

#endif