#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <optional>

class Student
{
public:
    Student(const int _rollNumber, const std::string& _name);
    ~Student();

    std::string get_name() const;
    int get_roll_number() const;
    std::vector<float> get_marks() const;
    std::optional<float> calculateAverageMarks() const;

    void set_name(std::string _name);
    void set_roll_number(int _roll_number);
    void add_mark(float mark);

private:
    std::string name;
    int rollNumber;
    std::vector<float> marks;
    int nMarks;
};

#endif // STUDENT_H
