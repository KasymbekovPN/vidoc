#include "targetfilehandler.h"

TargetFileHandler::TargetFileHandler(mode mode_, const QString &targetPath_, QWidget *parent)
    : QDialog(parent),
      m_mode(mode_),
      m_targetPath(targetPath_)
{

    QFileInfo fi(m_targetPath);
    QFile file(targetPath_);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удается открыть файл."));
        return;
    }

    QByteArray lines = file.readAll();
    QJsonObject jObj = QJsonDocument::fromJson(lines).object();

    mLbl_targetName = new QLabel(tr("Имя цели:"));    
    mLe_editTargetName = new QLineEdit;
    if (mode::edit == mode_)
    {
        mLe_editTargetName->setText(fi.baseName());
        mLe_editTargetName->setReadOnly(true);
    }

    mLbl_targetPath = new QLabel(tr("Путь до цели:"));
    mLe_editTargetPath = new QLineEdit;
    if (mode::edit == mode_)
    {
        mLe_editTargetPath->setText(fi.absoluteDir().path());
        mLe_editTargetPath->setReadOnly(true);
    }
    mBtn_targetPath = new QPushButton(tr("..."));

    mLbl_sourceDir = new QLabel(tr("Входные данные:"));
    mLe_editSourceDir = new QLineEdit;
    if (mode::edit == mode_)
    {
        mLe_editSourceDir->setText(jObj["source-dir"].toString());
        mLe_editSourceDir->setReadOnly(true);
    }
    mBtn_sourceDir = new QPushButton(tr("..."));

    mLbl_outputDir = new QLabel(tr("Выходные данные:"));
    mLe_editOutputDir = new QLineEdit;
    if (mode::edit == mode_)
    {
        mLe_editOutputDir->setText(jObj["output-dir"].toString());
        mLe_editOutputDir->setReadOnly(true);
    }
    mBtn_outputDir = new QPushButton(tr("..."));

    lblIgnored = new QLabel(tr("Игнорируемый файлы:"));

    mBtn_esc = new QPushButton(tr("Закрыть"));
    mBtn_ok = new QPushButton(tr("OK"));

    mBtn_clearIgnoredLst = new QPushButton(tr("Очистить"));
    mBtn_addIgnoredLst = new QPushButton(tr("Добавить"));
    mBtn_remoteIgnoredLst = new QPushButton(tr("Удалить"));

    mLstView_ignoredFiles = new QListView;
    mStrLstMdl_ignoredFiles = new QStringListModel;

    QList<QVariant> ignored_lst = jObj["ignored-files"].toArray().toVariantList();
    QStringList str_lst;
    foreach (auto line, ignored_lst) {
        str_lst.append(line.toString());
    }
    mStrLstMdl_ignoredFiles->setStringList(str_lst);

    mLstView_ignoredFiles->setModel(mStrLstMdl_ignoredFiles);
    mLstView_ignoredFiles->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QHBoxLayout *footLay = new QHBoxLayout;
    footLay->addSpacing(300);
    footLay->addWidget(mBtn_esc);
    footLay->addWidget(mBtn_ok);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(mLbl_targetName, 0, 0);
    layout->addWidget(mLe_editTargetName, 0, 1);

    layout->addWidget(mLbl_targetPath, 1, 0);
    layout->addWidget(mLe_editTargetPath, 1, 1);
    layout->addWidget(mBtn_targetPath, 1, 2);

    layout->addWidget(mLbl_sourceDir, 2, 0);
    layout->addWidget(mLe_editSourceDir, 2, 1);
    layout->addWidget(mBtn_sourceDir);

    layout->addWidget(mLbl_outputDir, 3, 0);
    layout->addWidget(mLe_editOutputDir, 3, 1);
    layout->addWidget(mBtn_outputDir, 3, 2);

    layout->addWidget(lblIgnored, 4, 0);
    layout->addWidget(mLstView_ignoredFiles, 4, 1, 3, 1);
    layout->addWidget(mBtn_addIgnoredLst, 4, 2);
    layout->addWidget(mBtn_remoteIgnoredLst, 5, 2);
    layout->addWidget(mBtn_clearIgnoredLst, 6, 2);
    layout->addLayout(footLay, 7, 0, 1, 3);

    setLayout(layout);

    setWindowTitle(mode::create == mode_ ? tr("Новая цель") : tr("Редактировать..."));
    setMinimumSize(200, 200);
    resize(470, 210);

    connect(mBtn_targetPath, SIGNAL(clicked()), this, SLOT(btn_on_click_target_path()));
    connect(mBtn_esc, SIGNAL(clicked()), this, SLOT(close()));
    connect(mBtn_ok, SIGNAL(clicked()), this, SLOT(btn_on_click_ok()));
    connect(mBtn_addIgnoredLst, SIGNAL(clicked()), this, SLOT(btn_on_click_add_ignored_lst()));
    connect(mBtn_clearIgnoredLst, SIGNAL(clicked()), this, SLOT(btn_on_click_clear_ignored_lst()));
    connect(mBtn_remoteIgnoredLst, SIGNAL(clicked()), this, SLOT(btn_on_click_remote_ignored_lst()));
    connect(mBtn_sourceDir, SIGNAL(clicked()), this, SLOT(btn_on_click_source_dir()));
    connect(mBtn_outputDir, SIGNAL(clicked()), this, SLOT(btn_on_click_output_dir()));

}

