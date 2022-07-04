#pragma once
#ifndef __SLC_SIMULATOR__H__
#define __SLC_SIMULATOR__H__
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"


/*----------------------------------------*/
/*          ���Ӹ�ͼ�������              */
/*----------------------------------------*/
class InSAR_API SLC_simulator
{
public:
	SLC_simulator();
	~SLC_simulator();
	/*@brief ��������Ǽ������ɢ��ϵ��
	* @param incidenceAngle                             �����
	* @param sigma                                      ����ɢ��ϵ��(����ֵ)
	* @return �ɹ�����0�����򷵻�-1
	*/
	int reflectivity(Mat& incidenceAngle, Mat& sigma);
	/*@brief �������ɢ��ϵ��
	* @param DEM_x                                      DEMת�����꣨X��
	* @param DEM_y                                      DEMת�����꣨Y��
	* @param DEM_z                                      DEMת�����꣨Z��
	* @param satellitePos_x                             DEM��Ӧ�����ǳ�������꣨X��
	* @param satellitePos_y                             DEM��Ӧ�����ǳ�������꣨Y��
	* @param satellitePos_z                             DEM��Ӧ�����ǳ�������꣨Z��
	* @param sigma                                      ����ɢ��ϵ��������ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeIncidenceAngle(
		Mat& DEM_x,
		Mat& DEM_y,
		Mat& DEM_z,
		Mat& satellitePos_x,
		Mat& satellitePos_y,
		Mat& satellitePos_z,
		Mat& sigma
	);
	/*@brief ���ݹ���ͳ���DEM�Լ�����������ɵ��Ӹ�ͼ��
	* @param stateVec                                  �������
	* @param dem                                       ����DEM������SRTM��
	* @param lon_upperleft                             DEM���ϽǾ���
	* @param lat_upperleft                             DEM���Ͻ�ά��
	* @param sceneHeight                               ����SLC�����߶�
	* @param sceneWidth                                ����SLC�������
	* @param nearRange                                 ���б��
	* @param prf                                       �����ظ�Ƶ��
	* @param wavelength                                ����
	* @param rangeSpacing                              ��������������m��
	* @param azimuthSpacing                            ��λ����������m��
	* @param acquisitionStartTime                      ��λ����ʼʱ��
	* @param acquisitionStopTime                       ��λ�����ʱ��
	* @param SNR                                       ����������ȣ�dB��
	* @param slc                                       ����SLCͼ�񣨷���ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int generateSLC(
		Mat& stateVec,
		Mat& dem,
		double lon_upperleft,
		double lat_upperleft,
		int sceneHeight,
		int sceneWidth,
		double nearRange,
		double prf,
		double wavelength,
		double rangeSpacing,
		double azimuthSpacing,
		double acquisitionStartTime,
		double acquisitionStopTime,
		double SNR,
		ComplexMat& slc
	);
private:
	char error_head[256];

};




#endif // !__SLC_SIMULATOR__H__