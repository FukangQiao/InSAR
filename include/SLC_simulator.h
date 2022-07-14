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
	/*@brief ���ݹ���ͳ���DEM�Լ�����������ɵ��Ӹ�ͼ�񣨵������գ�
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
	* @param GCP                                       ���Ƶ���Ϣ������ֵ��n��5����/��/��/γ/�ߣ�
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
		ComplexMat& slc,
		Mat& GCP
	);
	/*@brief ���ݹ���ͳ���DEM�Լ�����������ɵ��Ӹ�ͼ�񣨵���˫�ջ��ߵ������գ�����2��ͼ��
	* @param stateVec1                                 �������1�����ǣ��źŷ�����+�źŽ��չ����
	* @param stateVec2                                 �������2�����ǣ��źŽ��չ����
	* @param dem                                       ����DEM������SRTM��
	* @param lon_upperleft                             DEM���ϽǾ���
	* @param lat_upperleft                             DEM���Ͻ�ά��
	* @param sceneHeight1                              ��ͼ����SLC�����߶�
	* @param sceneWidth1                               ��ͼ����SLC�������
	* @param sceneHeight2                              ��ͼ����SLC�����߶�
	* @param sceneWidth2                               ��ͼ����SLC�������
	* @param nearRange1                                ��ͼ���б��
	* @param nearRange2                                ��ͼ���б��
	* @param prf                                       �����ظ�Ƶ��
	* @param wavelength                                ����
	* @param rangeSpacing                              ��������������m��
	* @param azimuthSpacing                            ��λ����������m��
	* @param acquisitionStartTime1                     ��ͼ��λ����ʼʱ��
	* @param acquisitionStopTime1                      ��ͼ��λ�����ʱ��
	* @param acquisitionStartTime2                     ��ͼ��λ����ʼʱ��
	* @param acquisitionStopTime2                      ��ͼ��λ�����ʱ��
	* @param SNR                                       ����������ȣ�dB��
	* @param slc1                                      ���Ƿ���SARͼ�񣨷���ֵ��
	* @param slc2                                      ���Ƿ���SARͼ�񣨷���ֵ��
	* @param GCP                                       ���Ƶ���Ϣ������ֵ��n��5����/��/��/γ/�ߣ�
	* @param mode                                      �շ�ģʽ��1���������գ�2������˫�գ�Ĭ��Ϊ�������գ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int generateSLC(
		Mat& stateVec1,
		Mat& stateVec2,
		Mat& dem,
		double lon_upperleft,
		double lat_upperleft,
		int sceneHeight1,
		int sceneWidth1,
		int sceneHeight2,
		int sceneWidth2,
		double nearRange1,
		double nearRange2,
		double prf,
		double wavelength,
		double rangeSpacing,
		double azimuthSpacing,
		double acquisitionStartTime1,
		double acquisitionStopTime1,
		double acquisitionStartTime2,
		double acquisitionStopTime2,
		double SNR,
		ComplexMat& slc1,
		ComplexMat& slc2,
		Mat& GCP,
		int mode = 1
	);
	/*@brief ���ݹ���ͳ���DEM�Լ�����������ɵ��Ӹ�ͼ�񣨵���˫�գ�ƹ��ģʽ������4��ͼ��
	* @param stateVec1                                 �������1�����ǣ��źŷ�����+�źŽ��չ����
	* @param stateVec2                                 �������2�����ǣ��źŽ��չ����
	* @param dem                                       ����DEM������SRTM��
	* @param lon_upperleft                             DEM���ϽǾ���
	* @param lat_upperleft                             DEM���Ͻ�ά��
	* @param sceneHeight1                              ��ͼ����SLC�����߶�
	* @param sceneWidth1                               ��ͼ����SLC�������
	* @param sceneHeight2                              ��ͼ����SLC�����߶�
	* @param sceneWidth2                               ��ͼ����SLC�������
	* @param nearRange1                                ��ͼ���б��
	* @param nearRange2                                ��ͼ���б��
	* @param prf                                       �����ظ�Ƶ��
	* @param wavelength                                ����
	* @param rangeSpacing                              ��������������m��
	* @param azimuthSpacing                            ��λ����������m��
	* @param acquisitionStartTime1                     ��ͼ��λ����ʼʱ��
	* @param acquisitionStopTime1                      ��ͼ��λ�����ʱ��
	* @param acquisitionStartTime2                     ��ͼ��λ����ʼʱ��
	* @param acquisitionStopTime2                      ��ͼ��λ�����ʱ��
	* @param SNR                                       ����������ȣ�dB��
	* @param slc1                                      �����Է����գ�����ֵ��
	* @param slc2                                      �����ո��ǣ�����ֵ��
	* @param slc3                                      �����Է����գ�����ֵ��
	* @param slc4                                      ���������ǣ�����ֵ��
	* @param GCP                                       ���Ƶ���Ϣ������ֵ��n��5����/��/��/γ/�ߣ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int generateSLC(
		Mat& stateVec1,
		Mat& stateVec2,
		Mat& dem,
		double lon_upperleft,
		double lat_upperleft,
		int sceneHeight1,
		int sceneWidth1,
		int sceneHeight2,
		int sceneWidth2,
		double nearRange1,
		double nearRange2,
		double prf,
		double wavelength,
		double rangeSpacing,
		double azimuthSpacing,
		double acquisitionStartTime1,
		double acquisitionStopTime1,
		double acquisitionStartTime2,
		double acquisitionStopTime2,
		double SNR,
		ComplexMat& slc1,
		ComplexMat& slc2,
		ComplexMat& slc3,
		ComplexMat& slc4,
		Mat& GCP
	);
private:
	char error_head[256];

};




#endif // !__SLC_SIMULATOR__H__