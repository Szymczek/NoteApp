#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QtWidgets>
#include <QTextDocument>
#include <string>
#include <cstring>
#include <cctype>
#include <QPixmap>
#include <QDateTime>
#include <dialog.h>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SaveFile->setIcon(QIcon(":/icons/img/icons8-save-64.png"));
    ui->SaveAs->setIcon(QIcon(":/icons/img/icons8-save-all-64.png"));
    ui->OpenFile->setIcon(QIcon(":/icons/img/open.png"));
    ui->SaveAsPDF->setIcon(QIcon(":/icons/img/pdf.png"));
    ui->CloseFile->setIcon(QIcon(":/icons/img/cancel.png"));
    ui->actionCopy->setIcon(QIcon(":/icons/img/copy.png"));
    ui->actionCut->setIcon(QIcon(":/icons/img/icons8-cut-48.png"));
    ui->actionPaste->setIcon(QIcon(":/icons/img/paste.png"));
    ui->actionUndo->setIcon(QIcon(":/icons/img/undo-arrow.png"));
    ui->actionRedo->setIcon(QIcon(":/icons/img/iconfinder_352438_redo_icon_512px.png"));
    ui->actionInformation->setIcon(QIcon(":/icons/img/icons8-info-26.png"));
    ui->actionAddTab->setIcon(QIcon(":/icons/img/addTab.png"));
    ui->actionRefresh->setIcon(QIcon(":/icons/img/refresh.png"));
    ui->actionStatistics->setIcon(QIcon(":/icons/img/stat.png"));
    setWindowTitle("Notepad");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SaveFile_triggered()
{
    if(isCreated == false)
        return;

    if(index_n != index_p || currentFile.isEmpty()){
        QString fileName = QFileDialog::getSaveFileName(this, "Save File");
        file_name = fileName;
        index_p = index_n;

    }
    currentFile = file_name;
    index_p = index_n;
    QFile file(file_name);
    QFileInfo name(file_name);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text)){
    QMessageBox::information(this, tr("Unable to open file"),
    file.errorString());
    return;
    }

    QTextStream out(&file);
    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    QString text = pTextEdit->toPlainText();
    ui->tabWidget->setTabText(index_n, name.baseName());

    out << text;
    file.close();
}

void MainWindow::on_SaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File");
    QFile file(fileName);


    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text)){
    QMessageBox::information(this, tr("Unable to open file"),
    file.errorString());
    return;
    }

    QFileInfo name(fileName);

    QTextStream out(&file);
    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    QString text = pTextEdit->toPlainText();
    ui->tabWidget->setTabText(index_n, name.baseName());
    out << text;
    file.close();
}

void MainWindow::on_OpenFile_triggered()
{
    if(isCreated == false)
        return;
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();

    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    pTextEdit->setPlainText(text);
    ui->statusbar->showMessage(fileName);
    ui->tabWidget->setTabText(index_n, fileName);
    file.close();
}

void MainWindow::on_SaveAsPDF_triggered()
{
    if(isCreated == false)
        return;
    //File
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) {
    fileName.append(".pdf");
    }

    //Text
    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    QString text = pTextEdit->toPlainText();
    //QString message = QString("%1").arg(text);

    //Printer
    QPrinter printer_text;
             printer_text.setOutputFormat(QPrinter::PdfFormat);//Set the output format to PDF
             printer_text.setOutputFileName(fileName);//Set save location
             QPrinter printer(QPrinter::PrinterResolution);
             QPdfWriter pdfWriter(fileName);

    //Painter
    QPainter painter;
    painter.begin(&printer_text);//Use printer_text as the current drawing device
    QPoint startPoint = QPoint(20,20);
    int y = startPoint.y();
    startPoint.setY(y+20);
    painter.drawText(startPoint,text);
    text.clear();
    painter.end();
}

void MainWindow::on_CloseFile_triggered()
{
    close();
}

void MainWindow::on_actionCopy_triggered()
{
    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    pTextEdit->copy();

}

void MainWindow::on_actionCut_triggered()
{
    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    pTextEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    pTextEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    pTextEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    QPlainTextEdit* pTextEdit = NULL;
    index_n = ui->tabWidget->currentIndex();
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    pTextEdit->redo();
}

void MainWindow::on_actionInformation_triggered()
{
}

QString MainWindow::characterCounter(){

    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    QString text = pTextEdit->toPlainText();
    int counter = 0;
    for (int i = 0; i<text.length() ; i++){
        counter++;
    }
    QString chars = QString::number(counter);
    return chars;
    //ui->statusbar->showMessage(chars);
}

QString MainWindow::letterCounter(){
    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    QString text = pTextEdit->toPlainText();
    int counter = 0;
    for (int i = 0; i<text.length() ; i++){
        if (text[i] != ' ')
        counter++;
    }
    QString letters = QString::number(counter);
    return letters;
}

QString MainWindow::wordCounter(){

    QPlainTextEdit* pTextEdit = NULL;
    QWidget* pWidget= ui->tabWidget->widget(index_n);
    pTextEdit = (QPlainTextEdit*)pWidget;
    QString text = pTextEdit->toPlainText();
        //QStringList list = text.split(' ');
        std::string utf8_text = text.toUtf8().constData();
        bool inSpaces = true;
        int numWords = 0;
        int len = utf8_text.length();

        for (int i = 0; i < len ; i++){

            if (utf8_text[i] == ' ')
            {
               inSpaces = true;
            }
            else if (utf8_text[i] == '\n')
            {
                numWords++;
            }
            else if (inSpaces)
            {
               numWords++;
               inSpaces = false;
            }

        }

        QString words = QString::number(numWords);
        //QString words = QString::number(list.length());
        return words;

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionAddTab_triggered()
{
    QPlainTextEdit *pteText = new QPlainTextEdit();
    QString tabName = QString("New Tab %0").arg(ui->tabWidget->count() + 1);
    ui->tabWidget->addTab(pteText, tabName);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    isCreated = true;
}

void MainWindow::on_actionRefresh_triggered()
{
    if(isCreated){
        ui->statusbar->showMessage("Characters: " + characterCounter() + " Letters: " + letterCounter() + " Words: " + wordCounter() + " Time: " + time);
    }
}

void MainWindow::on_actionStatistics_triggered()
{
    if(ui->tabWidget->count() == 0)
        return;
    Dialog dialog;
    letters_n = letterCounter();
    words_n = wordCounter();
    chars_n = characterCounter();
    dialog.setModal(true);
    dialog.setLabelText(words_n, letters_n, chars_n);
    dialog.exec();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    index_n = index;
    qDebug() << index_n;

}

