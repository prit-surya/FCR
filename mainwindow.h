#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QDateTime>
#include <QTime>
#include <QFile>
#include <QMessageBox>

#include "structures.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int fnComboToNumber(QString txt);
    QTimer tick;
    QTimer tick1;
    //QTimer tick2;
    QTableWidget  *tblLog;
    bool  bStartSim;
    void fnDecodeStsRep();
    void fnDecodeSTTTarRep();
    void fnDecodeTWSTargetType();
    void fnDecodeMflRep();
    void fnDecodeJamRep();
    void fnDecodeMaintRep();
    QString fnrdrState(unsigned int val);
    QString fnrdrMode(unsigned int val);
    QString fnrdrTgtTypeMode(unsigned int val);
    QString fnrdrTx(unsigned int val);
    QString fnElevatnCov(unsigned int val);
    QString fnFreqBand(unsigned int val);
    QString fnSTTTarType(unsigned int val);
    QString fnTWSTarRep(unsigned int val);
    QString fnSTTTarSt(unsigned int val);
    QString fnSTTTarQual(unsigned int val);
    QString fnLRUId(unsigned int val, unsigned int id);
    QString fnMFLSev(unsigned int val);
    QString fnJamType(unsigned int val);
    QString fnFreqSts(unsigned int val);
    void writeToLogFile(char *buff, unsigned int size, unsigned int type);
    void fnLogStateOfOperationCmd(StateOfOperationCmd *Str,int Source);
    void fnLogIntDesig(IntDesig *Str, int Source);
   // void fnLogPedMisAlgn(PedMisAlgn *Str, int Source);
    void fnLogExtDesig(ExtDesig *Str,int Source);
    void fnLogResetRdr(ResetRdr *Str, int Source);
    void fnLogAntPos(AntPos *Str, int Source);
    void fnLogINSData(INSData *Str, int Source);
    void fnLogStatus(Status *Str, int Source);
    void fnLogSTTTargetReport(STTTargetReport *Str, int Source);
    void fnLogTWSTargetReportt(TWSTargetReport *Str, int Source);
    void fnLogMFLReport(MFLReports *Str, int Source);
    void fnLogECCMReport(ECCMReport *Str, int Source);
    void fnLogMaintenance(Maintenance *Str, int Source);
    void fnLogDETAILEDBITREP();

    Status statusReport;
    STTTargetReport sttTargRep;


private:
    Ui::MainWindow *ui;

public slots:
    // void fnReadUDPRpMessage();
    // void fnTimerTimeOut();
private slots:
     void on_pbUpdateStateOfOperatn_clicked();
     void on_pbUpdateMisalignmentMess_clicked();
     void on_pbUpdateInternalDesignation_clicked();
     void on_pbUpdateExternalDesignation_clicked();
    // void on_pbSendInternalDesignation_clicked();
    // void on_pbSendMisalignmentMess_clicked();
    // void on_pbSendExternalDesignation_clicked();
     void on_pbAntPosition_clicked();
     void on_pbINSDataUpdate_clicked();
     void on_pbUpdateRstCmd_clicked();
    // void on_pbSendRstCmd_clicked();
     //void UpdateLogTbl();
     void on_pbClearLogTable_clicked();
     void on_pbClearStateofOperation_clicked();
     void on_ClearMisalignmentMess_clicked();
     void on_pbClearInternalDesignation_clicked();
     void on_pbClearRstCmd_clicked();
     void on_pbClearExternalDesignation_clicked();
     void on_pbClearAntPosition_clicked();
     void on_pbINSDataClear_clicked();
     void on_pBClearStsReport_clicked();
     void on_pBClearSTTTgtReport_clicked();
    // void on_pbClearTWSTgtRep_clicked();
    // void on_pbClearMFLRep_clicked();
    // void on_pbClearJamReport_clicked();
    // void on_pbClearMaintenance_clicked();
     void on_pbStartSimulation_clicked();
     void on_pbConnect_clicked();
     void on_chbFaultHalfPac_toggled(bool checked);
//     void on_leStateRepRdrState_inputRejected();
//     void on_leStateRepRdrState_activated(int index);
//     void on_cbStateRepRdrState_activated(int index);



//     void on_sbSttTarRepTgtCount_valueChanged(int arg1);
//     void on_cbSttTarRepTgtSt_currentTextChanged(const QString &arg2);
//     void on_cbStateRepRdrState_currentTextChanged(const QString &arg1);
//     void on_pbStatusReportSend_clicked();
//     void on_btnclose_clicked();
//     void on_pushButton_clicked();
//     void on_pbSTTtarRepSend_clicked();
 //    void on_wTest_customContextMenuRequested(const QPoint &pos);
};


#endif // MAINWINDOW_H
