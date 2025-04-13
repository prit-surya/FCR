#include "fcrradar.h"
#include "ui_fcrradar.h"
#include "structures.h"
#include "mainwindow.h"
char GarabageData[] = "Hello Friend this is garbage data so please uncheck the field of garbage data so that you dont get this data if you still want the same data then It is your wish. Happy testing. Live Long. Stay Happy. God Bless you. Thank you";
char RxData[20000];

Status statusReport;
STTTargetReport sttTargRep;
STTTrackData sttTrkData;


fcrRadar::fcrRadar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fcrRadar)
{
    ui->setupUi(this);

    for(int rowCnt =0;rowCnt < ui->tblTwsTarRep->rowCount();rowCnt++)
    {
        for(int colCnt = 0;colCnt < ui->tblTwsTarRep->columnCount();colCnt++)
        {
            ui->tblTwsTarRep->currentItem();
            ui->tblTwsTarRep->setItem(rowCnt,colCnt,new QTableWidgetItem("-"));
            ui->tblTwsTarRep->item(rowCnt,colCnt)->setFlags(ui->tblTwsTarRep->item(rowCnt,colCnt)->flags() &  ~Qt::ItemIsEditable);
        }
    }
    for(int rowCnt =0;rowCnt < ui->tblMFLRep->rowCount();rowCnt++)
    {
        for(int colCnt = 0;colCnt < ui->tblMFLRep->columnCount();colCnt++)
        {
            ui->tblMFLRep->setItem(rowCnt,colCnt,new QTableWidgetItem("-"));
            ui->tblMFLRep->item(rowCnt,colCnt)->setFlags(ui->tblMFLRep->item(rowCnt,colCnt)->flags() &  ~Qt::ItemIsEditable);

        }
    }
    for(int rowCnt =0;rowCnt < ui->tblJamRep->rowCount();rowCnt++)
    {
        for(int colCnt = 0;colCnt < ui->tblJamRep->columnCount();colCnt++)
        {
            ui->tblJamRep->setItem(rowCnt,colCnt,new QTableWidgetItem("-"));
            ui->tblJamRep->item(rowCnt,colCnt)->setFlags(ui->tblJamRep->item(rowCnt,colCnt)->flags() &  ~Qt::ItemIsEditable);

        }
    }

    tblLog = new QTableWidget(ui->tab_4);
    tblLog->setGeometry(10,800,1150,270);
    tblLog->setColumnCount(5);
    tblLog->setColumnWidth(4,750);
    tblLog->setHorizontalHeaderItem(0,new QTableWidgetItem("Time"));
    tblLog->setHorizontalHeaderItem(1,new QTableWidgetItem("Source"));
    tblLog->setHorizontalHeaderItem(2,new QTableWidgetItem("Type"));
    tblLog->setHorizontalHeaderItem(3,new QTableWidgetItem("SequenceNum"));
    tblLog->setHorizontalHeaderItem(4,new QTableWidgetItem("Data"));
    tblLog->show();

    //ui->setupUi(this);
    ui->cbStateRepRdrState->clear();
    ui->cbStateRepRdrState->addItem("Init");
    ui->cbStateRepRdrState->addItem("Standby");
    ui->cbStateRepRdrState->addItem("Maintenance");
    ui->cbStateRepRdrState->addItem("Operate");
    ui->cbStateRepRdrState->addItem("Reset");
    ui->cbStateRepRdrState->addItem("IBIT");
    ui->cbStateRepRdrState->addItem("Off");

    ui->cbStateRepRdrMode->clear();
    ui->cbStateRepRdrMode->addItem("AA_SECTOR");
    ui->cbStateRepRdrMode->addItem("AA_360");
    ui->cbStateRepRdrMode->addItem("AA_MANUAL");
    ui->cbStateRepRdrMode->addItem("AA_STT");
    ui->cbStateRepRdrMode->addItem("AA_ACQ");

    ui->cbStateRepTgtTypeMode->clear();
    ui->cbStateRepTgtTypeMode->addItem("Normal");
     ui->cbStateRepTgtTypeMode->addItem("Test target");
     ui->cbStateRepTgtTypeMode->addItem("Repeater");

     ui->cbStateRepTx->clear();
     ui->cbStateRepTx->addItem("OFF");
      ui->cbStateRepTx->addItem("ON");
       ui->cbStateRepTx->addItem("Disabled");

       ui->cbStateRepEleCov->clear();
       ui->cbStateRepEleCov->addItem("20 Degrees");
       ui->cbStateRepEleCov->addItem("30 Degrees");

       ui->cbStateRepTgtVelRej->clear();
       ui->cbStateRepTgtVelRej->addItem("High");
        ui->cbStateRepTgtVelRej->addItem("Low");

        ui->cbStateRepFreqBand->clear();
        ui->cbStateRepFreqBand->addItem("BAND A");
        ui->cbStateRepFreqBand->addItem("BAND B");
        ui->cbStateRepFreqBand->addItem("BAND C");
        ui->cbStateRepFreqBand->addItem("BAND D");
        ui->cbStateRepFreqBand->addItem("BAND E");
        ui->cbStateRepFreqBand->addItem("BAND F");

        ui->cbStateRepFreqChngMode->clear();
        ui->cbStateRepFreqChngMode->addItem("Manual");
        ui->cbStateRepFreqChngMode->addItem("Automatic");

        ui->cbStateRepSec0Type->clear();
        ui->cbStateRepSec0Type->addItem("Normal");
        ui->cbStateRepSec0Type->addItem("Blank");

        ui->cbStateRepSec1Type->clear();
        ui->cbStateRepSec1Type->addItem("Normal");
        ui->cbStateRepSec1Type->addItem("Blank");

        ui->sbStateRepDetectElHigh->setRange(-40,90);
        ui->sbStateRepDetectElLow->setRange(-40,90);

        ui->sbStateRepNValSec->setRange(0,2);

        ui->sbStateRepSec0StartAng->setRange(0,360);
        ui->sbStateRepSec0EndAng->setRange(0,360);

        ui->sbStateRepSec1EndAng_2->setRange(0,360);
        ui->sbStateRepSec1StartAng_2->setRange(0,360);

        ui->sbStateRepRdrPosUTMX->setRange(0,20000000);
        ui->sbStateRepRdrPosUTMY->setRange(0,20000000);
        ui->sbStateRepRdrPosUTMZ->setRange(-500,10000);

        ui->sbSttTarRepTgtCount->setRange(0,1);
        ui->dsbSttTarRepDeltaEl->setRange(-40,90);
        ui->dsbSttTarRepDeltaAz->setRange(-180,180);
        ui->dsbttTarRepSigDeltaEl->setRange(-40,90);
        ui->dsbSttTarRepSigDeltaAz->setRange(-180,180);
        ui->dsbSttTarRepRng->setRange(0,0);
        ui->dsbSttTarRepRngDot->setRange(0,0);
        ui->sbSttTarRepTimeTag->setRange(0,24);

        ui->cbSttTarRepTgtType->addItem("AIR NORMAL");
        ui->cbSttTarRepTgtType->addItem("HH");
        ui->cbSttTarRepTgtType->addItem("OTHER");
        ui->cbSttTarRepTgtType->addItem("TOJ");

        ui->cbSttTarRepTgtSt->addItem("TRK_INIT");
        ui->cbSttTarRepTgtSt->addItem("TRK_UPDATE");
        ui->cbSttTarRepTgtSt->addItem("TRK_DELETE");
        ui->cbSttTarRepTgtSt->addItem("TRK_EXTRAP");

        ui->cbSttTarRepTgtQual->addItem("TRACK_TGT");
        ui->cbSttTarRepTgtQual->addItem("Side Lobe Jammer");
        ui->cbSttTarRepTgtQual->addItem("Main Lobe Jammer");

        ui->sbSttTarRepINTID->setRange(1,240);
        ui->sbSttTarRepEXTID->setRange(1,1000);
        ui->dsbSttTarRepX->setRange(-40000,40000);
        ui->dsbSttTarRepY->setRange(-40000,40000);
        ui->dsbSttTarRepZ->setRange(-5000,20000);
        ui->sbSttTarRepUTMX->setRange(0,20000000);
        ui->sbSttTarRepUTMY->setRange(0,20000000);
        ui->sbSttTarRepUTMZ->setRange(-1000,100000);
        ui->sbSttTarRepUTMZone->setRange(0,60);
        ui->dbSbSttTarRepAlt->setRange(-500,20000);
        ui->dbSbSttTarRepSigAlt->setRange(-1000,10000);
        ui->dsbSttTarRepVx->setRange(-6000,6000);
        ui->dsbSttTarRepVy->setRange(-6000,6000);
        ui->dsbSttTarRepVz->setRange(-6000,6000);
        ui->sbSttTarRepTgtExtrapTime->setRange(0,24);
        ui->sbSttTarRepTgtUpdateTime->setRange(0,24);
        ui->dsbSttTarRepRngTTD->setRange(0,40000);
        ui->dsbSttTarRepSigRngTTD->setRange(0,40000);
        ui->dsbSttTarRepAz->setRange(-180,180);
        ui->dsbSttTarRepSigAz->setRange(-180,180);
        ui->dsbSttTarRepEl->setRange(-40,90);
        ui->dsbSttTarRepSigEl->setRange(-40,90);
        ui->dsbSttTarRepSigEl->setRange(-1200,1200);
        ui->dsbSttTarRepSigVel->setRange(-1200,1200);
        ui->dsbSttTarRepVLOS->setRange(-1200,1200);
        ui->dsbSttTarRepSigVLOS->setRange(-1200,1200);
        ui->dsbSttTarRepVxLOS_2->setRange(-1200,1200);
        ui->dsbSttTarRepSigVxLOS->setRange(-1200,1200);
        ui->dsbSttTarRepSNR->setRange(0,100);
        ui->dsbSttTarRepAvRCS->setRange(0,150);
        ui->dsbSttTarRepTarAzExtrap->setRange(-180,180);
        ui->dsbSttTarRepSigTarAzExtrap->setRange(-180,180);
        ui->dsbSttTarRepTarElExtrap->setRange(-40,90);
        ui->dsbSttTarRepSigTarElExtrap->setRange(-40,90);




}

