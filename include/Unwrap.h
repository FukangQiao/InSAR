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
	/** @brief ����Delaunay�����������С����������㷨
	
	@param wrapped_phase                           �������λ
	@param unwrapped_phase                         �����λ������ֵ��
	@param out_mask                                ��������Ĥ������ֵ��
	@param mask                                    ��Ҫ��������ص���Ĥ
	@param nodes                                   Delaunay��������ڵ�
	@param edges                                   Delaunay��������
	@param start                                   �����ʼ��
	@param pass                                    �Ƿ��ƹ�֦���ߣ�Ĭ��Ϊ��
	@param thresh                                  �߳���ֵ��������ֵ��ñ߲���������
	*/
	int MCF(
		const Mat& wrapped_phase,
		Mat& unwrapped_phase,
		Mat& out_mask,
		const Mat& mask,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges,
		int start,
		bool pass = false,
		double thresh = 10000.0
	);
	/*���ڲ������������С����������㷨�����ڵڶ��ν�������ܵ���ʹ�ã�
	* ����1 �ѽ����λ������˵�һ�ν������λ��
	* ����2 �ڶ��ν������������ڵ�����
	* ����3 �ڶ��ν�����������������
	* ����4 �ڶ��ν�����������������
	* ����5 �Ƿ��ƹ�֦���ߣ�Ĭ��Ϊ��
	* ����6 �߳���ֵ��������ֵ��ñ߲���������
	*/
	int MCF_second(
		Mat& unwrapped_phase,
		vector<tri_node>& nodes,
		tri_edge* edges,
		int num_edges,
		bool pass = false,
		double thresh = 1000000000.0
	);
	/** @brief ����mcf.exe��Delaunay����������С����������
	
	@param MCF_problem_file                   ��С���������������ļ�
	@param MCF_EXE_PATH                       ��С�������㷨��ִ���ļ�·��
	@return �ɹ�����0�����򷵻�-1
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
	/** @brief �������ͼ����С�������Ľ������һ�����ƹ��в�������ͼ����
	
	@param wrapped_phase                      �������λ
	@param unwrapped_phase                    �����λ
	@param out_mask                           �ѽ����Ԫ��Ĥ������ֵ��
	@param nodes                              Delaunay��������ڵ�
	@param edges                              Delaunay���������
	@param distance_thresh                    �߳���ֵ��������ֵ��ñ߲���������
	@param pass                               �Ƿ��ƹ��в�㣨Ĭ���ǣ�
	@return �ɹ�����0�����򷵻�-1
	*/
	int _QualityGuided_MCF_1(
		const Mat& wrapped_phase,
		Mat& unwrapped_phase,
		Mat& out_mask,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges,
		double distance_thresh = 1.5,
		bool pass = true
	);
	/** @brief �������ͼ����С�������Ľ�����ڶ�������һ��δ�����ʹ����С�������������
	
	@param unwrapped_phase                       �ѽ����λ������˵�һ�ν������λ��
	@param nodes                                 δ������ص���ɵ�Delaunay��������ڵ�
	@param edges                                 δ������ص���ɵ�Delaunay���������
	@param distance_thresh                       �߳���ֵ��������ֵ��ͨ���ñ߽��н������
	@return �ɹ�����0�����򷵻�-1
	*/
	int _QualityGuided_MCF_2(
		Mat& unwrapped_phase,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges,
		double distance_thresh = 1.5
	);
	/** @brief �������ͼ����С�������Ľ����
	 
	@param wrapped_phase                       �������λ
	@param unwrapped_phase                     �����λ������ֵ��
	@param coherence_thresh                    ���ϵ��������ֵ��0~1֮�䣬��������ز�������ͼ���������������ز�����С����������
	@param distance_thresh                     �߳���ֵ����������ֵ���������Ͳв����㣩
	@param tmp_path                            �м�������·��
	@param EXE_path                            ��С�����������/Delaunay������������·��
	*/
	int QualityGuided_MCF(
		const Mat& wrapped_phase,
		Mat& unwrapped_phase,
		double coherence_thresh,
		double distance_thresh,
		const char* tmp_path,
		const char* EXE_path
	);
	/** @brief ͳ�Ʒ������������SNAPHU��
	
	@param wrapped_phase_file                            ������λ�ļ���h5��
	@param unwrapped_phase                               �����λ
	@param project_path                                  ����·��
	@param tmp_folder                                    �м�������·��
	@param exe_path                                      snaphu.exe·��
	@return �ɹ�����0�����򷵻�-1
	*/
	int snaphu(
		const char* wrapped_phase_file,
		Mat& unwrapped_phase,
		const char* project_path,
		const char* tmp_folder,
		const char* exe_path
	);

private:
	char error_head[256];
	char parallel_error_head[256];

};



#endif