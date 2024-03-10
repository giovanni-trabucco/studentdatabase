#include "studentdatabase.h"
#include <functional>

StudentDatabase::StudentDatabase()
{
    nStudents = 0;
}

void StudentDatabase::addStudent(Student stud)
{
    studentsMap.insert(std::pair<int, Student>(stud.get_roll_number(), stud));
    nStudents = static_cast<int> (studentsMap.size());
}

float StudentDatabase::calculateAverageMarks() const
{
    float avg_total = 0;
    float alpha = nStudents/(nStudents + 1);

    for(const std::pair<int, Student> pair : studentsMap)
    {
        Student stud = pair.second;
        std::optional<float> avg_stud = stud.calculateAverageMarks();
        if(avg_stud)
            avg_total = avg_total * alpha + (1 - alpha) * avg_stud.value(); //calcola la media di tutti gli studenti
    }
    return avg_total;
}

std::map<int, Student> StudentDatabase::getStudentsMap() const
{
    return studentsMap;
}

int StudentDatabase::getNStudents() const
{
    return nStudents;
}

std::optional<Student> StudentDatabase::findStudentByRollNumber(int _rollNumber) const
{
    std::map<int, Student>::const_iterator it;
    it = studentsMap.find(_rollNumber);

    if(it != studentsMap.end())
        return it->second;

    else return std::nullopt;
}

void StudentDatabase::removeStudent(int rollID)
{
    studentsMap.erase(rollID);
}

StudentDatabase::~StudentDatabase()
{}
