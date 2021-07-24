#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

    ~Dialog();

   void setLabelText(QString words,QString letters,QString chars);

private slots:
   void on_pbPrint_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
