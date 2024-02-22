#include "customtableview.h"

CustomTableView::CustomTableView(QWidget *parent) : QTableView(parent)
{

}

void CustomTableView::mousePressEvent(QMouseEvent *event)
{
    QTableView::mousePressEvent(event);

    QModelIndex index = indexAt(event->pos());

    emit sig_table_clicked(index.isValid());
}