fcrRadar::~fcrRadar()
{
    delete ui;
}

QString fcrRadar::fnFreqBand(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case BAND_A: RetVal = "BAND_A";
        break;
    case BAND_B: RetVal = "BAND_B";
        break;
    case BAND_C: RetVal = "BAND_C";
        break;
    case BAND_D: RetVal = "BAND_D";
        break;
    case BAND_E: RetVal = "BAND_E";
        break;
    case BAND_F: RetVal = "BAND_F";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}
void fcrRadar::fnDecodeStsRep()
{

    //else in .ui file

    ui->cbStateRepRdrState->setCurrentIndex(stsRep.rdrState);
    ui->cbStateRepRdrMode->setCurrentIndex(stsRep.rdrMode-1);
    ui->cbStateRepTx->setCurrentIndex(stsRep.rdrTx-1);
     ui->cbStateRepTgtTypeMode->setCurrentIndex(stsRep.targetTypeMode);
     ui->cbStateRepEleCov->setCurrentIndex(stsRep.elvCov-1);
     ui->cbStateRepTgtVelRej->setCurrentIndex(stsRep.rdrTVel-1);

  //  ui->linEditStateRepPrefix->setText(QString::number(stsRep.messHeadRp.messPref));
 //   ui->lineEditStateRepSource->setText(QString::number(stsRep.messHeadRp.messSource));
 //   ui->lineEditStateRepId->setText(QString::number(stsRep.messHeadRp.messType));
 //   ui->lineEditStateRepBodyLen->setText(QString::number(stsRep.messHeadRp.bodyLen));
 //   ui->lineEditStateRepSeqNum->setText(QString::number(stsRep.messHeadRp.messSeqNum));
    if(stsRep.rdrTVel == 1)
    {
        ui->cbStateRepTgtVelRej->setEditText("LOW");
    }
    else if(stsRep.rdrTVel == 0)
    {
        ui->cbStateRepTgtVelRej->setEditText("HIGH");
    }
    else
    {
        ui->cbStateRepTgtVelRej->setEditText("INVALID");
    }

    ui->cbStateRepFreqBand->setEditText(fnFreqBand(stsRep.rdrFreqBand));

    if(stsRep.rdrFreqBandChange == 0)
    {
        ui->cbStateRepFreqChngMode->setEditText("MANUAL");
    }
    else if(stsRep.rdrFreqBandChange == 1)
    {
        ui->cbStateRepFreqChngMode->setEditText("AUTOMATIC");
    }
    else
    {
        ui->cbStateRepFreqChngMode->setEditText("INVALID");
    }

    ui->sbStateRepSec0StartAng->setValue(stsRep.dElvLow);
    ui->sbStateRepDetectElHigh->setValue(stsRep.dElvHigh);

    ui->sbStateRepNValSec->setValue(stsRep.noOfValidSectors);
    ui->sbStateRepSec0StartAng->setValue(stsRep.sectors[0].startAng);
    ui->sbStateRepSec0EndAng->setValue(stsRep.sectors[0].endAng);

    //SDS
    if(((stsRep.sectors[0].rdrSectorType) == 0) || ((stsRep.sectors[0].rdrSectorType) == 1))
    {
        ui->cbStateRepSec0Type->setCurrentIndex(stsRep.sectors[0].rdrSectorType);
    }
    if(((stsRep.sectors[0].rdrSectorType) == 0) || ((stsRep.sectors[0].rdrSectorType) == 1))
    {
        ui->cbStateRepSec1Type->setCurrentIndex(stsRep.sectors[0].rdrSectorType);
    }

    ui->sbStateRepSec0StartAng->setValue(stsRep.sectors[1].startAng);
    ui->sbStateRepSec0EndAng->setValue(stsRep.sectors[1].endAng);
    if((stsRep.sectors[1].rdrSectorType) == 0 || (stsRep.sectors[1].rdrSectorType) == 1)
    {
        ui->cbStateRepSec1Type->setCurrentIndex(stsRep.sectors[1].rdrSectorType);
    }

    ui->sbStateRepRdrPosUTMX->setValue(stsRep.utmXRadar);
    ui->sbStateRepRdrPosUTMY->setValue(stsRep.utmYRadar);
    ui->sbStateRepRdrPosUTMZ->setValue(stsRep.utmZRadar);

}

void fcrRadar::on_pBClearStsReport_clicked()
{
#if 1
 //   ui->linEditStateRepPrefix->setText(0);
 //   ui->lineEditStateRepSource->setText(0);
 //   ui->lineEditStateRepId->setText(0);
 //   ui->lineEditStateRepBodyLen->setText(0);
 //   ui->lineEditStateRepSeqNum->setText(0);
    ui->cbStateRepRdrState->setEditText(0);
    ui->cbStateRepRdrMode->setEditText(0);
    ui->cbStateRepTgtTypeMode->setEditText(0);
    ui->cbStateRepTx->setEditText(0);
    ui->cbStateRepEleCov->setEditText(0);
    ui->cbStateRepTgtVelRej->setEditText("");
    ui->cbStateRepFreqBand->setEditText("");
    ui->cbStateRepFreqChngMode->setEditText("");
    ui->sbStateRepSec0StartAng->setValue(0);
    ui->sbStateRepDetectElHigh->setValue(0);

    ui->sbStateRepNValSec->setValue(0);
    ui->sbStateRepSec0StartAng->setValue(0);
    ui->sbStateRepSec0EndAng->setValue(0);
    ui->cbStateRepSec0Type->setEditText(0);

    ui->sbStateRepSec1StartAng_2->setValue(0);
    ui->sbStateRepSec1EndAng_2->setValue(0);
    ui->cbStateRepSec1Type->setEditText(0);

    ui->sbStateRepRdrPosUTMX->setValue(0);
    ui->sbStateRepRdrPosUTMY->setValue(0);
    ui->sbStateRepRdrPosUTMZ->setValue(0);

    // This will clear the structure too
    memset(&stsRep,0,sizeof(stsRep));
#endif
}

