#ifndef CUSTOMSTANDARDITEM_H
#define CUSTOMSTANDARDITEM_H

#include <QStandardItem>

class CustomStandardItem : public QStandardItem
{
public:
    /*eredita TUTTI i costruttori di QStandardItem.
    In particolare, a me serve quello che in input prende una
    const QString& */
    using QStandardItem::QStandardItem;
    bool operator<(const QStandardItem& other) const;
};

#endif // CUSTOMSTANDARDITEM_H
