#include "structures.h"
#include <QTime>

/****************************************************************************************
*Function Name:fnSendStateOfOperationMessage()
*Description: This function is used to send the state of operation message.
*Input:void
*Output:int -> Number of bytes sent
*Function calls:none
*Functionality/Algorithm:
1. It will initialize the header of state of operation message.
2. It will it will send the structure of state of operation message.
******************************************************************************************/
int fnSendStateOfOperationMessage()
{
    int sentBytes;
    stateOfOperation.messHeadRp.messPref = 0xDBCA;
    stateOfOperation.messHeadRp.messSource = 0x2;
    stateOfOperation.messHeadRp.messType = 0x101;
    stateOfOperation.messHeadRp.bodyLen = sizeof(StateOfOperationCmd);
    stateOfOperation.messHeadRp.messSeqNum++;
    stateOfOperation.messHeadRp.spare =0;
    if(bFaultHalfPacket)
    {
        sentBytes =  udpSockRp.writeDatagram((char *)&stateOfOperation,sizeof(stateOfOperation)/2,QHostAddress(Ip),PortRp);
    }
    else
    {
        sentBytes =  udpSockRp.writeDatagram((char *)&stateOfOperation,sizeof(stateOfOperation),QHostAddress(Ip),PortRp);
    }
    return sentBytes;
}

/****************************************************************************************
*Function Name:fnSendAnteenaPosition()
*Description: This function is used to send the Anteena position message.
*Input:void
*Output:int -> Number of bytes sent
*Function calls:none
*Functionality/Algorithm:
1. It will initialize the header of Anteena position message.
2. It will it will send the structure of Anteena position message.
******************************************************************************************/
int fnSendAnteenaPosition()
{
    int sentBytes;
    QTime time;
    antPos.messAntHead.messId = 0xCEF005DE;
    antPos.messAntHead.messLen = sizeof(AntPos);
    antPos.messAntHead.messTimeTag =  time.msecsSinceStartOfDay();
    antPos.messAntHead.messSeqNum++;
    antPos.messAntHead.messChannId = 3;

    if(bFaultHalfPacket)
    {
        sentBytes =  udpSockAnt.writeDatagram((char *)&antPos,sizeof(antPos)/2,QHostAddress(Ip),PortAnt);
    }
    else
    {
        sentBytes =  udpSockAnt.writeDatagram((char *)&antPos,sizeof(antPos),QHostAddress(Ip),PortAnt);
    }

    return sentBytes;
}

/****************************************************************************************
*Function Name:fnSendINSDataMessage()
*Description: This function is used to send the INS message.
*Input:void
*Output:int -> Number of bytes sent
*Function calls:none
*Functionality/Algorithm:
1. It will initialize the header of INS message.
2. It will it will send the structure of INS message.
******************************************************************************************/
int fnSendINSDataMessage()
{
    int sentBytes;
    QTime time;
    InsData.messAntHead.messId = 0xCEF005DF;
    InsData.messAntHead.messLen = sizeof(INSData);
    InsData.messAntHead.messTimeTag =  time.msecsSinceStartOfDay();
    InsData.messAntHead.messSeqNum++;
    InsData.messAntHead.messChannId = 3;


    if(bFaultHalfPacket)
    {
        sentBytes =  udpSockAnt.writeDatagram((char *)&InsData,sizeof(InsData)/2,QHostAddress(Ip),PortAnt);
    }
    else
    {
        sentBytes =  udpSockAnt.writeDatagram((char *)&InsData,sizeof(InsData),QHostAddress(Ip),PortAnt);
    }

    return sentBytes;
}

