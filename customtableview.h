#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>
#include <QMouseEvent>
#include <QModelIndex>
#include <QStandardItem>

class CustomTableView: public QTableView
{
    Q_OBJECT
public:
    CustomTableView(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void sig_table_clicked(bool isIndexValid);
};

#endif // CUSTOMTABLEVIEW_H
