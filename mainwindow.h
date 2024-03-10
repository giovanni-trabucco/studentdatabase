#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addstudent_window.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT
public:
    View(QWidget *parent = nullptr);
    ~View();
    Ui::MainWindow* get_ui_element();
    friend class Controller;

private:
    Ui::MainWindow *ui;
    AddStudent_window *p_addStudent_window;
    void searchElement(const QString& text);

private slots:
    void slot_addStudent_okButtonClicked(QLineEdit &le_roll_id, QLineEdit &le_name, QLineEdit &le_gpa);
    void slot_pb_remove_clicked();
    void slot_pb_add_clicked();
    void slot_table_view_clicked(bool isIndexValid);
    void slot_search_le_changed(const QString& text);

signals:
    void sig_pb_remove_clicked();
    void sig_addStudent_okButtonClicked(QLineEdit& le_roll_id, QLineEdit& le_name, QLineEdit& le_gpa);
    void sig_studentAlreadyExists(int roll_id);
    void sig_studentAddedSuccesfully();
    void sig_left_mouse_pressed();
};
#endif // MAINWINDOW_H
