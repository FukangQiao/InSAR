#pragma once
#ifndef __DEFLAT__H__
#define __DEFLAT__H__
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"
#include"..\include\Utils.h"



class InSAR_API Deflat
{
public:
	Deflat();
	~Deflat();
	/*���ǹ�����
	 ����1 �������
	 ����2 ���ϵ��������ֵ��
	*/
	int Orbit_Polyfit(Mat& Orbit, Mat& coef);
	/*��ȡ���������ǳ���λ��ʱ��
	 ����1 ���ǹ�����ķ�λ��ʱ��
	 ����2 ������ϵ��
	 ����3 ���������
	 ����4 ���ǹ����ʼ��λ��ʱ��
	 ����5 ���������ǳ���λ��ʱ�̣�����ֵ��
	*/
	int get_satellite_aztime_NEWTON(double center_time, Mat& coef, Mat pos_xyz, double start_time, double* aztime);
	/*��ȡ������λ��ʱ�̵�����λ��
	 ����1 ������λ��ʱ��
	 ����2 ������ϵ��
	 ����3 ����λ�ã�����ֵ��
	*/
	int get_xyz(double aztime, Mat& coef, Mat& pos_xyz);
	/*��ȡ������λ��ʱ�̵������ٶ�
	����1 ������λ��ʱ��
	����2 ������ϵ��
	����3 �����ٶȣ�����ֵ��
	*/
	int get_vel(double aztime, Mat& coef, Mat& vel_xyz);
	/*��ȡ������λ��ʱ�̵����Ǽ��ٶ�
	����1 ������λ��ʱ��
	����2 ������ϵ��
	����3 ���Ǽ��ٶȣ�����ֵ��
	*/
	int get_acc(double aztime, Mat& coef, Mat& acc_xyz);
	/*ȥƽ�غ���
	 ����1 ��ȥƽ�ظ�����λ
	 ����2 ȥƽ�ظ�����λ
	 ����3 ƽ�ظ�����λ
	 ����4 �����������״���Ƶ�Ȳ�����
	 ����5 ȥƽ�ؿ��Ƶ�
	 ����6 ���ǹ��
	 ����7 ���ǹ��
	 ����8 �շ�ģʽ����������1������˫��2��
	 ����9 ������ӱ�����>= 1��
	*/
	int deflat(	
		Mat& phase,
		Mat& phase_deflat,
		Mat& flat_phase,
		Mat auxi,
		Mat gcps,
		Mat orbit_main,
		Mat orbit_slave,
		int mode,
		int multilook_times
	);
	/** @brief ȥƽ��
	
	@param stateVec1         �������1�����ǹ����δ��ֵ��
	@param stateVec2         �������2�����ǹ����δ��ֵ��
	@param lon_coef          ����ת��ϵ������ͼ������-->���ȣ�
	@param lat_coef          ����ת��ϵ������ͼ������-->γ�ȣ�
	@param phase             ������λ
	@param offset_row        ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param offset_col        ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param height            ƽ�ظ߶�
	@param time_interval1    ���1��ֵʱ������1/prf��
	@param time_interval2    ���2��ֵʱ������1/prf��
	@param mode              �շ���ʽ(1���Է����գ�2������˫��)
	@param wavelength        ����
	@param phase_deflated    ȥƽ����λ������ֵ��
	@param flat_phase        ƽ����λ������ֵ��δ���ƣ�
	*/
	int deflat(
		const Mat& stateVec1,
		const Mat& stateVec2,
		const Mat& lon_coef,
		const Mat& lat_coef,
		const Mat& phase,
		int offset_row,
		int offset_col,
		double height,
		double time_interval1,
		double time_interval2,
		int mode,
		double wavelength,
		Mat& phase_deflated,
		Mat& flat_phase
	);
	/** @brief �����ⲿDEM����ȥ��������λ

	@param phase                 ������λ
	@param dem                   �ⲿDEM����
	@param dem_range_lon         �ⲿDEM���ȷ�Χ��1��2���󣬵�һ����С���ȣ��ڶ�����󾭶ȣ�
	@param dem_range_lat         �ⲿDEMγ�ȷ�Χ��1��2���󣬵�һ����С���ȣ��ڶ�����󾭶ȣ�
	@param stateVec1             ���ǹ�����ݣ�δ��ֵ��
	@param stateVec2             ���ǹ�����ݣ�δ��ֵ��
	@param lon_coef              ����ת��ϵ������ͼ������-->���ȣ�
	@param lat_coef              ����ת��ϵ������ͼ������-->γ�ȣ�
	@param inc_coef              ���ӽ����ϵ����1��11����
	@param offset_row            ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param offset_col            ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param interp_interval1      ���ǹ����ֵʱ������1/prf��
	@param interp_interval2      ���ǹ����ֵʱ������1/prf��
	@param mode                  �շ���ʽ(1���Է����գ�2������˫��)
	@param wavelength            ����
	@param B_effect              ��ֱ����
	@param phase_detopo          ȥ������λ�����ֵ��
	*/
	int topo_removal(
		const Mat& phase,
		const Mat& dem,
		const Mat& dem_range_lon,
		const Mat& dem_range_lat,
		const Mat& stateVec1,
		const Mat& stateVec2,
		const Mat& lon_coef,
		const Mat& lat_coef,
		const Mat& inc_coef,
		int offset_row,
		int offset_col,
		double interp_interval1,
		double interp_interval2,
		int mode,
		double wavelength,
		double B_effect,
		Mat& phase_detopo
	);
private:
	char error_head[256];
	char parallel_error_head[256];

};


#endif // !__DEFLAT__H__
