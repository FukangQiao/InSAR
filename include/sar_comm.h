#pragma once
#ifndef _SARCOMM_H_INCLUDED
#define _SARCOMM_H_INCLUDED
#include "globalparam.h"
//#include "../../../Include/REGISStruct.h"

struct Para
{
	double AziDis;      //ͼ��λ��������
	double TSpace_R;	//ͼ�������������
	double AziStartTime;	//ͼ��λ����ʼ��ʱ��
	double RanStartTime;	//ͼ���������ʼ��ʱ��
	double frequency;	//�����ź�������Ƶ
};

typedef enum {
	COMPLEX_IMAGE,		/* complex image */
	PHASE_IMAGE,		/* phase image */
	DIFF_PHASE_IMAGE //Differential phase image
} Esip_LayerType;

typedef enum {
	CU4,		//�޷��Ÿ���,ʵ�鲿��4λ,��ʵ�����鲿
	CU5,		//�޷��Ÿ���,ʵ�鲿��5λ,��ʵ�����鲿
	CU8,		//�޷��Ÿ���,ʵ�鲿��8λ,��ʵ�����鲿
	CU16,		//�޷��Ÿ���,ʵ�鲿��16λ,��ʵ�����鲿
	CU32,		//�޷��Ÿ���,ʵ�鲿��32λ,��ʵ�����鲿
	CS4,		//�з��Ÿ���,ʵ�鲿��4λ,��ʵ�����鲿
	CS5,		//�з��Ÿ���,ʵ�鲿��5λ,��ʵ�����鲿
	CS8,		//�з��Ÿ���,ʵ�鲿��8λ,��ʵ�����鲿
	CS16,		//�з��Ÿ���,ʵ�鲿��16λ,��ʵ�����鲿
	CS32,		//�з��Ÿ���,ʵ�鲿��32λ,��ʵ�����鲿
	S16,		//�з���16λʵ��
	S32		    //�з���32λʵ��
} Esip_PixelType;

typedef enum {
	HH,
	HV,
	VH,
	VV
} Esip_Polarization; //������ʽ

typedef enum {
	STRIPE,	
	BEAMING
} Esip_SARMode;

typedef enum {
	RIGHT,	
	LEFT
} Esip_Look; //����������

/* -------------------------------------------------------------------- */
/* Class date     ʱ��ṹ��                                            */                                            
/* -------------------------------------------------------------------- */
#pragma pack (2)
typedef struct {
	long year;			//��
	long month;			//��
	long date;			//��
	long hour;			//ʱ
	long minute;		//��
	double second;      //��
} Esip_ClassDate;

/* -------------------------------------------------------------------- */
/* Class beam_position ��λ�����ṹ��                                   */                                            
/* -------------------------------------------------------------------- */
typedef struct {
	double prf;			//�����ظ�Ƶ��/Hz
	double lookAngle;	//�����������ӽ�/rad
	double spreadRatio;	//����������չ��ϵ��k2/�޵�λ
	double pulseWidth;	//�����ź�����/s
	double bandWidth;	//�����źŴ���/Hz
	double peakPower;	//�����źŷ�ֵ����/W
	double sampleFrequency;	//�����źŲ���Ƶ��/Hz
	double Da;	           //���߷�λ��ߴ�/m ����λ�������Ϊ0.886*lamda/Da
	double Dr;	           //���߾�����ߴ�/m �������������Ϊk2*0.886*lamda/Dr
	double spotAngle;	 //������λ��ǰ��ɨ�跶Χ/rad������ֵ+-0.6��/����ʱ��
	double slipFactor;   //��������
} Esip_Classbeam_position;

/* -------------------------------------------------------------------- */
/* Class sar_pos�״�������λ���Ĳ������ݽṹ�壨���Ĺ�������ϵ��        */                                            
/* -------------------------------------------------------------------- */
typedef struct {
	double gpsTime;			//GPSʱ��/s
	double positionX;	//λ��x/m
	double positionY;	//λ��y/m
	double positionZ;	//λ��z/m
	double velocityX;	//�ٶ�vx/ m/s
	double velocityY;	//�ٶ�vy/ m/s
	double velocityZ;	//�ٶ�vz/ m/s
} Esip_ClassSar_pos;

/* -------------------------------------------------------------------- */
/* Class sar_attitude������̬�ǲ�������        */                                            
/* -------------------------------------------------------------------- */
typedef struct {
	double gpsTime;			//GPSʱ��/s
	double rollAngle;	//�����
	double pitchAngle;	//������
	double yawAngle;	//��ƫ��
} Esip_ClassSar_attitude;

