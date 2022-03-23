#pragma once
#ifndef __REGISTRATION__H__
#define __REGISTRATION__H__
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"
#include"..\include\Utils.h"



class InSAR_API Registration
{
public:
	Registration();
	~Registration();
	/*��ȡ������ͼ���ʵ��غ���
	 ����1 ��ͼ�񣨸���
	 ����2 ��ͼ�񣨸���
	 ����3 ��ƫ����������ֵ��
	 ����4 ��ƫ����������ֵ��
	*/
	int real_coherent(ComplexMat& Master, ComplexMat& Slave, int* offset_row, int* offset_col);
	/*2D FFTSHIFT(ԭ�ز���)*/
	int fftshift2(Mat& matrix);
	/*2D FFT
	 ����1 �������
	 ����2 �������
	*/
	int fft2(Mat& Src, Mat& Dst);
	/*��Ԫ����׼��ԭ�ز�����
	 ����1 ��ͼ�񣨸���������ֵ/����ֵ��
	 ����2 ��ͼ�񣨸���������ֵ/����ֵ��
	 ����3 ��ƫ����������ֵ��
	 ����4 ��ƫ����������ֵ��
	*/
	int registration_pixel(ComplexMat& Master, ComplexMat& Slave, int* move_r = NULL, int* move_c = NULL);
	/*Ƶ�����ֵ
	 ����1 ������󣨸���
	 ����2 ������󣨸���
	 ����3 ��ֵ����������1�� ����2��n���ݣ�
	*/
	int interp_paddingzero(ComplexMat& InputMatrix, ComplexMat& OutputMatrix, int interp_times);
	/*������ֵ
	 ����1 �������
	 ����2 �������
	 ����3 ��ƫ����
	 ����4 ��ƫ����
	*/
	int interp_cubic(ComplexMat& InputMatrix, ComplexMat& OutputMatrix, double offset_row, double offset_col);
	/*������ֵ
	����1 �������
	����2 �������
	����3 ���ϵ��
	*/
	int interp_cubic(ComplexMat& InputMatrix, ComplexMat& OutputMatrix, Mat& Coefficient);
	/*����ÿ�����ص�ƫ����
	 ����1 �����к�
	 ����2 �����к�
	 ����3 ���ϵ��
	 ����4 ��ƫ����
	 ����5 ��ƫ����
	*/
	int every_subpixel_move(int i, int j, Mat& coefficient, double* offset_row, double* offset_col);
	/*��������Ȩ��*/
	double WeightCalculation(double offset);
	/*�����ؼ���׼
	 ����1 ��ͼ�񣨸���
	 ����2 ��ͼ�񣨸���
	 ����3 �ӿ��С������1��
	 ����4 ��ֵ����������1��
	*/
	int registration_subpixel(ComplexMat& Master, ComplexMat& Slave, int blocksize, int interp_times);
	/** @brief ����׼��֧��16λ���ͺ�64λ���������룩
	
	@param master              ��ͼ��
	@param slave               ��ͼ��
	@param blocksize           ��ͼ��ο���ֿ��С��blocksize��blocksize��blocksizeΪ2��n���ݣ�
	@param interp_times        ��ֵ����(InSARҪ������8����ֵ)
	*/
	int coregistration_subpixel(
		ComplexMat& master,
		ComplexMat& slave,
		int blocksize,
		int interp_times
	);
	/*�������ƫ����
	 ����1 �����к�
	 ����2 �����к�
	 ����3 ��ƫ����
	 ����4 ��ƫ����
	 ����5 ���ϵ��������ֵ��
	*/
	int all_subpixel_move(Mat& Coordinate_x, Mat& Coordinate_y, Mat& offset_row, Mat& offset_col, Mat& para);
	/*���ݴ���׼ƫ����ɸѡ���Ƶ�
	* ����1 ԭʼͼ������
	* ����2 ԭʼͼ������
	* ����3 ��ƫ��
	* ����4 ��ƫ��
	* ����5 ���Ƶ���Ϣ
	*/
	int gcps_sift(int rows, int cols, int move_rows, int move_cols, Mat& gcps);

