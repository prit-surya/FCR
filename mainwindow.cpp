#include "mainwindow.h"
#include "ui_mainwindow.h"

//char GarabageData[] = "Hello Friend this is garbage data so please uncheck the field of garbage data so that you dont get this data if you still want the same data then It is your wish. Happy testing. Live Long. Stay Happy. God Bless you. Thank you";
//char RxData[20000];
/****************************************************************************************
*Function Name: MainWindow()
*Description: This function is Constructor of main class.
*Input:QWidget
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will connect the slotfnReadUDPRpMessage of signal ReadyRead for Rp UDP socket.
2. Start timer which will call timerTimeout() function.
3. It will initialize all the messages structure according to UI default value.
4. It will initialize all the table with '-' value
******************************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(&udpSockRp,SIGNAL(readyRead()),this,SLOT(fnReadUDPRpMessage()));
    connect(&tick,SIGNAL(timeout()),this,SLOT(fnTimerTimeOut()));

    connect(&tick1,SIGNAL(timeout()),this,SLOT(fnReadUDPRpMessage()));
    tick.setTimerType(Qt::PreciseTimer);
    tick1.setTimerType(Qt::PreciseTimer);
    tick.start(TIMER_TIMEOUT);
    tick1.start(TIMER_TIMEOUT);
    ui->lblVersion->setText(VERSION);
    //    connect(&tick2,SIGNAL(timeout()),this,SLOT(UpdateLogTbl()));
    //    tick2.start(TIME_500MSEC);
    bStartSim = false;

    qDebug() << "Size of stateOfOperation" << sizeof(stateOfOperation);
    qDebug() << "Size of misAlign"<< sizeof(misAlign);
    qDebug() << "Size of intDesignation"<< sizeof(intDesignation);
    qDebug() << "Size of extDesignation"<< sizeof(extDesignation);
    qDebug() << "Size of antPos"<< sizeof(antPos);
    qDebug() << "Size of InsData"<< sizeof(InsData);
    qDebug() << "Size of rstRdr"<< sizeof(rstRdr);
    qDebug() << "Size of stsRep"<< sizeof(stsRep);
    qDebug() << "Size of stSTTTarRep"<< sizeof(stSTTTarRep);
    qDebug() << "Size of stTWSTarRep"<< sizeof(stTWSTarRep);
    qDebug() << "Size of stMflRep"<< sizeof(stMflRep);
    qDebug() << "Size of stEccmRep"<< sizeof(stEccmRep);
    qDebug() << "Size of stMaint"<< sizeof(stMaint);

    bFaultHalfPacket = 0;
    on_pbUpdateStateOfOperatn_clicked();
    on_pbUpdateMisalignmentMess_clicked();
    on_pbUpdateInternalDesignation_clicked();
    on_pbUpdateExternalDesignation_clicked();
    on_pbAntPosition_clicked();
    on_pbINSDataUpdate_clicked();
    on_pbUpdateRstCmd_clicked();
#if 0
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
        tblLog->setGeometry(10,480,1150,270);
    tblLog->setColumnCount(5);
    tblLog->setColumnWidth(4,750);
    tblLog->setHorizontalHeaderItem(0,new QTableWidgetItem("Time"));
    tblLog->setHorizontalHeaderItem(1,new QTableWidgetItem("Source"));
    tblLog->setHorizontalHeaderItem(2,new QTableWidgetItem("Type"));
    tblLog->setHorizontalHeaderItem(3,new QTableWidgetItem("SequenceNum"));
    tblLog->setHorizontalHeaderItem(4,new QTableWidgetItem("Data"));
    tblLog->show();
#endif

#if 0
    //PSS generating constructor generate combobox list
    ui->cbStateRepRdrState->clear();
    ui->cbStateRepRdrState->addItem("Init");
    ui->cbStateRepRdrState->addItem("Standby");
    ui->cbStateRepRdrState->addItem("Maintenance");
    ui->cbStateRepRdrState->addItem("Operate");
    ui->cbStateRepRdrState->addItem("Reset");
    ui->cbStateRepRdrState->addItem("IBIT");
    ui->cbStateRepRdrState->addItem("Off");

    ui->cbStateRepRdrMode->addItem("AA_SECTOR");
    ui->cbStateRepRdrMode->addItem("AA_360");
    ui->cbStateRepRdrMode->addItem("AA_MANUAL");
    ui->cbStateRepRdrMode->addItem("AA_STT");
    ui->cbStateRepRdrMode->addItem("AA_ACQ");

     ui->cbStateRepTgtTypeMode->addItem("Normal");
      ui->cbStateRepTgtTypeMode->addItem("Test target");

     ui->cbStateRepTgtTypeMode->addItem("Repeater");

     ui->cbStateRepTx->addItem("OFF");
      ui->cbStateRepTx->addItem("ON");
       ui->cbStateRepTx->addItem("Disabled");

       ui->cbStateRepEleCov->addItem("20 Degrees");
       ui->cbStateRepEleCov->addItem("30 Degrees");

       ui->cbStateRepTgtVelRej->addItem("High");
        ui->cbStateRepTgtVelRej->addItem("Low");

        ui->cbStateRepFreqBand->addItem("BAND A");
        ui->cbStateRepFreqBand->addItem("BAND B");
        ui->cbStateRepFreqBand->addItem("BAND C");
        ui->cbStateRepFreqBand->addItem("BAND D");
        ui->cbStateRepFreqBand->addItem("BAND E");
        ui->cbStateRepFreqBand->addItem("BAND F");

        ui->cbStateRepFreqChngMode->addItem("Manual");
        ui->cbStateRepFreqChngMode->addItem("Automatic");

        ui->cbStateRepSec0Type->addItem("Normal");
        ui->cbStateRepSec0Type->addItem("Blank");

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
#endif
#if 0
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

//        connect(ui->sbStateRepDetectElHigh,
//                SIGNAL(valueChanged(int)),
//                SLOT(onSpinBoxValueChanged(int)));

//        connect(ui->sbStateRepDetectElHigh,
//                SIGNAL(valueChanged(int)),
//                SLOT(onSpinBoxValueChanged(int)));
#endif
}



/****************************************************************************************
*Function Name:~MainWindow()
*Description: This function is Distructor of main class.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will disconnect the tcp socket.
2. Close the file
3. delete the UI object
******************************************************************************************/
MainWindow::~MainWindow()
{
    udpSockAnt.close();
    udpSockRp.close();
    delete ui;
}

/****************************************************************************************
*Function Name:fnComboToNumber()
*Description: This function is used to convert combobox text to number.
*Input:QString txt -> combo box text
*Output:int -> return number
*Function calls:none
*Functionality/Algorithm:
1. It will split the text of combo box with "-"
2. It will convert the 1st element to integer and return to calling function
******************************************************************************************/
int MainWindow::fnComboToNumber(QString txt)
{
    QStringList strLst = txt.split("-");
    return QString(strLst.at(0)).toInt();
}






/****************************************************************************************
*Function Name:fnDecodeStsRep()
*Description: This function is used to send the decode status report message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will copy the recieved number of bytes to the structure of status report.
2. It will assign the UI the values recieved.
******************************************************************************************/
void MainWindow::fnDecodeStsRep()
{
#if 0
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
#endif
}

/****************************************************************************************
*Function Name:fnDecodeSTTTarRep()
*Description: This function is used to send the decode status report message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will copy the recieved number of bytes to the structure of status report.
2. It will assign the UI the values recieved.
******************************************************************************************/
void MainWindow::fnDecodeSTTTarRep()
{

//    ui->lineEditSttTarRepPrefix->setText(QString::number(stSTTTarRep.messHeadRp.messPref));
//    ui->lineEditSttTarRepSource->setText(QString::number(stSTTTarRep.messHeadRp.messSource));
//    ui->lineEditSttTarRepId->setText(QString::number(stSTTTarRep.messHeadRp.messType));
//    ui->lineSttTarRepBodyLen->setText(QString::number(stSTTTarRep.messHeadRp.bodyLen));
//    ui->lineEditSttTarRepSeqNum->setText(QString::number(stSTTTarRep.messHeadRp.messSeqNum));
//    ui->sbSttTarRepTgtCount->setValue(stSTTTarRep.tgtCount);
//    ui->dsbSttTarRepDeltaEl->setValue(stSTTTarRep.delEl);
//    ui->dsbSttTarRepDeltaAz->setValue(stSTTTarRep.delAzm);
//    ui->dsbttTarRepSigDeltaEl->setValue(stSTTTarRep.sigmaDelEl);
//    ui->dsbSttTarRepSigDeltaAz->setValue(stSTTTarRep.sigmaDelAzm);
//    ui->dsbSttTarRepRng->setValue(stSTTTarRep.range);
//    ui->dsbSttTarRepRngDot->setValue(stSTTTarRep.rangeDot);
//    ui->sbSttTarRepTimeTag->setValue(stSTTTarRep.timeTag);
//    ui->cbSttTarRepTgtType->setEditText(fnSTTTarType(stSTTTarRep.sttTrackData.targetType));
//    ui->cbSttTarRepTgtSt->setEditText(fnSTTTarSt(stSTTTarRep.sttTrackData.targetStatus));
//    ui->cbSttTarRepTgtQual->setEditText(fnSTTTarQual(stSTTTarRep.sttTrackData.targetQuality));
//    ui->sbSttTarRepINTID->setValue(stSTTTarRep.sttTrackData.idInt);
//    ui->sbSttTarRepEXTID->setValue(stSTTTarRep.sttTrackData.idExt);
//    ui->dsbSttTarRepX->setValue(stSTTTarRep.sttTrackData.posX);
//    ui->dsbSttTarRepY->setValue(stSTTTarRep.sttTrackData.posY);
//    ui->dsbSttTarRepZ->setValue(stSTTTarRep.sttTrackData.posZ);
//    ui->sbSttTarRepUTMX->setValue(stSTTTarRep.sttTrackData.utmX);
//    ui->sbSttTarRepUTMY->setValue(stSTTTarRep.sttTrackData.utmY);
//    ui->sbSttTarRepUTMZ->setValue(stSTTTarRep.sttTrackData.utmZ);
//    ui->sbSttTarRepUTMZone->setValue(stSTTTarRep.sttTrackData.utmZone);
//    ui->dbSbSttTarRepAlt->setValue(stSTTTarRep.sttTrackData.alt);
//    ui->dbSbSttTarRepSigAlt->setValue(stSTTTarRep.sttTrackData.sigmaAlt);
//    ui->dsbSttTarRepVx->setValue(stSTTTarRep.sttTrackData.velX);
//    ui->dsbSttTarRepVy->setValue(stSTTTarRep.sttTrackData.velY);
//    ui->dsbSttTarRepVz->setValue(stSTTTarRep.sttTrackData.velZ);
//    ui->sbSttTarRepTgtExtrapTime->setValue(stSTTTarRep.sttTrackData.targetTime);
//    ui->sbSttTarRepTgtUpdateTime->setValue(stSTTTarRep.sttTrackData.lastUpdateTime);
//    ui->dsbSttTarRepRngTTD->setValue(stSTTTarRep.sttTrackData.range);
//    ui->dsbSttTarRepSigRngTTD->setValue(stSTTTarRep.sttTrackData.sigmaRange);
//    ui->dsbSttTarRepAz->setValue(stSTTTarRep.sttTrackData.azm);
//    ui->dsbSttTarRepSigAz->setValue(stSTTTarRep.sttTrackData.sigmaAzm);
//    ui->dsbSttTarRepEl->setValue(stSTTTarRep.sttTrackData.elv);
//    ui->dsbSttTarRepSigEl->setValue(stSTTTarRep.sttTrackData.sigmaElv);
//    ui->dsbSttTarRepVel->setValue(stSTTTarRep.sttTrackData.vTrue);
//    ui->dsbSttTarRepSigVel->setValue(stSTTTarRep.sttTrackData.sigmaVel);
//    ui->dsbSttTarRepVLOS->setValue(stSTTTarRep.sttTrackData.vLos);
//    ui->dsbSttTarRepSigVLOS->setValue(stSTTTarRep.sttTrackData.sigmaVelLos);
//    ui->dsbSttTarRepVxLOS_2->setValue(stSTTTarRep.sttTrackData.vxLos);
//    ui->dsbSttTarRepSigVxLOS->setValue(stSTTTarRep.sttTrackData.sigmaVelXLos);
//    ui->dsbSttTarRepSNR->setValue(stSTTTarRep.sttTrackData.snr);
//    ui->dsbSttTarRepAvRCS->setValue(stSTTTarRep.sttTrackData.avgRCS);
//    ui->dsbSttTarRepTarAzExtrap->setValue(stSTTTarRep.sttTrackData.extrapAz);
//    ui->dsbSttTarRepSigTarAzExtrap->setValue(stSTTTarRep.sttTrackData.sigmaExtrapAz);
//    ui->dsbSttTarRepTarElExtrap->setValue(stSTTTarRep.sttTrackData.extrapEl);
//    ui->dsbSttTarRepSigTarElExtrap->setValue(stSTTTarRep.sttTrackData.sigmaExtrapEl);
}

