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
    ui->le_search->setPlaceholderText("Filter by name or roll ID");

    //segnali da mainWindow verso l'etere
    connect(ui->pb_remove, &QPushButton::clicked, this, &View::slot_pb_remove_clicked);
    connect(ui->pb_add, &QPushButton::clicked, this, &View::slot_pb_add_clicked);
    connect(ui->tableView, &CustomTableView::sig_table_clicked, this, &View::slot_table_view_clicked);
    connect(ui->le_search, &QLineEdit::textChanged, this, &View::slot_search_le_changed);

    //segnali da e verso addStudent_window
    p_addStudent_window = new AddStudent_window(this);
    connect(p_addStudent_window, &AddStudent_window::sig_okButtonClicked, this, &View::sig_addStudent_okButtonClicked);
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

void View::slot_search_le_changed(const QString& text)
{
    if(text.isEmpty())
    {
        for(int row=0; row < ui->tableView->model()->rowCount(); row++)
            ui->tableView->setRowHidden(row, false);

        return;
    }

    else searchElement(text);
}

void View::searchElement(const QString& text)
{
    QModelIndexList matches;

    //cerca text nelle prime 2 colonne e aggiungi in lista gli indici di tutte le celle che lo matchano
    for(int col=0; col<2; col++)
        matches += (ui->tableView->model()->match(ui->tableView->model()->index(0, col), Qt::DisplayRole, text, -1, Qt::MatchContains));

    //cicla tutte le righe:
    for(int row=0; row<ui->tableView->model()->rowCount(); row++)
    {
        bool matchFound = false;

        //cicla tutte le colonne della riga. Se l' indice della cella (row, col) compare in matches, mi fermo e setto matchFound=true
        for(int col=0; col<2; col++)
        {
            QModelIndex current_idx = ui->tableView->model()->index(row, col);
            if(matches.contains(current_idx))
            {
                matchFound = true;
                break;
            }
        }
        ui->tableView->setRowHidden(row, !matchFound);
    }
}


View::~View()
{
    delete ui;
}
