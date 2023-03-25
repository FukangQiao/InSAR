#pragma once
#include<Package.h>
#include<ComplexMat.h>
using namespace cv;

class InSAR_API Evaluation
{
public:
	Evaluation();
	~Evaluation();
	/*@brief ������λ������
	* @param master_h5				   ��ͼ��h5�ļ�
	* @param slave_h5				   ��ͼ��h5�ļ�
	* @param Output                    ��������rad��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int PhasePreserve(const char* master_h5,
		const char* slave_h5,
		double* Output);
	/*@brief ��׼����
	* @param master_h5				   ��ͼ��h5�ļ�
	* @param slave_regis_h5			   ��׼��ͼ��h5�ļ�
	* @param coherence				   ���ϵ������
	* @param regis_error               ��׼��������λ���Ҿ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int Regis(const char* master_h5,
		const char* slave_regis_h5,
		Mat& coherence,
		Mat& regis_error);
	/*@brief ������λ������
	* @param master_h5				   �������λh5�ļ�
	* @param slave_h5				   ���ǰ��λh5�ļ�
	* @param Output                    ��������rad��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int Unwrap(const char* master_h5, 
		const char* slave_regis_h5, 
		const char* phase_unwrapped_h5, double* Output);
	int Pos(const char* unwrapped_phase_file, const char* project_path, const char* GCP_path,
		double* lat_abs, double* lat_rel,
		double* lon_Output, double* lon_rel,
		double* height_Output, double* height_rel);
	int FFT2(ComplexMat src, ComplexMat& dst, int win_size, int interp_times);
private:
	char error_head[256];
	char parallel_error_head[256];
};