/****************************************************************************************
*Function Name:fnDecodeTWSTargetType()
*Description: This function is used to send the decode TWS target type message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will copy the recieved number of bytes to the structure of TWS target type.
2. It will assign the UI the values recieved.
******************************************************************************************/
void MainWindow::fnDecodeTWSTargetType()
{

   // ui->sbTwsTarRepPrefix->setValue(stTWSTarRep.messHeadRp.messPref);
   // ui->sbTwsTarRepSource->setValue(stTWSTarRep.messHeadRp.messSource);
   // ui->sbTwsTarRepId->setValue(stTWSTarRep.messHeadRp.messType);
   // ui->sbTwsTarRepSeqNum->setValue(stTWSTarRep.messHeadRp.messSeqNum);
   // ui->sbTwsTarRepBodyLen->setValue(stTWSTarRep.messHeadRp.bodyLen);
   // ui->sbTwsTarRepNum->setValue(stTWSTarRep.noOfTgt);
#if 0
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
#endif
}
/****************************************************************************************
*Function Name:fnDecodeMflRep()
*Description: This function is used to send the decode MFL Report message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will copy the recieved number of bytes to the structure of MFL Report.
2. It will assign the UI the values recieved.
******************************************************************************************/
void MainWindow::fnDecodeMflRep()
{

  //  ui->sbMFLRepPrefix->setValue(stMflRep.messHeadRp.messPref);
  //  ui->sbMFLRepSource->setValue(stMflRep.messHeadRp.messSource);
  //  ui->sbMFLRepId->setValue(stMflRep.messHeadRp.messType);
  //  ui->sbMFLRepSeqNum->setValue(stMflRep.messHeadRp.messSeqNum);
  //  ui->sbMFLRepBodyLen->setValue(stMflRep.messHeadRp.bodyLen);
  //  ui->sbMFLRepMflCnt->setValue(stMflRep.mflCount);
#if 0
    for(int rowCnt = 0;rowCnt < ui->tblMFLRep->rowCount();rowCnt++)
    {
        ui->tblMFLRep->item(rowCnt,0)->setText(QString::number(stMflRep.reports[rowCnt].mflId));
        ui->tblMFLRep->item(rowCnt,1)->setText(QString::number(stMflRep.reports[rowCnt].testResult));
        ui->tblMFLRep->item(rowCnt,2)->setText(fnLRUId(stMflRep.reports[rowCnt].lruId,stMflRep.reports[rowCnt].mflId));
        ui->tblMFLRep->item(rowCnt,3)->setText(fnMFLSev(stMflRep.reports[rowCnt].severity));
        ui->tblMFLRep->item(rowCnt,4)->setText(QString::number(stMflRep.reports[rowCnt].aprTime));
    }
#endif
}

/****************************************************************************************
*Function Name:fnDecodeJamRep()
*Description: This function is used to send the decode ECCM Report message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will copy the recieved number of bytes to the structure of ECCM Report.
2. It will assign the UI the values recieved.
******************************************************************************************/
void MainWindow::fnDecodeJamRep()
{

 //   ui->sbJamRepPrefix->setValue(stEccmRep.messHeadRp.messPref);
 //   ui->sbJamRepSource->setValue(stEccmRep.messHeadRp.messSource);
 //   ui->sbJamRepId->setValue(stEccmRep.messHeadRp.messType);
 //   ui->sbJamRepSeqNum->setValue(stEccmRep.messHeadRp.messSeqNum);
 //   ui->sbJamRepBodyLen->setValue(stEccmRep.messHeadRp.bodyLen);
 //   ui->sbJamRepJamCnt->setValue(stEccmRep.jammerCount);
#if 0
    for(int rowCnt = 0;rowCnt < ui->tblJamRep->rowCount();rowCnt++)
    {
        ui->tblJamRep->item(rowCnt,0)->setText(fnJamType(stEccmRep.jammers[rowCnt].type));
        ui->tblJamRep->item(rowCnt,1)->setText(QString::number(stEccmRep.jammers[rowCnt].startAzm));
        ui->tblJamRep->item(rowCnt,2)->setText(QString::number(stEccmRep.jammers[rowCnt].endAzm));
        ui->tblJamRep->item(rowCnt,3)->setText(fnFreqSts(stEccmRep.jammers[rowCnt].freqStatus));
        ui->tblJamRep->item(rowCnt,4)->setText(QString::number(stEccmRep.jammers[rowCnt].elv));
    }
#endif
}

/****************************************************************************************
*Function Name:fnDecodeMaintRep()
*Description: This function is used to send the decode Maintenance message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will copy the recieved number of bytes to the structure of Maintenance.
2. It will assign the UI the values recieved.
******************************************************************************************/
void MainWindow::fnDecodeMaintRep()
{
#if 0

    ui->sbMaintPrefix->setValue(stMaint.messHeadRp.messPref);
    ui->sbMaintSource->setValue(stMaint.messHeadRp.messSource);
    ui->sbMaintId->setValue(stMaint.messHeadRp.messType);
    ui->sbMaintSeqNum->setValue(stMaint.messHeadRp.messSeqNum);
    ui->sbMaintBodyLen->setValue(stMaint.messHeadRp.bodyLen);
    ui->sbMaintRdrVer->setValue(stMaint.swVer);
    ui->sbMaintAntDigFwVer->setValue(stMaint.fwVer);
#endif
}

/****************************************************************************************
*Function Name:fnrdrState()
*Description: This function is used to convert the radar state number to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string as corresponding string.
2. It will return the string.
******************************************************************************************/
QString MainWindow::fnrdrState(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case RDR_STATE_INIT: RetVal = "Init";
        break;
    case RDR_STATE_STBY: RetVal = "StandBy";
        break;
    case RDR_STATE_MAINTAINANCE: RetVal = "Maintenance";
        break;
    case RDR_STATE_OPERATE: RetVal = "Operate";
        break;
    case RDR_STATE_RESET: RetVal = "Reset";
        break;
    case RDR_STATE_IBIT: RetVal = "IBIT";
        break;
    case RDR_STATE_OFF: RetVal = "OFF";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}

/****************************************************************************************
*Function Name:fnrdrMode()
*Description: This function is used to convert the radar Mode number to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string as corresponding string.
2. It will return the string.
******************************************************************************************/
QString MainWindow::fnrdrMode(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case AA_NULL: RetVal = "NULL";
        break;
    case AA_SECTOR: RetVal = "AA_SECTOR";
        break;
    case AA_360: RetVal = "AA_360";
        break;
    case AA_MANUAL: RetVal = "AA_MANUAL";
        break;
    case AA_STT_INT: RetVal = "AA_STT";
        break;
    case AA_ACQ: RetVal = "AA_ACQ";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}

/****************************************************************************************
*Function Name:fnrdrTgtTypeMode()
*Description: This function is used to convert the radar Target type number to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string as corresponding string.
2. It will return the string.
******************************************************************************************/
QString MainWindow::fnrdrTgtTypeMode(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case NORMAL: RetVal = "NORMAL";
        break;
    case TESTTARGET: RetVal = "TESTTARGET";
        break;
    case REPEATER: RetVal = "REPEATER";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}

