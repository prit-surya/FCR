#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <QUdpSocket>

#define TIMER_TIMEOUT    10
#define TIMER_1SEC       1000
#define TIME_500MSEC     500
#define SENDER           "FCR CONTROLLER,"
#define RECEIVER         "FCR,"

typedef int                  int32;
typedef unsigned int         u_int32;

#pragma pack(1)
struct MessHeadForRP
{
    unsigned short messPref;
    unsigned short messSource;
    unsigned short messType;
    unsigned short bodyLen;
    unsigned short messSeqNum;
    unsigned short spare;
};

#pragma pack(1)
struct MessHeadForAnt
{
    u_int32 messId;
    u_int32 messLen;
    u_int32 messTimeTag;
    u_int32 messSeqNum;
    u_int32 messChannId;
};

# pragma pack(1)
struct Sector
{
    int32 startAng;
    int32 endAng;
    u_int32 rdrSectorType;
};

# pragma pack(1)
struct StateOfOperationCmd           // Message Id 0x0101, 1 Hz freq, Sending
{
    MessHeadForRP messHeadRp;
    u_int32 rdrState;
    u_int32 rdrMode;
    u_int32 targetTypeMode;
    u_int32 rdrTx;
    u_int32 rdrDRange;
    float         rdrDElv;
    int32          spare1;
    u_int32 rdrTVel;
    u_int32 rdrFreqBand;
    u_int32 rdrFreqBandChange;
    u_int32 noOfValidSectors;
    Sector        sector[2];
    u_int32 clrTwsCmd;
    u_int32 acqPosReachedState;

};

# pragma pack(1)
struct IntDesig                    // Message Id 0x0104, Sending
{
    MessHeadForRP messHeadRp;
    u_int32       tId;
    u_int32       spare;
};

#pragma pack(1)
struct PedMisAlgn                 // Message Id 0x0105, Once,  Sending
{
 MessHeadForRP messHeadRp;
 float   pedAntRoll;
 float   pedAntPitch;
 float   pedAntYaw;
 float   pedInsRoll;
 float   pedInsPitch;
 float   pedInsYaw;
 int32    levArmX;
 int32    levArmY;
 int32    levArmZ;

};

#pragma pack(1)
struct ExtDesig                // Message Id 0x0106,Sending
{
   MessHeadForRP messHeadRp;
  u_int32  desigCoordinates;
  float           posX;
  float           posY;
  float           posZ;
  int32            utmX;
  int32            utmY;

  int32            utmZone;
  float           alt;
  float           sigmaAlt;
  float           lat;
  float           Long;
  float           velX;
  float           velY;
  float           velZ;
  u_int32  targetTime;
  u_int32  lastUpdateTime;
  float          range;
  float          sigmaRange;
  float          azm;
  float          sigmaAzm;
  float          elv;
  float          sigmaElv;
  float          vTrue;
  float          sigmaVel;
  float          vLos;
  float          sigmaVelLos;
  float          vxLos;
  float          sigmaVelXLos;
  float           rcs;
  u_int32   rcsTargetType;
  u_int32   tgtIdExt;
  float           spare[2];

};

#pragma pack(1)
struct ResetRdr
{
    MessHeadForRP messHeadRp;
    u_int32   resetCmd;
    u_int32   spare[3];

};

#pragma pack(1)
struct AntPos                   // Message Id 0xCEF005DE, Sending
{
  MessHeadForAnt messAntHead;
  float          azm;
  float          elv;
  float          azmRate;
  float          elvRate;
  u_int32  scanDir;
  u_int32  timeTag;

};

#pragma pack(1)
struct INSData                // Message Id  0xCEF005DF, Sending
{
  MessHeadForAnt messAntHead;
  u_int32  timeTag;
  int32           utmX;
  int32           utmY;
  int32           utmZ;
  u_int32  utmZone;
  float          trueHdng;
  float          roll;
  float          pitch;
  float          yawRate;
  float          rollRate;
  float          pitchRate;
  float          velX;
  float          velY;
  float          velZ;
  float          spare[3];

};

#pragma pack(1)
struct Status             // Message Id 0x0201, 1Hz, Recieving
{
 MessHeadForRP   messHeadRp;
 u_int32   rdrState;
 u_int32   rdrMode;
 u_int32   targetTypeMode;
 u_int32   rdrTx;
 u_int32   elvCov;
 u_int32   rdrTVel;
 u_int32   rdrFreqBand;
 u_int32   rdrFreqBandChange;
 int32            dElvLow;
 int32            dElvHigh;
 u_int32   noOfValidSectors;
 Sector          sectors[2];

