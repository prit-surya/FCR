
#include "configure.h"
#include <QApplication>
#include "structures.h"
QUdpSocket udpSockRp;
QUdpSocket udpSockAnt;
QString Ip;
StateOfOperationCmd  stateOfOperation;
PedMisAlgn           misAlign;
IntDesig             intDesignation;
ExtDesig             extDesignation;
AntPos               antPos;
INSData              InsData;
ResetRdr             rstRdr;
unsigned short      PortRp;
unsigned short      PortAnt;
Status               stsRep;
STTTargetReport      stSTTTarRep;
TWSTargetReport      stTWSTarRep;
MFLReports           stMflRep;
ECCMReport           stEccmRep;
Maintenance          stMaint;
QString Path;
Configure            *w;
MainWindow           *m;
char  bFaultHalfPacket;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    w = new Configure;
    m = new MainWindow();

    w->setWindowTitle("FCR Configuration");
    //SDS
     m->setWindowTitle("FCR Controller Simulator");
    //MainWindow w;
  //  w->setWindowFlag(Qt::FramelessWindowHint);
  //  m->setWindowFlag(Qt::FramelessWindowHint);
    w->show();



    return a.exec();
}