/****************************************************************************************
*Function Name:fnrdrTx()
*Description: This function is used to convert the radar Tx number to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string as corresponding string.
2. It will return the string.
******************************************************************************************/
QString MainWindow::fnrdrTx(unsigned int val)
{

    QString RetVal;
    switch(val)
    {
    case TX_ON: RetVal = "TX_ON";
        break;
    case TX_OFF: RetVal = "TX_OFF";
        break;
    case TX_DISABLED: RetVal = "TX_DISABLED";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;
}

/****************************************************************************************
*Function Name:fnElevatnCov()
*Description: This function is used to convert the elevaton conversion number to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string as corresponding string.
2. It will return the string.
******************************************************************************************/
QString MainWindow::fnElevatnCov(unsigned int val)
{
    QString RetVal;
    switch(val)
    {
    case DEG20: RetVal = "20 degrees";
        break;
    case DEG30: RetVal = "30 degrees";
        break;
    default: RetVal = "InValid";
        break;
    }
    return RetVal;

}

/****************************************************************************************
*Function Name:fnFreqBand()
*Description: This function is used to convert the Frequency band number to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string as corresponding string.
2. It will return the string.
******************************************************************************************/
QString MainWindow::fnFreqBand(unsigned int val)
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

/****************************************************************************************
*Function Name:fnSTTTarType()
*Description: This function is used to convert the STT Target type number to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string variable as corresponding string to number.
2. It will return the string.
******************************************************************************************/
#if 0
QString MainWindow::fnSTTTarType(unsigned int val)
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
#endif

#if 0
QString MainWindow::fnTWSTarRep(unsigned int val)
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
#endif


/****************************************************************************************
*Function Name:fnSTTTarSt()
*Description: This function is used to convert the STT Target number to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string variable as corresponding string to number.
2. It will return the string.
******************************************************************************************/
#if 0
QString MainWindow::fnSTTTarSt(unsigned int val)
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
#endif

/****************************************************************************************
*Function Name:fnSTTTarQual()
*Description: This function is used to convert the STT Quality number to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string variable as corresponding string to number.
2. It will return the string.
******************************************************************************************/
#if 0
QString MainWindow::fnSTTTarQual(unsigned int val)
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
#endif
/****************************************************************************************
*Function Name:fnLRUId()
*Description: This function is used to convert the LRU Id to its corresponding text.
*Input:unsigned int val -> Input number, unsigned int id -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. If id is a non-zero number, It will take the input number assign the return string
   variable as corresponding string to number.
2. It will return the string.
******************************************************************************************/
//SDS
#if 0
QString MainWindow::fnLRUId(unsigned int val, unsigned int id)
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
#endif

/****************************************************************************************
*Function Name:fnMFLSev()
*Description: This function is used to convert the MFL Id to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string variable as corresponding string to number.
2. It will return the string.
******************************************************************************************/
#if 0
QString MainWindow::fnMFLSev(unsigned int val)
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
#endif

/****************************************************************************************
*Function Name:fnJamType()
*Description: This function is used to convert the Jam Type to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string variable as corresponding string to number.
2. It will return the string.
******************************************************************************************/
//SDS
#if 0
QString MainWindow::fnJamType(unsigned int val)
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
#endif

/****************************************************************************************
*Function Name:fnFreqSts()
*Description: This function is used to convert the Freq Status to its corresponding text.
*Input:unsigned int val -> Input number
*Output:QString -> String corresponding to the input number
*Function calls:none
*Functionality/Algorithm:
1. It will take the input number assign the return string variable as corresponding string to number.
2. It will return the string.
******************************************************************************************/
#if 0
QString MainWindow::fnFreqSts(unsigned int val)
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
#endif



/****************************************************************************************
*Function Name:fnReadUDPRpMessage()
*Description: This function is used to read the UDP data.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will check for bytes avialable for the UDP.
2. If the bytes are available it will read the data from UDP.
3. Check the message type from UDP.
4. call the corresponding decode function according to message type
******************************************************************************************/
#if 0
void MainWindow::fnReadUDPRpMessage()
{

    if(bStartSim == true)
    {
        switch(fnRecieveMessage(RxData))
        {
        case STATUS_REPORT:
        {
            if(ui->chbLogStsRep->isChecked())
            {
//                writeToLogFile((char *)RxData,sizeof(Status),STATUS_REPORT);
                fnLogStatus(&stsRep,1);
            }
        }
            break;
        case STT_TARGET_REPORT:
        {
            if(ui->chbLogSttTarRep->isChecked())
            {
//                writeToLogFile((char *)RxData,sizeof(STTTargetReport),STT_TARGET_REPORT);
                fnLogSTTTargetReport(&stSTTTarRep,1);
            }
        }
            break;
        case TWS_TARGETS_REPORT:
        {
            if(ui->chbLogTwsTarRep->isChecked())
            {
//                writeToLogFile((char *)RxData,sizeof(TWSTargetReport),TWS_TARGETS_REPORT);
                fnLogTWSTargetReportt(&stTWSTarRep,1);
            }
        }
            break;
        case MFL_REPORTS:
        {
            if(ui->chbLogMflRep->isChecked())
            {
//                writeToLogFile((char *)RxData,sizeof(MFLReports),MFL_REPORTS);
                fnLogMFLReport(&stMflRep,1);
            }
        }
            break;
        case ECCM_REPORTS:
        {
            if(ui->chbLogJamRep->isChecked())
            {
//                writeToLogFile((char *)RxData,sizeof(ECCMReport),ECCM_REPORTS);
                fnLogECCMReport(&stEccmRep,1);
            }
        }
            break;
        case MAINTENANCE_REP:
        {
            if(ui->chbLogMaint->isChecked())
            {
//                writeToLogFile((char *)RxData,sizeof(Maintenance),MAINTENANCE_REP);
                fnLogMaintenance(&stMaint,1);
            }
        }
            break;
        default:
        {
            ;
        }
            break;
        }
    }

}
#endif

/****************************************************************************************
*Function Name:fnTimerTimeOut()
*Description: This function is used for timer time out function.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will send the Antenna Position message when It is enabled.
2. It will send the State of Operation message when It is enabled after every one second.
3. It will send the INS message when It is enable after every one second.
******************************************************************************************/
#if 0
void MainWindow::fnTimerTimeOut()
{

    static u_int32 cntr = 0;
    cntr+=TIMER_TIMEOUT;
    if((cntr%TIME_500MSEC) == 0)
    {
      //  ui->lblSytemDateTime->setText(QDateTime::currentDateTime().toString(Qt::ISODate));
    }
    if(bStartSim == true)
    {
        if(ui->chbEnableAnteenaControl->isChecked())
        {
            if(ui->chbFaultGarbageData->isChecked())
            {
                udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortAnt);
            }
            else
            {
                fnSendAnteenaPosition();

                if(ui->chbLogAntPos->isChecked())
                {
//                    if(bFaultHalfPacket)
//                    {
//                        writeToLogFile((char *)&antPos,sizeof(AntPos)/2,ANTENNA_POSITION);
//                    }
//                    else
//                    {
//                        writeToLogFile((char *)&antPos,sizeof(AntPos),ANTENNA_POSITION);
//                    }
                    fnLogAntPos(&antPos,0);
                }
            }

        }
        if((cntr%TIMER_1SEC) == 0)
        {
            if(ui->chbEnableStateOfOperatn->isChecked())
            {
                if(ui->chbFaultGarbageData->isChecked())
                {
                    udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
                }
                else
                {
                    fnSendStateOfOperationMessage();
                    if(ui->chbLogStateOfOper->isChecked())
                    {
//                        if(bFaultHalfPacket)
//                        {
//                            writeToLogFile((char *)&stateOfOperation,sizeof(StateOfOperationCmd)/2,STATEOFOPERATION);
//                        }
//                        else
//                        {
//                            writeToLogFile((char *)&stateOfOperation,sizeof(StateOfOperationCmd),STATEOFOPERATION);
//                        }
                        fnLogStateOfOperationCmd(&stateOfOperation,0);
                    }

                }

            }
            else
            {
                ;
            }
            if(ui->chbEnableInsData->isChecked())
            {
                if(ui->chbFaultGarbageData->isChecked())
                {
                    udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortAnt);
                }
                else
                {
                    fnSendINSDataMessage();
                    if(ui->chbLogINSData->isChecked())
                    {
//                        if(bFaultHalfPacket)
//                        {
//                            writeToLogFile((char *)&InsData,sizeof(INSData)/2,INS_DATA);
//                        }
//                        else
//                        {
//                            writeToLogFile((char *)&InsData,sizeof(INSData),INS_DATA);
//                        }
                        fnLogINSData(&InsData,0);
                    }
                }
            }
            else
            {
                ;
            }
        }
        if((cntr%TIME_500MSEC) == 0)
        {
            fnDecodeStsRep();
            fnDecodeSTTTarRep();
            fnDecodeTWSTargetType();
            fnDecodeMflRep();
            fnDecodeJamRep();
            fnDecodeMaintRep();

            if(ui->chbLogShow->isChecked())
            {
                UpdateLogTbl();
            }
        }
    }
}
#endif


/****************************************************************************************
*Function Name:fnTimerTimeOut()
*Description: This function is used for timer time out function.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will send the Antenna Position message when It is enabled.
2. It will send the State of Operation message when It is enabled after every one second.
3. It will send the INS message when It is enable after every one second.
******************************************************************************************/
void MainWindow::on_pbUpdateStateOfOperatn_clicked()
{
    stateOfOperation.rdrState = fnComboToNumber(ui->cbStateOfOperRdrState->currentText());
    stateOfOperation.rdrMode = fnComboToNumber(ui->cbStateOfOperRdrMode->currentText());
    stateOfOperation.targetTypeMode = fnComboToNumber(ui->cbStateOfOperTargetType->currentText());
    stateOfOperation.rdrTx = fnComboToNumber(ui->cbStateOfOperTx->currentText());
    stateOfOperation.rdrDRange = fnComboToNumber(ui->cbStateOfOperDetectRng->currentText());
    stateOfOperation.rdrDElv = ui->sbStateOfOperDetectEl->value();
    stateOfOperation.spare1 = 0;
    stateOfOperation.rdrTVel = fnComboToNumber(ui->cbStateOfOperTvel->currentText());
    stateOfOperation.rdrFreqBand = fnComboToNumber(ui->cbStateOfOperFreqBand->currentText());
    stateOfOperation.rdrFreqBandChange = fnComboToNumber(ui->cbStateOfOperRdrFreqBandChange->currentText());;
    stateOfOperation.noOfValidSectors = ui->sbStateOfOperRdrnValidSector->value();
    stateOfOperation.sector[0].startAng = ui->sbStateOfOperRdrStartAngSec0->value();
    stateOfOperation.sector[0].endAng = ui->sbStateOfOperRdrEndAngSec0->value();
    stateOfOperation.sector[0].rdrSectorType = fnComboToNumber(ui->cbStateOfOperRdrSectorTypeSec0->currentText());
    //SDS
    stateOfOperation.sector[1].startAng = ui->sbStateOfOperRdrStartAngSec1->value();
    stateOfOperation.sector[1].endAng = ui->sbStateOfOperRdrEndAngSec1->value();
    stateOfOperation.sector[1].rdrSectorType = fnComboToNumber(ui->cbStateOfOperRdrSectorTypeSec1->currentText());
    stateOfOperation.clrTwsCmd = fnComboToNumber(ui->cbStateOfOperRdrClrTwsCmd->currentText());
    stateOfOperation.acqPosReachedState = fnComboToNumber(ui->cbStateOfOperRdrAcqPos->currentText());
}