	/*@brief ����DEM�����ǹ���ȸ�����������DEM����SARͼ���е�λ��
	* @param DEM                          DEM��short�;���
	* @param stateVector                  ���ǹ�����ݣ�δ��ֵ��
	* @param rangePos                     DEM����SARͼ���о��������꣨�У�double�;��󣬷���ֵ��
	* @param azimuthPos                   DEM����SARͼ���з�λ�����꣨�У�double�;��󣬷���ֵ��
	* @param lon_upperleft                84����ϵDEM���ϽǾ���
	* @param lat_upperleft                84����ϵDEM���Ͻ�γ��
	* @param offset_row                   SARͼ����ԭ�����е���ƫ����
	* @param offset_col                   SARͼ����ԭ�����е���ƫ����
	* @param sceneHeight                  SARͼ�񳡾��߶�
	* @param sceneWidth                   SARͼ�񳡾����
	* @param prf                          SAR�����״������ظ�Ƶ��
	* @param rangeSpacing                 ��������������m��
	* @param wavelength                   ����
	* @param nearRangeTime                ���б��ʱ��
	* @param acquisitionStartTime         ��λ�������ʼʱ��
	* @param acquisitionStopTime          ��λ���������ʱ��
	* @param lon_spacing                  84����ϵDEM���Ȳ���������㣩
	* @param lat_spacing                  84����ϵDEMγ�Ȳ���������㣩
	* @return �ɹ�����0�����򷵻�-1
	*/
	int getDEMRgAzPos(
		Mat& DEM,
		Mat& stateVector,
		Mat& rangePos,
		Mat& azimuthPos,
		double lon_upperleft,
		double lat_upperleft,
		int offset_row,
		int offset_col,
		int sceneHeight,
		int sceneWidth,
		double prf,
		double rangeSpacing,
		double wavelength,
		double nearRangeTime,
		double acquisitionStartTime,
		double acquisitionStopTime,
		double lon_spacing,
		double lat_spacing
	);
	/*@brief ��ϸ�ͼ��ƫ�ƣ�1����ϣ�offset = a0 + a1 * x + a2 * y��
	* @param slaveOffset                           ƫ����
	* @param masterRange                           DEM������ͼ�еľ��������꣨������double�;���
	* @param masterAzimuth                         DEM������ͼ�еķ�λ�����꣨������double�;���
	* @param a0                                    ���ϵ��
	* @param a1                                    ���ϵ��
	* @param a2                                    ���ϵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int fitSlaveOffset(
		Mat& slaveOffset,
		Mat& masterRange,
		Mat& masterAzimuth,
		double* a0,
		double* a1,
		double* a2
	);
	/*@brief ���㸨ͼ��ƫ��
	* @param masterRange                           DEM������ͼ�еľ��������꣨������
	* @param masterAzimuth                         DEM������ͼ�еķ�λ�����꣨������
	* @param slaveRange                            DEM���ڸ�ͼ�еľ��������꣨������
	* @param slaveAzimuth                          DEM���ڸ�ͼ�еķ�λ�����꣨������
	* @param slaveAzimuthOffset                    ��ͼ��λ��ƫ�ƣ�����ֵ��
	* @param slaveRangeOffset                      ��ͼ�������ƫ�ƣ�����ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int computeSlaveOffset(
		Mat& masterRange,
		Mat& masterAzimuth,
		Mat& slaveRange,
		Mat& slaveAzimuth,
		Mat& slaveAzimuthOffset,
		Mat& slaveRangeOffset
	);
	/*@brief ��ͼ��˫���Բ�ֵ�ز�����inplace��ԭ�ز�����
	* @param slc                                   ���ز���ͼ��ԭ�ز�����
	* @param dstHeight                             �ز���ͼ��߶�
	* @param dstWidth                              �ز���ͼ����
	* @param a0Rg                                  ������ƫ�����ϵ��
	* @param a1Rg                                  ������ƫ�����ϵ��
	* @param a2Rg                                  ������ƫ�����ϵ��
	* @param a0Az                                  ��λ��ƫ�����ϵ��
	* @param a1Az                                  ��λ��ƫ�����ϵ��
	* @param a2Az                                  ��λ��ƫ�����ϵ��
	* @param offset_row                            ��ͼ�����Ͻ��������ͼ�����ƫ����������ֵ��
	* @param offset_col                            ��ͼ�����Ͻ��������ͼ�����ƫ����������ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int performBilinearResampling(
		ComplexMat& slc,
		int dstHeight,
		int dstWidth,
		double a0Rg, double a1Rg, double a2Rg,
		double a0Az, double a1Az, double a2Az,
		int* offset_row = NULL,
		int* offset_col = NULL
	);
private:
	char error_head[256];
	char parallel_error_head[256];
	double invalidOffset = -9999.0;

};




#endif // !__REGISTRATION__H__
