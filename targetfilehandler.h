#ifndef NEWTARGETCREATIONWINDOW_H
#define NEWTARGETCREATIONWINDOW_H

#include "appinfo.h"

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QListView>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QStringListModel>
#include <QMessageBox>
#include <QDir>
#include <QAbstractItemView>
#include <QList>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

class TargetFileHandler : public QDialog
{
    Q_OBJECT
public:

    enum class mode{
        create,
        edit
    };

    explicit TargetFileHandler(mode mode_, const QString& targetPath_ = "", QWidget *parent = nullptr);

signals:

public slots:

    void btn_on_click_target_path();
    void btn_on_click_ok();
    void btn_on_click_add_ignored_lst();
    void btn_on_click_clear_ignored_lst();
    void btn_on_click_remote_ignored_lst();
    void btn_on_click_source_dir();
    void btn_on_click_output_dir();

private:
    mode m_mode;
    QString m_targetPath;

    QLabel* mLbl_targetName;
    QLineEdit* mLe_editTargetName;

    QLabel* mLbl_targetPath;
    QLineEdit* mLe_editTargetPath;
    QPushButton* mBtn_targetPath;

    QLabel* mLbl_sourceDir;
    QLineEdit* mLe_editSourceDir;
    QPushButton* mBtn_sourceDir;

    QLabel* mLbl_outputDir;
    QLineEdit* mLe_editOutputDir;
    QPushButton* mBtn_outputDir;

    QLabel *lblIgnored;

    QPushButton* mBtn_ok;
    QPushButton* mBtn_esc;

    QPushButton* mBtn_clearIgnoredLst;
    QPushButton* mBtn_addIgnoredLst;
    QPushButton* mBtn_remoteIgnoredLst;

    QListView* mLstView_ignoredFiles;
    QStringListModel* mStrLstMdl_ignoredFiles;
};

#endif // NEWTARGETCREATIONWINDOW_H
