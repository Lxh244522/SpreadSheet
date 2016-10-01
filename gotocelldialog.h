#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
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

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // DIALOG_H
