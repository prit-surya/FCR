#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDialog>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
namespace Ui {
class Configure;
}

class Configure : public QDialog
{
    Q_OBJECT

public:
    explicit Configure(QWidget *parent = 0);
    ~Configure();
    QMessageBox msg;


private slots:
    void on_pbConfigure_clicked();

    void on_pbBrowse_clicked();

    void on_pbClose_clicked();

private:
    Ui::Configure *ui;
};

extern int stateRepDetectElHigh;

#endif // CONFIGURE_H
