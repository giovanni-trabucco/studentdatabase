#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H

#include "student.h"
#include <optional>
#include <map>

class StudentDatabase
{
public:
    StudentDatabase();
    ~StudentDatabase();

    void addStudent(Student stud);
    std::map<int, Student> getStudentsMap() const;
    float calculateAverageMarks() const;
    std::optional<Student> findStudentByRollNumber(int _roll_number) const;
    int getNStudents() const;
    void removeStudent(int idx);

private:
    std::map<int, Student> studentsMap;
    int nStudents;
};

#endif // STUDENTDATABASE_H
