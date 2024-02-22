#include "addstudent_window.h"
#include "ui_addstudent_window.h"
#include "QPushButton"
#include "QMessageBox"
#include "QIntValidator"
#include "QRegularExpression"

AddStudent_window::AddStudent_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudent_window)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->lb_no_letters_in_roll_n->hide();
    ui->lb_no_digits_in_name->hide();
    ui->lb_no_letters_in_gpa->hide();
    connectSignalsSlots();
}

void AddStudent_window::connectSignalsSlots()
{
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &AddStudent_window::sig_cancelButtonClicked);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &AddStudent_window::slot_okButtonClicked);
    connect(ui->le_roll_id, &QLineEdit::textChanged, this, &AddStudent_window::validate_input);
    connect(ui->le_name, &QLineEdit::textChanged, this, &AddStudent_window::validate_input);
    connect(ui->le_gpa, &QLineEdit::textChanged, this, &AddStudent_window::validate_input);
}

void AddStudent_window::slot_okButtonClicked()
{
    emit sig_okButtonClicked(*ui->le_roll_id, *ui->le_name, *ui->le_gpa);
}

void AddStudent_window::slot_studentAlreadyExists(int roll_id)
{
    QMessageBox error_window(this);
    QString error_msg = QString::fromStdString("Student with Roll number " + std::to_string(roll_id) + " already exists");
    error_window.critical(this, "Error", error_msg);
}

void AddStudent_window::validate_input()
{
    bool setEnabled = true;

    if(ui->le_name->text().isEmpty() || ui->le_roll_id->text().isEmpty())
        setEnabled = false;

    static QRegularExpression rx_roll("^\\d+$"); //voglio solo numeri nella matricola //statica in modo da non ricreare l'oggetto ogni volta
    if(!rx_roll.match(ui->le_roll_id->text()).hasMatch() && !ui->le_roll_id->text().isEmpty())
    {
        ui->lb_no_letters_in_roll_n->show();
        setEnabled = false;
    }
    else
        ui->lb_no_letters_in_roll_n->hide();

    static QRegularExpression rx_name("^[a-zA-Z]+$"); //voglio solo lettere nel nome
    if(!rx_name.match(ui->le_name->text()).hasMatch() && !ui->le_name->text().isEmpty())
    {
        ui->lb_no_digits_in_name->show();
        setEnabled = false;
    }
    else
        ui->lb_no_digits_in_name->hide();

    QRegularExpression rx_gpa = rx_roll;
    if(!rx_gpa.match(ui->le_gpa->text()).hasMatch() && !ui->le_gpa->text().isEmpty())
    {
        ui->lb_no_letters_in_gpa->show();
        setEnabled = false;
    }
    else
        ui->lb_no_letters_in_gpa->hide();


    // abilita il bottone "Ok" solo se entrambi i campi sono NON vuoti.
    // viene chiamata ogni volta che uno dei campi viene modificato.
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(setEnabled);
}

AddStudent_window::~AddStudent_window()
{
    delete ui;
}
