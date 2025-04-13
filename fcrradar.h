#ifndef FCRRADAR_H
#define FCRRADAR_H
#include <QTableWidget>
#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QTime>
#include <QFile>
#include <QMessageBox>

#include "structures.h"

#include <QWidget>



namespace Ui {
class fcrRadar;
}

class fcrRadar : public QWidget
{
    Q_OBJECT

public:
    explicit fcrRadar(QWidget *parent = nullptr);
    ~fcrRadar();

    void fnDecodeStsRep();
    QString fnFreqBand(unsigned int val);
    QString fnrdrState(unsigned int val);
    QString fnrdrMode(unsigned int val);
    QString fnrdrTgtTypeMode(unsigned int val);
    QString fnrdrTx(unsigned int val);
    QString fnElevatnCov(unsigned int val);
    QTableWidget  *tblLog;
    void fnDecodeTWSTargetType();
    void fnDecodeMflRep();
    QString fnLRUId(unsigned int val, unsigned int id);
    QString fnMFLSev(unsigned int val);
    QString fnTWSTarRep(unsigned int val);
    QString fnSTTTarSt(unsigned int val);
    void fnDecodeJamRep();
    QString fnJamType(unsigned int val);
    QString fnFreqSts(unsigned int val);
    void fnDecodeMaintRep();
    bool  bStartSim;
    void fnLogMaintenance(Maintenance *Str, int Source);
    void fnLogStatus(Status *Str, int Source);
    void fnLogSTTTargetReport(STTTargetReport *Str, int Source);
    void fnLogTWSTargetReportt(TWSTargetReport *Str, int Source);
    void fnLogMFLReport(MFLReports *Str, int Source);
    void fnLogECCMReport(ECCMReport *Str, int Source);
    void fnLogAntPos(AntPos *Str, int Source);
    void fnLogStateOfOperationCmd(StateOfOperationCmd *Str,int Source);
    void fnLogINSData(INSData *Str, int Source);
    void fnDecodeSTTTarRep();
    void fnLogIntDesig(IntDesig *Str, int Source);
    void fnLogResetRdr(ResetRdr *Str, int Source);
    void fnLogExtDesig(ExtDesig *Str,int Source);
    QString fnSTTTarType(unsigned int val);
    QString fnSTTTarQual(unsigned int val);









public slots:
    // void fnReadUDPRpMessage();
  //   void fnTimerTimeOut();



    //void initialize_fcrUI();

private slots:

    void on_pbStatusReportSend_clicked();
    void on_pBClearStsReport_clicked();
    void on_pbSTTtarRepSend_clicked();

    void UpdateLogTbl();
   // void on_pbSendInternalDesignation_clicked();
   // void on_pbSendRstCmd_clicked();
   // void on_pbSendMisalignmentMess_clicked();
    void fnLogPedMisAlgn(PedMisAlgn *Str, int Source);
   // void on_pbSendExternalDesignation_clicked();
   // void on_pbClearTWSTgtRep_clicked();
    //void on_pbClearMFLRep_clicked();
   // void on_pbClearJamReport_clicked();
    //void on_pbClearMaintenance_clicked();


    void on_pbTWStarRepSend_clicked();

    void on_pbMFLjamRepSend_clicked();

    void on_pbJammRepSend_clicked();

private:
    Ui::fcrRadar *ui;
};

#endif // FCRRADAR_H
