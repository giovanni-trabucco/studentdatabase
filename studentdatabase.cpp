#include "studentdatabase.h"

StudentDatabase::StudentDatabase()
{
    nStudents = 0;
}

void StudentDatabase::addStudent(const Student& _student)
{
    students.push_back(_student);
    nStudents++;
}

float StudentDatabase::calculateAverageMarks() const
{
    float avg_total = 0;
    float alpha = nStudents/(nStudents + 1);

    for(const Student& student : students)
    {
        std::optional<float> avg_stud = student.calculateAverageMarks();
        if(avg_stud)
            avg_total = avg_total * alpha + (1 - alpha) * avg_stud.value(); //calcola la media di tutti gli studenti
    }
    return avg_total;
}

std::vector<Student> StudentDatabase::displayStudents() const
{
    return students;
}

int StudentDatabase::getNStudents()
{
    return nStudents;
}

std::optional<Student> StudentDatabase::findStudentByRollNumber(int _rollNumber)
{
    for(const Student& stud : students)
    {
        if(stud.get_roll_number() == _rollNumber)
            return stud;
    }
    return {};
}

void StudentDatabase::removeStudent(int idx)
{
    if(idx < students.size())
        students.erase(students.begin() + idx);

    else return;
}

StudentDatabase::~StudentDatabase()
{}