/****************************************************************************************
*Function Name:fnSendInternalDesignation()
*Description: This function is used send the Internal Designation message.
*Input:void
*Output:void
*Function calls:none
*Functionality/Algorithm:
1. It will update the Header of Internal Designation Message
2. It will send the Internal Designation message.
******************************************************************************************/
void fnSendInternalDesignation()
{
    intDesignation.messHeadRp.messPref = 0xDBCA;
    intDesignation.messHeadRp.messSource = 0x2;
    intDesignation.messHeadRp.messType = 0x104;
    intDesignation.messHeadRp.bodyLen = sizeof(IntDesig);
    intDesignation.messHeadRp.messSeqNum++;
    intDesignation.messHeadRp.spare =0;

    if(bFaultHalfPacket)
    {
        udpSockRp.writeDatagram((char *)&intDesignation,sizeof(intDesignation)/2,QHostAddress(Ip),PortRp);
    }
    else
    {
        udpSockRp.writeDatagram((char *)&intDesignation,sizeof(intDesignation),QHostAddress(Ip),PortRp);
    }

}

void fnSendRstCmd()
{
    rstRdr.messHeadRp.messPref = 0xDBCA;
    rstRdr.messHeadRp.messSource = 0x2;
    rstRdr.messHeadRp.messType = 0x107;
    rstRdr.messHeadRp.bodyLen = sizeof(ResetRdr);
    rstRdr.messHeadRp.messSeqNum++;
    rstRdr.messHeadRp.spare = 0;

    if(bFaultHalfPacket)
    {
        udpSockRp.writeDatagram((char * )&rstRdr,sizeof(rstRdr)/2,QHostAddress(Ip),PortRp);
    }
    else
    {
        udpSockRp.writeDatagram((char * )&rstRdr,sizeof(rstRdr),QHostAddress(Ip),PortRp);
    }
}

void fnSendMisalignmentMess()
{
    misAlign.messHeadRp.messPref = 0xDBCA;
    misAlign.messHeadRp.messSource = 0x2;
    misAlign.messHeadRp.messType = 0x105;
    misAlign.messHeadRp.bodyLen =  sizeof(PedMisAlgn);
    misAlign.messHeadRp.messSeqNum++;
    misAlign.messHeadRp.spare =0;

    if(bFaultHalfPacket)
    {
        udpSockRp.writeDatagram((char *)&misAlign,sizeof(misAlign)/2,QHostAddress(Ip),PortRp);
    }
    else
    {
        udpSockRp.writeDatagram((char *)&misAlign,sizeof(misAlign),QHostAddress(Ip),PortRp);
    }
}

void fnSendExternalDesignation()
{
    extDesignation.messHeadRp.messSource = 0x2;
    extDesignation.messHeadRp.messType = 0x106;
    extDesignation.messHeadRp.bodyLen = sizeof(ExtDesig);
    extDesignation.messHeadRp.messSeqNum++;
    extDesignation.messHeadRp.spare =0;

    if(bFaultHalfPacket)
    {
        udpSockRp.writeDatagram((char *)&extDesignation,sizeof(extDesignation)/2,QHostAddress(Ip),PortRp);
    }
    else
    {
        udpSockRp.writeDatagram((char *)&extDesignation,sizeof(extDesignation),QHostAddress(Ip),PortRp);
    }


}