void fcrRadar::on_pbStatusReportSend_clicked()
{
    if(ui->cbStateRepRdrState->currentText()=="Init")
    {
        statusReport.rdrState=1;
    }
    else if(ui->cbStateRepRdrState->currentText()=="Standby")
    {
        statusReport.rdrState=2;
    }
    else if(ui->cbStateRepRdrState->currentText()=="Maintenance")
    {
        statusReport.rdrState=3;
    }
    else if(ui->cbStateRepRdrState->currentText()=="Operate")
    {
        statusReport.rdrState=4;
    }
    else if(ui->cbStateRepRdrState->currentText()=="Reset")
    {
        statusReport.rdrState=5;
    }
    else if(ui->cbStateRepRdrState->currentText()=="IBIT")
    {
        statusReport.rdrState=8;
    }
    else if(ui->cbStateRepRdrState->currentText()=="Off")
    {
        statusReport.rdrState=9;
    }


    if(ui->cbStateRepRdrMode->currentText()=="AA_SECTOR")
    {
        statusReport.rdrMode=1;
    }
    else if(ui->cbStateRepRdrMode->currentText()=="AA_360")
    {
        statusReport.rdrMode=2;
    }
    else if(ui->cbStateRepRdrMode->currentText()=="AA_MANUAL")
    {
        statusReport.rdrMode=3;
    }
    else if(ui->cbStateRepRdrMode->currentText()=="AA_STT")
    {
        statusReport.rdrMode=4;
    }
    else if(ui->cbStateRepRdrMode->currentText()=="AA_ACQ")
    {
        statusReport.rdrMode=6;
    }

    if(ui->cbStateRepTgtTypeMode->currentText()=="Normal")
    {
        statusReport.targetTypeMode=0;
    }
    else if(ui->cbStateRepTgtTypeMode->currentText()=="Test Target")
    {
        statusReport.targetTypeMode=1;
    }
    else if(ui->cbStateRepTgtTypeMode->currentText()=="Repeater")
    {
        statusReport.targetTypeMode=2;
    }

    if(ui->cbStateRepTx->currentText()=="OFF")
    {
        statusReport.rdrTx=0;
    }
    else if(ui->cbStateRepTx->currentText()=="ON")
    {
        statusReport.rdrTx=1;
    }
    else if(ui->cbStateRepTx->currentText()=="Disabled")
    {
        statusReport.rdrTx=2;
    }

    if(ui->cbStateRepEleCov->currentText()=="20 degrees")
    {
        statusReport.elvCov=5;
    }
    else if(ui->cbStateRepEleCov->currentText()=="30 degrees")
    {
        statusReport.elvCov=6;
    }

    if(ui->cbStateRepTgtVelRej->currentText()=="High")
    {
        statusReport.rdrTVel=0;
    }
    else if(ui->cbStateRepTgtVelRej->currentText()=="Low")
    {
        statusReport.rdrTVel=1;
    }

    if(ui->cbStateRepFreqBand->currentText()=="BAND A")
    {
        statusReport.rdrFreqBand=0;
    }
    else if(ui->cbStateRepFreqBand->currentText()=="BAND B")
    {
        statusReport.rdrFreqBand=1;
    }
    else if(ui->cbStateRepFreqBand->currentText()=="BAND C")
    {
        statusReport.rdrFreqBand=2;
    }
    else if(ui->cbStateRepFreqBand->currentText()=="BAND D")
    {
        statusReport.rdrFreqBand=3;
    }
    else if(ui->cbStateRepFreqBand->currentText()=="BAND E")
    {
        statusReport.rdrFreqBand=4;
    }
    else if(ui->cbStateRepFreqBand->currentText()=="BAND F")
    {
        statusReport.rdrFreqBand=5;
    }

    if(ui->cbStateRepFreqChngMode->currentText()=="Manual")
    {
        statusReport.rdrFreqBandChange=0;
    }
    else if(ui->cbStateRepFreqChngMode->currentText()=="Automatic")
    {
        statusReport.rdrFreqBandChange=1;
    }

    statusReport.dElvLow = ui->sbStateRepDetectElLow->value();
    statusReport.dElvHigh = ui->sbStateRepDetectElHigh->value();
    statusReport.noOfValidSectors = ui->sbStateRepNValSec->value();

    statusReport.sectors[0].startAng = ui->sbStateRepSec0StartAng->value();
    statusReport.sectors[0].endAng = ui->sbStateRepSec0EndAng->value();
    statusReport.sectors[0].rdrSectorType = ui->cbStateRepSec0Type->currentIndex();

    statusReport.sectors[1].startAng = ui->sbStateRepSec1StartAng_2->value();
    statusReport.sectors[1].endAng = ui->sbStateRepSec1EndAng_2->value();
    statusReport.sectors[1].rdrSectorType = ui->cbStateRepSec1Type->currentIndex();

    statusReport.utmXRadar = ui->sbStateRepRdrPosUTMX->value();
    statusReport.utmYRadar = ui->sbStateRepRdrPosUTMY->value();
    statusReport.utmZRadar = ui->sbStateRepRdrPosUTMZ->value();

//     qDebug()<<"Selection RdrState is-----"<<statusReport.rdrState;
//    qDebug()<<"Selection RdrMode is-----"<<statusReport.rdrMode;
//     qDebug()<<"Selection targetTypeMode is-----"<<statusReport.targetTypeMode;
//     qDebug()<<"Selection rdrTx is-----"<<statusReport.rdrTx;
//     qDebug()<<"Selection elvCov is-----"<<statusReport.elvCov;
//    qDebug()<<"Selection rdrTVel is-----"<<statusReport.rdrTVel;
//     qDebug()<<"Selection rdrFreqBand is-----"<<statusReport.rdrFreqBand;
//     qDebug()<<"Selection rdrFreqBandChange is-----"<<statusReport.rdrFreqBandChange;
//     qDebug()<<"Selection dElvLow is-----"<<statusReport.dElvLow;
//     qDebug()<<"Selection dElvHigh is-----"<<statusReport.dElvHigh;
//     qDebug()<<"Selection noOfValidSectors is-----"<<statusReport.noOfValidSectors;
//     qDebug()<<"Selection sectors[0].startAng is-----"<<statusReport.sectors[0].startAng;
//     qDebug()<<"Selection sectors[0].endAng is-----"<<statusReport.sectors[0].endAng;
//     qDebug()<<"Selection sectors[0].rdrSectorType is-----"<<statusReport.sectors[0].rdrSectorType;
//     qDebug()<<"Selection sectors[1].startAng is-----"<<statusReport.sectors[1].startAng;
//     qDebug()<<"Selection sectors[1].endAng is-----"<<statusReport.sectors[1].endAng;
//      qDebug()<<"Selection sectors[1].rdrSectorType is-----"<<statusReport.sectors[1].rdrSectorType;
//    qDebug()<<"Selection utmXRadar is-----"<<statusReport.utmXRadar;
//    qDebug()<<"Selection utmYRadar is-----"<<statusReport.utmYRadar;
//    qDebug()<<"Selection utmZRadar is-----"<<statusReport.utmZRadar;
}



