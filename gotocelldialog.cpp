#include "gotocelldialog.h"
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExp>

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel(tr("&Cell Location:"), this);
    lineEdit = new QLineEdit(this);

    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    lineEdit->setValidator(new QRegExpValidator(regExp, this));

    label->setBuddy(lineEdit);

    okButton = new QPushButton(tr("OK"), this);
    okButton->setDefault(false);
    okButton->setEnabled(false);
    cancelButton = new QPushButton(tr("Cancel"), this);

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableokButton()));
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(label);
    topLayout->addWidget(lineEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttonLayout);

    setWindowTitle(tr("Go to Cell"));
    setLayout(mainLayout);
    setFixedHeight(sizeHint().height());
}

void GoToCellDialog::enableokButton()
{
    okButton->setEnabled(lineEdit->hasAcceptableInput());
}

GoToCellDialog::~GoToCellDialog()
{

}
