#pragma once
#ifndef __SBAS__H__
#define __SBAS__H__
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"


/*----------------------------------------*/
/*          С���߼���������ڵ�          */
/*----------------------------------------*/
class InSAR_API SBAS_node
{
public:
	/*Ĭ�Ϲ��캯��*/
	SBAS_node();
	/*�������캯��*/
	SBAS_node(const SBAS_node& cp);
	/*��ʼ�����캯��1*/
	SBAS_node(int num_neigh_edge);
	~SBAS_node();
	/*��ֵ�����������*/
	SBAS_node operator = (const SBAS_node& src);


	/*��ֱ����(m)*/
	double B_spatial;
	/*ʱ�����(day)*/
	double B_temporal;
	/*�ڽӱ�����*/
	int num_neigh_edges;
	/*�ڽӱ����*/
	int* neigh_edges;
	/*�ڵ���λ*/
	double phase;
	/*�ڵ������*/
	double x;
	/*�ڵ�������*/
	double y;
	/*�Ƿ��ѽ��(Ĭ��δ���)*/
	bool b_unwrapped;
	/*�̲߳в�*/
	double epsilon_height;
	/*�����α�����*/
	double deformation_vel;
private:

	
};

/*----------------------------------------*/
/*        С���߼���������߽ṹ��        */
/*----------------------------------------*/
struct SBAS_edge
{
	/*�Ƿ�Ϊ�߽�(Ĭ��Ϊ��)*/
	bool isBoundry;
	/*�����*/
	int num;
	/*�˵�1���*/
	int end1;
	/*�˵�2���*/
	int end2;

	/*��������*/
	double gain;
	/*��λ�ݶȣ�����Ϊ����Ŷ˵� - С��Ŷ˵㣩*/
	double phase_gradient;
	/*�����α��ٶ��ݶ�(����Ϊ����Ŷ˵� - С��Ŷ˵�)*/
	double delta_deformation_vel;
	/*�̲߳в��ݶ�(����Ϊ����Ŷ˵� - С��Ŷ˵�)*/
	double delta_epsilon_height;
	/*Ȩֵ*/
	double weight;


	/*Ĭ�Ϲ��캯��*/
	SBAS_edge()
	{
		isBoundry = false;
		end1 = end2 = num = -1;
		phase_gradient = delta_deformation_vel = delta_epsilon_height = gain = 0.0;
		weight = 1.0;
	}
	/*�������캯��*/
	SBAS_edge(const SBAS_edge& cp)
	{
		isBoundry = cp.isBoundry;
		end1 = cp.end1;
		end2 = cp.end2;
		num = cp.num;
		phase_gradient = cp.phase_gradient;
		delta_deformation_vel = cp.delta_deformation_vel;
		delta_epsilon_height = cp.delta_epsilon_height;
		gain = cp.gain;
		weight = cp.weight;
	}
	/*��ֵ�������*/
	SBAS_edge operator = (const SBAS_edge& cp)
	{
		isBoundry = cp.isBoundry;
		end1 = cp.end1;
		end2 = cp.end2;
		num = cp.num;
		phase_gradient = cp.phase_gradient;
		delta_deformation_vel = cp.delta_deformation_vel;
		delta_epsilon_height = cp.delta_epsilon_height;
		gain = cp.gain;
		weight = cp.weight;
		return *this;
	}
};

/*----------------------------------------*/
/*      С���߼��������������νṹ��      */
/*----------------------------------------*/
struct SBAS_triangle
{
	/*���������*/
	int num;
	/*��1*/
	int p1;
	/*��2*/
	int p2;
	/*��3*/
	int p3;
	/*�����βв�ֵ*/
	double residue;
	/*�������������1*/
	int neigh1;
	/*�������������2*/
	int neigh2;
	/*�������������3*/
	int neigh3;
	/*��1����1��ʼ��*/
	int edge1;
	/*��2����1��ʼ��*/
	int edge2;
	/*��3����1��ʼ��*/
	int edge3;

