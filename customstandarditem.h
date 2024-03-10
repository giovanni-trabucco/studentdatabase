#ifndef CUSTOMSTANDARDITEM_H
#define CUSTOMSTANDARDITEM_H

#include <QStandardItem>

template <typename T>
class CustomStandardItem : public QStandardItem
{
public:
    CustomStandardItem(T value); //template: voglio questo comportamento per tutti i possibili dati numerici
    QVariant data(int role) const override;
    bool operator<(const QStandardItem& other) const;

private:
    T m_value;
};

template <typename T>
CustomStandardItem<T>::CustomStandardItem(T value)
    : QStandardItem()
{
    m_value = value;
};

template <typename T>
QVariant CustomStandardItem<T>::data(int role) const
{
    if(role == Qt::DisplayRole)
        return QVariant(m_value);
    else
        return QStandardItem::data(role);
}

template <typename T>
bool CustomStandardItem<T>::operator<(const QStandardItem& other) const
{
    if(other.text() == "N/A")
        return true;

    else return QStandardItem::operator<(other);
}

#endif // CUSTOMSTANDARDITEM_H
