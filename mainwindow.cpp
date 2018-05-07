#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);

    QWidget *filler = new QWidget(this);
    filler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(filler);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("ViDoc"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createNewTarget()
{
    qDebug() << tr("action createNew Target");
}

void MainWindow::about()
{
    QString msg = tr("Версия приложения: ") + tr(VER_APPVERSION);
    QMessageBox::about(this, tr("Справка"), msg);
}

void MainWindow::createActions()
{
    actCreateNewTarget = new QAction(tr("Новая цель..."), this);
    actCreateNewTarget->setStatusTip(tr("Создать новую цель."));
    connect(actCreateNewTarget, &QAction::triggered, this, &MainWindow::createNewTarget);

    actExit = new QAction(tr("Закрыть"), this);
    actExit->setStatusTip(tr("Закрыть приложение"));
    connect(actExit, &QAction::triggered, this, &QWidget::close);

    actAbout = new QAction(tr("Справка"), this);
    connect(actAbout, &QAction::triggered, this, &MainWindow::about);

    actAboutQt = new QAction(tr("Qt"), this);
    connect(actAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("Файл"));
    fileMenu->addAction(actCreateNewTarget);
    fileMenu->addAction(actExit);

    helpMenu = menuBar()->addMenu(tr("Справка"));
    helpMenu->addAction(actAbout);
    helpMenu->addAction(actAboutQt);
}

