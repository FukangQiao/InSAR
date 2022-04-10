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


	/*Ĭ�Ϲ��캯��*/
	SBAS_edge()
	{
		isBoundry = false;
		end1 = end2 = num = -1;
		phase_gradient = delta_deformation_vel = delta_epsilon_height = gain = 0.0;
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







	/*@brief ����ʱ�ջ������������ɲ�ָ�����λ����ͼ��ʱ��>��ͼ��ʱ�䣩
	* @param SLCH5Files          SLCͼ���ļ�
	* @param edges               SBAS_edge�����α߽ṹ������
	* @param nodes               SBAS_node�����νڵ�����
	* @param multilook_az        ��λ����ӱ���
	* @param multilook_rg        ��������ӱ���
	* @param ifgSavePath         �����λh5�ļ�����·��
	* @return �ɹ�����0�����򷵻�-1
	*/
	int generate_interferograms(
		vector<string>& SLCH5Files,
		vector<SBAS_edge>& edges,
		vector<SBAS_node>& nodes,
		int multilook_az,
		int multilook_rg,
		const char* ifgSavePath
	);
	/*@brief ���Ʋ�ָ�����λ���ݶ�ջ���ϵ�������ɸ������Ĥ
	* @param phaseFiles               ��ָ�����λ�����ļ�
	* @param wndsize_rg               ���ϵ�����ƾ����򴰿ڴ�С��������
	* @param wndsize_az               ���ϵ�����Ʒ�λ�򴰿ڴ�С��������
	* @param coherence_thresh         �������ֵ
	* @param mask                     �������Ĥ������ֵ��int�ͣ�
	* @return �ɹ�����0�����򷵻�-1
	*/
	int generate_high_coherence_mask(
		vector<string>& phaseFiles,
		int wndsize_rg,
		int wndsize_az,
		double coherence_thresh,
		Mat& mask
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
	/*@brief ���ݸ������Ĥ����������������ڵ���λֵ
	* @param mask                     �������Ĥ����int�ͣ�
	* @param nodes                    �������������ڵ�����
	* @param phase                    ������λ
	* @return �ɹ�����0�����򷵻�-1
	*/
	int set_high_coherence_node_phase(
		Mat& mask,
		vector<SBAS_node>& nodes,
		Mat& phase
	);

private:
	char error_head[256];
};




#endif // !__SBAS__H__
