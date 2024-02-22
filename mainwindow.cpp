#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addstudent_window.h"
#include <QMessageBox>
#include <QFocusEvent>
#include "customtableview.h"

View::View(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pb_remove->setEnabled(false);
    ui->pb_edit->setEnabled(false);

    connect(ui->pb_remove, &QPushButton::clicked, this, &View::slot_pb_remove_clicked);
    connect(ui->pb_add, &QPushButton::clicked, this, &View::slot_pb_add_clicked);
    connect(ui->tableView, &CustomTableView::sig_table_clicked, this, &View::slot_table_view_clicked);

    p_addStudent_window = new AddStudent_window(this);
    connect(p_addStudent_window, &AddStudent_window::sig_okButtonClicked, this, &View::slot_addStudent_okButtonClicked);
    connect(p_addStudent_window, &AddStudent_window::sig_cancelButtonClicked, this, &View::slot_addStudent_cancelButtonClicked);

    connect(this, &View::sig_studentAlreadyExists, p_addStudent_window, &AddStudent_window::slot_studentAlreadyExists);
}

Ui::MainWindow* View::get_ui_element()
{
    return ui;
}

void View::slot_pb_add_clicked()
{
    p_addStudent_window->exec();
}

void View::slot_addStudent_okButtonClicked(QLineEdit& le_roll_id, QLineEdit& le_name, QLineEdit& le_gpa)
{   
    emit sig_addStudent_okButtonClicked(le_roll_id, le_name, le_gpa);
    p_addStudent_window->accept();
}

void View::slot_addStudent_cancelButtonClicked()
{
    p_addStudent_window->reject();
}

void View::slot_studentAlreadyExists(int roll_id)
{
    emit sig_studentAlreadyExists(roll_id);
}

void View::slot_pb_remove_clicked()
{
    QItemSelectionModel* select = ui->tableView->selectionModel();
    if(!select->hasSelection()) //se nessuna riga è selezionata il tasto remove non può essere cliccato
        return;

    ui->pb_remove->setEnabled(true);

    QMessageBox mb(this);
    mb.setText("Are you sure you want to delete this object?");
    mb.addButton(QMessageBox::No);
    mb.addButton(QMessageBox::Yes);
    int choice = mb.exec();

    if(choice == QMessageBox::Yes)
    {
        emit sig_pb_remove_clicked();
        mb.accept();
    }
    else mb.reject();
}


void View::slot_table_view_clicked(bool isIndexValid)
{
    ui->pb_remove->setEnabled(isIndexValid);
    ui->pb_edit->setEnabled(isIndexValid);
}


View::~View()
{
    delete ui;
}