void fcrRadar::on_pbSTTtarRepSend_clicked()
{
    sttTargRep.tgtCount = ui->sbSttTarRepTgtCount->value();
    sttTargRep.delEl = ui->dsbSttTarRepDeltaEl->value();
    sttTargRep.delAzm = ui->dsbSttTarRepDeltaAz->value();
    sttTargRep.sigmaDelEl = ui->dsbttTarRepSigDeltaEl->value();
    sttTargRep.sigmaDelAzm = ui->dsbSttTarRepSigDeltaAz->value();
    sttTargRep.range = ui->dsbSttTarRepRng->value();
    sttTargRep.rangeDot = ui->dsbSttTarRepRngDot->value();
    sttTargRep.timeTag = ui->sbSttTarRepTimeTag->value();
    sttTargRep.sttTrackData.targetType=ui->cbSttTarRepTgtType->currentIndex();

    if(ui->cbSttTarRepTgtSt->currentText()=="TRK_INIT")
    {
        sttTargRep.sttTrackData.targetStatus=0;
    }
    else if(ui->cbSttTarRepTgtSt->currentText()=="TRK_UPDATE")
    {
        sttTargRep.sttTrackData.targetStatus=1;
    }
    else if(ui->cbSttTarRepTgtSt->currentText()=="TRK_DELETE")
    {
         sttTargRep.sttTrackData.targetStatus=2;
    }
    else if(ui->cbSttTarRepTgtSt->currentText()=="TRK_EXTRAP")
    {
         sttTargRep.sttTrackData.targetStatus=3;
    }


    if(ui->cbSttTarRepTgtQual->currentText()=="TRACK_TGT")
    {
         sttTargRep.sttTrackData.targetQuality=1;
    }
    else if(ui->cbSttTarRepTgtQual->currentText()=="Side Lobe Jammer")
    {
         sttTargRep.sttTrackData.targetQuality=5;
    }
    else if(ui->cbSttTarRepTgtQual->currentText()=="Main Lobe Jammer")
    {
         sttTargRep.sttTrackData.targetQuality=7;
    }

     sttTargRep.sttTrackData.idInt = ui->sbSttTarRepINTID->value();
     sttTargRep.sttTrackData.idExt = ui->sbSttTarRepEXTID->value();
     sttTargRep.sttTrackData.posX = ui->dsbSttTarRepX->value();
     sttTargRep.sttTrackData.posY = ui->dsbSttTarRepY->value();
     sttTargRep.sttTrackData.posZ = ui->dsbSttTarRepZ->value();
     sttTargRep.sttTrackData.utmX = ui->sbSttTarRepUTMX->value();
     sttTargRep.sttTrackData.utmY = ui->sbSttTarRepUTMY->value();
     sttTargRep.sttTrackData.utmZ = ui->sbSttTarRepUTMZ->value();
     sttTargRep.sttTrackData.utmZone = ui->sbSttTarRepUTMZone->value();
     sttTargRep.sttTrackData.alt = ui->dbSbSttTarRepAlt->value();
     sttTargRep.sttTrackData.sigmaAlt = ui->dbSbSttTarRepSigAlt->value();
     sttTargRep.sttTrackData.velX = ui->dsbSttTarRepVx->value();
     sttTargRep.sttTrackData.velY = ui->dsbSttTarRepVy->value();
     sttTargRep.sttTrackData.velZ = ui->dsbSttTarRepVz->value();
     sttTargRep.sttTrackData.targetTime = ui->sbSttTarRepTgtExtrapTime->value();
     sttTargRep.sttTrackData.lastUpdateTime = ui->sbSttTarRepTgtUpdateTime->value();
     sttTargRep.sttTrackData.range = ui->dsbSttTarRepRngTTD->value();
     sttTargRep.sttTrackData.sigmaRange = ui->dsbSttTarRepSigRngTTD->value();
     sttTargRep.sttTrackData.azm = ui->dsbSttTarRepAz->value();
     sttTargRep.sttTrackData.sigmaAzm = ui->dsbSttTarRepSigAz->value();
     sttTargRep.sttTrackData.elv = ui->dsbSttTarRepEl->value();
     sttTargRep.sttTrackData.sigmaElv = ui->dsbSttTarRepSigEl->value();
     sttTargRep.sttTrackData.vTrue = ui->dsbSttTarRepVel->value();
     sttTargRep.sttTrackData.sigmaVel = ui->dsbSttTarRepSigVel->value();
     sttTargRep.sttTrackData.vLos = ui->dsbSttTarRepVLOS->value();
     sttTargRep.sttTrackData.sigmaVelLos = ui->dsbSttTarRepSigVLOS->value();
     sttTargRep.sttTrackData.vxLos = ui->dsbSttTarRepVxLOS_2->value();
     sttTargRep.sttTrackData.sigmaVelXLos = ui->dsbSttTarRepSigVxLOS->value();
     sttTargRep.sttTrackData.snr = ui->dsbSttTarRepSNR->value();
     sttTargRep.sttTrackData.avgRCS = ui->dsbSttTarRepAvRCS->value();
     sttTargRep.sttTrackData.extrapAz = ui->dsbSttTarRepTarAzExtrap->value();
     sttTargRep.sttTrackData.sigmaExtrapAz = ui->dsbSttTarRepSigTarAzExtrap->value();
     sttTargRep.sttTrackData.extrapEl = ui->dsbSttTarRepTarElExtrap->value();
     sttTargRep.sttTrackData.sigmaExtrapEl = ui->dsbSttTarRepSigTarElExtrap->value();


//     qDebug()<<"Selection tgtCount is-----"<<sttTargRep.tgtCount;
//     qDebug()<<"Selection delEl is-----"<<sttTargRep.delEl;
//     qDebug()<<"Selection delAzm is-----"<<sttTargRep.delAzm;
//     qDebug()<<"Selection sigmaDelEl is-----"<<sttTargRep.sigmaDelEl;
//     qDebug()<<"Selection sigmaDelAzm is-----"<<sttTargRep.sigmaDelAzm;
//      qDebug()<<"Selection range is-----"<<sttTargRep.range;
//      qDebug()<<"Selection rangeDot is-----"<<sttTargRep.rangeDot;
//      qDebug()<<"Selection timeTag is-----"<<sttTargRep.timeTag;
//       qDebug()<<"Selection targetType is-----"<<sttTrkData.targetType;
//      qDebug()<<"Selection targetStatus is-----"<<sttTrkData.targetStatus;
//     qDebug()<<"Selection targetQuality is-----"<<sttTrkData.targetQuality;
//     qDebug()<<"Selection idInt is-----"<<sttTrkData.idInt;
//     qDebug()<<"Selection idExt is-----"<<sttTrkData.idExt;
//     qDebug()<<"Selection posX is-----"<<sttTrkData.posX;
//     qDebug()<<"Selection posY is-----"<<sttTrkData.posY;
//     qDebug()<<"Selection posZ is-----"<<sttTrkData.posZ;
//     qDebug()<<"Selection utmX is-----"<<sttTrkData.utmX;
//     qDebug()<<"Selection utmY is-----"<<sttTrkData.utmY;
//     qDebug()<<"Selection utmZ is-----"<<sttTrkData.utmZ;
//     qDebug()<<"Selection utmZone is-----"<<sttTrkData.utmZone;
//     qDebug()<<"Selection alt is-----"<<sttTrkData.alt;
//     qDebug()<<"Selection sigmaAlt is-----"<<sttTrkData.sigmaAlt;
//     qDebug()<<"Selection velX is-----"<<sttTrkData.velX;
//     qDebug()<<"Selection velY is-----"<<sttTrkData.velY;
//     qDebug()<<"Selection velZ is-----"<<sttTrkData.velZ;
//     qDebug()<<"Selection targetTime is-----"<<sttTrkData.targetTime;
//     qDebug()<<"Selection lastUpdateTime is-----"<<sttTrkData.lastUpdateTime;
//     qDebug()<<"Selection range is-----"<<sttTrkData.range;
//     qDebug()<<"Selection sigmaRange is-----"<<sttTrkData.sigmaRange;
//     qDebug()<<"Selection azm is-----"<<sttTrkData.azm;
//     qDebug()<<"Selection sigmaAzm is-----"<<sttTrkData.sigmaAzm;
//     qDebug()<<"Selection elv is-----"<<sttTrkData.elv;
//     qDebug()<<"Selection sigmaElv is-----"<<sttTrkData.sigmaElv;
//     qDebug()<<"Selection vTrue is-----"<<sttTrkData.vTrue;
//     qDebug()<<"Selection sigmaVel is-----"<<sttTrkData.sigmaVel;
//     qDebug()<<"Selection vLos is-----"<<sttTrkData.vLos;
//     qDebug()<<"Selection sigmaVelLos is-----"<<sttTrkData.sigmaVelLos;
//     qDebug()<<"Selection vxLos is-----"<<sttTrkData.vxLos;
//     qDebug()<<"Selection sigmaVelXLos is-----"<<sttTrkData.sigmaVelXLos;
//     qDebug()<<"Selection snr is-----"<<sttTrkData.snr;
//     qDebug()<<"Selection avgRCS is-----"<<sttTrkData.avgRCS;
//     qDebug()<<"Selection extrapAz is-----"<<sttTrkData.extrapAz;
//     qDebug()<<"Selection sigmaExtrapAz is-----"<<sttTrkData.sigmaExtrapAz;
//     qDebug()<<"Selection extrapEl is-----"<<sttTrkData.extrapEl;
//     qDebug()<<"Selection sigmaExtrapEl is-----"<<sttTrkData.sigmaExtrapEl;


}

void fcrRadar::on_pbTWStarRepSend_clicked()
{

}


void fcrRadar::on_pbMFLjamRepSend_clicked()
{

}


void fcrRadar::on_pbJammRepSend_clicked()
{

}


void fcrRadar::fnDecodeTWSTargetType()
{

//    ui->sbTwsTarRepPrefix->setValue(stTWSTarRep.messHeadRp.messPref);
//    ui->sbTwsTarRepSource->setValue(stTWSTarRep.messHeadRp.messSource);
//    ui->sbTwsTarRepId->setValue(stTWSTarRep.messHeadRp.messType);
//    ui->sbTwsTarRepSeqNum->setValue(stTWSTarRep.messHeadRp.messSeqNum);
//    ui->sbTwsTarRepBodyLen->setValue(stTWSTarRep.messHeadRp.bodyLen);
//    ui->sbTwsTarRepNum->setValue(stTWSTarRep.noOfTgt);

    for(int rowCnt = 0;rowCnt < ui->tblTwsTarRep->rowCount();rowCnt++)
    {
        ui->tblTwsTarRep->item(rowCnt,0)->setText(fnTWSTarRep(stTWSTarRep.twsTracks[rowCnt].targetType));
        ui->tblTwsTarRep->item(rowCnt,1)->setText(fnSTTTarSt(stTWSTarRep.twsTracks[rowCnt].targetStatus));
        ui->tblTwsTarRep->item(rowCnt,2)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].idInt));
        ui->tblTwsTarRep->item(rowCnt,3)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].idExt));
        ui->tblTwsTarRep->item(rowCnt,4)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].posX,'f',2));
        ui->tblTwsTarRep->item(rowCnt,5)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].posY,'f',2));
        ui->tblTwsTarRep->item(rowCnt,6)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].posZ,'f',2));
        ui->tblTwsTarRep->item(rowCnt,7)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].utmX));
        ui->tblTwsTarRep->item(rowCnt,8)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].utmY));
        ui->tblTwsTarRep->item(rowCnt,9)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].utmZ));
        ui->tblTwsTarRep->item(rowCnt,10)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].utmZone));
        ui->tblTwsTarRep->item(rowCnt,11)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].alt,'f',2));
        ui->tblTwsTarRep->item(rowCnt,12)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].sigmaAlt,'f',2));
        ui->tblTwsTarRep->item(rowCnt,13)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].velX,'f',2));
        ui->tblTwsTarRep->item(rowCnt,14)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].velY,'f',2));
        ui->tblTwsTarRep->item(rowCnt,15)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].velZ,'f',2));
        ui->tblTwsTarRep->item(rowCnt,16)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].targetTime));
        ui->tblTwsTarRep->item(rowCnt,17)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].lastUpdateTime));
        ui->tblTwsTarRep->item(rowCnt,18)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].range,'f',2));
        ui->tblTwsTarRep->item(rowCnt,19)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].sigmaRange,'f',2));
        ui->tblTwsTarRep->item(rowCnt,20)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].azm,'f',2));
        ui->tblTwsTarRep->item(rowCnt,21)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].sigmaAzm,'f',2));
        ui->tblTwsTarRep->item(rowCnt,22)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].elv,'f',2));
        ui->tblTwsTarRep->item(rowCnt,23)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].sigmaElv,'f',2));
        ui->tblTwsTarRep->item(rowCnt,24)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].vTrue,'f',2));
        ui->tblTwsTarRep->item(rowCnt,25)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].sigmaVel,'f',2));
        ui->tblTwsTarRep->item(rowCnt,26)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].vLos,'f',2));
        ui->tblTwsTarRep->item(rowCnt,27)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].sigmaVelLos,'f',2));
        ui->tblTwsTarRep->item(rowCnt,28)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].vxLos,'f',2));
        ui->tblTwsTarRep->item(rowCnt,29)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].sigmaVelXLos,'f',2));
        ui->tblTwsTarRep->item(rowCnt,30)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].snr,'f',2));
        ui->tblTwsTarRep->item(rowCnt,31)->setText(QString::number(stTWSTarRep.twsTracks[rowCnt].avgRCS,'f',2));

    }
}