/****************************************************************************************
*Function Name:on_pbUpdateMisalignmentMess_clicked()
*Description: This function is used update the Mis alignment message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will send the Antenna Position message when It is enabled.
2. It will send the State of Operation message when It is enabled after every one second.
3. It will send the INS message when It is enable after every one second.
******************************************************************************************/
void MainWindow::on_pbUpdateMisalignmentMess_clicked()
{
    misAlign.pedAntRoll = ui->sbMisAlignMessAntRoll->value();
    misAlign.pedAntPitch = ui->sbMisAlignMessAntPitch->value();
    misAlign.pedAntYaw = ui->sbMisAlignMessAntYaw->value();
    misAlign.pedInsRoll = ui->sbMisAlignMessINSRoll->value();
    misAlign.pedInsPitch = ui->sbMisAlignMessINSPitch->value();
    misAlign.pedInsYaw = ui->sbMisAlignMessINSYaw->value();
    misAlign.levArmX = ui->sbMisAlignMessLeverArmX->value();
    misAlign.levArmY = ui->sbMisAlignMessLeverArmY->value();
    misAlign.levArmZ = ui->sbMisAlignMessLeverArmZ->value();
}

/****************************************************************************************
*Function Name:on_pbUpdateInternalDesignation_clicked()
*Description: This function is used update the Internal Designation message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the Internal Designation message structure
******************************************************************************************/
void MainWindow::on_pbUpdateInternalDesignation_clicked()
{
    bool ok;
    qDebug() << ui->leIntDesSttTargetId->text().toULong(&ok,16);
    intDesignation.tId = ui->leIntDesSttTargetId->text().toULong(&ok,16);
}

/****************************************************************************************
*Function Name:on_pbUpdateExternalDesignation_clicked()
*Description: This function is used update the External Designation message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the Internal Designation message structure
******************************************************************************************/
void MainWindow::on_pbUpdateExternalDesignation_clicked()
{

    extDesignation.desigCoordinates = fnComboToNumber(ui->cbExternDesigCoordSel->currentText());
    extDesignation.posX = ui->sbExternalDesigX->value();
    extDesignation.posY = ui->sbExternalDesigY->value();
    extDesignation.posZ = ui->sbExternalDesigZ->value();
    extDesignation.utmX = ui->sbExternalDesigUTMX->value();
    extDesignation.utmY = ui->sbExternalDesigUTMY->value();
    extDesignation.utmZone = ui->sbExternalDesigZone->value();
    extDesignation.alt = ui->sbExternalDesigAlt->value();
    extDesignation.sigmaAlt = ui->sbExternalDesigSigAlt->value();
    extDesignation.lat = ui->sbExternalDesigLat->value();
    extDesignation.Long = ui->sbExternalDesigLon->value();
    extDesignation.velX = ui->sbExternalDesigVx->value();
    extDesignation.velY = ui->sbExternalDesigVy->value();
    extDesignation.velZ = ui->sbExternalDesigVz->value();
    extDesignation.targetTime = ui->sbExternalDesigExtrapTime->value();
    extDesignation.lastUpdateTime = ui->sbExternalDesigUpdateTime->value();
    extDesignation.range = ui->sbExternalDesigRange->value();
    extDesignation.sigmaRange = ui->sbExternalDesigSigRange->value();
    extDesignation.azm = ui->sbExternalDesigAzimuth->value();
    extDesignation.sigmaAzm = ui->sbExternalDesigSigAzm->value();
    extDesignation.elv = ui->sbExternalDesigElevatn->value();
    extDesignation.sigmaElv = ui->sbExternalDesigSigElevatn->value();
    extDesignation.vTrue = ui->sbExternalDesigVel->value();
    extDesignation.sigmaVel = ui->sbExternalDesigSigVel->value();
    extDesignation.vLos = ui->sbExternalDesigVlos->value();
    extDesignation.sigmaVelLos = ui->sbExternalDesigSigVelLos->value();
    extDesignation.vxLos = ui->sbExternalDesigVxLos->value();
    extDesignation.sigmaVelXLos = ui->sbExternalDesigSigVxLos->value();
    extDesignation.rcs = ui->sbExternalDesigRCS->value();
    extDesignation.tgtIdExt = ui->sbExternalDesigId->value();
    extDesignation.rcsTargetType = fnComboToNumber(ui->cbExternalDesigTargetType->currentText());

}

/****************************************************************************************
*Function Name:on_pbSendInternalDesignation_clicked()
*Description: This function is used send the Internal Designation message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the Header of Internal Designation Message
2. It will send the Internal Designation message.
******************************************************************************************/
#if 0

void MainWindow::on_pbSendInternalDesignation_clicked()
{

    if(ui->chbFaultGarbageData->isChecked())
    {
        udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
    }
    else
    {
        fnSendInternalDesignation();
        if(ui->chbLogInterDesig->isChecked())
        {
//            if(bFaultHalfPacket)
//            {
//                writeToLogFile((char *)&intDesignation,sizeof(IntDesig)/2,INTERNALDESIGNATION);
//            }
//            else
//            {
//                writeToLogFile((char *)&intDesignation,sizeof(IntDesig),INTERNALDESIGNATION);
//            }
            fnLogIntDesig(&intDesignation,0);

        }
    }
}
#endif

/****************************************************************************************
*Function Name:on_pbSendRstCmd_clicked()
*Description: This function is used send the Reset Cmd message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the Header of Reset Cmd Message
2. It will send the Reset Cmd message.
******************************************************************************************/
#if 0

void MainWindow::on_pbSendRstCmd_clicked()
{

    if(ui->chbFaultGarbageData->isChecked())
    {
        udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
    }
    else
    {

        fnSendRstCmd();

        if(ui->chbLogRstCmd->isChecked())
        {
//            if(bFaultHalfPacket)
//            {
//                writeToLogFile((char *)&rstRdr,sizeof(ResetRdr)/2,RESET_CMD);
//            }
//            else
//            {
//                writeToLogFile((char *)&rstRdr,sizeof(ResetRdr),RESET_CMD);
//            }
            fnLogResetRdr(&rstRdr,0);
        }
    }
}
#endif




/****************************************************************************************
*Function Name:on_pbSendMisalignmentMess_clicked()
*Description: This function is used send the Misalignment message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the Header of Misalignment Message
2. It will send the Misalignment message.
******************************************************************************************/
#if 0

void MainWindow::on_pbSendMisalignmentMess_clicked()
{

    if(ui->chbFaultGarbageData->isChecked())
    {
        udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
    }
    else
    {
        fnSendMisalignmentMess();

        if(ui->chbLogMisalignMes->isChecked())
        {
//            if(bFaultHalfPacket)
//            {
//                writeToLogFile((char *)&misAlign,sizeof(PedMisAlgn)/2,MISALIGNMENT);
//            }
//            else
//            {
//                writeToLogFile((char *)&misAlign,sizeof(PedMisAlgn),MISALIGNMENT);
//            }
            fnLogPedMisAlgn(&misAlign,0);
        }
    }
}
#endif


/****************************************************************************************
*Function Name:on_pbSendExternalDesignation_clicked()
*Description: This function is used send the External Designation message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the Header of External Designation Message
2. It will send the External Designation message.
******************************************************************************************/
#if 0

void MainWindow::on_pbSendExternalDesignation_clicked()
{
    if(ui->chbFaultGarbageData->isChecked())
    {
        udpSockAnt.writeDatagram((char *)&GarabageData,sizeof(GarabageData),QHostAddress(Ip),PortRp);
    }
    else
    {

        fnSendExternalDesignation();
        if(ui->chbLogExtDesig->isChecked())
        {
//            if(bFaultHalfPacket)
//            {
//                writeToLogFile((char *)&extDesignation,sizeof(ExtDesig)/2,EXTERNAMDESIGNATION);
//            }
//            else
//            {
//                writeToLogFile((char *)&extDesignation,sizeof(ExtDesig),EXTERNAMDESIGNATION);
//            }
            fnLogExtDesig(&extDesignation,0);
        }
    }
}
#endif


/****************************************************************************************
*Function Name:on_pbAntPosition_clicked()
*Description: This function is used send the Anteena Position message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the Header of Anteena Position Message.
2. It will send the Anteena Position message.
******************************************************************************************/
void MainWindow::on_pbAntPosition_clicked()
{
    antPos.azm = ui->sbAntControlAz->value();
    antPos.elv = ui->sbAntControlEl->value();
    antPos.azmRate = ui->sbAntControlAzRate->value();
    antPos.elvRate = ui->sbAntControlElRate->value();
    antPos.scanDir = ui->cbAntControlScanDir->currentIndex();
    antPos.timeTag = ui->sbAntControlAntPosTime->value();
}

/****************************************************************************************
*Function Name:on_pbINSDataUpdate_clicked()
*Description: This function is used update the INS message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the INS Position message.
******************************************************************************************/
void MainWindow::on_pbINSDataUpdate_clicked()
{
    InsData.timeTag = ui->sbINSDataTimeTag->value();
    InsData.utmX = ui->sbINSDataUTMX->value();
    InsData.utmY = ui->sbINSDataUTMY->value();
    InsData.utmZ = ui->sbINSDataUTMZ->value();
    InsData.utmZone = ui->sbINSDataUTMZone->value();
    InsData.trueHdng = ui->sbINSDataTrueHead->value();
    InsData.roll = ui->sbINSDataRoll->value();
    InsData.pitch = ui->sbINSDataPitch->value();
    InsData.yawRate = ui->sbINSDataYawRate->value();
    InsData.rollRate = ui->sbINSDataRollRate->value();
    InsData.pitchRate = ui->sbINSDataPitchRate->value();
    InsData.velX = ui->sbINSDataAvnVelX->value();
    InsData.velY = ui->sbINSDataAvnVelY->value();
    InsData.velZ = ui->sbINSDataAvnVelZ->value();
}


