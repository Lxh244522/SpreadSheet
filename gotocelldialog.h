#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class GoToCellDialog : public QDialog
{
    Q_OBJECT
private slots:
    void enableokButton();

public:
    GoToCellDialog(QWidget *parent = 0);
    ~GoToCellDialog();

public:
    QLineEdit *lineEdit;

private:
    QLabel *label;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // CELLDIALOG_H
