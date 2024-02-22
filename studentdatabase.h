#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H

#include "student.h"
#include <optional>

class StudentDatabase
{
public:
    StudentDatabase();
    ~StudentDatabase();

    void addStudent(const Student& _student);
    std::vector<Student> displayStudents() const;
    float calculateAverageMarks() const;
    std::optional<Student> findStudentByRollNumber(int _roll_number);
    int getNStudents();
    void removeStudent(int idx);

private:
    std::vector<Student> students;
    int nStudents;
};

#endif // STUDENTDATABASE_H