/****************************************************************************************
*Function Name:on_pbUpdateRstCmd_clicked()
*Description: This function is used update the Reset Cmd message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the Reset Cmd Position message.
******************************************************************************************/
void MainWindow::on_pbUpdateRstCmd_clicked()
{
    rstRdr.resetCmd = fnComboToNumber(ui->cbRstCmd->currentText());
}


/****************************************************************************************
*Function Name:writeToLogFile()
*Description: This function will initialise all the structures.
*Input:char *buff
*      unsigned int size
*      char type
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. This function will initialize all the struct.
******************************************************************************************/
void MainWindow::writeToLogFile(char *buff, unsigned int size, unsigned int type)
{
    QFile file;
    //unsigned int RowCnt = tblLog->rowCount();
    QString StrLog;
    //  tblLog->insertRow(RowCnt);

    file.setFileName(Path);
    if(file.open(QIODevice::Append  | QIODevice::Text))
    {
        file.write(QDateTime::currentDateTime().toString(Qt::ISODateWithMs).toStdString().data());
        //       tblLog->setItem(RowCnt,0,new QTableWidgetItem(QDateTime::currentDateTime().toString(Qt::ISODate).toStdString().data()));
        file.write(",");
        switch(type)
        {
        case STATEOFOPERATION:
            file.write("STATEOFOPERATION,");
            //tblLog->setItem(RowCnt,1,new QTableWidgetItem("STATEOFOPERATION"));
            break;
        case INTERNALDESIGNATION:
            file.write("INTERNALDESIGNATION,");
            //tblLog->setItem(RowCnt,1,new QTableWidgetItem("INTERNALDESIGNATION"));
            break;
        case MISALIGNMENT:
            file.write("MISALIGNMENT,");
            //tblLog->setItem(RowCnt,1,new QTableWidgetItem("MISALIGNMENT"));
            break;
        case EXTERNAMDESIGNATION:
            file.write("EXTERNAMDESIGNATION,");
            // tblLog->setItem(RowCnt,1,new QTableWidgetItem("EXTERNAMDESIGNATION"));
            break;
        case RESET_CMD:
            file.write("RESET_CMD,");
            // tblLog->setItem(RowCnt,1,new QTableWidgetItem("RESET_CMD"));
            break;
        case ANTENNA_POSITION:
            file.write("ANTENNA_POSITION,");
            // tblLog->setItem(RowCnt,1,new QTableWidgetItem("ANTENNA_POSITION"));
            break;
        case INS_DATA:
            file.write("INS_DATA,");
            // tblLog->setItem(RowCnt,1,new QTableWidgetItem("INS_DATA"));
            break;
        case STATUS_REPORT:
            file.write("STATUS_REPORT,");
            // tblLog->setItem(RowCnt,1,new QTableWidgetItem("STATUS_REPORT"));
            break;
        case STT_TARGET_REPORT:
            file.write("STT_TARGET_REPORT,");
            // tblLog->setItem(RowCnt,1,new QTableWidgetItem("STT_TARGET_REPORT"));
            break;
        case TWS_TARGETS_REPORT:
            file.write("TWS_TARGETS_REPORT,");
            // tblLog->setItem(RowCnt,1,new QTableWidgetItem("TWS_TARGETS_REPORT"));
            break;
        case MFL_REPORTS:
            file.write("MFL_REPORTS,");
            // tblLog->setItem(RowCnt,1,new QTableWidgetItem("MFL_REPORTS"));
            break;
        case ECCM_REPORTS:
            file.write("ECCM_REPORTS,");
            //  tblLog->setItem(RowCnt,1,new QTableWidgetItem("ECCM_REPORTS"));
            break;
        case MAINTENANCE_REP:
            file.write("MAINTENANCE_REP,");
            //  tblLog->setItem(RowCnt,1,new QTableWidgetItem("MAINTENANCE_REP"));
            break;
        case DETAILED_BIT_REP:
            file.write("DETAILED_BIT_REP,");
            //  tblLog->setItem(RowCnt,1,new QTableWidgetItem("DETAILED_BIT_REP"));
            break;
        default:
            file.write("Unknown type of Msg,");
            break;
        }

        for(unsigned int i =0 ;i < size;i++)
        {
            StrLog.append(QString::number((unsigned char)buff[i],16));
            StrLog.append(" ");
        }
        StrLog.append("\n");
        file.write(StrLog.toStdString().data());
        // tblLog->setItem(RowCnt,2,new QTableWidgetItem(StrLog));
    }
    file.close();
}

#if 0
void MainWindow::UpdateLogTbl()
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
#endif

void MainWindow::on_pbClearLogTable_clicked()
{
    //    QFile file;
    //    file.setFileName(Path);
    //    if(file.open(QIODevice::WriteOnly  | QIODevice::Text))
    //    {
    //        file.write("Time,Type,Data\n");
    //    }
    //    file.close();
    tblLog->deleteLater();
    tblLog = new QTableWidget(ui->tab_4);
    tblLog->setGeometry(10,480,1150,270);
    tblLog->setColumnCount(5);
    tblLog->setColumnWidth(4,750);
    tblLog->setHorizontalHeaderItem(0,new QTableWidgetItem("Time"));
    tblLog->setHorizontalHeaderItem(1,new QTableWidgetItem("Source"));
    tblLog->setHorizontalHeaderItem(2,new QTableWidgetItem("Type"));
    tblLog->setHorizontalHeaderItem(3,new QTableWidgetItem("SequenceNum"));
    tblLog->setHorizontalHeaderItem(4,new QTableWidgetItem("Data"));
    tblLog->show();

}

void MainWindow::on_pbClearStateofOperation_clicked()
{
    ui->cbStateOfOperRdrState->setCurrentIndex(0);
    ui->cbStateOfOperRdrMode->setCurrentIndex(0);
    ui->cbStateOfOperTargetType->setCurrentIndex(0);
    ui->cbStateOfOperTx->setCurrentIndex(0);
    ui->cbStateOfOperDetectRng->setCurrentIndex(0);
    ui->sbStateOfOperDetectEl->setValue(0);
    ui->cbStateOfOperTvel->setCurrentIndex(0);
    ui->cbStateOfOperFreqBand->setCurrentIndex(0);
    ui->cbStateOfOperRdrFreqBandChange->setCurrentIndex(0);
    ui->sbStateOfOperRdrnValidSector->setValue(0);
    ui->sbStateOfOperRdrStartAngSec0->setValue(0);
    ui->sbStateOfOperRdrEndAngSec0->setValue(0);
    ui->cbStateOfOperRdrSectorTypeSec0->setCurrentIndex(0);
    ui->sbStateOfOperRdrStartAngSec1->setValue(0);
    ui->sbStateOfOperRdrEndAngSec1->setValue(0);
    ui->cbStateOfOperRdrSectorTypeSec1->setCurrentIndex(0);
    ui->cbStateOfOperRdrClrTwsCmd->setCurrentIndex(0);
    ui->cbStateOfOperRdrAcqPos->setCurrentIndex(0);

    // This will clear the structure too
    on_pbUpdateStateOfOperatn_clicked();
}

void MainWindow::on_ClearMisalignmentMess_clicked()
{
    ui->sbMisAlignMessAntRoll->setValue(0);
    ui->sbMisAlignMessAntPitch->setValue(0);
    ui->sbMisAlignMessAntYaw->setValue(0);
    ui->sbMisAlignMessINSRoll->setValue(0);
    ui->sbMisAlignMessINSPitch->setValue(0);
    ui->sbMisAlignMessINSYaw->setValue(0);
    ui->sbMisAlignMessLeverArmX->setValue(0);
    ui->sbMisAlignMessLeverArmY->setValue(0);
    ui->sbMisAlignMessLeverArmZ->setValue(0);

    // This will clear the structure too
    on_pbUpdateMisalignmentMess_clicked();
}

void MainWindow::on_pbClearInternalDesignation_clicked()
{
    ui->leIntDesSttTargetId->clear();

    // This will clear the structure too
    on_pbUpdateInternalDesignation_clicked();
}

void MainWindow::on_pbClearRstCmd_clicked()
{
    ui->cbRstCmd->setCurrentIndex(0);

    // This will clear the structure too
    on_pbUpdateRstCmd_clicked();
}

void MainWindow::on_pbClearExternalDesignation_clicked()
{
    ui->cbExternDesigCoordSel->setCurrentIndex(0);
    ui->sbExternalDesigX->setValue(0);
    ui->sbExternalDesigY->setValue(0);
    ui->sbExternalDesigZ->setValue(0);
    ui->sbExternalDesigUTMX->setValue(0);
    ui->sbExternalDesigUTMY->setValue(0);
    ui->sbExternalDesigZone->setValue(0);
    ui->sbExternalDesigAlt->setValue(0);
    ui->sbExternalDesigSigAlt->setValue(0);
    ui->sbExternalDesigLat->setValue(0);
    ui->sbExternalDesigLon->setValue(0);
    ui->sbExternalDesigVx->setValue(0);
    ui->sbExternalDesigVy->setValue(0);
    ui->sbExternalDesigVz->setValue(0);
    ui->sbExternalDesigExtrapTime->setValue(0);
    ui->sbExternalDesigUpdateTime->setValue(0);
    ui->sbExternalDesigRange->setValue(0);
    ui->sbExternalDesigSigRange->setValue(0);
    ui->sbExternalDesigAzimuth->setValue(0);
    ui->sbExternalDesigSigAzm->setValue(0);
    ui->sbExternalDesigElevatn->setValue(0);
    ui->sbExternalDesigSigElevatn->setValue(0);
    ui->sbExternalDesigVel->setValue(0);
    ui->sbExternalDesigSigVel->setValue(0);
    ui->sbExternalDesigVlos->setValue(0);
    ui->sbExternalDesigSigVelLos->setValue(0);
    ui->sbExternalDesigVxLos->setValue(0);
    ui->sbExternalDesigSigVxLos->setValue(0);
    ui->sbExternalDesigRCS->setValue(0);
    ui->sbExternalDesigId->setValue(0);
    ui->cbExternalDesigTargetType->setCurrentIndex(0);

    // This will clear the structure too
    on_pbUpdateExternalDesignation_clicked();
}