/* -------------------------------------------------------------------- */
/* Class tag ��־�����ݽṹ��        */                                            
/* -------------------------------------------------------------------- */
typedef struct {
	long no;			 //��־�����
	double pixelAzimuth; //��ͼ���еķ�λ������ֵ/Pixel
	double pixelRange;	 //��ͼ���еľ�����������ֵ/Pixel
	double coordinateX;	 //�ع�����x/m
	double coordinateY;	 //�ع�����y/m
	double coordinateZ;	 //�ع�����z/m
} Esip_ClassTag;

/* -------------------------------------------------------------------- */
/*      Structure definitions from eprj.h, with some type               */
/*      simplifications.                                                */
/* -------------------------------------------------------------------- */
typedef struct {
	double x;			/* coordinate x-value */
	double y;			/* coordinate y-value */
} Eprj_Coordinate;


/* -------------------------------------------------------------------- */
/*      Esip_HeaderTag structure               */
/* -------------------------------------------------------------------- */
typedef struct {
	char label[16];			/* label:ESIP_HEADER_TAG */
	GInt32 headerPos;		/* point to Esip_file node */
} Esip_HeaderTag;

/* -------------------------------------------------------------------- */
/*      Esip_HeaderTag structure               */
/* -------------------------------------------------------------------- */
#pragma pack (2)
typedef struct {
	short version;			//version
	short type;		//file type 
	GInt32 freeListPtr;    //the points to list of freed blocks
	GInt32 rootEntryPtr;
	GUInt16 entryHeaderLength;
	GUInt32 dictionaryPtr;
} Esip_File;

/* -------------------------------------------------------------------- */
/*      Esip_Entry structure  ͷ����Ϣ             */
/* -------------------------------------------------------------------- */
#pragma pack (1)
typedef struct {
	GUInt32 nextPtr;	  //next node
	GUInt32 prevPtr;	  //previous node 
	GUInt32 parentPtr;    //parent node
	GUInt32 childPtr;     //child node
	GUInt32 dataPtr;     //data pointer
	GUInt32 datasize;    //data size
	char name[64];   //node name
	char type[32];   //node type
	ModTime modeTime;
} Esip_Entry;


/* -------------------------------------------------------------------- */
/*      Img_Layer structure               */
/* -------------------------------------------------------------------- */
typedef struct {
	double longitudeSceneLocation;			//���ȹ۲�����
	double latitudeSceneLocation;       	//ά�ȹ۲����� 
	long   azimuthWidth;    //��λ�����ص���/����
	long   rangHeight;  //���������ص���/����
	Esip_LayerType layerType;
	int pixelType;
	long blockWidth;
	long blockheight;
} Esip_ImgLayer;

/* -------------------------------------------------------------------- */
/*      Esip_ClassBlock structure               */
/* -------------------------------------------------------------------- */
typedef struct {
	GUInt32 offset;			//points to the byte location in the file
	long size;  //The number of bytes in the block
} Esip_ClassBlock;

/* -------------------------------------------------------------------- */
/*      ImgBlock structure               */
/* -------------------------------------------------------------------- */
typedef struct {
	long   numvirtualblocks;    //The number of blocks in this layer
	long   numobjectsperblock;  //The number of pixels represented by one block
	Esip_ClassBlock Block[32];
	ModTime modeTime;
} Esip_ImgBlock;

/* -------------------------------------------------------------------- */
/*      LayerInfo structure               */
/* -------------------------------------------------------------------- */
typedef struct {
	short   dataSimulation;    //���ݷ��淽ʽ:��������1;��ʵ����2
	double  azimuthSample;     //ͼ��λ��������/��
	double  rangeSample;       //ͼ�������������/��
	double  azimuthStartTime;  //ͼ��λ����ʼ��ʱ��
	double  rangeStartTime;    //ͼ���������ʼ��ʱ��
} Esip_LayerInfo;

