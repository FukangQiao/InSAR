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
	/*@brief ���ݹ���ͳ���DEM�Լ���������ο�б�ࣨ����˫�գ�ƹ��ģʽ��
	* @param stateVec1                                 �������1�����ǣ��źŷ�����+�źŽ��չ����
	* @param stateVec2                                 �������2�����ǣ��źŽ��չ����
	* @param dem                                       ����DEM������SRTM��
	* @param lon_upperleft                             DEM���ϽǾ���
	* @param lat_upperleft                             DEM���Ͻ�ά��
	* @param sceneHeight1                              ��ͼ����SLC�����߶�
	* @param sceneWidth1                               ��ͼ����SLC�������
	* @param nearRange1                                ��ͼ���б��
	* @param prf                                       �����ظ�Ƶ��
	* @param wavelength                                ����
	* @param rangeSpacing                              ��������������m��
	* @param azimuthSpacing                            ��λ����������m��
	* @param acquisitionStartTime1                     ��ͼ��λ����ʼʱ��
	* @param acquisitionStopTime1                      ��ͼ��λ�����ʱ��
	* @param acquisitionStartTime2                     ��ͼ��λ����ʼʱ��
	* @param acquisitionStopTime2                      ��ͼ��λ�����ʱ��
	* @param R1                                        ����б��
	* @param R2                                        ����б��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int generateSlantrange(
		Mat& stateVec1,
		Mat& stateVec2,
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
		double acquisitionStartTime1,
		double acquisitionStopTime1,
		double acquisitionStartTime2,
		double acquisitionStopTime2,
		Mat& R1,
		Mat& R2
	);
	/*@brief ƹ��ģʽȥ�ο���λ
	* @param mappedDEM                              ��׼��ͼ������ϵDEM
	* @param mappedLat                              DEMγ������
	* @param mappedLon                              DEM��������
	* @param slcH5File1                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5file2                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5file3                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5file4                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5File1_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ�ȥ�ο���λ����ֵ��
	* @param slcH5file2_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ�ȥ�ο���λ����ֵ��
	* @param slcH5file3_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ�ȥ�ο���λ����ֵ��
	* @param slcH5file4_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ�ȥ�ο���λ����ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int SLC_deramp(
		Mat& mappedDEM,
		Mat& mappedLat,
		Mat& mappedLon,
		const char* slcH5File1,
		const char* slcH5File2,
		const char* slcH5File3,
		const char* slcH5File4,
		const char* slcH5File1_out,
		const char* slcH5File2_out,
		const char* slcH5File3_out,
		const char* slcH5File4_out
	);
	/*@brief ȥ�ο���λ
	* @param master_index                           ��ͼ���кţ�1-based��
	* @param mappedDEM                              ��׼��ͼ������ϵDEM
	* @param mappedLat                              DEMγ������
	* @param mappedLon                              DEM��������
	* @param mode                                   �շ�ģʽ��1���������գ�2������˫�գ�3��ƹ��ģʽ��4��˫Ƶƹ��ģʽ��
	* @param slcH5FilesList                         ��׼h5�ļ�����
	* @param slcH5FileListOut                       ȥ�ο���h5�ļ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int SLC_deramp_14(
		vector<string>& slcH5FilesList,
		vector<string>& slcH5FilesListOut,
		int master_index,
		Mat& mappedDEM,
		Mat& mappedLat,
		Mat& mappedLon,
		int mode
	);
	/*@brief ƹ��ģʽ���¼���ο���λ
	* @param mappedDEM                              ��׼��ͼ������ϵDEM
	* @param mappedLat                              DEMγ������
	* @param mappedLon                              DEM��������
	* @param slcH5File1                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5file2                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5file3                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5file4                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5File1_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ��Ӳο���λ����ֵ��
	* @param slcH5file2_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ��Ӳο���λ����ֵ��
	* @param slcH5file3_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ��Ӳο���λ����ֵ��
	* @param slcH5file4_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ��Ӳο���λ����ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int SLC_reramp(
		Mat& mappedDEM,
		Mat& mappedLat,
		Mat& mappedLon,
		const char* slcH5File1,
		const char* slcH5File2,
		const char* slcH5File3,
		const char* slcH5File4,
		const char* slcH5File1_out,
		const char* slcH5File2_out,
		const char* slcH5File3_out,
		const char* slcH5File4_out
	);
	/*@brief ƹ��ģʽ������λ����
	* @param estimation_wndsize                     ���ƴ��ڴ�С
	* @param slcH5File1                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5file2                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5file3                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5file4                             ��׼SLCͼ��h5�ļ������Ƿ������գ�
	* @param slcH5File1_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ�����ֵ��
	* @param slcH5file2_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ�����ֵ��
	* @param slcH5file3_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ�����ֵ��
	* @param slcH5file4_out                         ��׼SLCͼ��h5�ļ������Ƿ������գ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int MB_phase_estimation(
		int estimation_wndsize,
		const char* slcH5File1,
		const char* slcH5File2,
		const char* slcH5File3,
		const char* slcH5File4,
		const char* slcH5File1_out,
		const char* slcH5File2_out,
		const char* slcH5File3_out,
		const char* slcH5File4_out
	);
	/*@brief ˫Ƶƹ��ģʽ������λ����
	* @param estimation_wndsize                     ���ƴ��ڴ�С
	* @param slcH5File1                             ��׼SLCͼ��h5�ļ���Ƶ��1�����Ƿ������գ�
	* @param slcH5file2                             ��׼SLCͼ��h5�ļ���Ƶ��1�����Ƿ������գ�
	* @param slcH5file3                             ��׼SLCͼ��h5�ļ���Ƶ��1�����Ƿ������գ�
	* @param slcH5file4                             ��׼SLCͼ��h5�ļ���Ƶ��1�����Ƿ������գ�
	* @param slcH5File5                             ��׼SLCͼ��h5�ļ���Ƶ��2�����Ƿ������գ�
	* @param slcH5file6                             ��׼SLCͼ��h5�ļ���Ƶ��2�����Ƿ������գ�
	* @param slcH5file7                             ��׼SLCͼ��h5�ļ���Ƶ��2�����Ƿ������գ�
	* @param slcH5file8                             ��׼SLCͼ��h5�ļ���Ƶ��2�����Ƿ������գ�
	* @param slcH5File1_out                         ��׼SLCͼ��h5�ļ���Ƶ��1�����Ƿ������գ�����ֵ��
	* @param slcH5file2_out                         ��׼SLCͼ��h5�ļ���Ƶ��1�����Ƿ������գ�����ֵ��
	* @param slcH5file3_out                         ��׼SLCͼ��h5�ļ���Ƶ��1�����Ƿ������գ�����ֵ��
	* @param slcH5file4_out                         ��׼SLCͼ��h5�ļ���Ƶ��1�����Ƿ������գ�����ֵ��
	* @param slcH5File5_out                         ��׼SLCͼ��h5�ļ���Ƶ��2�����Ƿ������գ�����ֵ��
	* @param slcH5file6_out                         ��׼SLCͼ��h5�ļ���Ƶ��2�����Ƿ������գ�����ֵ��
	* @param slcH5file7_out                         ��׼SLCͼ��h5�ļ���Ƶ��2�����Ƿ������գ�����ֵ��
	* @param slcH5file8_out                         ��׼SLCͼ��h5�ļ���Ƶ��2�����Ƿ������գ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int MB_phase_estimation(
		int estimation_wndsize,
		const char* slcH5File1,
		const char* slcH5File2,
		const char* slcH5File3,
		const char* slcH5File4,
		const char* slcH5File5,
		const char* slcH5File6,
		const char* slcH5File7,
		const char* slcH5File8,
		const char* slcH5File1_out,
		const char* slcH5File2_out,
		const char* slcH5File3_out,
		const char* slcH5File4_out,
		const char* slcH5File5_out,
		const char* slcH5File6_out,
		const char* slcH5File7_out,
		const char* slcH5File8_out
	);
	/*@brief ƹ��ģʽ˫Ƶ��ģ�������Ȼ��λ����
	* @param phase_reference                �ο���λ�����������Ȼ����������ȷ����
	* @param wrapped_phase_low              ��Ƶ��λ
	* @param wrapped_phase_high             ��Ƶ��λ
	* @param outphase                       �ں���λ
	* @param lat_coef                       γ��ת��ϵ��
	* @param lon_coef                       ����ת��ϵ��
	* @param wavelength_low                 ��Ƶ����
	* @param wavelength_high                ��Ƶ����
	* @param nearRangeTime                  ��ͼ���б��ʱ�䣨s��
	* @param rangeSpacing                   ��ͼ��������������m��
	* @param azimuthSpacing                 ��ͼ��λ����������m��
	* @param offset_row                     ��ͼ����ԭͼ�е���ƫ��
	* @param offset_col                     ��ͼ����ԭͼ�е���ƫ��
	* @param start1                         ��ͼ������ʼʱ�� 
	* @param end1                           ��ͼ�������ʱ��
	* @param start2                         ��ͼ������ʼʱ��
	* @param end2                           ��ͼ�������ʱ��
	* @param statevec1                      ���ǹ��
	* @param statevec2                      ���ǹ��
	* @param prf                            �����ظ�Ƶ��
	* @param demPath                        SRTM DEM·��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int pingpong_MLE(
		Mat& phase_reference,
		Mat& wrapped_phase_low,
		Mat& wrapped_phase_high,
		Mat& outphase,
		Mat& lat_coef,
		Mat& lon_coef,
		double wavelength_low,
		double wavelength_high,
		double nearRangeTime,
		double rangeSpacing,
		double azimuthSpacing,
		int offset_row,
		int offset_col,
		double start1,
		double end1,
		double start2,
		double end2,
		Mat& statevec1,
		Mat& statevec2,
		double prf,
		string demPath
	);
private:
	char error_head[256];

};




#endif // !__SLC_SIMULATOR__H__