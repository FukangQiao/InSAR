#pragma once
#ifndef __FILTER__H__
#define __FILTER__H__
#include"..\include\Package.h"
#include"..\include\Utils.h"




class InSAR_API Filter
{
public:
	Filter();
	~Filter();
	/*2D CZT�任
	 ����1 �������
	 ����2 2D CZT�任���������ֵ��
	 ����3 CZT�任����
	 ����4 CZT�任����
	 ����5 CZT�任����
	 ����6 CZT�任����
	*/
	int czt2(Mat& src, Mat& dst, int M, int N, double theta0, double phi0);
	/*��ֵ�˲�����ԭ�ز�����
	 ����1 ���루����ֵ��
	 ����2 �˲����ڴ�С��������������
	*/
	int meanfilter(Mat& Src, int WndSize);
	/*2D FFTSHIFT(ԭ�ز���)*/
	int fftshift2(Mat& matrix);
	/*б������Ӧ�˲���
	 ����1 ���˲����루������λ��
	 ����2 �˲�������˲��������λ��
	 ����3 �˲����ڴ�С��������������
	 ����4 ��ֵ�˲����ڴ�С��������������
	*/
	int slope_adaptive_filter(Mat& phase, Mat& phase_filtered, int wndsize_filter, int wndsize_prefilter);
	/** @brief ���ѧϰ�˲���·����Ҫ�����ģ�
	 
	 @param filter_dl_path              �˲�����·��
	 @param tmp_path                    �м��ļ�����·��
	 @param dl_model_file               ���ѧϰģ���ļ�
	 @param phase                       ���˲���λ
	 @param phase_filtered              �˲�����λ������ֵ��
	*/
	int filter_dl(
		const char* filter_dl_path,
		const char* tmp_path,
		const char* dl_model_file,
		Mat& phase,
		Mat& phase_filtered
	);
	/*����Goldstein�˲�
	* ����1 ���˲���λ
	* ����2 �˲�����λ
	* ����3 �˲�������
	* ����4 ����Ҷ�任���ڴ�С
	* ����5 ���㴰�ڴ�С
	*/
	int Goldstein_filter(
		Mat& phase,
		Mat& phase_filter,
		double alpha,
		int n_win,
		int n_pad
	);
	/*����Goldstein�˲������У�
	* ����1 ���˲���λ
	* ����2 �˲�����λ
	* ����3 �˲�������
	* ����4 ����Ҷ�任���ڴ�С
	* ����5 ���㴰�ڴ�С
	*/
	int Goldstein_filter_parallel(
		Mat& phase,
		Mat& phase_filter,
		double alpha,
		int n_win,
		int n_pad
	);
	// ����ά��˹����ʵ�ָ�˹�˲�
	int GaussianFilter(Mat& src, Mat& dst, Mat window);
	int GenerateGaussMask(Mat& Mask, int window_height, int win_width, double sigma);
private:
	char error_head[256];
	char parallel_error_head[256];
};


#endif // !__FILTER__H__
