#ifndef DIALOGSELECTFILE_H
#define DIALOGSELECTFILE_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class DialogSelectFile;
}

class DialogSelectFile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSelectFile(QWidget *parent = nullptr);
    ~DialogSelectFile();

    void setType(bool bIsPic,QString sFilter);

    void setFileList(QStringList list, QString sPath="");

    QStringList fileList();

    void setPreview(bool bEnable = true);
private slots:
    void on_btnOk_clicked();

    void on_listView_pressed(const QModelIndex &index);

    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_btnUp_clicked();

    void on_btnDown_clicked();

private:
    Ui::DialogSelectFile *ui;

    QStringList m_listFile;

    bool m_bPreView = true;

    QStandardItemModel *m_model;

    bool m_bIsPic = true;

    QString m_sFilter = "*.png *jpg *jpeg";

    void refreshList();
};

#endif // DIALOGSELECTFILE_H
