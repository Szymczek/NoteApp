#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QtWidgets>
#include <QPainter>
#include <QPrinter>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setLabelText(QString words,QString letters,QString chars)
{
ui->lbWordsOutput->setText(words);
ui->lbLettersOutput->setText(letters);
ui->lbCharsOutput->setText(chars);
}

void Dialog::on_pbPrint_clicked()
{
    //File
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) {
    fileName.append(".pdf");
    }

    //Text
    QString letters = ui->lbLettersOutput->text();
    QString chars = ui->lbCharsOutput->text();
    QString words = ui->lbWordsOutput->text();

    QString text = "Ilosc wyrazów: " + words + " " +
                    "Ilość znaków: " + chars + " " +
                    "Ilość liter: " + letters + ".";
;
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