void fcrRadar::fnDecodeMflRep()
{

  //  ui->sbMFLRepPrefix->setValue(stMflRep.messHeadRp.messPref);
  //  ui->sbMFLRepSource->setValue(stMflRep.messHeadRp.messSource);
  //  ui->sbMFLRepId->setValue(stMflRep.messHeadRp.messType);
  //  ui->sbMFLRepSeqNum->setValue(stMflRep.messHeadRp.messSeqNum);
  //  ui->sbMFLRepBodyLen->setValue(stMflRep.messHeadRp.bodyLen);
  //  ui->sbMFLRepMflCnt->setValue(stMflRep.mflCount);

    for(int rowCnt = 0;rowCnt < ui->tblMFLRep->rowCount();rowCnt++)
    {
        ui->tblMFLRep->item(rowCnt,0)->setText(QString::number(stMflRep.reports[rowCnt].mflId));
        ui->tblMFLRep->item(rowCnt,1)->setText(QString::number(stMflRep.reports[rowCnt].testResult));
        ui->tblMFLRep->item(rowCnt,2)->setText(fnLRUId(stMflRep.reports[rowCnt].lruId,stMflRep.reports[rowCnt].mflId));
        ui->tblMFLRep->item(rowCnt,3)->setText(fnMFLSev(stMflRep.reports[rowCnt].severity));
        ui->tblMFLRep->item(rowCnt,4)->setText(QString::number(stMflRep.reports[rowCnt].aprTime));
    }

}

void fcrRadar::fnDecodeJamRep()
{

 //   ui->sbJamRepPrefix->setValue(stEccmRep.messHeadRp.messPref);
 //   ui->sbJamRepSource->setValue(stEccmRep.messHeadRp.messSource);
 //   ui->sbJamRepId->setValue(stEccmRep.messHeadRp.messType);
 //   ui->sbJamRepSeqNum->setValue(stEccmRep.messHeadRp.messSeqNum);
 //   ui->sbJamRepBodyLen->setValue(stEccmRep.messHeadRp.bodyLen);
 //   ui->sbJamRepJamCnt->setValue(stEccmRep.jammerCount);

    for(int rowCnt = 0;rowCnt < ui->tblJamRep->rowCount();rowCnt++)
    {
        ui->tblJamRep->item(rowCnt,0)->setText(fnJamType(stEccmRep.jammers[rowCnt].type));
        ui->tblJamRep->item(rowCnt,1)->setText(QString::number(stEccmRep.jammers[rowCnt].startAzm));
        ui->tblJamRep->item(rowCnt,2)->setText(QString::number(stEccmRep.jammers[rowCnt].endAzm));
        ui->tblJamRep->item(rowCnt,3)->setText(fnFreqSts(stEccmRep.jammers[rowCnt].freqStatus));
        ui->tblJamRep->item(rowCnt,4)->setText(QString::number(stEccmRep.jammers[rowCnt].elv));
    }
}

//void fcrRadar::fnDecodeMaintRep()
//{

//    ui->sbMaintPrefix->setValue(stMaint.messHeadRp.messPref);
//    ui->sbMaintSource->setValue(stMaint.messHeadRp.messSource);
//    ui->sbMaintId->setValue(stMaint.messHeadRp.messType);
//    ui->sbMaintSeqNum->setValue(stMaint.messHeadRp.messSeqNum);
//    ui->sbMaintBodyLen->setValue(stMaint.messHeadRp.bodyLen);
//    ui->sbMaintRdrVer->setValue(stMaint.swVer);
//    ui->sbMaintAntDigFwVer->setValue(stMaint.fwVer);

//}

//void fcrRadar::fnReadUDPRpMessage()
//{
//    if(bStartSim == true)
//    {
//        switch(fnRecieveMessage(RxData))
//        {
//        case STATUS_REPORT:
//        {
//            if(ui->chbLogStsRep->isChecked())
//            {
////                writeToLogFile((char *)RxData,sizeof(Status),STATUS_REPORT);
//                fnLogStatus(&stsRep,1);
//            }
//        }
//            break;
//        case STT_TARGET_REPORT:
//        {
//            if(ui->chbLogSttTarRep->isChecked())
//            {
////                writeToLogFile((char *)RxData,sizeof(STTTargetReport),STT_TARGET_REPORT);
//                fnLogSTTTargetReport(&stSTTTarRep,1);
//            }
//        }
//            break;
//        case TWS_TARGETS_REPORT:
//        {
//            if(ui->chbLogTwsTarRep->isChecked())
//            {
////                writeToLogFile((char *)RxData,sizeof(TWSTargetReport),TWS_TARGETS_REPORT);
//                fnLogTWSTargetReportt(&stTWSTarRep,1);
//            }
//        }
//            break;
//        case MFL_REPORTS:
//        {
//            if(ui->chbLogMflRep->isChecked())
//            {
////                writeToLogFile((char *)RxData,sizeof(MFLReports),MFL_REPORTS);
//                fnLogMFLReport(&stMflRep,1);
//            }
//        }
//            break;
//        case ECCM_REPORTS:
//        {
//            if(ui->chbLogJamRep->isChecked())
//            {
////                writeToLogFile((char *)RxData,sizeof(ECCMReport),ECCM_REPORTS);
//                fnLogECCMReport(&stEccmRep,1);
//            }
//        }
//            break;
//        case MAINTENANCE_REP:
//        {
//            if(ui->chbLogMaint->isChecked())
//            {
////                writeToLogFile((char *)RxData,sizeof(Maintenance),MAINTENANCE_REP);
//                fnLogMaintenance(&stMaint,1);
//            }
//        }
//            break;
//        default:
//        {
//            ;
//        }
//            break;
//        }
//    }
//}



//void fcrRadar::fnTimerTimeOut()
//{
//    static u_int32 cntr = 0;
//    cntr+=TIMER_TIMEOUT;
//    if((cntr%TIME_500MSEC) == 0)
//    {
//      //  ui->lblSytemDateTime->setText(QDateTime::currentDateTime().toString(Qt::ISODate));
//    }
//    if(bStartSim == true)
//    {
//        if(ui->chbEnableAnteenaControl->isChecked())
//        {
//            if(ui->chbFaultGarbageData->isChecked())
//            {
//                udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortAnt);
//            }
//            else
//            {
//                fnSendAnteenaPosition();

//                if(ui->chbLogAntPos->isChecked())
//                {
////                    if(bFaultHalfPacket)
////                    {
////                        writeToLogFile((char *)&antPos,sizeof(AntPos)/2,ANTENNA_POSITION);
////                    }
////                    else
////                    {
////                        writeToLogFile((char *)&antPos,sizeof(AntPos),ANTENNA_POSITION);
////                    }
//                    fnLogAntPos(&antPos,0);
//                }
//            }

//        }
//        if((cntr%TIMER_1SEC) == 0)
//        {
//            if(ui->chbEnableStateOfOperatn->isChecked())
//            {
//                if(ui->chbFaultGarbageData->isChecked())
//                {
//                    udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
//                }
//                else
//                {
//                    fnSendStateOfOperationMessage();
//                    if(ui->chbLogStateOfOper->isChecked())
//                    {
////                        if(bFaultHalfPacket)
////                        {
////                            writeToLogFile((char *)&stateOfOperation,sizeof(StateOfOperationCmd)/2,STATEOFOPERATION);
////                        }
////                        else
////                        {
////                            writeToLogFile((char *)&stateOfOperation,sizeof(StateOfOperationCmd),STATEOFOPERATION);
////                        }
//                        fnLogStateOfOperationCmd(&stateOfOperation,0);
//                    }

