#include "mainwindow.h"
#include "spreadsheetdelegate.h"
#include "spreadsheetitem.h"
#include <QApplication>
#include <QLayout>
#include <QMessageBox>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(int rows, int cols, QWidget *parent)
    : QMainWindow(parent)
{
    tableWidget = new QTableWidget(rows, cols, this);

    tableWidget->setSizeAdjustPolicy(QTableWidget::AdjustToContents);

    for (int c=0; c<cols; ++c){
        QString character(QChar('A' + c));
        tableWidget->setHorizontalHeaderItem(c, new QTableWidgetItem(character));
    }
    tableWidget->setItemDelegate(new SpreadSheetDelegate());
    tableWidget->setItemPrototype(tableWidget->item(rows-1, cols-1));

    setCentralWidget(tableWidget);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    setupContents();

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void decode_pos(const QString &pos, int *row, int *col)
{
    if(pos.isEmpty()){
        *col = -1;
        *row = -1;
    } else {
        *col = pos.at(0).toLatin1() - 'A';
        *row = pos.right(pos.size() - 1).toInt() - 1;
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    //File Menu Action
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a new spreadsheet file"));

    saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save spreadsheet file"));

    saveAsAction = new QAction(tr("Save &As..."), this);
    separatorAction = new QAction(this);
    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);

    //Edit Menu Action
    cutAction = new QAction(QIcon(":/images/cut.png"), tr("Cut"), this);
    cutAction->setShortcut(QKeySequence::Cut);

    copyAction = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);

    pasteAction = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);

    selectAction = new QAction(tr("&Select"), this);
    subMenu = new QMenu(this);
    rowAction = new QAction(tr("Row"), subMenu);
    columnAction = new QAction(tr("&Column"), subMenu);
    allAction = new QAction(tr("&All"), subMenu);
    allAction->setShortcut(QKeySequence::SelectAll);
    subMenu->addAction(rowAction);
    subMenu->addAction(columnAction);
    subMenu->addAction(allAction);
    selectAction->setMenu(subMenu);

    findAction = new QAction(tr("&Find"), this);
    findAction->setShortcut(QKeySequence::Find);

    goToCellAction = new QAction(tr("&Go to Cell"), this);
    goToCellAction->setShortcut(QKeySequence::FindNext);

    aboutAction = new QAction(tr("&About"), this);

    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    //FileMenu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    //EditMenu
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);
    editMenu->addAction(selectAction);
    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);
    //HelpMenu
    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
    aboutMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    //editToolBar->addSeparator();
    //editToolBar->addAction(findAction);
    //editToolBar->addAction(goToCellAction);
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel(tr("W999"));
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

}

void MainWindow::setupContents()
{
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = tableWidget->font();
    titleFont.setBold(true);

    tableWidget->setItem(0, 0, new SpreadSheetItem("Item"));
    tableWidget->item(0, 0)->setBackgroundColor(titleBackground);
    tableWidget->item(0, 0)->setFont(titleFont);

    tableWidget->setItem(1, 0, new SpreadSheetItem("AirportBut"));
}

bool MainWindow::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, tr("SpreadSheet"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);

    out<<quint32(MagicNumber);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    int RowCount = tableWidget->rowCount();
    int ColumnCount = tableWidget->columnCount();

    for (int row=0; row < RowCount; ++row){
        for (int column=0; column<ColumnCount; ++ column){
            QString str = forMula(row, column);
            if(!str.isEmpty())
                out << quint16(row) << quint16(column) << str;
        }
    }
    QApplication::restoreOverrideCursor();
    return true;
}

QString MainWindow::forMula(int row, int col)
{
    QTableWidgetItem *item = new QTableWidgetItem;
    item = tableWidget->item(row, col);
    return item->text();
}

bool MainWindow::okToContinue()
{
    if(isWindowModified()){
        int r = QMessageBox::warning(this, tr("Spreadsheet"),
                                    tr("The document has been modified.\n"
                                       "Do you want to save your changes?"),
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(r == QMessageBox::Yes){
            return save();
        } else if(r == QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if(!curFile.isEmpty()){
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName)
                   .arg(tr("Spreadsheet")));
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);

    while(i.hasNext()){
        if(!QFile::exists(i.next()))
            i.remove();
    }

    for(int j=0; j<MaxRecentFile; j++){
        if(j<recentFiles.count()){
            QString text = tr("&%1 %2").arg(j + 1)
                                       .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recnetFile[j]);
            recentFileActions[j]->setVisible(true);
        } else {
            recentFileActions[j]->setVisible(false);
        }
    }

    separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::newFile()
{
    if(okToContinue()){
        tableWidget->clear();
        setCurrentFile("");
    }
}

void MainWindow::openRecentFile()
{
    if(okToContinue()){
        QAction *action = qboject_cast<QAction *>(sender());
        if(action){
            loadFile(action->data().toString());
        }
    }
}
