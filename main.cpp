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
    Student stud1(9, "marco");
    Student stud2(100, "luca");
    Student stud3(1, "francesco");
    Student stud4(20, "federico");
    Student stud5(3000, "matteo");
    Student stud6(40, "giovanni");
    Student stud7(16, "mirco");

    StudentDatabase *db = new StudentDatabase();
    db->addStudent(stud1);
    db->addStudent(stud2);
    db->addStudent(stud3);
    db->addStudent(stud4);
    db->addStudent(stud5);
    db->addStudent(stud6);
    db->addStudent(stud7);


    Student *stud8 = new Student(167, "mirco");
    db->addStudent(*stud8);

    delete stud8;


    //VIEW
    View *w = new View();

    //MODEL
    Model *m = new Model(db);

    //CONTROLLER
    Controller controller(m, w);

    w->show();



    return a.exec();
}
