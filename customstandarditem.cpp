#include "customstandarditem.h"

bool CustomStandardItem::operator<(const QStandardItem& other) const
{
    return this->text().toInt() < other.text().toInt();
}
