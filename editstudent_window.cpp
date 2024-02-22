#include "editstudent_window.h"
#include "ui_editstudent_window.h"

EditStudent_window::EditStudent_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStudent_window)
{
    ui->setupUi(this);
}

EditStudent_window::~EditStudent_window()
{
    delete ui;
}