void MainWindow::on_pbClearAntPosition_clicked()
{
    ui->sbAntControlAz->setValue(0);
    ui->sbAntControlEl->setValue(0);
    ui->sbAntControlAzRate->setValue(0);
    ui->sbAntControlElRate->setValue(0);
    ui->cbAntControlScanDir->setCurrentIndex(0);
    ui->sbAntControlAntPosTime->setValue(0);

    // This will clear the structure too
    on_pbAntPosition_clicked();
}

void MainWindow::on_pbINSDataClear_clicked()
{
    ui->sbINSDataTimeTag->setValue(0);
    ui->sbINSDataUTMX->setValue(0);
    ui->sbINSDataUTMY->setValue(0);
    ui->sbINSDataUTMZ->setValue(0);
    ui->sbINSDataUTMZone->setValue(0);
    ui->sbINSDataTrueHead->setValue(0);
    ui->sbINSDataRoll->setValue(0);
    ui->sbINSDataPitch->setValue(0);
    ui->sbINSDataYawRate->setValue(0);
    ui->sbINSDataRollRate->setValue(0);
    ui->sbINSDataPitchRate->setValue(0);
    ui->sbINSDataAvnVelX->setValue(0);
    ui->sbINSDataAvnVelY->setValue(0);
    ui->sbINSDataAvnVelZ->setValue(0);

    // This will clear the structure too
    on_pbINSDataUpdate_clicked();
}

