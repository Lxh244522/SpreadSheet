#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class SortDialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    void setColumnRange(QChar first, QChar last);

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::SortDialog *ui;
};

#endif // DIALOG_H
