#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

class FindDialog : public QWidget
{
    Q_OBJECT

signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
    void findClicked();
    void enableFindButton(const QString &text);

public:
    FindDialog(QWidget *parent = 0);
    ~FindDialog();

private:
    QLabel *lable;
    QLineEdit *lineEdit;
    QPushButton *findPushButton;
    QPushButton *closePushButton;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
};

#endif // WIDGET_H
