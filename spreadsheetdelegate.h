#ifndef SPREADSHEETDELEGATE_H
#define SPREADSHEETDELEGATE_H
#include <QItemDelegate>

#include "mainwindow.h"

class SpreadSheetDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    SpreadSheetDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

private slots:
    void commitAndCloseEditor();
};

#endif // SPREADSHEETDELEGATE_H