/* -------------------------------------------------------------------- */
/*      SensorInfo ��������Ϣ�ڵ�               */
/* -------------------------------------------------------------------- */
typedef struct {
	Esip_Polarization polarization; //������ʽ
	Esip_SARMode sarMode;          //����ģʽ
	Esip_ClassDate TimeStart;      //�ز���ʼʱ��
	long   numberOfBeamPosition;  //����ģʽ��λ��
	Esip_Classbeam_position transmitter; //�����ǲ�λ����
	Esip_Classbeam_position receiver; //�������ǲ�λ����
	double  carrierFrequency;       //�����ź�������Ƶ/Hz
	short signModulationFrequency; //�����źŵ�Ƶ�ʼ���:��1����1
	double squintTransmitter; //��������б�ӽ�/rad
	double squintReceiver;    //��������б�ӽ�/rad
	Esip_Look look;           //����������
	double  resolutionAzimuth;  //���۷�λ�ֱ���
	double  resolutionRange;  //����б��ֱ���
	//Esip_ClassDate timeStartTransmitter; //�����״���λ�������ݷ�����ʼʱ��
	//long sampleNumberTransmitter; //�����״���λ����������
	//double sampleIntervalTransmitter; //�����״���λ�������ݲ������
	//Esip_ClassSar_pos *antennaPosTransmitter; //�����״���λ��������
	//Esip_ClassDate timeStartReceiver; //�����״���λ�������ݷ�����ʼʱ��
	//long sampleNumberReceiver; //�����״���λ����������
	//double sampleIntervalReceiver; //�����״���λ�������ݲ������
	//Esip_ClassSar_pos *antennaPosReceiver; //�����״���λ��������
	//long numofDopplerCenterFrequency; //�ο�����������Ƶ��������Ŀ
	//double *dopplerCenterFrequency; //�ο�����������Ƶ������
} Esip_SensorInfo;

/* -------------------------------------------------------------------- */
/*      OrbitInfo structure     �����Ϣ�ڵ�          */
/* -------------------------------------------------------------------- */
typedef struct {
	double  earthRotationSpeed;     //������ת�ٶ�
	double  AverGroundVelocity;     //ƽ������Vg/m/s
	char  satelliteTransmitter[64]; //����������
	char  satelliteReceiver[64];    //����������
	Esip_ClassSar_pos  positionTransmitter;  //�������ǵ���������
	Esip_ClassSar_pos  positionReceiver;    //�������ǵ���������
	Esip_ClassSar_attitude attitudeTransmitter; //����������̬��������
	Esip_ClassSar_attitude attitudeReceiver; //����������̬��������
} Esip_OrbitInfo;

/* -------------------------------------------------------------------- */
/*      SceneInfo structure     ������Ϣ�ڵ�          */
/* -------------------------------------------------------------------- */
typedef struct {
	long  numOfTag;     //������Ƶ���
	Esip_ClassTag *dataPointTag; //��־������
	char fileNameDEM[64]; //��DEM�����ļ���
} Esip_SceneInfo;


/* -------------------------------------------------------------------- */
//������������2018.5.30      
/*Esip_Additional_Data  �������ݽṹ��
/* -------------------------------------------------------------------- */
#if 0
typedef struct {
	Esip_ClassDate  sendRadarClassData;  //�����״���λ�������ݷ�����ʼʱ��
	long  sendRadarXWZXDataNum;          //�����״���λ����������
	double sendRadarXWZXDataInteral;     //�����״���λ�������ݲ������
	Esip_ClassSar_pos *sendRadarSarPos;  //�����״���λ��������
	Esip_ClassDate  recvRadarClassData;  //�����״���λ�������ݷ�����ʼʱ��
	long  recvRadarXWZXDataNum;          //�����״���λ����������
	double recvRadarXWZXDataInteral;     //�����״���λ�������ݲ������
	Esip_ClassSar_pos *recvRadarSarPos;  //�����״���λ��������
	long dopplerCenterFrepNum;
	double *usedRangeDopplerCenterFrep;
	long gndCtrlPointNum;
	Esip_ClassTag *tagPointData; //��־������
	char fileNameDEM[64]; //��DEM�����ļ���
} Esip_Additional_Data;
#endif
struct Esip_Additional_Data
{
	double AziDis;      //ͼ��λ��������(m)
	double TSpace_R;	//ͼ�������������(m)
	double AziStartTime;	//ͼ��λ����ʼ��ʱ��
	double RanStartTime;	//ͼ���������ʼ��ʱ��
	double frequency;	//�����ź�������Ƶ

	Esip_ClassDate  sendRadarClassData;  //�����״���λ�������ݷ�����ʼʱ��
	long  sendRadarXWZXDataNum;          //�����״���λ����������
	double sendRadarXWZXDataInteral;     //�����״���λ�������ݲ������
	double *sendRadarSarPos = NULL;  //�����״���λ��������
	Esip_ClassDate  recvRadarClassData;  //�����״���λ�������ݷ�����ʼʱ��
	long  recvRadarXWZXDataNum;          //�����״���λ����������
	double recvRadarXWZXDataInteral;     //�����״���λ�������ݲ������
	double *recvRadarSarPos;  //�����״���λ��������
	long dopplerCenterFrepNum;
	double *usedRangeDopplerCenterFrep;
	long gndCtrlPointNum;
	double *tagPointData; //��־������
	char fileNameDEM[512]; //��DEM�����ļ���

} ;