	/*Ĭ�Ϲ��캯��*/
	SBAS_triangle()
	{
		num = p1 = p2 = p3 = neigh1 = neigh2 = neigh3 = edge1 = edge2 = edge3 = 0;
		residue = 0.0;
	}
	/*�������캯��*/
	SBAS_triangle(const SBAS_triangle& cp)
	{
		this->edge1 = cp.edge1;
		this->edge2 = cp.edge2;
		this->edge3 = cp.edge3;
		this->neigh1 = cp.neigh1;
		this->neigh2 = cp.neigh2;
		this->neigh3 = cp.neigh3;
		this->num = cp.num;
		this->p1 = cp.p1; this->p2 = cp.p2; this->p3 = cp.p3;
		this->residue = cp.residue;
	}
	/*��ֵ(���)*/
	SBAS_triangle operator= (const SBAS_triangle& cp)
	{
		this->edge1 = cp.edge1;
		this->edge2 = cp.edge2;
		this->edge3 = cp.edge3;
		this->neigh1 = cp.neigh1;
		this->neigh2 = cp.neigh2;
		this->neigh3 = cp.neigh3;
		this->num = cp.num;
		this->p1 = cp.p1; this->p2 = cp.p2; this->p3 = cp.p3;
		this->residue = cp.residue;
		return *this;
	}
};

/*----------------------------------------*/
/*             С���߼�������             */
/*----------------------------------------*/
class InSAR_API SBAS
{
public:
	SBAS();
	~SBAS();

