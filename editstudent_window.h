#ifndef EDITSTUDENT_WINDOW_H
#define EDITSTUDENT_WINDOW_H

#include <QDialog>

namespace Ui {
class EditStudent_window;
}

class EditStudent_window : public QDialog
{
    Q_OBJECT

public:
    explicit EditStudent_window(QWidget *parent = nullptr);
    ~EditStudent_window();

private:
    Ui::EditStudent_window *ui;
};

#endif // EDITSTUDENT_WINDOW_H
