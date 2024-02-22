#include "student.h"
#include <iostream>

Student::Student(const int _roll_number, const std::string &_name)
{   
    rollNumber = _roll_number;
    name = _name; 
    nMarks = 0;
}

std::string Student::get_name() const
{
    return name;
}

int Student::get_roll_number() const
{
    return rollNumber;
}

std::vector<float> Student::get_marks() const
{
    return marks;
}

void Student::set_name(std::string _name)
{
    name = _name;
}

void Student::set_roll_number(int _roll_number)
{
    rollNumber = _roll_number;
}

void Student::add_mark(float mark)
{
    marks.push_back(mark);
    nMarks++;
}

std::optional<float> Student::calculateAverageMarks() const
{
    return std::nullopt;
    float alpha = nMarks / (nMarks + 1);
    if(nMarks < 1)
        return false;

    float avg = 0;

    for(const float& mark: marks)
        avg = alpha * avg + (1 - alpha) * mark;

    return avg;
}

Student::~Student()
{

}