MessageType fnRecieveMessage(char *RxData)
{
    QHostAddress    Addr;
    unsigned short  Port;
    int size;
    unsigned short MessType = 0;

        if(udpSockRp.hasPendingDatagrams())
        {
            size = udpSockRp.readDatagram((char *)RxData,20000,&Addr,&Port);
            if(size > 0)
            {
                MessType = RxData[4] | (RxData[5] << 8);
                switch(MessType)
                {
                case STATUS_REPORT:
                {
                    memcpy(&stsRep,RxData,sizeof(Status));

                }
                break;
                case STT_TARGET_REPORT:
                {
                    memcpy(&stSTTTarRep,RxData,sizeof(STTTargetReport));

                }
                    break;
                case TWS_TARGETS_REPORT:
                {
                    memcpy(&stTWSTarRep,RxData,sizeof(TWSTargetReport));

                }
                    break;
                case MFL_REPORTS:
                {
                    memcpy(&stMflRep,RxData,sizeof(MFLReports));

                }
                    break;
                case ECCM_REPORTS:
                {
                    memcpy(&stEccmRep,RxData,sizeof(ECCMReport));
                }
                    break;
                case MAINTENANCE_REP:
                {
                    memcpy(&stMaint,RxData,sizeof(Maintenance));
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
    return (MessageType)MessType;
}

void fnSendStatusReport(){


    stsRep.messHeadRp.messPref = 0xDBCA;
    stsRep.messHeadRp.messSource = 0x01;
    stsRep.messHeadRp.messType = 0x0201;
    stsRep.messHeadRp.bodyLen = sizeof(Status);
    stsRep.messHeadRp.messSeqNum++;
    stsRep.messHeadRp.spare=0;


    udpSockRp.writeDatagram((char *)&stsRep,sizeof(stsRep),QHostAddress(Ip),PortRp);

}

void fnSendSttTargetReport(){

    stSTTTarRep.messHeadRp.messPref = 0xDBCA;
    stSTTTarRep.messHeadRp.messSource = 0x01;
    stSTTTarRep.messHeadRp.messType = 0x0203;
    stSTTTarRep.messHeadRp.bodyLen = sizeof(STTTargetReport);
    stSTTTarRep.messHeadRp.messSeqNum++;
    stSTTTarRep.messHeadRp.spare=0;

    udpSockRp.writeDatagram((char *)&stSTTTarRep,sizeof(stSTTTarRep),QHostAddress(Ip),PortRp);

}

void fnSendTWSTargetReport(){

    stTWSTarRep.messHeadRp.messPref = 0xDBCA;
    stTWSTarRep.messHeadRp.messSource = 0x01;
    stTWSTarRep.messHeadRp.messType = 0x0204;
    stTWSTarRep.messHeadRp.bodyLen = sizeof(TWSTargetReport);
    stTWSTarRep.messHeadRp.messSeqNum++;
    stTWSTarRep.messHeadRp.spare=0;


    udpSockRp.writeDatagram((char *)&stTWSTarRep,sizeof(stTWSTarRep),QHostAddress(Ip),PortRp);

}

void fnSendMFLReport(){

    stMflRep.messHeadRp.messPref = 0xDBCA;
    stMflRep.messHeadRp.messSource = 0x01;
    stMflRep.messHeadRp.messType = 0x0205;
    stMflRep.messHeadRp.bodyLen = sizeof(MFLReports);
    stMflRep.messHeadRp.messSeqNum++;
    stMflRep.messHeadRp.spare=0;

    udpSockRp.writeDatagram((char *)&stMflRep,sizeof(stMflRep),QHostAddress(Ip),PortRp);

}

void fnSendECCMReport(){

    stEccmRep.messHeadRp.messPref = 0xDBCA;
    stEccmRep.messHeadRp.messSource = 0x01;
    stEccmRep.messHeadRp.messType = 0x0206;
    stEccmRep.messHeadRp.bodyLen = sizeof(ECCMReport);
    stEccmRep.messHeadRp.messSeqNum++;
    stEccmRep.messHeadRp.spare=0;

    udpSockRp.writeDatagram((char *)&stEccmRep,sizeof(stEccmRep),QHostAddress(Ip),PortRp);

}

void fnSendMaintenance(){

    stMaint.messHeadRp.messPref = 0xDBCA;
    stMaint.messHeadRp.messSource = 0x01;
    stMaint.messHeadRp.messType = 0x0207;
    stMaint.messHeadRp.bodyLen = sizeof(Maintenance);
    stMaint.messHeadRp.messSeqNum++;
    stMaint.messHeadRp.spare=0;

    udpSockRp.writeDatagram((char *)&stMaint,sizeof(stMaint),QHostAddress(Ip),PortRp);

}
