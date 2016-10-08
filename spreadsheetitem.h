#ifndef SPREADSHEETITEM_H
#define SPREADSHEETITEM_H

#include <QTableWidgetItem>
#include "mainwindow.h"

class SpreadSheetItem : public QTableWidgetItem
{
public:
    SpreadSheetItem();
    SpreadSheetItem(const QString &text);

    QTableWidgetItem *clone() const Q_DECL_OVERRIDE;

    QVariant data(int role) const Q_DECL_OVERRIDE;
    void setData(int role, const QVariant &value) Q_DECL_OVERRIDE;
    QVariant display() const;

    inline QString formula() const
    {
        return QTableWidgetItem::data(Qt::DisplayRole).toString();
    }

    static QVariant computeFormula(const QString &formula,
                                   const QTableWidget *widget,
                                   const QTableWidgetItem *self = 0);

private:
    mutable bool isResolving;
};

#endif // SPREADSHEETITEM_H
