#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class CellDialog : public QDialog
{
    Q_OBJECT
private slots:
    void enableokButton();

public:
    CellDialog(QWidget *parent = 0);
    ~CellDialog();

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // DIALOG_H