//                }

//            }
//            else
//            {
//                ;
//            }
//            if(ui->chbEnableInsData->isChecked())
//            {
//                if(ui->chbFaultGarbageData->isChecked())
//                {
//                    udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortAnt);
//                }
//                else
//                {
//                    fnSendINSDataMessage();
//                    if(ui->chbLogINSData->isChecked())
//                    {
////                        if(bFaultHalfPacket)
////                        {
////                            writeToLogFile((char *)&InsData,sizeof(INSData)/2,INS_DATA);
////                        }
////                        else
////                        {
////                            writeToLogFile((char *)&InsData,sizeof(INSData),INS_DATA);
////                        }
//                        fnLogINSData(&InsData,0);
//                    }
//                }
//            }
//            else
//            {
//                ;
//            }
//        }
//        if((cntr%TIME_500MSEC) == 0)
//        {
//            fnDecodeStsRep();
//            fnDecodeSTTTarRep();
//            fnDecodeTWSTargetType();
//            fnDecodeMflRep();
//            fnDecodeJamRep();
//            fnDecodeMaintRep();

//            if(ui->chbLogShow->isChecked())
//            {
//                UpdateLogTbl();
//            }
//        }
//    }
//}


//void fcrRadar::on_pbSendInternalDesignation_clicked()
//{


//    if(ui->chbFaultGarbageData->isChecked())
//    {
//        udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
//    }
//    else
//    {
//        fnSendInternalDesignation();
//        if(ui->chbLogInterDesig->isChecked())
//        {
////            if(bFaultHalfPacket)
////            {
////                writeToLogFile((char *)&intDesignation,sizeof(IntDesig)/2,INTERNALDESIGNATION);
////            }
////            else
////            {
////                writeToLogFile((char *)&intDesignation,sizeof(IntDesig),INTERNALDESIGNATION);
////            }
//            fnLogIntDesig(&intDesignation,0);

//        }
//    }
//}


//void fcrRadar::on_pbSendRstCmd_clicked()
//{


//    if(ui->chbFaultGarbageData->isChecked())
//    {
//        udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
//    }
//    else
//    {

//        fnSendRstCmd();

//        if(ui->chbLogRstCmd->isChecked())
//        {
////            if(bFaultHalfPacket)
////            {
////                writeToLogFile((char *)&rstRdr,sizeof(ResetRdr)/2,RESET_CMD);
////            }
////            else
////            {
////                writeToLogFile((char *)&rstRdr,sizeof(ResetRdr),RESET_CMD);
////            }
//            fnLogResetRdr(&rstRdr,0);
//        }
//    }
//}


//void fcrRadar::on_pbSendMisalignmentMess_clicked()
//{


//    if(ui->chbFaultGarbageData->isChecked())
//    {
//        udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
//    }
//    else
//    {
//        fnSendMisalignmentMess();

//        if(ui->chbLogMisalignMes->isChecked())
//        {
////            if(bFaultHalfPacket)
////            {
////                writeToLogFile((char *)&misAlign,sizeof(PedMisAlgn)/2,MISALIGNMENT);
////            }
////            else
////            {
////                writeToLogFile((char *)&misAlign,sizeof(PedMisAlgn),MISALIGNMENT);
////            }
//            fnLogPedMisAlgn(&misAlign,0);
//        }
//    }
//}


//void fcrRadar::on_pbSendExternalDesignation_clicked()
//{

//    if(ui->chbFaultGarbageData->isChecked())
//    {
//        udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
//    }
//    else
//    {

//        fnSendExternalDesignation();
//        if(ui->chbLogExtDesig->isChecked())
//        {
////            if(bFaultHalfPacket)
////            {
////                writeToLogFile((char *)&extDesignation,sizeof(ExtDesig)/2,EXTERNAMDESIGNATION);
////            }
////            else
////            {
////                writeToLogFile((char *)&extDesignation,sizeof(ExtDesig),EXTERNAMDESIGNATION);
////            }
//            fnLogExtDesig(&extDesignation,0);
//        }
//    }
//}


//void fcrRadar::on_pbClearTWSTgtRep_clicked()
//{
// //   ui->sbTwsTarRepPrefix->setValue(0);
// //   ui->sbTwsTarRepSource->setValue(0);
// //   ui->sbTwsTarRepId->setValue(0);
// //   ui->sbTwsTarRepSeqNum->setValue(0);
// //   ui->sbTwsTarRepBodyLen->setValue(0);
// //   ui->sbTwsTarRepNum->setValue(0);

//    for(int rowCnt = 0;rowCnt < ui->tblTwsTarRep->rowCount();rowCnt++)
//    {
//        ui->tblTwsTarRep->item(rowCnt,0)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,1)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,2)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,3)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,4)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,5)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,6)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,7)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,8)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,9)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,10)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,11)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,12)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,13)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,14)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,15)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,16)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,17)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,18)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,19)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,20)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,21)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,22)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,23)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,24)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,25)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,26)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,27)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,28)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,29)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,30)->setText("");
//        ui->tblTwsTarRep->item(rowCnt,31)->setText("");
//    }

//    // This will clear the structure too
//    memset(&stTWSTarRep,0,sizeof(stTWSTarRep));
//}

//void fcrRadar::on_pbClearMFLRep_clicked()
//{
// //   ui->sbMFLRepPrefix->setValue(0);
//  //  ui->sbMFLRepSource->setValue(0);
// //   ui->sbMFLRepId->setValue(0);
// //   ui->sbMFLRepSeqNum->setValue(0);
// //   ui->sbMFLRepBodyLen->setValue(0);
// //   ui->sbMFLRepMflCnt->setValue(0);

//    for(int rowCnt = 0;rowCnt < ui->tblMFLRep->rowCount();rowCnt++)
//    {
//        ui->tblMFLRep->item(rowCnt,0)->setText(0);
//        ui->tblMFLRep->item(rowCnt,1)->setText(0);
//        ui->tblMFLRep->item(rowCnt,2)->setText(0);
//        ui->tblMFLRep->item(rowCnt,3)->setText(0);
//        ui->tblMFLRep->item(rowCnt,4)->setText(0);
//    }
//    // This will clear the structure too
//    memset(&stMflRep,0,sizeof(stMflRep));
//}

//void fcrRadar::on_pbClearJamReport_clicked()
//{
//  //  ui->sbJamRepPrefix->setValue(0);
//  //  ui->sbJamRepSource->setValue(0);
//  //  ui->sbJamRepId->setValue(0);
//  //  ui->sbJamRepSeqNum->setValue(0);
//  //  ui->sbJamRepBodyLen->setValue(0);
//  //  ui->sbJamRepJamCnt->setValue(0);

//    for(int rowCnt = 0;rowCnt < ui->tblJamRep->rowCount();rowCnt++)
//    {
//        ui->tblJamRep->item(rowCnt,0)->setText("");
//        ui->tblJamRep->item(rowCnt,1)->setText("");
//        ui->tblJamRep->item(rowCnt,2)->setText("");
//        ui->tblJamRep->item(rowCnt,3)->setText("");
//        ui->tblJamRep->item(rowCnt,4)->setText("");
//    }

//    // This will clear the structure too
//    memset(&stEccmRep,0,sizeof(stEccmRep));
//}

//void fcrRadar::on_pbClearMaintenance_clicked()
//{
//    ui->sbMaintPrefix->setValue(0);
//    ui->sbMaintSource->setValue(0);
//    ui->sbMaintId->setValue(0);
//    ui->sbMaintSeqNum->setValue(0);
//    ui->sbMaintBodyLen->setValue(0);
//    ui->sbMaintRdrVer->setValue(0);
//    ui->sbMaintAntDigFwVer->setValue(0);

//    // This will clear the structure too
//    memset(&stMaint,0,sizeof(stMaint));
//}


QString fcrRadar::fnTWSTarRep(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case AIR_NORMAL: RetVal = "AIR_NORMAL";
        break;
    case HH: RetVal = "HH";
        break;
    case TOJ: RetVal = "MLJ";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}

QString fcrRadar::fnSTTTarSt(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case TRK_INIT: RetVal = "TRK_INIT";
        break;
    case TRACK_UPDATE: RetVal = "TRACK_UPDATE";
        break;
    case TRACK_DELETE: RetVal = "TRACK_DELETE";
        break;
    case TRACK_EXTRAP: RetVal = "TRACK_EXTRAP";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}

QString fcrRadar::fnLRUId(unsigned int val, unsigned int id)
{
    QString RetVal;

    RetVal = "InValid";
    if(id != 0)
    {
        switch(val)
        {
        case SYSTEM: RetVal = "SYSTEM";
            break;
        case RP: RetVal = "RP";
            break;
        case ANT: RetVal = "ANT";
            break;
        case PROCESSING_COMP: RetVal = "PROCESSING_COMP";
            break;
        default: RetVal = "InValid";
            break;
        }
    }
    return RetVal;
}