/* -------------------------------------------------------------------- */
/*      ProcessInfo structure     ������Ϣ�ڵ�          */
/* -------------------------------------------------------------------- */
struct Esip_ProcessInfo {
	short  numOfSource;     //���������ݵ�Դ���ݸ�����0Ϊ���ڱ��ĵ�
	char *dataSource[64];   //���������ݵ�Դ�������ڵĽڵ�����
	short filerSizeAzimuth; //�˲���λ�򴰿ڴ�С/Pixels
	short filerSizeRange;   //�˲������򴰿ڴ�С/Pixels
	double flatFrequency;   //ȥƽ�ص�ƽ��Ƶ��/1/pixel
	short TimePhaseUnwrapping; //��λչ������
	char cmments[1024];     //�Ը����ݴ����ߡ��������߹��̵�����
} ;

struct ExtImgHeaderInfo {
	long  fileKey;        //��Կ,ʶ���ļ�����
	long reserved1;      //Ԥ��������չ
	char filenameTransmitter[64];   //�����״���λ����״̬�����ļ���
	char filenameReceiver[64];   //�����״���λ����״̬�����ļ���
	char filenameTagData[64];   //��־�������ļ���
	char filenameEchoesData[64]; //�ز������ļ���
	char filenameTransmitterOfMeasure[64];   //�����״���λ����״̬���������ļ���
	char filenameReceiverOfMeasure[64];   //�����״���λ����״̬���������ļ���
	char filenameSendSatelliteAttitude[64];   //����������̬�����ļ���
	char filenameRecvSatelliteAttitude[64];   //����������̬�����ļ���
	char nameSendSatellite[64];   //����������
	char nameRecvSatellite[64];   //����������
	char dataSimulation[64]; //ֱ�ӽ�����copy���buf��
	long workmode;   //����ģʽ
	long noBeamPosition; //��λ�ţ���ʱ����
	Esip_ClassDate timeStartEhcoes; //�ز�������ʼʱ��
	long reserved2;  //Ԥ��2
	Esip_Classbeam_position transmitter; //�����ǲ�λ����
	Esip_Classbeam_position receiver; //�������ǲ�λ����
	double  carrierFrequency;  //�����ź�������Ƶ
	long  signModulationFrequency; //�����źŵ�Ƶ�ʼ���
	long reserved3;  //Ԥ��3
	double squintTransmitter; //��������б�ӽ�/rad
	double squintReceiver;    //��������б�ӽ�/rad
	long look;           //����������
	long reserved4;  //Ԥ��4
	long   azimuthLength;    //��λ�����ص���/���� //(��nr,��Ӧͼ��߶�) 
	long   rangeLength;     //���������ص���/���� //(��nc,��Ӧͼ����)
	double  azimuthSample;     //ͼ��λ��������/��
	double  rangeSample;       //ͼ�������������/��
	double  azimuthStartTime;  //ͼ��λ����ʼ��ʱ��
	double  rangeStartTime;    //ͼ���������ʼ��ʱ��
	double avgVG;  //ƽ������
	double  resolutionAzimuth;  //���۷�λ�ֱ���
	double  resolutionRange;  //����б��ֱ���
} ;  //��չͼ���ļ��ṹ

struct ExtImgHandle_t {
	FILE	*fp;
	//char	*pszPath;
	char    *pszFilename;
	ExtImgHeaderInfo *pszExtHeaderInfo;
	GUInt32	nDataPos;
	GUInt32 nBytesPerPixel;

};

struct HFAInfo_t {
	FILE	*fp;
	char	*pszPath;
	char    *pszFilename; /* sans path */

	GUInt32 nEndOfFile;
	GUInt32 nHeaderPos;
	GUInt32	nRootPos;
	GUInt32	nDictionaryPos;

	GInt16	nEntryHeaderLength;
	GInt32	nVersion;

	int         bTreeDirty;
	//HFAEntry	*poRoot;
	Esip_Entry *poRoot;

	//HFADictionary *poDictionary;
	char	*pszDictionary;

	int		nXSize;
	int		nYSize;

	int		nBands;
	//HFABand	**papoBand;

	void	*pMapInfo;
	void    *pDatum;
	void     *pProParameters;

} ;

//typedef struct demPara
//{
//	//�������
//	int m;          //�����������ӽ����ȡ
//	//����
//	int nr;             //�����λ������
//	int nc;             //�����λ������
//	int tag_M;              //��ͼ�������Ƶ���
//	Para para_M;       //��ͼ�����
//	Para para_S;	   //��ͼ�����
//}demPara;

typedef HFAInfo_t *HFAHandle;

#endif /* ndef _SARCOMM_H_INCLUDED */