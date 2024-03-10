#ifndef ADDSTUDENT_WINDOW_H
#define ADDSTUDENT_WINDOW_H

#include <QDialog>
#include "QDialogButtonBox"
#include "QLineEdit"

namespace Ui {
class AddStudent_window;
}

class AddStudent_window : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudent_window(QWidget *parent = nullptr);
    ~AddStudent_window();

private:
    Ui::AddStudent_window *ui;
    bool check_input();
    void connectSignalsSlots();

signals:
    void sig_cancelButtonClicked();
    void sig_okButtonClicked(QLineEdit& roll_id, QLineEdit& le_name, QLineEdit& gpa);

private slots:
    void slot_okButtonClicked();
    void slot_validate_input();
    void slot_cancelButtonClicked();

public slots:
    void slot_studentAlreadyExists(int roll_id);
    void slot_studentAddedSuccesfully();
};

#endif // ADDSTUDENT_WINDOW_H
