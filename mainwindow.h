#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include "dialog.h"
#include "gotocelldialog.h"
#include "finddialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:


};

#endif // MAINWINDOW_H