QString fcrRadar::fnMFLSev(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case INFORMATION: RetVal = "INFORMATION";
        break;
    case WARNING: RetVal = "WARNING";
        break;
    case FAIL: RetVal = "FAIL";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}


QString fcrRadar::fnJamType(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case NO_JAM: RetVal = "NO_JAM";
        break;
    case MAIN_LOBE_JAM: RetVal = "MAIN_LOBE_JAM";
        break;
    case SLIDE_LOBE_JAM: RetVal = "SLIDE_LOBE_JAM";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}


QString fcrRadar::fnFreqSts(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case DEFAULT: RetVal = "DEFAULT";
        break;
    case OCCURED: RetVal = "OCCURED";
        break;
    case RECOMMENDED: RetVal = "RECOMMENDED";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}


void fcrRadar::fnLogStatus(Status *Str, int Source)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("Status Report,");

        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");
        file.write(",");
        file.write(QString::number(Str->rdrState).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrMode).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->targetTypeMode).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrTx).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->elvCov).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrTVel).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrFreqBand).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrFreqBandChange).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->dElvLow).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->dElvHigh).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->noOfValidSectors).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sectors[0].startAng).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sectors[0].endAng).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sectors[0].rdrSectorType).toStdString().data());
        file.write(",");
        //SDS
        file.write(QString::number(Str->sectors[1].startAng).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sectors[1].endAng).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sectors[1].rdrSectorType).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmXRadar).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmYRadar).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmZRadar).toStdString().data());
        file.write("\n");
        file.close();
    }
}


void fcrRadar::fnLogSTTTargetReport(STTTargetReport *Str, int Source)
{

    QFile file;
    QString StrLog;

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("STT Target report,");
        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->tgtCount).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->delEl).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->delAzm).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sigmaDelEl).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sigmaDelAzm).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->range).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rangeDot).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->timeTag).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->sttTrackData.targetType).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.targetStatus).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.targetQuality).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.idInt).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.idExt).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.posX,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.posY,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.posZ,'f',2).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->sttTrackData.utmX).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.utmY).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.utmZ).toStdString().data()); // tgt_quality
        file.write(",");
        file.write(QString::number(Str->sttTrackData.utmZone).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.alt,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.sigmaAlt,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.velX,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.velY,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.velZ,'f',2).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->sttTrackData.targetTime).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.lastUpdateTime).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->sttTrackData.range,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.sigmaRange,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.azm,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.sigmaAzm,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.elv,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.sigmaElv,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.vTrue,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.sigmaVel,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.vLos,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.sigmaVelLos,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.vxLos,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.sigmaVelXLos,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.snr,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.avgRCS,'f',2).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->sttTrackData.extrapAz,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.sigmaExtrapAz,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.extrapEl,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.sigmaExtrapEl,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.spare[0],'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.spare[1],'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sttTrackData.spare[2],'f',2).toStdString().data());
        file.write("\n");
        file.close();
    }
}


void fcrRadar::fnLogTWSTargetReportt(TWSTargetReport *Str, int Source)
{
    QFile file;
    QString StrLog;

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("TWS Targets Report,");

        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->noOfTgt).toStdString().data());
        file.write(",");


        for(int i=0;i<120;i++)
        {
            file.write(QString::number(Str->twsTracks[i].targetType).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].targetStatus).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].spare).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].idInt).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].idExt).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].posX,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].posY,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].posZ,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].utmX).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].utmY).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].utmZ).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].utmZone).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].alt,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].sigmaAlt,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].velX,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].velY,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].velZ,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].targetTime).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].lastUpdateTime).toStdString().data());
            file.write(",");

            file.write(QString::number(Str->twsTracks[i].range,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].sigmaRange,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].azm,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].sigmaAzm,'f',2).toStdString().data());
            file.write(",");

            file.write(QString::number(Str->twsTracks[i].elv,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].sigmaElv,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].vTrue,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].sigmaVel,'f',2).toStdString().data());
            file.write(",");

            file.write(QString::number(Str->twsTracks[i].vLos,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].sigmaVelLos,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].vxLos,'f',2).toStdString().data());
            file.write(",");

            file.write(QString::number(Str->twsTracks[i].sigmaVelXLos,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].snr,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].avgRCS,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].sdToExt,'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].spare1[0],'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].spare1[1],'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].spare1[2],'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].spare1[3],'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].spare1[4],'f',2).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->twsTracks[i].spare1[5],'f',2).toStdString().data());

        }
file.write("\n");
file.close();
    }
}


void fcrRadar::fnLogMFLReport(MFLReports *Str, int Source)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("MFL Report,");

        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->mflCount).toStdString().data());
        file.write(",");

         //SDS
        for(int i=0;i<20;i++)
        {
            file.write(QString::number(Str->reports[i].mflId).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->reports[i].testResult).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->reports[i].lruId).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->reports[i].severity).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->reports[i].aprTime).toStdString().data());
            file.write(",");


        }
        file.write("\n");
        file.close();
    }

}


void fcrRadar::fnLogECCMReport(ECCMReport *Str, int Source)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("ECCM Report,");
        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->jammerCount).toStdString().data());
        file.write(",");


        //SDS
        for(int i=0;i<16;i++)
        {
            file.write(QString::number(Str->jammers[i].type).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->jammers[i].startAzm).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->jammers[i].endAzm).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->jammers[i].freqStatus).toStdString().data());
            file.write(",");
            file.write(QString::number(Str->jammers[i].elv).toStdString().data());
            file.write(",");


        }
        file.write("\n");
        file.close();
    }

}


void fcrRadar::fnLogMaintenance(Maintenance *Str, int Source)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("Maintenance,");

        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());;
        file.write(",");

        file.write(QString::number(Str->swVer,'f',2).toStdString().data());
        file.write(",");

        file.write(QString::number(Str->fwVer,'f',2).toStdString().data());
        file.write("\n");
        file.close();

    }
}


void fcrRadar::fnLogAntPos(AntPos *Str, int Source)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("Antenna Position,");

        file.write(QString::number(Str->messAntHead.messSeqNum).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->azm,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->elv,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->azmRate,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->elvRate,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->scanDir).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->timeTag).toStdString().data());
        file.write("\n");
        file.close();
    }
}


void fcrRadar::fnLogStateOfOperationCmd(StateOfOperationCmd *Str, int Source)
{
    QFile file;
    QString StrLog;

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }

        file.write("State Of Operation,");
        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrState).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrMode).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->targetTypeMode).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrTx).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrDRange).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrDElv,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->spare1).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrTVel).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrFreqBand).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rdrFreqBandChange).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->noOfValidSectors).toStdString().data());
        file.write(",");
        //SDS
        file.write(QString::number(Str->sector[0].startAng).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sector[0].endAng).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sector[0].rdrSectorType).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sector[1].startAng).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sector[1].endAng).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sector[1].rdrSectorType).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->clrTwsCmd).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->acqPosReachedState).toStdString().data());
        file.write("\n");
        file.close();
    }
}


void fcrRadar::fnLogINSData(INSData *Str, int Source)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("INS Data,");

        file.write(QString::number(Str->messAntHead.messSeqNum).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->timeTag).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmX).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmY).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmZ).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmZone).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->trueHdng,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->roll,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->pitch,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->yawRate,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rollRate,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->pitchRate,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->velX,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->velY,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->velZ,'f',2).toStdString().data());
        file.write("\n");
        file.close();
    }
}


