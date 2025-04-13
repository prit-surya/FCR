#include "configure.h"
#include "ui_configure.h"
#include "structures.h"
#include <QHostAddress>

extern MainWindow           *m;
extern Configure            *w;
Configure::Configure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Configure)
{
    ui->setupUi(this);
}

Configure::~Configure()
{
    delete ui;
}

void Configure::on_pbConfigure_clicked()
{
    int RetVal = 0;
    QString Err;

    Ip = (QString::number(ui->sbIpField1->value()) + "."+ QString::number(ui->sbIpField2->value()) + "."
                 + QString::number(ui->sbIpField3->value())+ "." + QString::number(ui->sbIpField4->value()));

    PortRp  = ui->sbPortRp->value();
    PortAnt = ui->sbPortAnt->value();
    udpSockRp.open(QIODevice::ReadWrite);
    udpSockAnt.open(QIODevice::ReadWrite);
    if(udpSockRp.bind(PortRp))
    {

    }
    else
    {
        RetVal = -1;
        Err = "Bind failed for RP\n";

    }
    if(udpSockAnt.bind(PortAnt))
    {

    }
    else
    {
        RetVal = -1;
        Err = Err + "Bind failed for Ant\n";
    }
    QFile file;
    Path = ui->leConfigFilePath->text();
   // Path = Path.replace("/","\\");
    file.setFileName(Path);
//    if(file.open(QIODevice::Append | QIODevice::Text | QIODevice::ReadWrite))
    if(file.open(QIODevice::ReadWrite))
    {
        QString str = file.readAll();
        if(str.contains("Time,Source,Type,SequenceNum,Data"))
        {

        }
        else
        {
            file.close();
            if(file.open(QIODevice::Append | QIODevice::Text))
            {
                qDebug() << str;
               file.write("Time,Source,Type,SequenceNum,Data\n");

            }
            file.close();
        }


    }
    else
    {
        RetVal = -1;
        Err = Err +"File Open Failed\n";

    }
    if(RetVal == -1)
    {
        udpSockRp.disconnect();
        udpSockAnt.disconnect();
        udpSockRp.close();
        udpSockAnt.close();
        msg.setText(Err);
        msg.show();
    }
    else
    {
            this->hide();
            m->tick.start(TIMER_TIMEOUT);
            m->tick1.start(TIMER_TIMEOUT);
            m->show();
    }

}


void Configure::on_pbBrowse_clicked()
{
    ui->leConfigFilePath->setText(QFileDialog::getSaveFileName(this,"Log File To Open",QDir::currentPath().toStdString().data(),"*.csv *.txt"));
}

void MainWindow::on_pbConnect_clicked()
{
    if(ui->pbConnect->text() == "DISCONNECT")
    {
        tick.stop();
        tick1.stop();
        udpSockRp.close();
        udpSockAnt.close();
        ui->pbConnect->setText("CONNECT");
    }
    else
    {
        ui->pbConnect->setText("DISCONNECT");
        this->hide();
        w->show();
    }
}

void Configure::on_pbClose_clicked()
{
    QApplication::quit();
}

int stateRepDetectElHigh = 0;
