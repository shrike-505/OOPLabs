#include <iostream>
#include <string>
#include <iomanip>
#include "student.hpp"

float sumup(int i, student s[]){
    float sum = 0;
    for (size_t u = 0; u < 10; u++)
    {
        sum += float(s[u].getscorei(i));
    }
    return sum;
}


int main()
{
    // 10 students
    student s[10];
    // Input Part
    // Input 10 students' names and scores, meanwhile calculate average score foreach student and course
    for (int i = 0; i < 10; i++)
    {
        std::string name;
        std::cout << "Enter name for student " << i + 1 << ": ";
        std::cin >> name;
        s[i].setname(name);
        std::cout << std::endl;
        for (int j = 0; j < 3; j++){
            int score;
            std::cout << "Enter score of course " << j + 1 << " for student " << i + 1 << ": ";
            std::cin >> score;
            s[i].setscorei(j, score);
            std::cout << std::endl;
        }
        s[i].setaverage();
    }
    // Calculate Average Part
    // Calculate the average score foreach course
    float avg[3] = {0};
    for (size_t i = 0; i < 3; i++){
        avg[i] = sumup(i, s) / 10;
    }

    // Get min/max score
    int CourseMin[3] = {0};
    for (size_t i = 0; i < 3; i++)
    {
        CourseMin[i] = s[0].getscorei(i);
        for (size_t j = 1; j < 10; j++)
        {
            if (s[j].getscorei(i) < CourseMin[i])
            {
                CourseMin[i] = s[j].getscorei(i);
            }
            
        }
    }
    int CourseMax[3] = {0};
    for (size_t i = 0; i < 3; i++)
    {
        CourseMax[i] = s[0].getscorei(i);
        for (size_t j = 1; j < 10; j++)
        {
            if (s[j].getscorei(i) > CourseMax[i])
            {
                CourseMax[i] = s[j].getscorei(i);
            }
        }
    }

    // Output a chart
    std::cout << "no      name    score1  score2  score3  average" << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << std::setw(8) << std::left << i+1 
                  << std::setw(8) << std::left << s[i].getname() 
                  << std::setw(8) << std::left << s[i].getscorei(0) 
                  << std::setw(8) << std::left << s[i].getscorei(1) 
                  << std::setw(8) << std::left << s[i].getscorei(2) 
                  << std::setw(8) << std::left << s[i].getaverage() 
                  << std::endl;
    }
    std::cout << "        " << std::setw(8) << "average" << std::setw(8) << avg[0] << std::setw(8) << avg[1] << std::setw(8) << avg[2] << std::endl;
    std::cout << "        " << std::setw(8) << "min" << std::setw(8) << CourseMin[0] << std::setw(8) << CourseMin[1] << std::setw(8) << CourseMin[2] << std::endl;
    std::cout << "        " << std::setw(8) << "max" << std::setw(8) << CourseMax[0] << std::setw(8) << CourseMax[1] << std::setw(8) << CourseMax[2] << std::endl;
}
    