 int32            utmXRadar;
 int32            utmYRadar;
 float            utmZRadar;

};

#pragma pack(1)
struct STTTrackData
{
 u_int32   targetType;
 u_int32   targetStatus;
 u_int32   targetQuality;
 u_int32   idInt;
 u_int32   idExt;
 float           posX;
 float            posY;
 float            posZ;
 int32             utmX;
 int32            utmY;
 int32            utmZ;
 int32            utmZone;
 float           alt;
 float           sigmaAlt;
 float           velX;
 float           velY;
 float           velZ;
 u_int32   targetTime;
 u_int32   lastUpdateTime;
 float           range;
 float           sigmaRange;
 float           azm;
 float           sigmaAzm;
 float           elv;
 float           sigmaElv;

 float           vTrue;
 float           sigmaVel;
 float           vLos;
 float           sigmaVelLos;
 float           vxLos;
 float           sigmaVelXLos;
 float           snr;
 float           avgRCS;
 float           extrapAz;
 float           sigmaExtrapAz;
 float           extrapEl;
 float           sigmaExtrapEl;
 float           spare[3];

};

#pragma pack(1)
struct STTTargetReport         // Message Id 0x0203, 50Hz,  Recieving
{
  MessHeadForRP   messHeadRp;
  u_int32  tgtCount;
  float          delEl;
  float          delAzm;
  float          sigmaDelEl;
  float          sigmaDelAzm;
  float          range;
  float          rangeDot;
  u_int32  timeTag;
  STTTrackData  sttTrackData;

};

#pragma pack(1)
struct TWSTrackData
{
 u_int32   targetType;
 u_int32   targetStatus;
 u_int32   spare;
 u_int32   idInt;
 u_int32   idExt;
 float           posX;
 float           posY;
 float           posZ;
 u_int32   utmX;
 u_int32   utmY;
 int32            utmZ;
 u_int32   utmZone;
 float           alt;
 float           sigmaAlt;
 float           velX;
 float           velY;
 float           velZ;
 u_int32   targetTime;
 u_int32   lastUpdateTime;
 float           range;
 float           sigmaRange;
 float           azm;
 float           sigmaAzm;
 float           elv;
 float           sigmaElv;

 float           vTrue;
 float           sigmaVel;
 float           vLos;
 float           sigmaVelLos;
 float           vxLos;
 float           sigmaVelXLos;
 float           snr;
 float           avgRCS;
 float           sdToExt;
 float           spare1[6];

};

#pragma pack(1)
struct TWSTargetReport            // Message Id 0x0204, 1Hz in TWS and 10 Hz in Acq, Recieving
{
  MessHeadForRP messHeadRp;
  u_int32 noOfTgt;
  TWSTrackData  twsTracks[120];

};

#pragma pack(1)
struct MFLReport
{
 u_int32   mflId;
 int32            testResult;
 unsigned short  lruId;
 unsigned short   severity;
 u_int32   aprTime;
 int32            spare[2];

};

#pragma pack(1)
struct MFLReports              // Message Id 0x0205,1 Hz, Recieving
{
 MessHeadForRP messHeadRp;
 u_int32   mflCount;
 MFLReport   reports[20];

};

#pragma pack(1)
struct JamReport
{
 u_int32   type;
 int32            startAzm;
 int32            endAzm;
 u_int32   freqStatus;
 int32            elv;
 int32            spare[2];

};

#pragma pack(1)
struct ECCMReport          // Message Id 0x0206, 1 Hz, Recieving
{
  MessHeadForRP messHeadRp;
  u_int32  jammerCount;
  JamReport  jammers[16];

};

#pragma pack(1)
struct Maintenance        // Message Id 0x0207,once, Recieving
{
  MessHeadForRP messHeadRp;
  float  swVer;
  float  fwVer;
  float  spare[6];

};

enum RDR_STATE
{
    RDR_STATE_INIT = 1,
    RDR_STATE_STBY = 2,
    RDR_STATE_MAINTAINANCE = 3,
    RDR_STATE_OPERATE =4,
    RDR_STATE_RESET = 5,
    RDR_STATE_IBIT = 8,
    RDR_STATE_OFF = 9

};

