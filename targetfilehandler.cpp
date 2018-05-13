#include "targetfilehandler.h"

TargetFileHandler::TargetFileHandler(mode mode_, QWidget *parent) : QDialog(parent)
{

    lblTargetName = new QLabel(tr("Имя цели:"));
    lblPath2Target = new QLabel(tr("Путь до цели:"));
    lblIgnored = new QLabel(tr("Игнорируемый файлы:"));
    leTargetName = new QLineEdit;
    lePath2Target = new QLineEdit;
    btnPath2Target = new QPushButton(tr("..."));
    btnEsc = new QPushButton(tr("Закрыть"));
    btnOk = new QPushButton(tr("OK"));
    btnIgnoredListClear = new QPushButton(tr("Очитить"));
    btnIgnoredListRemote = new QPushButton(tr("Удалить"));
    btnIgnoredListAdd = new QPushButton(tr("Добавить"));

    lblSourceDir = new QLabel(tr("Входные данные:"));
    leSourceDir = new QLineEdit;
    btnSourceDir = new QPushButton(tr("..."));

    lblOutputDir = new QLabel(tr("Выходные данные:"));
    leOutputDir = new QLineEdit;
    btnOutputDir = new QPushButton(tr("..."));

    lstvIgnored = new QListView;
    ignoredListModel = new QStringListModel;
    lstvIgnored->setModel(ignoredListModel);
    lstvIgnored->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QHBoxLayout *footLay = new QHBoxLayout;
    footLay->addSpacing(300);
    footLay->addWidget(btnEsc);
    footLay->addWidget(btnOk);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lblTargetName, 0, 0);
    layout->addWidget(leTargetName, 0, 1);
    layout->addWidget(lblPath2Target, 1, 0);
    layout->addWidget(lePath2Target, 1, 1);
    layout->addWidget(btnPath2Target, 1, 2);

    layout->addWidget(lblSourceDir, 2, 0);
    layout->addWidget(leSourceDir, 2, 1);
    layout->addWidget(btnSourceDir, 2, 2);

    layout->addWidget(lblOutputDir, 3, 0);
    layout->addWidget(leOutputDir, 3, 1);
    layout->addWidget(btnOutputDir, 3, 2);

    layout->addWidget(lblIgnored, 4, 0);
    layout->addWidget(lstvIgnored, 4, 1, 3, 1);
    layout->addWidget(btnIgnoredListAdd, 4, 2);
    layout->addWidget(btnIgnoredListRemote, 5, 2);
    layout->addWidget(btnIgnoredListClear, 6, 2);
    layout->addLayout(footLay, 7, 0, 1, 3);

    setLayout(layout);

    setWindowTitle(tr("Новая цель"));
    setMinimumSize(200, 200);
    resize(470, 210);

    connect(btnPath2Target, SIGNAL(clicked()), this, SLOT(btnPath2TargetOnClick()));
    connect(btnEsc, SIGNAL(clicked()), this, SLOT(close()));
    connect(btnOk, SIGNAL(clicked()), this, SLOT(btnOkOnClick()));
    connect(btnIgnoredListAdd, SIGNAL(clicked()), this, SLOT(btnIgnoredListAddOnClick()));
    connect(btnIgnoredListClear, SIGNAL(clicked()), this, SLOT(btnIgnoredListClearOnClick()));
    connect(btnIgnoredListRemote, SIGNAL(clicked()), this, SLOT(btnIgnoredListRemoteOnClick()));
    connect(btnSourceDir, SIGNAL(clicked()), this, SLOT(btnSourceDirOnClick()));
    connect(btnOutputDir, SIGNAL(clicked()), this, SLOT(btnOutputDirOnClick()));
}

void TargetFileHandler::btnPath2TargetOnClick()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Укажите путь к папке"), tr("C://"));
    lePath2Target->setText(path);
}

void TargetFileHandler::btnOkOnClick()
{
    qDebug() << "btnOkOnClick";
}

void TargetFileHandler::btnIgnoredListAddOnClick()
{    

    QString warningMsg = "";
    if ("" == lePath2Target->text())
    {
        warningMsg = tr("Путь до директории не указан.");
    }

    QDir dir = lePath2Target->text();
    if (!dir.exists())
    {
        warningMsg = tr("Указан путь до несуществующей директории.");
    }

    if ("" != warningMsg)
    {
        QMessageBox::warning(this, tr("ВАнимание"), warningMsg);
        return;
    }

    QStringList selectedFileNames = QFileDialog::getOpenFileNames(this, "Open Dialog", "", "*.cpp *.c *.hpp *.h");
    QStringList ignoredList = ignoredListModel->stringList();

    QStringList resList = ignoredList;
    foreach (QString selectedItem, selectedFileNames)
    {
        if (ignoredList.empty())
        {
            resList.append(selectedItem);
        }
        else
        {
            bool uniq = true;
            foreach (QString ignoredItem, ignoredList)
            {
                if (ignoredItem == selectedItem)
                {
                    uniq = false;
                }
            }

            if (uniq)
            {
                resList.append(selectedItem);
            }
        }
    }

    ignoredListModel->setStringList(resList);
}

void TargetFileHandler::btnIgnoredListClearOnClick()
{
    QStringList lst;
    ignoredListModel->setStringList(lst);
}

void TargetFileHandler::btnIgnoredListRemoteOnClick()
{
    QList<int> lst;
    foreach (auto item, lstvIgnored->selectionModel()->selectedIndexes()) {
        lst << item.row();
    }

    qSort(lst.begin(), lst.end(), qGreater<int>());

    QStringList strLst = ignoredListModel->stringList();
    foreach (auto index, lst) {
        strLst.removeAt(index);
    }

    ignoredListModel->setStringList(strLst);

}

void TargetFileHandler::btnSourceDirOnClick()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Укажите путь к папке"), tr("C://"));
    leSourceDir->setText(path);
}

void TargetFileHandler::btnOutputDirOnClick()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Укажите путь к папке"), tr("C://"));
    leOutputDir->setText(path);
}