	/*@brief д��ʱ�ջ�����������ڵ�
	* @param nodeFile                   �ڵ��ļ�
	* @param B_temporal                 ʱ����ߣ�1��n����λ��day��
	* @param B_effect                   �ռ���ߣ�1��n����λ��m��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_spatialTemporal_node(
		const char* nodeFile,
		Mat& B_temporal,
		Mat& B_effect
	);
	/*@brief ����ʱ�ջ�����������ڵ��ʱ�ջ���ֵ�ͽڵ�����
	* @param nodes                     ��������ڵ�����
	* @param B_temporal                 ʱ����ߣ�1��n����λ��day��
	* @param B_effect                   �ռ���ߣ�1��n����λ��m��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int set_spatialTemporalBaseline(
		vector<SBAS_node>& nodes,
		Mat& B_temporal,
		Mat& B_effect
	);
	/** @brief ��.edge�ļ���ȡDelaunay�������ı���Ϣ
	* @param edge_file               .edge�ļ�
	* @param num_nodes               �ڵ���
	* @param edges                   Delaunay�����������飨����ֵ��
	* @param node_neighbours         ÿ���ڵ���ڽӱ���������ֵ��
	* @return  �ɹ�����0�� ���򷵻�-1
	*/
	int read_edges(
		const char* edge_file,
		int num_nodes,
		vector<SBAS_edge>& edges,
		vector<int>& node_neighbours
	);
	/*@brief ��ʼ��SBAS_node��ֻ��ʼ�����������ϵ��
	* @param node                   SBAS_node�ڵ�����
	* @param edges                  SBAS_edge������
	* @param node_neighbours        ÿ���ڵ���ڽӱ���
	* @return  �ɹ�����0�� ���򷵻�-1
	*/
	int init_SBAS_node(
		vector<SBAS_node>& node,
		vector<SBAS_edge>& edges,
		vector<int>& node_neighbours
	);
	/*@brief ��ʼ��SBAS_triangle��ֻ��ʼ�����������ϵ��
	* @param ele_file            .ele�ļ�
	* @param neigh_file          .neigh�ļ�
	* @param triangles           SBAS_triangle�����νṹ������
	* @param edges               SBAS_edge�����α߽ṹ������
	* @param nodes               SBAS_node�����νڵ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int init_SBAS_triangle(
		const char* ele_file,
		const char* neigh_file,
		vector<SBAS_triangle>& triangles,
		vector<SBAS_edge>& edges,
		vector<SBAS_node>& nodes
	);
	/*@brief ����ʱ�ջ�����������в�㣨�в���ַ���Ϊ��ʱ�룩
	* @param nodes                ʱ�ջ�����������ڵ�����
	* @param edges                ʱ�ջ����������������
	* @param triangles            ʱ�ջ���������������������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int compute_spatialTemporal_residue(
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges,
		vector<SBAS_triangle>& triangles
	);
	/*@brief ����С����������д��DIMACS�ļ���׼����⣨ʱ�ջ�����������
	* @param DIMACS_file          DIMACS�ļ�
	* @param nodes                ʱ�ջ�����������ڵ�����
	* @param edges                ʱ�ջ����������������
	* @param triangle             ʱ�ջ���������������������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int writeDIMACS_temporal(
		const char* DIMACS_file,
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges,
		vector<SBAS_triangle>& triangle
	);
	/*@brief ����ʱ�ջ������������ɲ�ָ�����λ����ͼ��ʱ��>��ͼ��ʱ�䣩,���ɵĲ����λ��ʱ�ջ�����������������Ӧ
	* @param SLCH5Files          SLCͼ���ļ�
	* @param edges               ʱ�ջ�����������߽ṹ������
	* @param nodes               ʱ�ջ�����������ڵ�����
	* @param multilook_az        ��λ����ӱ���
	* @param multilook_rg        ��������ӱ���
	* @param ifgSavePath         �����λh5�ļ�����·��
	* @param b_save_images       �Ƿ񱣴�ΪͼƬ��Ĭ��Ϊ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int generate_interferograms(
		vector<string>& SLCH5Files,
		vector<SBAS_edge>& edges,
		vector<SBAS_node>& nodes,
		int multilook_az,
		int multilook_rg,
		const char* ifgSavePath,
		bool b_save_images = false
	);
	/*@brief ���ݸ������Ĥ����д���������ڵ��ļ�
	* @param mask                     �������Ĥ����(int��)
	* @param nodeFile                 ��������ڵ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int write_high_coherence_node(
		Mat& mask,
		const char* nodeFile
	);
	/*@brief ���ݸ������Ĥ����������������ڵ������ֵ
	* @param mask                     �������Ĥ����int�ͣ�
	* @param nodes                    �������������ڵ�����
	* @return �ɹ�����0�����򷵻�-1
	*/
	int set_high_coherence_node_coordinate(
		Mat& mask,
		vector<SBAS_node>& nodes
	);
	/*@brief ���ݸ������Ĥ����������������ڵ���λֵ�����������ڽڵ�֮�����λ�ݶȣ��ݶȶ���Ϊ�����-С��ţ�
	* @param mask                     �������Ĥ����int�ͣ�
	* @param nodes                    �������������ڵ�����
	* @param edges                    ������������������
	* @param phase                    ������λ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int set_high_coherence_node_phase(
		Mat& mask,
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges,
		Mat& phase
	);
	
	/*@brief ����С����������д��DIMACS�ļ���׼����⣨����ɵ���������
	* @param DIMACS_file          DIMACS�ļ�
	* @param nodes                ����ɵ���������ڵ�����
	* @param edges                ����ɵ��������������
	* @param triangles            ����ɵ�������������������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int writeDIMACS_spatial(
		const char* DIMACS_file,
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges,
		vector<SBAS_triangle>& triangles
	);
	/*@brief ����С����������������ļ��ж�ȡ���(�����ݶ�)
	* @param MCF_solution_file    ��С����������������ļ�
	* @param nodes                ��������ڵ�����
	* @param edges                �������������
	* @param triangles            ������������������
	* @param obj_value            ����Ŀ��ֵ
	* @param flowcount            ������ֵ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int readDIMACS(
		const char* MCF_solution_file,
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges,
		vector<SBAS_triangle>& triangles,
		double* obj_value,
		double* flowcount = NULL
	);
	/*@brief ����ָ�����λ��ջ����ɵ�֮�����λ�ݶ���Ϣ�������ɵ���������ı߶�Ӧ��������h5�ļ���
	* @param phaseFiles           ��ָ�����λ���ݶ�ջ�ļ�
	* @param mask                 ����ɵ���Ĥ
	* @param nodes                �������������ڵ�����
	* @param edges                ������������������
	* @param dstH5File            ����h5�ļ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int saveGradientStack(
		vector<string>& phaseFiles,
		Mat& mask,
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges,
		const char* dstH5File
	);
	/*@brief ���Ʋ�ָ�����λ���ݶ�ջ���ϵ�������ɸ������Ĥ
	* @param phaseFiles               ��ָ�����λ���ݶ�ջ�ļ�
	* @param wndsize_rg               ���ϵ�����ƾ����򴰿ڴ�С��������
	* @param wndsize_az               ���ϵ�����Ʒ�λ�򴰿ڴ�С��������
	* @param coherence_thresh         ����ɵ����ϵ����ֵ��0~1��
	* @param count_thresh             ��Ĥɸѡ��ֵ��0~1����ĳ�����ϵ��������ֵ��ͼ��������count_thresh��ͼ��������õ�Ϊ����ɵ㣩
	* @param mask                     �������Ĥ������ֵ��int�ͣ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int generate_high_coherence_mask(
		vector<string>& phaseFiles,
		int wndsize_rg,
		int wndsize_az,
		double coherence_thresh,
		double count_thresh,
		Mat& mask
	);
	/*@brief ��ˮ��û������ɵ���ֽ��������������ݶ��Ѿ���MCF������
	* @param nodes                   ����ɵ���������ڵ�
	* @param edges                   ����ɵ����������
	* @param start                   �����ʼ�ڵ�
	* @param b_zero_start            �����ʼ��ֵ�Ƿ�����Ϊ0
	* @return �ɹ�����0�����򷵻�-1
	*/
	int floodFillUnwrap(
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges,
		int start,
		bool b_zero_start = false
	);
	/*@brief �����ϵ�����ø���ɵ���������ߵ�Ȩ��
	* @param coherence               ���ϵ��
	* @param nodes                   ����ɵ���������ڵ�
	* @param edges                   ����ɵ����������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int set_weight_by_coherence(
		Mat& coherence,
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges
	);
	/*@brief ����������ڵ��л�ȡ�����λ
	* @param nodes                   ��������ڵ�
	* @param phase                   ��λ������ֵ��inplace������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int retrieve_unwrapped_phase(
		vector<SBAS_node>& nodes,
		Mat& phase
	);
	/*@brief ����ԭʼ�����λ���������ɵ���������в�㣨�в���ַ���Ϊ��ʱ�룩
	* @param nodes                   �������������ڵ�
	* @param edges                   ��������������
	* @param triangles               �������������������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int compute_high_coherence_residue(
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges,
		vector<SBAS_triangle>& triangle
	);
	/*@brief ����ʱ��ά����ݶȣ��������ɵ���������в�㣨�в���ַ���Ϊ��ʱ�룩
	* @param nodes                   �������������ڵ�
	* @param edges                   ��������������
	* @param triangles               �������������������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int compute_high_coherence_residue_by_gradient(
		vector<SBAS_node>& nodes,
		vector<SBAS_edge>& edges,
		vector<SBAS_triangle>& triangle
	);
	/*@brief ������������вв����
	* @param triangles              ��������������
	* @param num                    �в����������ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int residue_num(
		vector<SBAS_triangle>& triangles,
		int* num
	);
	/*@brief ����ʱ�ջ��߷ֲ�����Ӧ��ֵ�õ�������Ͼ��󣬲������Ӧ��ʱ�ջ���
	* @param spatial                        �ռ����(1��n����λ��m)
	* @param temporal                       ʱ����ߣ�1��n����λ��day��
	* @param spatial_thresh                 �ռ������ֵ��m��
	* @param temporal_thresh                ʱ�������ֵ��year��
	* @param formation_matrix               ������Ͼ��󣨷���ֵ��int�ͣ�n��n��
	* @param spatial_baseline               �ռ���߾����������Ͼ����Ӧ����λ��m��
	* @param temporal_baseline              ʱ����߾����������Ͼ����Ӧ����λ��year��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int get_formation_matrix(
		Mat& spatial,
		Mat& temporal,
		double spatial_thresh,
		double temporal_thresh,
		Mat& formation_matrix,
		Mat& spatial_baseline,
		Mat& temporal_baseline
	);
	/*@brief ���ݸ�����Ͼ������ɲ�ָ�����λ����ͼ��ʱ��>��ͼ��ʱ�䣩
	* @param SLCH5Files          SLCͼ���ļ�
	* @param formation_matrix    ������λ��Ͼ���
	* @param spatial_baseline    �ռ���ߣ��������Ͼ����Ӧ��
	* @param temporal_baseline   ʱ����ߣ��������Ͼ����Ӧ��
	* @param multilook_az        ��λ����ӱ���
	* @param multilook_rg        ��������ӱ���
	* @param ifgSavePath         �����λh5�ļ�����·��
	* @param b_save_images       �Ƿ񱣴�ΪͼƬ��Ĭ��Ϊ��
	* @param Goldstein_alpha     Goldstein�˲�ǿ�ȣ�Ĭ��Ϊ0.8��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int generate_interferograms(
		vector<string>& SLCH5Files,
		Mat& formation_matrix,
		Mat& spatial_baseline,
		Mat& temporal_baseline,
		int multilook_az,
		int multilook_rg,
		const char* ifgSavePath,
		bool b_save_images = false,
		double alpha = 0.8
	);
	/*@brief ����ʱ�����ϵ����temporal_coherence��������ʱ�����й���Ч��
	* @param estimated_phase_series              ʱ�����в����λ���ƽ��(n��1)
	* @param phase_series                        ԭʼ�����λ(n��1)
	* @param temporal_coherence                  ʱ�����ϵ��������ֵ��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int compute_temporal_coherence(
		Mat& estimated_phase_series,
		Mat& phase_series,
		double* temporal_coherence
	);
	/*@brief ����ͬ����Ԫʶ�������Ӧ���Ӹ�����λ���ɣ��ֿ��ȡ�����㡢���棩
	@param coregis_slc_files              ��׼��ȥб��SARͼ�����ݶ�ջ���ļ���
	@param ifgSavePath                    �����λh5�ļ�����·��
	@param formation_matrix               SBAS������Ͼ���
	@param spatial_baseline               �ռ���ߣ��������Ͼ����Ӧ��
	@param temporal_baseline              ʱ����ߣ��������Ͼ����Ӧ��
	@param blocksize_row                  �ӿ�ߴ磨�У��������ͬ�ʼ����������ڰ뾶��
	@param blocksize_col                  �ӿ�ߴ磨�У��������ͬ�ʼ����������ڰ뾶��
	@param out_mask                       ��Ĥ�����int�ͣ���Ǿ���EVD�����Ƶ����ص㣬�����thresh_c1_to_c2�йأ�
	@param b_coh_est                      �Ƿ�������ϵ����Ĭ���ǣ�
	@param homogeneous_test_wnd           ͬ�ʼ����������ڴ�С��������homogeneous_test_wnd��homogeneous_test_wnd�� Ĭ��Ϊ21��21��
	@param thresh_c1_to_c2                Э��������2����ֵ���1����ֵ��ֵ��ֵ��0-1֮�䣬Ĭ��Ϊ0.7��С����ֵ�����EVD���ƣ�
	@param b_normalize                    Э��������Ƿ��һ����Ĭ���ǣ�
	@param b_save_images                  �Ƿ񽫸�����λ����ΪͼƬ��Ĭ���ǣ�
	*/
	int adaptive_multilooking(
		vector<string>& coregis_slc_files,
		const char* ifgSavePath,
		Mat& formation_matrix,
		Mat& spatial_baseline,
		Mat& temporal_baseline,
		int blocksize_row,
		int blocksize_col,
		Mat& out_mask,
		bool b_coh_est = true,
		int homogeneous_test_wnd = 21,
		double thresh_c1_to_c2 = 0.7,
		bool b_normalize = true,
		bool b_save_images = true
	);
	/*@brief ���������ȥƽ��һ����ϣ�
	* @param unwrapped_phase                       �����λ
	* @param mask                                  ����ɵ���Ĥ
	* @param coherence                             ���ϵ��
	* @param coh_thresh                            ѡ���Ƶ����ϵ����ֵ
	* @param reference                             �ο������
	* @return �ɹ�����0�����򷵻�-1
	*/
	int refinement_and_reflattening(
		Mat& unwrapped_phase,
		Mat& mask,
		Mat& coherence,
		double coh_thresh,
		int reference
	);
private:
	char error_head[256];
};




#endif // !__SBAS__H__
