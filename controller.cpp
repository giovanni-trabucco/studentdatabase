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

    p_view->get_ui_element()->tableView->setModel(p_model);
    p_view->get_ui_element()->tableView->sortByColumn(0, Qt::AscendingOrder);

    connectSignalsSlots();
}

void Controller::slot_pb_remove_clicked()
{
    QModelIndexList selectedIndexes = p_view->get_ui_element()->tableView->selectionModel()->selectedIndexes();
    if(!selectedIndexes.isEmpty())
    {
        int row_idx = selectedIndexes.first().row();
        int rollID = p_model->item(row_idx, 0)->data().toInt(); //estrapola numero di matricola dello studente in questione

        p_model->slot_pb_remove_clicked(rollID, row_idx);
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

    p_model->slot_addStudent_okButtonClicked(roll_id, name, gpa);
}

void Controller::slot_studentAddedSuccesfully()
{
    p_view->get_ui_element()->tableView->setSortingEnabled(true);
    p_view->p_addStudent_window->slot_studentAddedSuccesfully();
}

void Controller::connectSignalsSlots()
{
    connect(p_view, &View::sig_pb_remove_clicked, this, &Controller::slot_pb_remove_clicked);
    connect(p_view, &View::sig_addStudent_okButtonClicked, this, &Controller::slot_addStudent_okButtonClicked);

    connect(p_model, &Model::sig_studentAlreadyExists, p_view->p_addStudent_window, &AddStudent_window::slot_studentAlreadyExists);
    connect(p_model, &Model::sig_studentAddedSuccesfully, this, &Controller::slot_studentAddedSuccesfully);
}

Controller::~Controller()
{
    delete p_view;
    delete p_model;
}
