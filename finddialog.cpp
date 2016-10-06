#include "finddialog.h"
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>

FindDialog::FindDialog(QWidget *parent)
    : QWidget(parent)
{
    lable = new QLabel(tr("Find &what:"), this);
    lineEdit = new QLineEdit(this);
    lable->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findPushButton = new QPushButton(tr("&Find"), this);
    findPushButton->setDefault(true);
    findPushButton->setEnabled(false);

    closePushButton = new QPushButton(tr("Close"), this);
    connect(lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableFindButton(QString)));
    connect(findPushButton, SIGNAL(clicked(bool)),
            this, SLOT(findClicked()));
    connect(closePushButton, SIGNAL(clicked(bool)),
            this, SLOT(close()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(lable);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findPushButton);
    rightLayout->addWidget(closePushButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);

    setFixedHeight(sizeHint().height());
}

FindDialog::~FindDialog()
{

}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs =
            caseCheckBox->isChecked() ? Qt::CaseSensitive
                                      : Qt::CaseInsensitive;
    if(backwardCheckBox->isChecked()){
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void FindDialog::enableFindButton(const QString &text)
{
    findPushButton->setEnabled(!text.isEmpty());
}
