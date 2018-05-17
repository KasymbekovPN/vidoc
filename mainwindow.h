#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "appinfo.h"
#include "targetfilehandler.h"

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <QApplication>
#include <QMenuBar>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createNewTarget();
#ifdef  TASK_0_0_2
    void clickOnActtion_OpenTarget();
#endif
    void about();

private:
    void createActions();
    void createMenus();

    QMenu* fileMenu;
    QMenu* helpMenu;

    QAction* actCreateNewTarget;
#ifdef  TASK_0_0_2
    QAction* actOpenTarget;
#endif
    QAction* actExit;
    QAction* actAbout;
    QAction* actAboutQt;
};

#endif // MAINWINDOW_H
