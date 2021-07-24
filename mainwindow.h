#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString currentFile;
    QString file_name;
    QString file_name_p;
    QFile path_n;
    int index_n;
    int index_p;
    bool isCreated = false;
    QString words_n = 0;
    QString letters_n = 0;
    QString chars_n = 0;


private slots:

    void on_SaveFile_triggered();

    void on_SaveAs_triggered();

    void on_OpenFile_triggered();

    void on_SaveAsPDF_triggered();

    void on_CloseFile_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionInformation_triggered();

    QString characterCounter();
    QString letterCounter();
    QString wordCounter();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionAddTab_triggered();

    void on_actionRefresh_triggered();

    void on_actionStatistics_triggered();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    QString time = QDateTime::currentDateTime().toString("hh : mm : ss");
};
#endif // MAINWINDOW_H
