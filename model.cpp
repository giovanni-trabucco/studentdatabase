#include "model.h"
#include <vector>
#include <iostream>
#include <string>
#include "customstandarditem.h"

Model::Model(StudentDatabase *db, QObject* parent) : QStandardItemModel(parent)
{
    p_db = db;
    this->setHorizontalHeaderLabels({"Roll number", "Name", "Marks Average"});
    initDataModel(db);
}

void Model::initDataModel(StudentDatabase *db)
{
    std::map<int, Student> studentsMap = db->getStudentsMap();

    int row = 0;
    for(std::map<int, Student>::iterator it = studentsMap.begin(); it != studentsMap.end(); it++)
    {
        Student current_student = it->second;
        this->setItem(row, 0, new CustomStandardItem<int>(current_student.get_roll_number()));
        this->setItem(row, 1, new QStandardItem(QString::fromStdString(current_student.get_name())));

        std::optional<float> averageMarks = current_student.calculateAverageMarks();
        if(averageMarks)
            this->setItem(row, 2, new CustomStandardItem<float>(averageMarks.value()));

        else
            this->setItem(row, 2, new QStandardItem(QString("N/A")));

        row++;
    }
}

void Model::slot_addStudent_okButtonClicked(const int roll_id, const std::string name, const std::optional<float> gpa)
{
    std::optional<Student> found_stud = p_db->findStudentByRollNumber(roll_id);
    if(found_stud)
    {
        emit sig_studentAlreadyExists(roll_id);
        return;
    }

    Student stud(roll_id, name);
    p_db->addStudent(stud);

    int rowCount = this->rowCount();
    this->insertRow(rowCount);

    this->setItem(rowCount, 0, new CustomStandardItem<int>(roll_id));
    this->setItem(rowCount, 1, new QStandardItem(QString::fromStdString(name)));

    if(gpa)
        this->setItem(rowCount, 2, new CustomStandardItem<float>(gpa.value()));
    else
        this->setItem(rowCount, 2, new QStandardItem(QString("N/A")));

    emit sig_studentAddedSuccesfully();
}


void Model::slot_pb_remove_clicked(int rollID, int idx)
{
    p_db->removeStudent(rollID);
    this->removeRow(idx);
}

Model::~Model()
{
    delete p_db;
}
