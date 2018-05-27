#include "mainwindow.h"

#include <QAbstractItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);

    model = new TreeModel;

    treeView = new QTreeView;
    treeView->setModel(model);
    treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(treeView);
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
    TargetFileHandler win(TargetFileHandler::mode::create, "", this);
    win.exec();
}

void MainWindow::clickOnActtion_OpenTarget()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.json");
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удается открыть файл."));
    }

    QByteArray lines = file.readAll();
    QJsonObject jObj = QJsonDocument::fromJson(lines).object();

    QFileInfo fi = filePath;
    model->setConfig(jObj, fi.baseName());
    treeView->reset();

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

    actOpenTarget = new QAction(tr("Открыть цель..."), this);
    connect(actOpenTarget, &QAction::triggered, this, &MainWindow::clickOnActtion_OpenTarget);

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
    fileMenu->addAction(actOpenTarget);
    fileMenu->addAction(actExit);

    helpMenu = menuBar()->addMenu(tr("Справка"));
    helpMenu->addAction(actAbout);
    helpMenu->addAction(actAboutQt);
}