void MainWindow::on_pBClearStsReport_clicked()
{
#if 0
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

void MainWindow::on_pBClearSTTTgtReport_clicked()
{
  //  ui->lineEditSttTarRepPrefix->setText(0);
  //  ui->lineEditSttTarRepSource->setText(0);
  //  ui->lineEditSttTarRepId->setText(0);
  //  ui->lineSttTarRepBodyLen->setText(0);
  //  ui->lineEditSttTarRepSeqNum->setText(0);
//    ui->sbSttTarRepTgtCount->setValue(0);
//    ui->dsbSttTarRepDeltaEl->setValue(0);
//    ui->dsbSttTarRepDeltaAz->setValue(0);
//    ui->dsbttTarRepSigDeltaEl->setValue(0);
//    ui->dsbSttTarRepSigDeltaAz->setValue(0);
//    ui->dsbSttTarRepRng->setValue(0);
//    ui->dsbSttTarRepRngDot->setValue(0);
//    ui->sbSttTarRepTimeTag->setValue(0);
//    ui->cbSttTarRepTgtType->setEditText(0);
//    ui->cbSttTarRepTgtSt->setEditText(0);
//    ui->cbSttTarRepTgtQual->setEditText(0);
//    ui->sbSttTarRepINTID->setValue(0);
//    ui->sbSttTarRepEXTID->setValue(0);
//    ui->dsbSttTarRepX->setValue(0);
//    ui->dsbSttTarRepY->setValue(0);
//    ui->dsbSttTarRepZ->setValue(0);
//    ui->sbSttTarRepUTMX->setValue(0);
//    ui->sbSttTarRepUTMY->setValue(0);
//    ui->sbSttTarRepUTMZ->setValue(0);
//    ui->sbSttTarRepUTMZone->setValue(0);
//    ui->dbSbSttTarRepAlt->setValue(0);
//    ui->dbSbSttTarRepSigAlt->setValue(0);
//    ui->dsbSttTarRepVx->setValue(0);
//    ui->dsbSttTarRepVy->setValue(0);
//    ui->dsbSttTarRepVz->setValue(0);
//    ui->sbSttTarRepTgtExtrapTime->setValue(0);
//    ui->sbSttTarRepTgtUpdateTime->setValue(0);
//    ui->dsbSttTarRepRngTTD->setValue(0);
//    ui->dsbSttTarRepSigRngTTD->setValue(0);
//    ui->dsbSttTarRepAz->setValue(0);
//    ui->dsbSttTarRepSigAz->setValue(0);
//    ui->dsbSttTarRepEl->setValue(0);
//    ui->dsbSttTarRepSigEl->setValue(0);
//    ui->dsbSttTarRepVel->setValue(0);
//    ui->dsbSttTarRepSigVel->setValue(0);
//    ui->dsbSttTarRepVLOS->setValue(0);
//    ui->dsbSttTarRepSigVLOS->setValue(0);
//    ui->dsbSttTarRepVxLOS_2->setValue(0);
//    ui->dsbSttTarRepSigVxLOS->setValue(0);
//    ui->dsbSttTarRepSNR->setValue(0);
//    ui->dsbSttTarRepAvRCS->setValue(0);
//    ui->dsbSttTarRepTarAzExtrap->setValue(0);
//    ui->dsbSttTarRepSigTarAzExtrap->setValue(0);
//    ui->dsbSttTarRepTarElExtrap->setValue(0);
//    ui->dsbSttTarRepSigTarElExtrap->setValue(0);

//    // This will clear the structure too
//    memset(&stSTTTarRep,0,sizeof(stSTTTarRep));
}

#if 0

void MainWindow::on_pbClearTWSTgtRep_clicked()
{
    //   ui->sbTwsTarRepPrefix->setValue(0);
 //   ui->sbTwsTarRepSource->setValue(0);
 //   ui->sbTwsTarRepId->setValue(0);
 //   ui->sbTwsTarRepSeqNum->setValue(0);
 //   ui->sbTwsTarRepBodyLen->setValue(0);
 //   ui->sbTwsTarRepNum->setValue(0);

    for(int rowCnt = 0;rowCnt < ui->tblTwsTarRep->rowCount();rowCnt++)
    {
        ui->tblTwsTarRep->item(rowCnt,0)->setText("");
        ui->tblTwsTarRep->item(rowCnt,1)->setText("");
        ui->tblTwsTarRep->item(rowCnt,2)->setText("");
        ui->tblTwsTarRep->item(rowCnt,3)->setText("");
        ui->tblTwsTarRep->item(rowCnt,4)->setText("");
        ui->tblTwsTarRep->item(rowCnt,5)->setText("");
        ui->tblTwsTarRep->item(rowCnt,6)->setText("");
        ui->tblTwsTarRep->item(rowCnt,7)->setText("");
        ui->tblTwsTarRep->item(rowCnt,8)->setText("");
        ui->tblTwsTarRep->item(rowCnt,9)->setText("");
        ui->tblTwsTarRep->item(rowCnt,10)->setText("");
        ui->tblTwsTarRep->item(rowCnt,11)->setText("");
        ui->tblTwsTarRep->item(rowCnt,12)->setText("");
        ui->tblTwsTarRep->item(rowCnt,13)->setText("");
        ui->tblTwsTarRep->item(rowCnt,14)->setText("");
        ui->tblTwsTarRep->item(rowCnt,15)->setText("");
        ui->tblTwsTarRep->item(rowCnt,16)->setText("");
        ui->tblTwsTarRep->item(rowCnt,17)->setText("");
        ui->tblTwsTarRep->item(rowCnt,18)->setText("");
        ui->tblTwsTarRep->item(rowCnt,19)->setText("");
        ui->tblTwsTarRep->item(rowCnt,20)->setText("");
        ui->tblTwsTarRep->item(rowCnt,21)->setText("");
        ui->tblTwsTarRep->item(rowCnt,22)->setText("");
        ui->tblTwsTarRep->item(rowCnt,23)->setText("");
        ui->tblTwsTarRep->item(rowCnt,24)->setText("");
        ui->tblTwsTarRep->item(rowCnt,25)->setText("");
        ui->tblTwsTarRep->item(rowCnt,26)->setText("");
        ui->tblTwsTarRep->item(rowCnt,27)->setText("");
        ui->tblTwsTarRep->item(rowCnt,28)->setText("");
        ui->tblTwsTarRep->item(rowCnt,29)->setText("");
        ui->tblTwsTarRep->item(rowCnt,30)->setText("");
        ui->tblTwsTarRep->item(rowCnt,31)->setText("");
    }

    // This will clear the structure too
    memset(&stTWSTarRep,0,sizeof(stTWSTarRep));
}
#endif

#if 0

void MainWindow::on_pbClearMFLRep_clicked()
{
 //   ui->sbMFLRepPrefix->setValue(0);
  //  ui->sbMFLRepSource->setValue(0);
 //   ui->sbMFLRepId->setValue(0);
 //   ui->sbMFLRepSeqNum->setValue(0);
 //   ui->sbMFLRepBodyLen->setValue(0);
 //   ui->sbMFLRepMflCnt->setValue(0);

    for(int rowCnt = 0;rowCnt < ui->tblMFLRep->rowCount();rowCnt++)
    {
        ui->tblMFLRep->item(rowCnt,0)->setText(0);
        ui->tblMFLRep->item(rowCnt,1)->setText(0);
        ui->tblMFLRep->item(rowCnt,2)->setText(0);
        ui->tblMFLRep->item(rowCnt,3)->setText(0);
        ui->tblMFLRep->item(rowCnt,4)->setText(0);
    }
    // This will clear the structure too
    memset(&stMflRep,0,sizeof(stMflRep));
}
#endif


#if 0

void MainWindow::on_pbClearJamReport_clicked()
{
  //  ui->sbJamRepPrefix->setValue(0);
  //  ui->sbJamRepSource->setValue(0);
  //  ui->sbJamRepId->setValue(0);
  //  ui->sbJamRepSeqNum->setValue(0);
  //  ui->sbJamRepBodyLen->setValue(0);
  //  ui->sbJamRepJamCnt->setValue(0);

    for(int rowCnt = 0;rowCnt < ui->tblJamRep->rowCount();rowCnt++)
    {
        ui->tblJamRep->item(rowCnt,0)->setText("");
        ui->tblJamRep->item(rowCnt,1)->setText("");
        ui->tblJamRep->item(rowCnt,2)->setText("");
        ui->tblJamRep->item(rowCnt,3)->setText("");
        ui->tblJamRep->item(rowCnt,4)->setText("");
    }

    // This will clear the structure too
    memset(&stEccmRep,0,sizeof(stEccmRep));
}
#endif

#if 0

void MainWindow::on_pbClearMaintenance_clicked()
{
    ui->sbMaintPrefix->setValue(0);
    ui->sbMaintSource->setValue(0);
    ui->sbMaintId->setValue(0);
    ui->sbMaintSeqNum->setValue(0);
    ui->sbMaintBodyLen->setValue(0);
    ui->sbMaintRdrVer->setValue(0);
    ui->sbMaintAntDigFwVer->setValue(0);

    // This will clear the structure too
    memset(&stMaint,0,sizeof(stMaint));
}
#endif


void MainWindow::on_pbStartSimulation_clicked()
{
    if(ui->pbStartSimulation->text() == "START SIMULATION")
    {
        bStartSim = true;
        ui->pbStartSimulation->setText("STOP SIMULATION");
    }
    else
    {
        bStartSim = false;
        ui->pbStartSimulation->setText("START SIMULATION");
    }

}


void MainWindow::on_chbFaultHalfPac_toggled(bool checked)
{
    bFaultHalfPacket = checked;
}

#if 0
void MainWindow::fnLogStateOfOperationCmd(StateOfOperationCmd *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogIntDesig(IntDesig *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogPedMisAlgn(PedMisAlgn *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogExtDesig(ExtDesig *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogResetRdr(ResetRdr *Str, int Source)
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
#endif


#if 0
void MainWindow::fnLogAntPos(AntPos *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogINSData(INSData *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogStatus(Status *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogSTTTargetReport(STTTargetReport *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogTWSTargetReportt(TWSTargetReport *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogMFLReport(MFLReports *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogECCMReport(ECCMReport *Str, int Source)
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
#endif

#if 0
void MainWindow::fnLogMaintenance(Maintenance *Str, int Source)
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
#endif
//PSS implement send and close button
#if 0
void MainWindow::on_pbStatusReportSend_clicked()
{


     if(ui->cbStateRepRdrState->currentText()=="Init")
     {
         statusReport.rdrState=1;
        // qDebug()<<"Selection RdrState is-----"<<statusReport.rdrState;
     }
     else if(ui->cbStateRepRdrState->currentText()=="Standby")
     {
         statusReport.rdrState=2;
        // qDebug()<<"Selection RdrState is-----"<<statusReport.rdrState;
     }
     else if(ui->cbStateRepRdrState->currentText()=="Maintenance")
     {
         statusReport.rdrState=3;
        // qDebug()<<"Selection RdrState is-----"<<statusReport.rdrState;
     }
     else if(ui->cbStateRepRdrState->currentText()=="Operate")
     {
         statusReport.rdrState=4;
       //  qDebug()<<"Selection RdrState is-----"<<statusReport.rdrState;
     }
     else if(ui->cbStateRepRdrState->currentText()=="Reset")
     {
         statusReport.rdrState=5;
        // qDebug()<<"Selection RdrState is-----"<<statusReport.rdrState;
     }
     else if(ui->cbStateRepRdrState->currentText()=="IBIT")
     {
         statusReport.rdrState=8;
        // qDebug()<<"Selection RdrState is-----"<<statusReport.rdrState;
     }
     else if(ui->cbStateRepRdrState->currentText()=="Off")
     {
         statusReport.rdrState=9;
         //qDebug()<<"Selection RdrState is-----"<<statusReport.rdrState;
     }


     if(ui->cbStateRepRdrMode->currentText()=="AA_SECTOR")
     {
         statusReport.rdrMode=1;
         //qDebug()<<"Selection RdrMode is-----"<<statusReport.rdrMode;
     }
     else if(ui->cbStateRepRdrMode->currentText()=="AA_360")
     {
         statusReport.rdrMode=2;
        // qDebug()<<"Selection RdrMode is-----"<<statusReport.rdrMode;
     }
     else if(ui->cbStateRepRdrMode->currentText()=="AA_MANUAL")
     {
         statusReport.rdrMode=3;
         //qDebug()<<"Selection RdrMode is-----"<<statusReport.rdrMode;
     }
     else if(ui->cbStateRepRdrMode->currentText()=="AA_STT")
     {
         statusReport.rdrMode=4;
         //qDebug()<<"Selection RdrMode is-----"<<statusReport.rdrMode;
     }
     else if(ui->cbStateRepRdrMode->currentText()=="AA_ACQ")
     {
         statusReport.rdrMode=6;
        // qDebug()<<"Selection RdrMode is-----"<<statusReport.rdrMode;
     }



     if(ui->cbStateRepTgtTypeMode->currentText()=="Normal")
     {
         statusReport.targetTypeMode=0;
        // qDebug()<<"Selection targetTypeMode is-----"<<statusReport.targetTypeMode;
     }
     else if(ui->cbStateRepTgtTypeMode->currentText()=="Test Target")
     {
         statusReport.targetTypeMode=1;
         //qDebug()<<"Selection targetTypeMode is-----"<<statusReport.targetTypeMode;
     }
     else if(ui->cbStateRepTgtTypeMode->currentText()=="Repeater")
     {
         statusReport.targetTypeMode=2;
         //qDebug()<<"Selection targetTypeMode is-----"<<statusReport.targetTypeMode;
     }



     if(ui->cbStateRepTx->currentText()=="OFF")
     {
         statusReport.rdrTx=0;
        // qDebug()<<"Selection rdrTx is-----"<<statusReport.rdrTx;
     }
     else if(ui->cbStateRepTx->currentText()=="ON")
     {
         statusReport.rdrTx=1;
        // qDebug()<<"Selection rdrTx is-----"<<statusReport.rdrTx;
     }
     else if(ui->cbStateRepTx->currentText()=="Disabled")
     {
         statusReport.rdrTx=2;
         //qDebug()<<"Selection rdrTx is-----"<<statusReport.rdrTx;
     }


     if(ui->cbStateRepEleCov->currentText()=="20 degrees")
     {
         statusReport.elvCov=5;
        // qDebug()<<"Selection elvCov is-----"<<statusReport.elvCov;
     }
     else if(ui->cbStateRepEleCov->currentText()=="30 degrees")
     {
         statusReport.elvCov=6;
        // qDebug()<<"Selection elvCov is-----"<<statusReport.elvCov;
     }


     if(ui->cbStateRepTgtVelRej->currentText()=="High")
     {
         statusReport.rdrTVel=0;
         //qDebug()<<"Selection rdrTVel is-----"<<statusReport.rdrTVel;
     }
     else if(ui->cbStateRepTgtVelRej->currentText()=="Low")
     {
         statusReport.rdrTVel=1;
        // qDebug()<<"Selection rdrTVel is-----"<<statusReport.rdrTVel;
     }


     if(ui->cbStateRepFreqBand->currentText()=="BAND A")
     {
         statusReport.rdrFreqBand=0;
        // qDebug()<<"Selection rdrFreqBand is-----"<<statusReport.rdrFreqBand;
     }
     else if(ui->cbStateRepFreqBand->currentText()=="BAND B")
     {
         statusReport.rdrFreqBand=1;
        // qDebug()<<"Selection rdrFreqBand is-----"<<statusReport.rdrFreqBand;
     }
     else if(ui->cbStateRepFreqBand->currentText()=="BAND C")
     {
         statusReport.rdrFreqBand=2;
         //qDebug()<<"Selection rdrFreqBand is-----"<<statusReport.rdrFreqBand;
     }
     else if(ui->cbStateRepFreqBand->currentText()=="BAND D")
     {
         statusReport.rdrFreqBand=3;
        // qDebug()<<"Selection rdrFreqBand is-----"<<statusReport.rdrFreqBand;
     }
     else if(ui->cbStateRepFreqBand->currentText()=="BAND E")
     {
         statusReport.rdrFreqBand=4;
         //qDebug()<<"Selection rdrFreqBand is-----"<<statusReport.rdrFreqBand;
     }
     else if(ui->cbStateRepFreqBand->currentText()=="BAND F")
     {
         statusReport.rdrFreqBand=5;
        // qDebug()<<"Selection rdrFreqBand is-----"<<statusReport.rdrFreqBand;
     }



     if(ui->cbStateRepFreqChngMode->currentText()=="Manual")
     {
         statusReport.rdrFreqBandChange=0;
        // qDebug()<<"Selection rdrFreqBandChange is-----"<<statusReport.rdrFreqBandChange;
     }
     else if(ui->cbStateRepFreqChngMode->currentText()=="Automatic")
     {
         statusReport.rdrFreqBandChange=1;
       //  qDebug()<<"Selection rdrFreqBandChange is-----"<<statusReport.rdrFreqBandChange;
     }

     statusReport.dElvLow = ui->sbStateRepDetectElLow->value();
    // qDebug()<<"Selection dElvLow is-----"<<statusReport.dElvLow;

     statusReport.dElvHigh = ui->sbStateRepDetectElHigh->value();
    // qDebug()<<"Selection dElvHigh is-----"<<statusReport.dElvHigh;

     statusReport.noOfValidSectors = ui->sbStateRepNValSec->value();
    // qDebug()<<"Selection noOfValidSectors is-----"<<statusReport.noOfValidSectors;


     statusReport.sectors[0].startAng = ui->sbStateRepSec0StartAng->value();
    // qDebug()<<"Selection sectors[0].startAng is-----"<<statusReport.sectors[0].startAng;

     statusReport.sectors[0].endAng = ui->sbStateRepSec0EndAng->value();
    // qDebug()<<"Selection sectors[0].endAng is-----"<<statusReport.sectors[0].endAng;

     statusReport.sectors[0].rdrSectorType = ui->cbStateRepSec0Type->currentIndex();
    // qDebug()<<"Selection sectors[0].rdrSectorType is-----"<<statusReport.sectors[0].rdrSectorType;


     statusReport.sectors[1].startAng = ui->sbStateRepSec1StartAng_2->value();
    // qDebug()<<"Selection sectors[1].startAng is-----"<<statusReport.sectors[1].startAng;

     statusReport.sectors[1].endAng = ui->sbStateRepSec1EndAng_2->value();
    // qDebug()<<"Selection sectors[1].endAng is-----"<<statusReport.sectors[1].endAng;

     statusReport.sectors[1].rdrSectorType = ui->cbStateRepSec1Type->currentIndex();
   //  qDebug()<<"Selection sectors[1].rdrSectorType is-----"<<statusReport.sectors[1].rdrSectorType;





     statusReport.utmXRadar = ui->sbStateRepRdrPosUTMX->value();
     //qDebug()<<"Selection utmXRadar is-----"<<statusReport.utmXRadar;

     statusReport.utmYRadar = ui->sbStateRepRdrPosUTMY->value();
     //qDebug()<<"Selection utmYRadar is-----"<<statusReport.utmYRadar;


     statusReport.utmZRadar = ui->sbStateRepRdrPosUTMZ->value();
#if 0
     qDebug()<<"Selection utmZRadar is-----"<<statusReport.utmZRadar;
#endif
/* -------------------------------------------------------------------*/

}
#endif

#if 0
void MainWindow::on_pbSTTtarRepSend_clicked()
{
    sttTargRep.tgtCount = ui->sbSttTarRepTgtCount->value();
    //qDebug()<<"Selection tgtCount is-----"<<sttTargRep.tgtCount;

    sttTargRep.delEl = ui->dsbSttTarRepDeltaEl->value();
    //qDebug()<<"Selection delEl is-----"<<sttTargRep.delEl;

    sttTargRep.delAzm = ui->dsbSttTarRepDeltaAz->value();
    qDebug()<<"Selection delAzm is-----"<<sttTargRep.delAzm;

    sttTargRep.sigmaDelEl = ui->dsbttTarRepSigDeltaEl->value();
    //qDebug()<<"Selection sigmaDelEl is-----"<<sttTargRep.sigmaDelEl;

    sttTargRep.sigmaDelAzm = ui->dsbSttTarRepSigDeltaAz->value();
    //qDebug()<<"Selection sigmaDelAzm is-----"<<sttTargRep.sigmaDelAzm;

    sttTargRep.range = ui->dsbSttTarRepRng->value();
   // qDebug()<<"Selection range is-----"<<sttTargRep.range;

    sttTargRep.rangeDot = ui->dsbSttTarRepRngDot->value();
   // qDebug()<<"Selection rangeDot is-----"<<sttTargRep.rangeDot;

    sttTargRep.timeTag = ui->sbSttTarRepTimeTag->value();
   // qDebug()<<"Selection timeTag is-----"<<sttTargRep.timeTag;

    sttTargRep.sttTrackData.targetType=ui->cbSttTarRepTgtType->currentIndex();
  //  qDebug()<<"Selection targetType is-----"<<sttTrkData.targetType;

    if(ui->cbSttTarRepTgtSt->currentText()=="TRK_INIT")
    {
        sttTargRep.sttTrackData.targetStatus=0;
       // qDebug()<<"Selection targetStatus is-----"<<sttTrkData.targetStatus;
    }
    else if(ui->cbSttTarRepTgtSt->currentText()=="TRK_UPDATE")
    {
        sttTargRep.sttTrackData.targetStatus=1;
       // qDebug()<<"Selection targetStatus is-----"<<sttTrkData.targetStatus;
    }
    else if(ui->cbSttTarRepTgtSt->currentText()=="TRK_DELETE")
    {
         sttTargRep.sttTrackData.targetStatus=2;
        //qDebug()<<"Selection targetStatus is-----"<<sttTrkData.targetStatus;
    }
    else if(ui->cbSttTarRepTgtSt->currentText()=="TRK_EXTRAP")
    {
         sttTargRep.sttTrackData.targetStatus=3;
       // qDebug()<<"Selection targetStatus is-----"<<sttTrkData.targetStatus;
    }



    if(ui->cbSttTarRepTgtQual->currentText()=="TRACK_TGT")
    {
         sttTargRep.sttTrackData.targetQuality=1;
        //qDebug()<<"Selection targetQuality is-----"<<sttTrkData.targetQuality;
    }
    else if(ui->cbSttTarRepTgtQual->currentText()=="Side Lobe Jammer")
    {
         sttTargRep.sttTrackData.targetQuality=5;
        //qDebug()<<"Selection targetQuality is-----"<<sttTrkData.targetQuality;
    }
    else if(ui->cbSttTarRepTgtQual->currentText()=="Main Lobe Jammer")
    {
         sttTargRep.sttTrackData.targetQuality=7;
        //qDebug()<<"Selection targetQuality is-----"<<sttTrkData.targetQuality;
    }


     sttTargRep.sttTrackData.idInt = ui->sbSttTarRepINTID->value();
    //qDebug()<<"Selection idInt is-----"<<sttTrkData.idInt;

     sttTargRep.sttTrackData.idExt = ui->sbSttTarRepEXTID->value();
    //qDebug()<<"Selection idExt is-----"<<sttTrkData.idExt;

     sttTargRep.sttTrackData.posX = ui->dsbSttTarRepX->value();
    //qDebug()<<"Selection posX is-----"<<sttTrkData.posX;

     sttTargRep.sttTrackData.posY = ui->dsbSttTarRepY->value();
    //qDebug()<<"Selection posY is-----"<<sttTrkData.posY;

     sttTargRep.sttTrackData.posZ = ui->dsbSttTarRepZ->value();
    //qDebug()<<"Selection posZ is-----"<<sttTrkData.posZ;

     sttTargRep.sttTrackData.utmX = ui->sbSttTarRepUTMX->value();
    //qDebug()<<"Selection utmX is-----"<<sttTrkData.utmX;

     sttTargRep.sttTrackData.utmY = ui->sbSttTarRepUTMY->value();
    //qDebug()<<"Selection utmY is-----"<<sttTrkData.utmY;

     sttTargRep.sttTrackData.utmZ = ui->sbSttTarRepUTMZ->value();
    //qDebug()<<"Selection utmZ is-----"<<sttTrkData.utmZ;

     sttTargRep.sttTrackData.utmZone = ui->sbSttTarRepUTMZone->value();
    //qDebug()<<"Selection utmZone is-----"<<sttTrkData.utmZone;

     sttTargRep.sttTrackData.alt = ui->dbSbSttTarRepAlt->value();
    //qDebug()<<"Selection alt is-----"<<sttTrkData.alt;

     sttTargRep.sttTrackData.sigmaAlt = ui->dbSbSttTarRepSigAlt->value();
    //qDebug()<<"Selection sigmaAlt is-----"<<sttTrkData.sigmaAlt;

     sttTargRep.sttTrackData.velX = ui->dsbSttTarRepVx->value();
    //qDebug()<<"Selection velX is-----"<<sttTrkData.velX;

     sttTargRep.sttTrackData.velY = ui->dsbSttTarRepVy->value();
    //qDebug()<<"Selection velY is-----"<<sttTrkData.velY;

     sttTargRep.sttTrackData.velZ = ui->dsbSttTarRepVz->value();
    //qDebug()<<"Selection velZ is-----"<<sttTrkData.velZ;

     sttTargRep.sttTrackData.targetTime = ui->sbSttTarRepTgtExtrapTime->value();
    //qDebug()<<"Selection targetTime is-----"<<sttTrkData.targetTime;

     sttTargRep.sttTrackData.lastUpdateTime = ui->sbSttTarRepTgtUpdateTime->value();
    //qDebug()<<"Selection lastUpdateTime is-----"<<sttTrkData.lastUpdateTime;

     sttTargRep.sttTrackData.range = ui->dsbSttTarRepRngTTD->value();
    //qDebug()<<"Selection range is-----"<<sttTrkData.range;

     sttTargRep.sttTrackData.sigmaRange = ui->dsbSttTarRepSigRngTTD->value();
    //qDebug()<<"Selection sigmaRange is-----"<<sttTrkData.sigmaRange;

     sttTargRep.sttTrackData.azm = ui->dsbSttTarRepAz->value();
    //qDebug()<<"Selection azm is-----"<<sttTrkData.azm;

     sttTargRep.sttTrackData.sigmaAzm = ui->dsbSttTarRepSigAz->value();
    //qDebug()<<"Selection sigmaAzm is-----"<<sttTrkData.sigmaAzm;

     sttTargRep.sttTrackData.elv = ui->dsbSttTarRepEl->value();
    //qDebug()<<"Selection elv is-----"<<sttTrkData.elv;

     sttTargRep.sttTrackData.sigmaElv = ui->dsbSttTarRepSigEl->value();
    //qDebug()<<"Selection sigmaElv is-----"<<sttTrkData.sigmaElv;

     sttTargRep.sttTrackData.vTrue = ui->dsbSttTarRepVel->value();
    //qDebug()<<"Selection vTrue is-----"<<sttTrkData.vTrue;

     sttTargRep.sttTrackData.sigmaVel = ui->dsbSttTarRepSigVel->value();
    //qDebug()<<"Selection sigmaVel is-----"<<sttTrkData.sigmaVel;

     sttTargRep.sttTrackData.vLos = ui->dsbSttTarRepVLOS->value();
    //qDebug()<<"Selection vLos is-----"<<sttTrkData.vLos;

     sttTargRep.sttTrackData.sigmaVelLos = ui->dsbSttTarRepSigVLOS->value();
    //qDebug()<<"Selection sigmaVelLos is-----"<<sttTrkData.sigmaVelLos;

     sttTargRep.sttTrackData.vxLos = ui->dsbSttTarRepVxLOS_2->value();
    //qDebug()<<"Selection vxLos is-----"<<sttTrkData.vxLos;

     sttTargRep.sttTrackData.sigmaVelXLos = ui->dsbSttTarRepSigVxLOS->value();
    //qDebug()<<"Selection sigmaVelXLos is-----"<<sttTrkData.sigmaVelXLos;

     sttTargRep.sttTrackData.snr = ui->dsbSttTarRepSNR->value();
    //qDebug()<<"Selection snr is-----"<<sttTrkData.snr;

     sttTargRep.sttTrackData.avgRCS = ui->dsbSttTarRepAvRCS->value();
    //qDebug()<<"Selection avgRCS is-----"<<sttTrkData.avgRCS;

     sttTargRep.sttTrackData.extrapAz = ui->dsbSttTarRepTarAzExtrap->value();
    //qDebug()<<"Selection extrapAz is-----"<<sttTrkData.extrapAz;

     sttTargRep.sttTrackData.sigmaExtrapAz = ui->dsbSttTarRepSigTarAzExtrap->value();
    //qDebug()<<"Selection sigmaExtrapAz is-----"<<sttTrkData.sigmaExtrapAz;

     sttTargRep.sttTrackData.extrapEl = ui->dsbSttTarRepTarElExtrap->value();
    //qDebug()<<"Selection extrapEl is-----"<<sttTrkData.extrapEl;

     sttTargRep.sttTrackData.sigmaExtrapEl = ui->dsbSttTarRepSigTarElExtrap->value();
    //qDebug()<<"Selection sigmaExtrapEl is-----"<<sttTrkData.sigmaExtrapEl;
}
#endif