void fcrRadar::fnDecodeSTTTarRep()
{

  //  ui->lineEditSttTarRepPrefix->setText(QString::number(stSTTTarRep.messHeadRp.messPref));
  //  ui->lineEditSttTarRepSource->setText(QString::number(stSTTTarRep.messHeadRp.messSource));
  //  ui->lineEditSttTarRepId->setText(QString::number(stSTTTarRep.messHeadRp.messType));
  //  ui->lineSttTarRepBodyLen->setText(QString::number(stSTTTarRep.messHeadRp.bodyLen));
  //  ui->lineEditSttTarRepSeqNum->setText(QString::number(stSTTTarRep.messHeadRp.messSeqNum));
    ui->sbSttTarRepTgtCount->setValue(stSTTTarRep.tgtCount);
    ui->dsbSttTarRepDeltaEl->setValue(stSTTTarRep.delEl);
    ui->dsbSttTarRepDeltaAz->setValue(stSTTTarRep.delAzm);
    ui->dsbttTarRepSigDeltaEl->setValue(stSTTTarRep.sigmaDelEl);
    ui->dsbSttTarRepSigDeltaAz->setValue(stSTTTarRep.sigmaDelAzm);
    ui->dsbSttTarRepRng->setValue(stSTTTarRep.range);
    ui->dsbSttTarRepRngDot->setValue(stSTTTarRep.rangeDot);
    ui->sbSttTarRepTimeTag->setValue(stSTTTarRep.timeTag);
    ui->cbSttTarRepTgtType->setEditText(fnSTTTarType(stSTTTarRep.sttTrackData.targetType));
    ui->cbSttTarRepTgtSt->setEditText(fnSTTTarSt(stSTTTarRep.sttTrackData.targetStatus));
    ui->cbSttTarRepTgtQual->setEditText(fnSTTTarQual(stSTTTarRep.sttTrackData.targetQuality));
    ui->sbSttTarRepINTID->setValue(stSTTTarRep.sttTrackData.idInt);
    ui->sbSttTarRepEXTID->setValue(stSTTTarRep.sttTrackData.idExt);
    ui->dsbSttTarRepX->setValue(stSTTTarRep.sttTrackData.posX);
    ui->dsbSttTarRepY->setValue(stSTTTarRep.sttTrackData.posY);
    ui->dsbSttTarRepZ->setValue(stSTTTarRep.sttTrackData.posZ);
    ui->sbSttTarRepUTMX->setValue(stSTTTarRep.sttTrackData.utmX);
    ui->sbSttTarRepUTMY->setValue(stSTTTarRep.sttTrackData.utmY);
    ui->sbSttTarRepUTMZ->setValue(stSTTTarRep.sttTrackData.utmZ);
    ui->sbSttTarRepUTMZone->setValue(stSTTTarRep.sttTrackData.utmZone);
    ui->dbSbSttTarRepAlt->setValue(stSTTTarRep.sttTrackData.alt);
    ui->dbSbSttTarRepSigAlt->setValue(stSTTTarRep.sttTrackData.sigmaAlt);
    ui->dsbSttTarRepVx->setValue(stSTTTarRep.sttTrackData.velX);
    ui->dsbSttTarRepVy->setValue(stSTTTarRep.sttTrackData.velY);
    ui->dsbSttTarRepVz->setValue(stSTTTarRep.sttTrackData.velZ);
    ui->sbSttTarRepTgtExtrapTime->setValue(stSTTTarRep.sttTrackData.targetTime);
    ui->sbSttTarRepTgtUpdateTime->setValue(stSTTTarRep.sttTrackData.lastUpdateTime);
    ui->dsbSttTarRepRngTTD->setValue(stSTTTarRep.sttTrackData.range);
    ui->dsbSttTarRepSigRngTTD->setValue(stSTTTarRep.sttTrackData.sigmaRange);
    ui->dsbSttTarRepAz->setValue(stSTTTarRep.sttTrackData.azm);
    ui->dsbSttTarRepSigAz->setValue(stSTTTarRep.sttTrackData.sigmaAzm);
    ui->dsbSttTarRepEl->setValue(stSTTTarRep.sttTrackData.elv);
    ui->dsbSttTarRepSigEl->setValue(stSTTTarRep.sttTrackData.sigmaElv);
    ui->dsbSttTarRepVel->setValue(stSTTTarRep.sttTrackData.vTrue);
    ui->dsbSttTarRepSigVel->setValue(stSTTTarRep.sttTrackData.sigmaVel);
    ui->dsbSttTarRepVLOS->setValue(stSTTTarRep.sttTrackData.vLos);
    ui->dsbSttTarRepSigVLOS->setValue(stSTTTarRep.sttTrackData.sigmaVelLos);
    ui->dsbSttTarRepVxLOS_2->setValue(stSTTTarRep.sttTrackData.vxLos);
    ui->dsbSttTarRepSigVxLOS->setValue(stSTTTarRep.sttTrackData.sigmaVelXLos);
    ui->dsbSttTarRepSNR->setValue(stSTTTarRep.sttTrackData.snr);
    ui->dsbSttTarRepAvRCS->setValue(stSTTTarRep.sttTrackData.avgRCS);
    ui->dsbSttTarRepTarAzExtrap->setValue(stSTTTarRep.sttTrackData.extrapAz);
    ui->dsbSttTarRepSigTarAzExtrap->setValue(stSTTTarRep.sttTrackData.sigmaExtrapAz);
    ui->dsbSttTarRepTarElExtrap->setValue(stSTTTarRep.sttTrackData.extrapEl);
    ui->dsbSttTarRepSigTarElExtrap->setValue(stSTTTarRep.sttTrackData.sigmaExtrapEl);
}


QString fcrRadar::fnSTTTarType(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case AIR_NORMAL: RetVal = "AIR_NORMAL";
        break;
    case HH: RetVal = "HH";
        break;
    case TOJ: RetVal = "TOJ";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}


QString fcrRadar::fnSTTTarQual(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case TRACK_TGT: RetVal = "TRACK_TGT";
        break;
    case SLIDE_LOBE_JAMMER: RetVal = "Slide Lobe Jammer";
        break;
    case MAIN_LOBE_JAMMER: RetVal = "Main Lobe Jammer";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}


void fcrRadar::UpdateLogTbl()
{

    QFile file;
    int RowCnt = tblLog->rowCount() + 1;
    QString StrLog;
    QStringList StrLst;
    file.setFileName(Path);
    if(file.open(QIODevice::ReadOnly  | QIODevice::Text))
    {
        StrLog = file.readAll().toStdString().data();
        StrLst = StrLog.split("\n");

        if((StrLst.size()-1) > RowCnt)
        {
            for(int Indx = RowCnt;Indx < StrLst.size()-1 ; Indx++)
            {
                QString StrData = StrLst.at(RowCnt);
                QStringList StrDataLst = StrData.split(",");
                tblLog->insertRow(RowCnt-1);
                tblLog->setItem(RowCnt-1,0,new QTableWidgetItem(StrDataLst.at(0)));
                tblLog->item(RowCnt-1,0)->setFlags(tblLog->item(RowCnt-1,0)->flags() &  ~Qt::ItemIsEditable);
                tblLog->setItem(RowCnt-1,1,new QTableWidgetItem(StrDataLst.at(1)));
                tblLog->item(RowCnt-1,1)->setFlags(tblLog->item(RowCnt-1,1)->flags() &  ~Qt::ItemIsEditable);
                tblLog->setItem(RowCnt-1,2,new QTableWidgetItem(StrDataLst.at(2)));
                tblLog->item(RowCnt-1,2)->setFlags(tblLog->item(RowCnt-1,2)->flags() &  ~Qt::ItemIsEditable);
                tblLog->setItem(RowCnt-1,3,new QTableWidgetItem(StrDataLst.at(3)));
                tblLog->item(RowCnt-1,3)->setFlags(tblLog->item(RowCnt-1,3)->flags() &  ~Qt::ItemIsEditable);
                QString DataFile;
                for(int i = 4;i < StrDataLst.size();i++)
                {
                   DataFile += StrDataLst.at(i);
                   DataFile += " ";
                }
                tblLog->setItem(RowCnt-1,4,new QTableWidgetItem(DataFile));
                tblLog->item(RowCnt-1,4)->setFlags(tblLog->item(RowCnt-1,4)->flags() &  ~Qt::ItemIsEditable);
                RowCnt++;
            }
        }
    }
    file.close();
}



void fcrRadar::fnLogIntDesig(IntDesig *Str, int Source)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("Internal Designation,");

        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->tId).toStdString().data());
        file.write("\n");
        file.close();
    }
}


void fcrRadar::fnLogResetRdr(ResetRdr *Str, int Source)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("Reset radar.,");

        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->resetCmd).toStdString().data());
        file.write("\n");
        file.close();
    }
}


void fcrRadar::fnLogPedMisAlgn(PedMisAlgn *Str, int Source)
{
    QFile file;
    QString StrLog;

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("Misalignment message,");

        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->pedAntRoll,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->pedAntPitch,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->pedAntYaw,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->pedInsRoll,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->pedInsPitch,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->pedInsYaw,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->levArmX).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->levArmY).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->levArmZ).toStdString().data());
        file.write("\n");
        file.close();
    }
}


void fcrRadar::fnLogExtDesig(ExtDesig *Str, int Source)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        file.write(",");
        if(Source == 0)
        {
            file.write(SENDER);
        }
        else
        {
            file.write(RECEIVER);
        }
        file.write("External Designation,");

        file.write(QString::number(Str->messHeadRp.messSeqNum).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->desigCoordinates).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->posX,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->posY,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->posZ,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmX).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmY).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->utmZone).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->alt,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sigmaAlt,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->lat,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->Long,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->velX,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->velY,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->velZ,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->targetTime).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->lastUpdateTime).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->range,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sigmaRange,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->azm,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sigmaAzm,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->elv,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sigmaElv,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->vTrue,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sigmaVel,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->vLos,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sigmaVelLos,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->vxLos,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->sigmaVelXLos,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rcs,'f',2).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->rcsTargetType).toStdString().data());
        file.write(",");
        file.write(QString::number(Str->tgtIdExt).toStdString().data());
        file.write("\n");
        file.close();
    }
}








