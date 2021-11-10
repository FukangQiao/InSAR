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
	/** @brief ����׼
	
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


private:
	char error_head[256];
	char parallel_error_head[256];

};




#endif // !__REGISTRATION__H__
