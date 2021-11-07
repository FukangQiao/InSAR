#pragma once
#ifndef __UNWRAP__H__
#define __UNWRAP__H__
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"
#include"..\include\Utils.h"



class InSAR_API Unwrap
{
public:
	Unwrap();
	~Unwrap();
	/*���ڹ����������С��������λ����㷨
	  ����1���������λ
	  ����2�������λ������ֵ��
	  ����3��������λ���ϵ��
	  ����4��������λ�в��
	  ����5����С���������������ļ�
	  ����6����С�������㷨��ִ���ļ�·��
	*/
	int MCF(
		Mat& wrapped_phase,
		Mat& unwrapped_phase,
		Mat& coherence, Mat& residue,
		const char* MCF_problem_file,
		const char* MCF_EXE_PATH
	);
	/*���ڲ������������С����������㷨
	* ����1 �������λ
	* ����2 �����λ������ֵ��
	* ����3 mask
	* ����4 Delaunay��������ڵ�
	* ����5 Delaunay��������
	* ����6 Delaunay������������
	* ����7 �����ʼ�ڵ�
	* ����8 �Ƿ��ƹ�֦���ߣ�Ĭ��Ϊ��
	* ����9 �߳���ֵ��������ֵ��ñ߲���������
	*/
	int MCF(
		Mat& wrapped_phase,
		Mat& unwrapped_phase,
		Mat& mask,
		vector<tri_node>& nodes,
		tri_edge* edges,
		int num_edges,
		int start,
		bool pass = false,
		double thresh = 10000.0
	);
	/*���ڲ������������С����������㷨�����ڵڶ��ν�������ܵ���ʹ�ã�
	* ����1 �ѽ����λ������˵�һ�ν������λ��
	* ����2 �ڶ��ν������������ڵ�����
	* ����3 �ڶ��ν�����������������
	* ����4 �ڶ��ν�����������������
	* ����5 �����ʼ�ڵ�
	* ����6 �Ƿ��ƹ�֦���ߣ�Ĭ��Ϊ��
	* ����7 �߳���ֵ��������ֵ��ñ߲���������
	*/
	int MCF_second(
		Mat& unwrapped_phase,
		vector<tri_node>& nodes,
		tri_edge* edges,
		int num_edges,
		bool pass = false,
		double thresh = 1000000000.0
	);
	/*����mcf.exe��Delaunay����������С����������
	* ����1����С���������������ļ�
	* ����2����С�������㷨��ִ���ļ�·��
	*/
	int mcf_delaunay(
		const char* MCF_problem_file,
		const char* MCF_EXE_PATH
	);
	/*�������ͼ����С�������Ľ�������˷���Ҫ��ǰ����ÿ���ߵ�����ֵ��
	* ����1 �������λ
	* ����2 �����λ������ֵ��
	* ����3 mask
	* ����4 Delaunay��������ڵ�
	* ����5 Delaunay��������
	* ����6 Delaunay������������
	* ����7 �����ʼ�ڵ�
	* ����8 �Ƿ��ƹ�֦���ߣ�Ĭ��Ϊ��
	* ����9 �߳���ֵ��������ֵ��ñ߲���������
	*/
	int QualityMap_MCF(
		Mat& wrapped_phase,
		Mat& unwrapped_phase,
		Mat& mask,
		vector<tri_node>& nodes,
		tri_edge* edges,
		int num_edges,
		int start,
		bool pass = false,
		double thresh = 10000.0
	);
private:
	char error_head[256];
	char parallel_error_head[256];

};

Unwrap::Unwrap()
{
	memset(this->error_head, 0, 256);
	memset(this->parallel_error_head, 0, 256);
	strcpy(this->error_head, "UNWRAP_DLL_ERROR: error happens when using ");
	strcpy(this->parallel_error_head, "UNWRAP_DLL_ERROR: error happens when using parallel computing in function: ");
}

Unwrap::~Unwrap()
{
}

#endif