enum RDR_MODE
{
  AA_NULL = 0,
  AA_SECTOR = 1,
  AA_360 = 2,
  AA_MANUAL = 3,
  AA_STT_INT = 4,
  AA_ACQ = 6,
  AA_STT_EXT = 7,
  AA_STT_EXT_RST = 8
};

enum TGT_TYPE_MODE
{
    NORMAL = 0,
    TESTTARGET = 1,
    REPEATER = 2
};

enum STT_TGT_TYPE
{
    AIR_NORMAL = 1,
    HH = 2,
    TOJ = 3
};

enum STT_TGT_ST
{
    TRK_INIT = 0,
    TRACK_UPDATE = 1,
    TRACK_DELETE = 2,
    TRACK_EXTRAP = 3,
};

enum STT_TGT_QUAL
{
    TRACK_TGT = 1,
    SLIDE_LOBE_JAMMER = 5,
    MAIN_LOBE_JAMMER = 7

};

enum DETECTION_RNG
{
    KM5  = 1,
    KM10 = 2,
    KM20 = 3,
    KM40 = 4

};
enum TX
{
    TX_OFF = 0,
    TX_ON = 1,
    TX_DISABLED = 2
};

enum ELEVATION_COV
{
  DEG20 = 5,
  DEG30 = 6
};

enum FREQ_BAND
{
    BAND_A = 0,
    BAND_B = 1,
    BAND_C = 2,
    BAND_D = 3,
    BAND_E = 4,
    BAND_F = 5
};

enum LRU
{
  SYSTEM = 0,
  RP = 1,
  ANT = 2,
  PROCESSING_COMP = 3
};

enum MFL_SEVERITY
{
    INFORMATION = 1,
    WARNING = 2,
    FAIL = 3
};

enum JAMMER_TYPE
{
    NO_JAM = 0,
    MAIN_LOBE_JAM = 1,
    SLIDE_LOBE_JAM = 2,
    STL = 3
};

enum FREQ_STS
{
    DEFAULT = 0,
    OCCURED = 1,
    RECOMMENDED = 2
};


#define MESSAGE_PREFIX                  0xDBCA
#define MESS_SOURCE_RADAR               0x1
#define MESS_SOURCE_C2                  0x2
#define VERSION                         "V03"

enum MessageType
{
  STATEOFOPERATION = 0x101,
  INTERNALDESIGNATION = 0x104,
  MISALIGNMENT = 0x105,
  EXTERNAMDESIGNATION = 0x106,
  RESET_CMD = 0x107,
  ANTENNA_POSITION = 0xCEF005DE,
  INS_DATA = 0xCEF005DF,
  STATUS_REPORT = 0x201,
  STT_TARGET_REPORT = 0x203,
  TWS_TARGETS_REPORT = 0x204,
  MFL_REPORTS = 0x205,
  ECCM_REPORTS = 0x206,
  MAINTENANCE_REP = 0x207,
  DETAILED_BIT_REP = 0x588
};

extern QUdpSocket udpSockRp;
extern QUdpSocket udpSockAnt;
extern unsigned short PortRp;
extern unsigned short PortAnt;
extern QString Ip;
extern QString Path;
extern StateOfOperationCmd  stateOfOperation;
extern PedMisAlgn           misAlign;
extern IntDesig             intDesignation;
extern ExtDesig             extDesignation;
extern AntPos               antPos;
extern INSData              InsData;
extern ResetRdr             rstRdr;
extern Status               stsRep;
extern STTTargetReport      stSTTTarRep;
extern TWSTargetReport      stTWSTarRep;
extern MFLReports           stMflRep;
extern ECCMReport           stEccmRep;
extern Maintenance          stMaint;
extern char  bFaultHalfPacket;

int fnSendStateOfOperationMessage();
int fnSendAnteenaPosition();
int fnSendINSDataMessage();
void fnSendInternalDesignation();
void fnSendRstCmd();
void fnSendMisalignmentMess();
void fnSendExternalDesignation();
MessageType fnRecieveMessage(char *RxData);
void fnSendStatusReport();
void fnSendSttTargetReport();
void fnTWSTargetReport();
void fnMFLReport();
void fnECCMReport();
#endif // STRUCTURES_H