void TargetFileHandler::btn_on_click_target_path()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Укажите путь к папке"), tr("C://"));
    mLe_editTargetPath->setText(path);
}

void TargetFileHandler::btn_on_click_ok()
{
    if (mLe_editTargetName->text().toStdString().empty())
    {
        QMessageBox::warning(this, tr("Внимание!"), tr("Имя цели не заданно."));
        return;
    }

    if (mLe_editTargetPath->text().toStdString().empty())
    {
        QMessageBox::warning(this, tr("Внимание!"), tr("Путь до цели не задан."));
        return;
    }

    QDir dir = mLe_editTargetPath->text();
    if (!dir.exists())
    {
        QMessageBox::warning(this, tr("Внимание!"), tr("<b>Путь до цели.</b><br>"
                                                       "Указан путь до несуществующей директории."));
        return;
    }

    if (mLe_editSourceDir->text().toStdString().empty())
    {
        QMessageBox::warning(this, tr("Внимание!"), tr("Путь до входных данных не задан."));
        return;
    }

    dir.setPath(mLe_editSourceDir->text());
    if (!dir.exists())
    {
        QMessageBox::warning(this, tr("Внимание"), tr("<b>Входные данные</b><br>"
                                                      "Указан путь до несуществующей директории."));
        return;
    }

    if (mLe_editOutputDir->text().toStdString().empty())
    {
        QMessageBox::warning(this, tr("Внимание!"), tr("Путь до выходных данных не задан."));
        return;
    }

    dir.setPath(mBtn_outputDir->text());
    if (!dir.exists())
    {
        QMessageBox::warning(this, tr("Внимание"), tr("<b>Выходные данные</b><br>"
                                                      "Указан путь до несуществующей директории."));
        return;
    }

    QJsonArray ignoredLstArray;
    QStringList ignoredLst = mStrLstMdl_ignoredFiles->stringList();
    for(int i = 0; i < ignoredLst.size(); ++i)
    {
        ignoredLstArray.insert(i, QJsonValue(ignoredLst[i]));
    }

    QJsonObject root;    
    root.insert("ignored-files", QJsonValue(ignoredLstArray));    
    root.insert("output-dir", QJsonValue(mLe_editOutputDir->text()));
    root.insert("source-dir", QJsonValue(mLe_editSourceDir->text()));

    QJsonDocument jDoc;
    jDoc.setObject(root);

    QString fileName = mLe_editTargetPath->text() + "/" + mLe_editTargetName->text() + ".json";
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jDoc.toJson());
    jsonFile.close();

    close();
}

void TargetFileHandler::btn_on_click_add_ignored_lst()
{    

    QString warningMsg = "";
    if (mLe_editTargetPath->text().toStdString().empty())
    {
        warningMsg = tr("Путь до директории не указан.");
    }

    QDir dir = mLe_editTargetPath->text();
    if (!dir.exists())
    {
        warningMsg = tr("Указан путь до несуществующей директории.");
    }

    if ("" != warningMsg)
    {
        QMessageBox::warning(this, tr("Внимание"), warningMsg);
        return;
    }

    QStringList selectedFileNames = QFileDialog::getOpenFileNames(this, "Open Dialog", mLe_editSourceDir->text(), "*.cpp *.c *.hpp *.h");
    QStringList ignoredList = mStrLstMdl_ignoredFiles->stringList();
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

    mStrLstMdl_ignoredFiles->setStringList(resList);
}

void TargetFileHandler::btn_on_click_clear_ignored_lst()
{
    QStringList lst;
    mStrLstMdl_ignoredFiles->setStringList(lst);
}

void TargetFileHandler::btn_on_click_remote_ignored_lst()
{
    QList<int> lst;
    foreach (auto item, mLstView_ignoredFiles->selectionModel()->selectedIndexes())
    {
        lst << item.row();
    }

    qSort(lst.begin(), lst.end(), qGreater<int>());

    QStringList strLst = mStrLstMdl_ignoredFiles->stringList();
    foreach (auto index, lst) {
        strLst.removeAt(index);
    }

    mStrLstMdl_ignoredFiles->setStringList(strLst);
}

void TargetFileHandler::btn_on_click_source_dir()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Укажите путь к папке"), tr("C://"));
    mLe_editSourceDir->setText(path);
}

void TargetFileHandler::btn_on_click_output_dir()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Укажите путь к папке"), tr("C://"));
    mLe_editOutputDir->setText(path);
}
