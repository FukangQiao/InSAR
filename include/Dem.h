#pragma once
#ifndef __DEM__H__
#define __DEM__H__
#include"..\include\Package.h"
#include"..\include\Deflat.h"



class InSAR_API Dem
{
public:
	Dem();
	~Dem();
	/*��λ�߳�ת��
	* ����1 �����λ
	* ����2 ƽ����λ
	* ����3 �߳�ֵ������ֵ��
	* ����4 ���Ǹ�������
	* ����5 ���Ǹ�������
	* ����6 ���ǹ������
	* ����7 ���ǹ������
	* ����8 ����������Ƶ��
	* ����9 ������Ƶ�
	* ����10 ��׼�����������׼ƫ��������׼ǰͼ��ߴ磩
	* ����11 ���ǳ�����ʱ��
	* ����12 ���ǳ�����ʱ��
	* ����13 ������ӱ���
	* ����14 �շ�ģʽ��1���������գ�2������˫�գ�
	* ����15 ţ�ٵ���������Ĭ��30�Σ�
	*/
	int phase2dem_newton_iter(
		Mat unwrapped_phase,
		Mat flat_phase,
		Mat& dem,
		Mat auxi_m,
		Mat auxi_s,
		Mat orbit_m,
		Mat orbit_s,
		Mat doppler_frequency,
		Mat gcps,
		Mat regis_out,
		double delta_m,
		double delta_s,
		int multilook_times,
		int mode, 
		int iters
	);
	/** @brief ţ�ٵ��������ݸ߳�
	
	@param unwrapped_phase_file                            �����λh5�ļ�
	@param dem                                             �̷߳��ݽ��������ֵ��
	@param project_path                                    ����·��
	@param iter_times                                      ��������
	@param mode                                            �շ���ʽ��1�Է����գ�Ĭ�ϣ���2����˫�գ�
	@return  �ɹ�����0�����򷵻�-1
	*/
	int dem_newton_iter(
		const char* unwrapped_phase_file,
		Mat& dem,
		const char* project_path,
		int iter_times,
		int mode = 1
	);

	/** @brief ţ�ٵ��������ݸ̣߳����԰棩
	@param unwrapped_phase_file                            �����λh5�ļ�
	@param dem                                             �̷߳��ݽ��������ֵ��
	@param project_path                                    ����·��
	@param iter_times                                      ��������
	@param mode                                            �շ���ʽ��1�Է����գ�Ĭ�ϣ���2����˫�գ�
	@return  �ɹ�����0�����򷵻�-1
	*/
	int dem_newton_iter_test(
		const char* unwrapped_phase_file,
		Mat& dem,
		const char* project_path,
		int iter_times,
		int mode = 1
	);

private:
	char error_head[256];
	char parallel_error_head[256];

};


#endif // !__DEM__H__
