#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MagicNumber 0x7F51C883

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTabWidget>
#include <QTableWidgetItem>
#include "dialog.h"
#include "gotocelldialog.h"
#include "finddialog.h"

//QT_BEGIN_NAMESPACE
//class QTabWidget;
//class QMenu;
//class QToolBar;
//class QAction;
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void setupContents();
    bool writeFile(const QString &fileName);
    QString forMula(int row, int col);
//    void readSettings();
//    void writeSettings();
    bool okToContinue();
//    bool loadFile(const QString &fileName);
//    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
//    QString strippedName(const QString &fullFileName);

private slots:
    void newFile();
//    void open();
//    bool save();
//    bool saveAs();
//    void find();
//    void goToCell();
//    void sort();
//    void about();
    void openRecentFile();
//    void updateStatusBar();
//    void spreadsheetModified();

public:
    //MainWindow(QWidget *parent = 0);
    MainWindow(int rows, int cols, QWidget *parent = 0);
    ~MainWindow();

private:
    QTableWidget *tableWidget;
    FindDialog *findDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;
    QStringList recentFiles;
    QString curFile;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    enum { MaxRecentFile = 5 };
    QAction *recentFileActions[MaxRecentFile];
    QAction *separatorAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *aboutMenu;
    //File Action
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    //Edit Action
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectAction;
    QMenu *subMenu;
    QAction *rowAction;
    QAction *columnAction;
    QAction *allAction;
    QAction *findAction;
    QAction *goToCellAction;

    //Help Action
    QAction *aboutAction;
    QAction *aboutQtAction;
};

void decode_pos(const QString &pos, int *row, int *col);

#endif // MAINWINDOW_H
