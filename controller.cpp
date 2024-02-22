#include "controller.h"
#include <QModelIndexList>
#include "ui_mainwindow.h"

Controller::Controller(Model *model, View *view, QWidget *parent) : QWidget(parent)
{
    p_model = model;
    p_view = view;

    pb_add = p_view->get_ui_element()->pb_add;
    pb_edit = p_view->get_ui_element()->pb_edit;
    pb_remove = p_view->get_ui_element()->pb_remove;

    p_view->get_ui_element()->tableView->setModel(model);

    connect(p_view, &View::sig_pb_remove_clicked, this, &Controller::slot_pb_remove_clicked);
    connect(p_view, &View::sig_addStudent_okButtonClicked, this, &Controller::slot_addStudent_okButtonClicked);

    connect(this, &Controller::sig_pb_remove_clicked, p_model, &Model::slot_pb_remove_clicked);
    connect(this, &Controller::sig_addStudent_okButtonClicked, p_model, &Model::slot_addStudent_okButtonClicked);

    connect(p_model, &Model::sig_studentAlreadyExists, this, &Controller::slot_studentAlreadyExists);
    connect(this, &Controller::sig_studentAlreadyExists, p_view, &View::slot_studentAlreadyExists);
}

void Controller::slot_pb_remove_clicked()
{
    QModelIndexList selectedIndexes = p_view->get_ui_element()->tableView->selectionModel()->selectedIndexes();
    if(!selectedIndexes.isEmpty())
    {
        int row_idx = selectedIndexes.first().row();
        emit sig_pb_remove_clicked(row_idx);
    }
}

void Controller::slot_addStudent_okButtonClicked(QLineEdit& le_roll_id, QLineEdit& le_name, QLineEdit& le_gpa)
{
    int roll_id = le_roll_id.text().toInt();
    std::string name = le_name.text().toStdString();

    std::optional<float> gpa;
    if(le_gpa.text().isEmpty())
        gpa = std::nullopt;

    else
        gpa = le_gpa.text().toFloat();

    emit sig_addStudent_okButtonClicked(roll_id, name, gpa);
}

void Controller::slot_studentAlreadyExists(int roll_id)
{
    emit sig_studentAlreadyExists(roll_id);
}
