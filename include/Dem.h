#pragma once
#ifndef __DEM__H__
#define __DEM__H__
#include"..\include\Package.h"
#include"..\include\Deflat.h"
#ifdef _DEBUG
#pragma comment(lib, "Utils_d.lib")
#pragma comment(lib, "Deflat_d.lib")
#else
#pragma comment(lib, "Utils.lib")
#pragma comment(lib, "Deflat.lib")
#endif // _DEBUG


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

private:
	char error_head[256];
	char parallel_error_head[256];

};

Dem::Dem()
{
	memset(this->error_head, 0, 256);
	memset(this->parallel_error_head, 0, 256);
	strcpy(this->error_head, "DEM_DLL_ERROR: error happens when using ");
	strcpy(this->parallel_error_head, "DEM_DLL_ERROR: error happens when using parallel computing in function: ");
}

Dem::~Dem()
{
}

#endif // !__DEM__H__
