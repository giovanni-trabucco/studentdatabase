#ifndef BUTTONSWIDGET_H
#define BUTTONSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <model.h>
#include <mainwindow.h>
#include <QSortFilterProxyModel>

class Controller : public QWidget
{
    Q_OBJECT
public:
    Controller(Model *model, View *view, QWidget *parent=nullptr);
    ~Controller();

private:
    View *p_view;
    Model *p_model;
    QSortFilterProxyModel *p_proxy_model;

    QPushButton *pb_add;
    QPushButton *pb_edit;
    QPushButton *pb_remove;

    void connectSignalsSlots();

signals:
    void sig_pb_remove_clicked(int idx);
    void sig_addStudent_okButtonClicked(int le_roll_id, std::string le_name, std::optional<float> gpa);
    void sig_studentAlreadyExists(int roll_id);

private slots:
    void slot_pb_remove_clicked();
    void slot_addStudent_okButtonClicked(QLineEdit& le_roll_id, QLineEdit& le_name, QLineEdit& le_gpa);
    void slot_studentAddedSuccesfully();
};

#endif // BUTTONSWIDGET_H
