#include "controller.h"
#include "model.h"
#include "mainwindow.h"
#include "studentdatabase.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MODEL
    Student stud1(101, "marco");
    Student stud2(11, "luca");
    Student stud3(10, "francesco");
    StudentDatabase db;
    db.addStudent(stud1);
    db.addStudent(stud2);
    db.addStudent(stud3);

    //VIEW
    View w;

    //MODEL
    Model m(&db);

    //CONTROLLER
    Controller controller(&m, &w);

    w.show();
    return a.exec();
}
