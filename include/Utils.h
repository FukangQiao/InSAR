#pragma once
#ifndef __UTILS__H__
#define __UTILS__H__
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"
#include<fstream>
#include<iostream>
#include<string>
#include"..\include\sar_comm.h"
#define INPUTMAXSIZE 1024
#define PI 3.141592653589793238
#define VEL_C 299792458.0
/*********************************************************/
/*                Delaunay������ �ڵ���                  */
/*********************************************************/
class InSAR_API tri_node
{
public:
	/*Ĭ�Ϲ��캯��*/
	tri_node();
	/*�������캯��*/
	tri_node(const tri_node& node);
	/*���캯��
	* ����1 �ڵ�����
	* ����2 �ڵ�����
	* ����3 �ڵ��ڽӱ���
	* ����4 �ڵ���λ
	*/
	tri_node(int, int, int, double);
	~tri_node();
	/*��ֵ�����������ֵ��*/
	tri_node operator = (const tri_node& src);
	/*��ȡ�ڵ���λ
	* ����1 ��λָ�루����ֵ��
	*/
	int get_phase(double* phi) const;
	/*��ȡ�ڵ���������
	* ����1 �����
	* ����2 �����
	*/
	int get_pos(int* rows, int* cols) const;
	/*�ڵ���λ��ֵ
	* ����1 ������λ
	*/
	int set_phase(double phi);
	/*��ȡ�ڽӱ�ָ��
	* ����1 ָ���ڽӱ�ָ���ָ�루����ֵ��
	* ����2 �ڽӱ߸���ָ�루����ֵ��
	*/
	int get_neigh_ptr(long** ptr2ptr, int* num) const;
	/*�ı���״̬
	* ����1 �Ƿ��Ѿ����
	*/
	int set_status(bool b_unwrapped);
	/*�ı�ƽ��״̬
	* ����1 �Ƿ����ڲв�ƽ��������
	*/
	int set_balance(bool b_balanced);
	/*��ӡ�ڽӱ����
	* 
	*/
	int print_neighbour() const;
	/*��ȡ�ڽӱ߸���
	* ����1 �ڽӱ߸���ָ��
	*/
	int get_num_neigh(int* num_neigh) const;
	/*��ȡ����һ�ڵ�ľ���
	* ����1 ��һ�ڵ�
	* ����2 ����
	*/
	int get_distance(tri_node node, double* distance) const;
	/*��ȡ���״̬
	* ����ֵ���Ƿ��ѽ����
	*/
	bool get_status() const;
	/*��ȡƽ��״̬
	* ����ֵ���Ƿ�ƽ�⣩
	*/
	bool get_balance() const;
	/*�����Ƿ�ڵ����ڲв�������
	*/
	bool is_residue_node() const;
	/*���ýڵ��Ƿ����ڲв�ڵ�
	*/
	int set_residue(bool b_res);
	/*��ȡ�α�����*/
	double get_vel() const;
	/*��ȡ�߳����*/
	double get_height() const;
	/*�����α�����*/
	int set_vel(double vel);
	/*���ø߳����*/
	int set_height(double height);

private:

	/*****************InSAR�������*******************/

	/*�Ƿ��ѽ��(Ĭ��δ���)*/
	bool b_unwrapped;
	/*�Ƿ����ڲв�ڵ�*/
	bool b_residue;
	/*�Ƿ�����ƽ�������εĶ��㣨Ĭ��Ϊ�ǣ���ͬʱ��PS-InSAR�г䵱�Ƿ�ڵ㱻�����ı�־(Ϊtrue��ʾ���������� Ϊfalse��ʾ������)*/
	bool b_balanced;
	/*�ڵ���������ʼֵΪ0��*/
	int rows;
	/*�ڵ���������ʼֵΪ0��*/
	int cols;
	/*�ڵ��ڽӱ���*/
	int num_neigh_edges;
	/*�ڵ���λ*/
	double phase;
	/*�ڵ��ڽӱ����*/
	long* neigh_edges;

	/*****************PS-InSAR�������*******************/
	
	/*�α�����*/
	double vel;
	/*�߳����*/
	double epsilon_height;
};

/*********************************************************/
/*             Delaunay������ �����νṹ��               */
/*********************************************************/
struct triangle
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
	triangle()
	{
		num = p1 = p2 = p3 = neigh1 = neigh2 = neigh3 = edge1 = edge2 = edge3 = 0;
		residue = 0.0;
	}
	/*�������캯��*/
	triangle(const triangle& cp)
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
	triangle operator= (const triangle& cp)
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


/*********************************************************/
/*             Delaunay������ �����α߽ṹ��             */
/*********************************************************/
struct tri_edge
{
	/**********InSAR����**********/

	/*�������棨��Ŵ�С����Ϊ����*/
	double gain;
	/*��λ��������������ͼ�������*/
	double quality;
	/*�����к�*/
	int num;
	/*�˵�1*/
	int end1;
	/*�˵�2*/
	int end2;
	/*�в�߱�־*/
	bool isResidueEdge;
	/*����߽��־*/
	bool isBoundry;


	/**********PS_InSAR����**********/

	/*�����α��ٶȲ�ϵ����4 * pi / lambda * Ti��*/
	//double coef_delta_vel;
	/*�߳����ϵ����4 * pi * bperp_i / lambda / R_i / sin_theta_i  ��*/
	//double coef_delta_height;
	/*�����α��ٶȲ�(����Ϊ������ - С����)*/
	double delta_vel;
	/*�߳����(����Ϊ������ - С����)*/
	double delta_height;
	/*ģ�����ϵ��*/
	double MC;
	/*�˵���λ���λ���Ϊ������Ŷ˵��С��Ŷ˵㣩*/
	double phase_diff;

	/*Ĭ�Ϲ��캯��*/
	tri_edge() {
		gain = 0.0;
		quality = 0.0;
		num = 0;
		end1 = 0; end2 = 0;
		isResidueEdge = false;
		isBoundry = false;
		delta_vel = 0.0;
		delta_height = 0.0; MC = 0.0; phase_diff = 0.0;
	}
	/*�������캯��*/
	tri_edge(const tri_edge& cp)
	{
		gain = cp.gain;
		quality = cp.quality;
		num = cp.num;
		end1 = cp.end1; end2 = cp.end2;
		isResidueEdge = cp.isResidueEdge;
		isBoundry = cp.isBoundry;
		delta_vel = cp.delta_vel;
		delta_height = cp.delta_height; MC = cp.MC; phase_diff = cp.phase_diff;
	}
	/*��ֵ�����������ֵ��*/
	tri_edge operator = (const tri_edge& cp)
	{
		gain = cp.gain;
		quality = cp.quality;
		num = cp.num;
		end1 = cp.end1; end2 = cp.end2;
		isResidueEdge = cp.isResidueEdge;
		isBoundry = cp.isBoundry;
		delta_vel = cp.delta_vel;
		delta_height = cp.delta_height; MC = cp.MC; phase_diff = cp.phase_diff;
		return *this;
	}
};

/*********************************************************/
/*          Delaunay������ �����α����кŽṹ��          */
/*********************************************************/

struct edge_index
{
	double quality;
	int num;
	edge_index() { num = 0; quality = 0.0; }
	friend bool operator < (struct edge_index a, struct edge_index b)
	{
		return a.quality > b.quality;
	}
	
};

/*-------------------------------------------------------*/
/*                   ��������ڵ�ṹ��                  */
/*-------------------------------------------------------*/

struct node_index
{
	/*�ڵ���������0��ʼ��*/
	int row;
	/*�ڵ���������0��ʼ��*/
	int col;
	/*Ĭ�Ϲ��캯��*/
	node_index()
	{
		row = 0; col = 0;
	}
	/*�������캯��*/
	node_index(const node_index& cp)
	{
		this->row = cp.row; this->col = cp.col;
	}
	/*��ֵ����*/
	node_index operator = (const node_index& cp)
	{
		this->row = cp.row; this->col = cp.col;
		return *this;
	}
};


/*********************************************************/
/*               ����SAR��������������                 */
/*********************************************************/
class InSAR_API Utils
{
public:
	Utils();
	~Utils();
	/*��������ݶ�
	 ����1 Դ����
	 ����2 �з����ݶȣ�����ֵ��
	 ����3 �з����ݶȣ�����ֵ��
	 ����4 �Ƿ���ʹ���ݶȾ����Դ�����С��ͬ��Ĭ�ϲ��㣩
	*/
	int diff(Mat& Src, Mat& diff_1, Mat& diff_2, bool same = true);
	/*���������λ
	 ����1 ��ͼ�񣨸���
	 ����2 ��ͼ�񣨸���
	 ����3 ������λ������ֵ��
	*/
	int generate_phase(const ComplexMat& Master, const ComplexMat& Slave, Mat& phase);

	/** @brief �����Ȼ��ɹ�����
	 
	@param master_image                       ��ͼ�񣨸���
	@param slave_image                        ��ͼ�񣨸���
	@param coherence                          ���ϵ��������ֵ��
	@return �ɹ�����0�����򷵻�-1
	*/
	int real_coherence(ComplexMat& master_image, ComplexMat& slave_image, Mat& coherence);
	/** @brief �����Ȼ��ɹ������������ƴ��ڳߴ�ӿڣ�
	
	@param master_image                       ��ͼ�񣨸���
	@param slave_image                        ��ͼ�񣨸���
	@param est_wndsize_rg                     ���ƴ��ھ�����ߴ磨������
	@param est_wndsize_az                     ���ƴ��ڷ�λ��ߴ磨������
	@param coherence                          ���ϵ��������ֵ��
	*/
	int real_coherence(
		const ComplexMat& master_image,
		const ComplexMat& slave_image,
		int est_wndsize_rg,
		int est_wndsize_az,
		Mat& coherence
	);
	/** @brief Ƶ���޹���ɹ�����
	
	 @param master_image                        ��ͼ�񣨸���
	 @param slave_image                         ��ͼ�񣨸���
	 @param coherence                           ���ϵ��������ֵ��
	 @return �ɹ�����0�����򷵻�-1
	*/
	int complex_coherence(ComplexMat& master_image, ComplexMat& slave_image, Mat& coherence);
	/** @brief Ƶ���޹���ɹ������������ƴ��ڳߴ�ӿڣ�
	
	@param master_image                         ��ͼ��
	@param slave_image                          ��ͼ��
	@param est_wndsize_rg                       ���ƴ��ھ�����ߴ磨������
	@param est_wndsize_az                       ���ƴ��ڷ�λ��ߴ磨������
	@param coherence                            ���ϵ��������ֵ��
	@return �ɹ�����0�����򷵻�-1
	*/
	int complex_coherence(
		const ComplexMat& master_image,
		const ComplexMat& slave_image,
		int est_wndsize_rg,
		int est_wndsize_az,
		Mat& coherence
	);
	/** @brief ���ݸ�����λ�����ϵ��
	@param phase                          ������λ
	@param coherence                      ���ϵ��������ֵ��
	@return �ɹ�����0�����򷵻�-1
	*/
	int phase_coherence(Mat& phase, Mat& coherence);
	/** @brief ���ݸ�����λ�����ϵ���������ƴ��ڳߴ�ӿڣ�
	
	@param phase                          ������λ
	@param est_wndsize_rg                 ���ƴ��ھ�����ߴ磨������
	@param est_wndsize_az                 ���ƴ��ڷ�λ��ߴ磨������
	@param coherence                      ���ϵ��������ֵ��
	@return �ɹ�����0�����򷵻�-1
	*/
	int phase_coherence(
		const Mat& phase,
		int est_wndsize_rg,
		int est_wndsize_az,
		Mat& coherence
	);
	/*�����λ��������
	* ����1 ������λ
	* ����2 ��λ�����������ֵ��
	* ����3 ���㴰�ڴ�С��������
	*/
	int phase_derivatives_variance(Mat& phase, Mat& phase_derivatives_variance, int wndsize = 3);
	/*���ɻ�����
	* ����1 ԭʼ��λ
	* ����2 ���ɻ����루����ֵ��
	* ����3 ����ֵ�������־��벻�ܳ�����ֵ��
	*/
	int max_integrable_distance(Mat& phase, Mat& max_integrable_distance, double conservative_thresh = 20.0);
	/*FFTSHIFT
	 ����1 ��fftshift�ľ���ԭ�ؽ���fftshift������
	*/
	int fftshift(Mat& matrix);

	/*���������λͼ�Ĳв�ֵ���㣩
	 ����1 ������λ
	 ����2 �в����󣨷���ֵ��
	*/
	int residue(Mat& phase, Mat& residue);
	/*����Delaunay��������Ĳв�ֵ�����ұ�ע�в�ߺͲв�ڵ�,���ڽ��ʱ�ܿ���
	* ����1 Delaunay�����������νṹ������
	* ����2 Delaunay����������������
	* ����3 Delaunay�������ڵ�����
	* ����4 Delaunay�������߽ṹ������
	* ����5 Delaunay������������
	*/
	int residue(triangle* tri, int num_triangle, vector<tri_node>& nodes, tri_edge* edges, int num_edges);
	/** @brief ����Delaunay��������Ĳв�ֵ�����ұ�ע�в�ߺͲв�ڵ㣩
	
	@param triangle                              Delaunay�����������νṹ������
	@param nodes                                 Delaunay�������ڵ�����
	@param edges                                 Delaunay�������߽ṹ������
	@param distance_thresh                       �߳�����ֵ����������ֵ������в����㣩
	@return �ɹ�����0�����򷵻�-1
	*/
	int residue(
		vector<triangle>& triangle,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges,
		double distance_thresh
	);
	/*����mask��ɸѡ�������㣩
	* ����1 ���ϵ������
	* ����2 mask�پ��󣨷���ֵ��
	* ����3 ���ڰ뾶
	* ����4 ��ֵ
	*/
	int gen_mask(Mat& coherence, Mat& mask, int wnd_size, double thresh);
	/*����mask��ɸѡ�������㣩
	* ����1 ���ϵ������
	* ����2 ��λ��������
	* ����3 mask�پ��󣨷���ֵ��
	* ����4 ���ڰ뾶
	* ����5 ���ϵ����ֵ
	* ����6 ��λ����������ֵ
	*/
	int gen_mask(
		Mat& coherence,
		Mat& phase_derivatives,
		Mat& mask, int wnd_size,
		double coh_thresh,
		double phase_derivative_thresh
	);
	/*�����趨��ֵɸѡ�в��
	* ����1 ԭʼ�в�����
	* ����2 ɸѡ��в�����
	* ����3 ɸѡ��ֵ������0��
	* ����4 �в�����
	*/
	int residue_sift(Mat& residue_src, Mat& residue_dst, double thresh, long* num_residue);
	/*������λ����-pi,pi��
	 ����1 ��������λ
	 ����2 ���ƺ����λ������ֵ��
	*/
	int wrap(Mat& Src, Mat& Dst);

	/*���л����ۼƻ���
	 ����1 ����������
	 ����2 ���ַ���(dim = 1,���м��� dim = 2,���м���)
	*/
	int cumsum(Mat& phase, int dim);
	/*������㣨��ά��
	* ����1 ����һ(n * 3)
	* ����2 ������(n * 3)
	* ����3 ���
	*/
	int cross(Mat& vec1, Mat& vec2, Mat& out);

	/*д��DIMACS�ļ���������С�������⣩
	 ����1 Ŀ���ļ���
	 ����2 �в�����
	 ����3 ���ϵ������
	 ����4 �в����ֵ(����0)
	*/
	int write_DIMACS(const char* DIMACS_file_problem, Mat& residue, Mat& coherence, double thresh);
	/*д��DIMACS�ļ���������С�������⣬�������������磩
	* ����1 Ŀ���ļ���
	* ����2 Delaunay�����νṹ������
	* ����3 Delaunay����������
	* ����4 Delaunay�������ڵ�����
	* ����5 Delaunay�������߽ṹ������
	* ����6 Delaunay������������
	* ����7 ÿ���ڵ�ķ���
	*/
	int write_DIMACS(
		const char* DIMACS_file_problem,
		triangle* tri,
		int num_triangle,
		vector<tri_node>& nodes,
		tri_edge* edges,
		long num_edges,
		Mat& cost
	);
	/** @brief д��DIMACS�ļ���������С�������⣬Delaunay�������磩
	
	@param DIMACS_file_problem                         Ŀ��DIMACS�ļ�
	@param triange                                     Delaunay�����νṹ������
	@param nodes                                       Delaunay�������ڵ�����
	@param edges                                       Delaunay�������߽ṹ������
	@param cost                                        ÿ���ڵ�ķ���
	@return �ɹ�����0�����򷵻�-1
	*/
	int write_DIMACS(
		const char* DIMACS_file_problem,
		vector<triangle>& triangle,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges,
		const Mat& cost
	);
	/*��ȡDIMACS�ļ�����ȡ������������
	 ����1 ��С������������ļ�
	 ����2 ֦��·��1
	 ����3 ֦��·��2
	 ����4 ������λͼ������
	 ����5 ������λͼ������
	*/
	int read_DIMACS(const char* DIMACS_file_solution, Mat& k1, Mat& k2, int rows, int cols);
	/*��ȡDIMACS�ļ�����ȡ������������
	* ����1 ��С������������ļ�
	* ����2 Delaunay�������߽ṹ������
	* ����3 Delaunay������������
	* ����4 Delaunay�������ڵ�����
	* ����5 Delaunay����������������
	* ����6 Delaunay����������������
	*/
	int read_DIMACS(
		const char* DIMACS_file_solution,
		tri_edge* edges,
		int num_edges,
		vector<tri_node>& nodes,
		triangle* tri,
		int num_triangle
	);
	/** @brief ��ȡDIMACS�ļ�����ȡ������������
	
	@param DIMACS_file_solution                         ��С������������ļ�
	@param edges                                        Delaunay�������߽ṹ������
	@param nodes                                        Delaunay�������ڵ�����
	@param triangle                                     Delaunay����������������
	@param return �ɹ�����0�����򷵻�-1
	*/
	int read_DIMACS(
		const char* DIMACS_file_solution,
		vector<tri_edge>& edges,
		vector<tri_node>& nodes,
		vector<triangle>& triangle
	);
	/*��OpenCV Mat�����Զ����Ʒ�ʽд��Ŀ���ļ�
	* ����1 Ŀ���ļ���
	* ����2 ��д������
	*/
	int cvmat2bin(const char* Dst_file, Mat& Src);
	/*�Ӷ������ļ��ж����ݣ���������ת����OpenCV Mat��ʽ
	* ����1 �������ļ�
	* ����2 Ŀ�����
	*/
	int bin2cvmat(const char* Src_file, Mat& Dst);
	/*InSAR���Ӵ�����׼֮����У� �ı�ͼ��ߴ磩
	* ����1 ��ͼ��SLC��
	* ����2 ��ͼ��SLC��
	* ����3 ������λ
	* ����4 ���ӱ���������1��
	*/
	int multilook(ComplexMat& Master, ComplexMat& Slave, Mat& phase, int multilook_times);
	/** @brief InSAR���Ӵ������ı�ͼ��ߴ磩
	
	@param master_slc                    ��ͼ��
	@param slave_slc                     ��ͼ��
	@param multilook_rg                  ��������ӱ���
	@param multilook_az                  ��λ����ӱ���
	@param multilooked_phase             ������λ
	*/
	int multilook(const ComplexMat& master, const ComplexMat& slave, int multilook_rg, int multilook_az, Mat& phase);
	/** @brief ����λת����cos��sin��ʵ�����鲿��
	
	@param phase                     ������λ
	@param cos                       ʵ��
	@param sin                       �鲿
	@return �ɹ�����0�����򷵻�-1
	*/
	int phase2cos(const Mat& phase, Mat& cos, Mat& sin);
	/*84����ϵת��γ������ϵ
	* ����1 84����ϵ����
	* ����2 ��γ������ϵ���꣨��/��/�ף�
	*/
	int xyz2ell(Mat xyz, Mat& llh);
	/*��γ������ϵת84����ϵ
	* ����1 ��γ������ϵ���꣨γ��/����/�߶ȣ�
	* ����2 84����ϵ����
	*/
	int ell2xyz(Mat llh, Mat& xyz);


	/*
	* SARͼ���ļ���д��������
	*/

	/*��img�ļ��ж���ͼ�����ݲ�ת����opencv mat
	* ����1 img�ļ���
	* ����2 cvmat
	*/
	int img2cvmat(const char* filename, Mat& cvmat);
	/*��cvmat����д�뵽img�ļ���
	* ����1 img�ļ���
	* ����2 cvmat
	*/
	int cvmat2img(
		const char* filename, 
		Mat& cvmat,
		Esip_ImgLayer* imglayer,
		Esip_LayerInfo* layerinfo
	);
	/*��ComplexMat���ݱ��浽img�ļ���(��SLCд�뵽img�ļ�)
	* ����1 Ŀ��img�ļ�
	* ����2 ComplexMat����
	* ����3 Esip_ImgLayer
	* ����4 Esip_LayerInfo
	*/
	int complexmat2img(const char* filename, ComplexMat& complexmat, Esip_ImgLayer* imglayer,  Esip_LayerInfo* layerinfo);
	/*��img�ļ��ж�����ͼ�����ݲ�ת����ComplexMat
	* ����1 img�ļ���
	* ����2 ComplexMat
	*/
	int img2complexmat(const char* filename, ComplexMat& complexmat);
	

	/*��imgͼ���ļ��ж�ȡ��ͼ��ʵ�����鲿����
	* ����1 �ļ���
	* ����2 ͼ���ȣ�������
	* ����3 ͼ��߶ȣ�������
	* ����4 ʵ�����ݣ�����ֵ��
	* ����5 �鲿���ݣ�����ֵ��
	*/
	int getRealImag(const char* filename, int width, int height, char* realBuf, char* imagBuf);
	/*��img�ļ��ж�ȡͼ�����ݣ�������λ/��ָ�����λ��
	* ����1 Դimg�ļ�
	* ����2 �������ݿ�ָ��
	*/
	int getImagesData(const char* filename, char* outbuffer);
	/*��ȡimg�ļ�ͷ��Flag��ע�⣺�˺���������Ҫ����ʹ�ã���Ϊ��û�йرմ򿪵��ļ���
	* ����1 �ļ���
	* ����2 Esip_HeaderTag�ṹ��
	* ����ֵ ƫ�ƺ���ļ�ָ��
	*/
	FILE* getFileHeadFlag(const char* filename, Esip_HeaderTag* esip_header);
	/*��ȡ���ڵ��ַ��ע�⣺�˺���������Ҫ����ʹ�ã���Ϊ��û�йرմ򿪵��ļ���
	* ����1 �ļ�ָ��
	* ����2 �ļ�ͷ
	* ����ֵ ���ڵ��ַ
	*/
	GUInt32 getRootNodeptr(FILE* fp, GInt32 headerPtr);
	/*��ȡͼ����Ϣ�ڵ��ַ
	* ����1 �ļ�ָ��
	* ����2 ���ڵ��ַ
	* ����ֵ ͼ����Ϣ�ڵ��ַ
	*/
	GUInt32 getImgLayerNodeptr(FILE* fp, GInt32 rootPtr);
	/*��ȡͼ����Ϣ�ӽڵ�ָ��
	* ����1 �ļ�ָ��
	* ����2 ͼ����Ϣ���ڵ��ַ
	* ����3 ͼ����Ϣ��ַ
	* ����4 ͼ����ַ
	*/
	int getImgLayerChildNodeptr(FILE* fp, GInt32 imgLayerPtr, GInt32* layerInfoPtr, GInt32* imgBlockPtr);
	/*��ȡͼ�������
	* ����1 �ļ�ָ��
	* ����2 ͼ����ַ
	* ����3 ����buffer
	*/
	int getImgBlockData(FILE* fp, GInt32 imgBlockPtr, char* dataBuf);
	/*��ȡimg�ļ���ͼ��Ŀ��/�߶�/ͼ������/������ռ�ڴ��С
	* ����1 �ļ���
	* ����2 ��ȣ�����ֵ��
	* ����3 �߶ȣ�����ֵ��
	* ����4 ͼ�����ͣ�SLC/phase/diff_phase��
	* ����5 ÿ������ռ���ڴ��С��byte��
	*/
	int getImgWidthAndHeight(const char* filename, GInt32* width, GInt32* height, Esip_LayerType* imgType, int* bytes_perpixel);
	/*��img�ļ��л�ȡimglayer��Ϣ
	* ����1 img�ļ�·��
	* ����2 imglayer�ṹ��ָ�루����ֵ��
	*/
	int get_imglayer(const char* filename, Esip_ImgLayer* imglayer);
	/*��img�ļ��л�ȡlayerinfo��Ϣ
	* ����1 img�ļ�·��
	* ����2 layerinfo�ṹ��ָ��
	*/
	int get_layerinfo(const char* filename, Esip_LayerInfo* layerinfo);
	/*��ȡimg�ļ��еĿ��Ƶ�͹�����ݵȸ�������(������ֵС��0�������Ƿ���Ҫ�ͷ���Ӧ�ڴ�)
	* ����1 img�ļ�·��
	* ����2 ��������ָ�루����ֵ��
	*/
	int getAdditionalData(const char* filename, Esip_Additional_Data* esip_additional_data);
	/*��img�ļ�д����Ƶ�͹�����ݵȸ�������
	* ����1 img�ļ�·��
	* ����2 д������ָ��
	*/
	int writeAdditionalData(const char* filename, Esip_Additional_Data* esip_additional_data);
	/*��ȡimg�ļ��еĿ��Ƶ�͹�����ݵȸ��������ĵ�ַ
	* 
	*/
	int getAddtionalAddr(FILE* fp, GInt32 imgLayerPtr, long* AdditionalDataPtr);
	/*�ͷ�Esip_Additional_Data�е�malloc������ڴ�
	* ����1 Esip_Additional_Dataָ��
	*/
	int free_AdditionalData(Esip_Additional_Data* ptr);
	/*��ʼ��Esip_Additional_Data�ṹ�����������ָ��
	* ����1 Esip_Additional_Dataָ��
	*/
	int init_AdditionalDataPtr(Esip_Additional_Data* ptr);
	/*��ʼ�������Esip_Additional_Data�ṹ���������ݣ����ı��ļ��ж�ȡ��
	* ����1 Esip_Additional_Data�ṹ��
	* ����2 Ŀ���ı��ļ���
	*/
	int init_AdditionalData(Esip_Additional_Data* addtional_data, const char* filename);
	/*��ȡ��ǰʱ��
	* ����1 ʱ��ṹ��ָ��
	*/
	void gettimeofday(ModTime* tp);
	/*���첢д��EsipHeaderTag
	* ����1 �ļ�ָ��
	* ����2 �ļ�ͷ��ַ
	*/
	int createEsipHeaderTag(FILE* fp, GInt32 headerPrt);
	/*д���ļ�ͷ��Ϣ
	*/
	int createEsipFile(FILE* fp, int file_pos, Esip_File* esip_file);
	/*д����ڵ�*/
	int writeRootNode(FILE* fp, int nodePos, int* childPtr);
	/**/
	int createEsipEntry(FILE* fp, int nodePos, Esip_Entry* esip_entry);
	/*д��imglayer�ڵ�*/
	int writeImgLayerNode(FILE* fp, int nodePos, Esip_Entry* esip_entry, Esip_ImgLayer* esip_imglayer);
	/*д��imglayer����*/
	int writeImgLayerData(FILE* fp, int nodePos, Esip_ImgLayer* esip_imgLayer);
	/**/
	int writeHfaNodeData(FILE* fp, int nodePos, void* buf, int buflen);
	/*��img�ļ�д��ʵ�����鲿���ݣ�SLC��
	* ����1 �ļ�ָ��
	* ����2 ���ݽڵ��ַ
	* ����3 ʵ������
	* ����4 �鲿����
	* ����5 SLCͼ����
	* ����6 SLCͼ��߶�
	*/
	int writeRealAndImagData(FILE* fp, int nodePos, void* realBuf, void* imagBuf, int width, int height);
	/*����Esip_ImgLayer�ṹ��
	* ����1 Esip_ImgLayer�ṹ��ָ��
	* ����2 ͼ����
	* ����3 ͼ��߶�
	* ����4 ͼ�����ͣ����Ӹ�ͼ��/������λͼ/��ָ�����λͼ��
	* ����5 ÿ��������ռ�ֽڴ�С
	*/
	int init_esip_imglayer(
		Esip_ImgLayer* imglayer,
		int width,
		int height,
		int type,
		int bytes_perpixel
	);
	/*����Esip_LayerInfo�ṹ��
	* ����1 Esip_LayerInfo�ṹ��ָ��
	* ����2 ���ݻ�ȡ��ʽ��1���������ݣ�2����ʵ���ݣ�
	* ����3 ��λ��������
	* ����4 ������������
	* ����5 ��λ����ʼʱ��
	* ����6 ��������ʼʱ��
	*/
	int init_esip_layerinfo(
		Esip_LayerInfo* layerinfo,
		int data_simulation,
		double azimuthSample,
		double rangeSample,
		double azimuthStartTime,
		double rangeStartTime
	);


	/*******************************************************/
	/*                     ͼ��洢���߼�                  */
	/*******************************************************/

	/*��������SLC����ͼ
	* ����1 Ŀ���ļ���
	* ����2 �����������������ӷ�ΧdB��
	* ����3 ���Ӹ�ͼ��
	*/
	int saveSLC(const char* filename, double db, ComplexMat& SLC);
	/*���������λͼ
	* ����1 Ŀ���ļ���
	* ����2 ��ɫӳ�䣨jet/hsv/cool/parula�ȣ�
	* ����3 ��������λ
	*/
	int savephase(const char* filename, const char* colormap, Mat phase);
	/*ͼ���ز���
	* ����1 ԭͼ��
	* ����2 Ŀ��ͼ��
	* ����3 Ŀ��ͼ��߶�
	* ����4 Ŀ��ͼ����
	*/
	int resampling(const char* Src_file, const char* Dst_file, int dst_height, int dst_width);
	/*����SARͼ���������λ����
	* ����1 ����SARͼ��
	* ����2 ������λͼ
	* ����3 ����ͼ��
	* ����4 SARͼ��ռ��
	*/
	int amplitude_phase_blend(
		const char* amplitude_file,
		const char* phase_file,
		const char* blended_file,
		double SAR_ratio = 0.9
	);



	/*******************************************************/
	/*                Delaunay��������غ�����             */
	/*******************************************************/

	/*��.edge�ļ���ȡDelaunay�������ı���Ϣ
	* ����1 .edge�ļ�
	* ����2 ָ��߽ṹ���ָ�루����ֵ���ڴ���Ҫ�ֶ��ͷţ�
	* ����3 ָ��߸�����ָ�루����ֵ��
	* ����4 ͳ��ÿ���ڵ���ڽӱ���������ֵ���ڴ���Ҫ�ֶ��ͷţ�
	* ����5 �ڵ���
	*/
	int read_edges(const char* filename, tri_edge** edges, long* num_edges, int** neighbours, long num_nodes);
	/** @brief ��.edge�ļ���ȡDelaunay�������ı���Ϣ
	
	@param edge_file               .edge�ļ�
	@param num_nodes               �ڵ���
	@param edges                   Delaunay�����������飨����ֵ��
	@param node_neighbours         ÿ���ڵ���ڽӱ���������ֵ��
	@return  �ɹ�����0�� ���򷵻�-1
	*/
	int read_edges(
		const char* edge_file,
		vector<tri_edge>& edges,
		vector<int>& node_neighbours,
		long num_nodes
	);
	/*��ʼ��Delaunay�������ڵ�
	* ����1 �ڵ����飨����ֵ��
	* ����2 ��λ(double��)
	* ����3 ��λmask��int �ͣ�
	* ����4 edges�ṹ������
	* ����5 edges����
	* ����6 ÿ���ڵ���ڽӱ���Ϣ
	* ����7 �ڵ���
	*/
	int init_tri_node(
		vector<tri_node>& node_array,
		Mat& phase,
		Mat& mask,
		tri_edge* edges,
		long num_edges,
		int* num_neighbour,
		int num_nodes
	);
	/** @brief ��ʼ��Delaunay�������ڵ�
	
	@param node_array                 �ڵ����飨����ֵ��
	@param phase                      ��λֵ
	@param mask                       ��λ��Ĥ
	@param edges                      Delaunay��������߽ṹ������
	@param node_neighbours            ÿ���ڵ���ڱ߸���
	@param num_nodes                  �ڵ���
	@return �ɹ�����0�����򷵻�-1
	*/
	int init_tri_node(
		vector<tri_node>& node_array,
		const Mat& phase,
		const Mat& mask,
		const vector<tri_edge>& edges,
		const vector<int>& node_neighbours,
		int num_nodes
	);
	/** @brief ��ʼ��Delaunay�����������λ��
	
	@param edges                  Delaunay������������飨�Ѿ�ʹ��read_edges������ʼ�����ģ�
	@param node_array             Delaunay��������ڵ����飨�Ѿ�ʹ��init_tri_node������ʼ�����ģ�
	@return �ɹ�����0�����򷵻�-1
	*/
	int init_edge_phase_diff(
		vector<tri_edge>& edges,
		const vector<tri_node>& node_array
	);
	/*��ʼ��Delaunay�������ߵ���λ����
	* ����1 ��λ����ͼ
	* ����2 Delaunay�������߽ṹ������ָ��
	* ����3 Delaunay�������߽ṹ�������С
	* ����4 Delaunay�������ڵ�����
	*/
	int init_edges_quality(Mat& quality, tri_edge* edges, int num_edges, vector<tri_node>& nodes);
	/** @brief ��ʼ��Delaunay�������ߵ���λ����ָ��
	
	@param quality_index                  ��λ����ͼָ��������λ�����෴��
	@param edges                          Delaunay�������߽ṹ������
	@param nodes                          Delaunay�������ڵ�����
	@return �ɹ�����0�� ���򷵻�-1
	*/
	int init_edges_quality(
		const Mat& quality_index,
		vector<tri_edge>& edges,
		const vector<tri_node>& nodes
	);
	/*��.ele�ļ���.neigh�ļ���ȡDelaunay����������������Ϣ
	* ����1 .ele�ļ�
	* ����2 .neigh�ļ�
	* ����3 �����νṹ������ָ�루����ֵ, �ڴ���Ҫ�ֶ��ͷţ�
	* ����4 �����θ���������ֵ��
	* ����5 Delaunay�������ڵ�����
	* ����6 Delaunay������������
	* ����7 Delaunay������������
	*/
	int read_triangle(
		const char* ele_file,
		const char* neigh_file,
		triangle** tri,
		int* num_triangle,
		vector<tri_node>& nodes,
		tri_edge* edges,
		int num_edgs
	);
	/** @brief ��.ele�ļ���.neigh�ļ���ȡDelaunay����������������Ϣ
	
	@param ele_file                        .ele�ļ�
	@param neigh_file                      .neigh�ļ�
	@param triangle                        �����νṹ�����飨����ֵ��
	@param nodes                           Delaunay�������ڵ�����
	@param edges                           Delaunay������������
	@return �ɹ�����0�����򷵻�-1
	*/
	int read_triangle(
		const char* ele_file,
		const char* neigh_file,
		vector<triangle>& triangle,
		vector<tri_node>& nodes,
		vector<tri_edge>& edges
	);
	/*����Delaunay������
	* ����1 .node�ļ�
	* ����2 triangle.exe����·��
	*/
	int gen_delaunay(const char* filename, const char* exe_path);
	/*д.node�ļ�
	* ����1 .node�ļ�
	* ����2 �ڵ�����
	*/
	int write_node_file(const char* filename, const Mat& mask);




	/*********************************************************/
    /*                PS-InSAR ���ú���                      */
    /*********************************************************/

	/*������ָ����ɸѡPS�㣨D_A��
	* ����1 SAR���Ⱦ�����
	* ����2 ��������ֵ
	* ����3 mask������������PS��λ��maskΪ1������Ϊ0��
	*/
	int PS_amp_dispersion(const vector<Mat>& amplitude, double thresh, Mat& mask);
	/*fifth-order butterworth filter����װ�����˹�˲�����
	* ����1 grid_size
	* ����2 n_win
	* ����3 low_pass_wavelength
	* ����4 �˲���ϵ��������ֵ��
	*/
	int butter_lowpass(int grid_size, int n_win, double low_pass_wavelength, Mat& lowpass);
	/*circle_shift
	*/
	int circshift(Mat& out, const cv::Point& delta);
	/*fftshift2
	*/
	int fftshift2(Mat& out);
	/*ifftshift
	*/
	int ifftshift(Mat& out);
	/*��ά����Ҷ�任
	* ����1 �������
	* ����2 ������
	*/
	int fft2(Mat& Src, Mat& Dst);
	/*������ά����Ҷ�任
	* ����1 �������
	* ����2 ������
	*/
	int fft2(ComplexMat& src, ComplexMat& dst);
	/*���ά����Ҷ�任
	* ����1 �������
	* ����2 ������
	*/
	int ifft2(ComplexMat& src, ComplexMat& dst);
	/*���׼��
	* ����1 �������
	* ����2 ��׼���ֵ
	*/
	int std(const Mat& input, double* std);
	/*�ü�����Ȥ��SARͼ������AOI��
	* ����1 SARͼ�������ļ�����img��ʽ��
	* ����2 �ü����SARͼ�����б���·��
	* ����2 AOI����γ��/����/�߶�(1��3)
	* ����3 AOI��������
	* ����4 AOI�ߣ�������
	*/
	int PS_cut_AOI(
		vector<string>& SAR_images_files,
		const char* save_path,
		Mat& llh,
		int rows,
		int cols
	);
	/*SARͼ�������λ����ȥƽ��
	* ����1 ������λ���У�ԭ�ز�����
	* ����2 �������
	* ����3 ���ǹ����������ֵ�� n_images��6��
	* ����4 ������Ƶ���Ϣ��γ��/����/�߶�/��/��, n_gcps �� 5��
	* ����5 SARͼ�����Ͻ���ԭSARͼ���е�����(����ֱ������Ϊ1)
	* ����6 SARͼ�����Ͻ���ԭSARͼ���е�����(����ֱ������Ϊ1)
	* ����7 �շ���ʽ��1�������գ� 2����˫�գ�
	* ����8 ����
	*/
	int PS_deflat(
		vector<Mat>& interf_phase,
		Mat& interf_combination,
		vector<Mat>& pos,
		vector<Mat>& gcps,
		Mat& start_row,
		Mat& start_col,
		int mode,
		double lambda
	);
	/*ȥƽ��(������Ϸ�)
	* ����1 ������λ��ԭ�ز�����
	* ����2 ���ǹ����������ֵ�� n_images��6��
	* ����3 ���ǹ����������ֵ�� n_images��6��
	* ����4 ������Ƶ���Ϣ��γ��/����/�߶�/��/��, n_gcps �� 5��
	* ����5 SARͼ�����Ͻ���ԭSARͼ���е�����(����ֱ������Ϊ1)
	* ����6 SARͼ�����Ͻ���ԭSARͼ���е�����(����ֱ������Ϊ1)
	* ����7 �շ���ʽ��1�������գ� 2����˫�գ�
	* ����8 ����
	*/
	int _PS_deflat(
		Mat& phase,
		Mat& pos1,
		Mat& pos2,
		Mat& gcps,
		int start_row,
		int start_col,
		int mode,
		double lambda
	);
	/** @brief ʱ��SARͼ��������׼(����slcͬʱ�����ڴ�)
	
	@param SAR_images            ʱ��SARͼ��inplace��ԭ�ز�����
	@param offset                ��׼�����Ͻ�ƫ����(�ߴ磺n_images �� 2) 
	@param Master_index          ��ͼ�����(��Ŵ�1��ʼ)
	@param coh_method            ����ʵ��ػ��Ǹ���أ�0����ʵ��أ� 1������أ�
	@param interp_times          ��ֵ������2��n���ݣ�
	@param blocksize             �ӿ��С��2��n���ݣ�
	*/
	int stack_coregistration(
		vector<ComplexMat>& SAR_images,
		Mat& offset,
		int Master_index,
		int coh_method,
		int interp_times,
		int blocksize
	);
	/** @brief ʱ��SARͼ��������׼(slc���������ڴ棬�Խ�ʡ�ڴ�)
	
	@param SAR_images            ʱ��SARͼ���ļ�
	@param SAR_images_out        ��׼����ļ�
	@param offset                ��׼�����Ͻ�ƫ����(�ߴ磺n_images �� 2)
	@param Master_index          ��ͼ�����(��Ŵ�1��ʼ)
	@param interp_times          ��ֵ������2��n���ݣ�
	@param blocksize             �ӿ��С��2��n���ݣ�
	*/
	int stack_coregistration(
		vector<string>& SAR_images,
		vector<string>& SAR_images_out,
		Mat& offset,
		int Master_index,
		int interp_times,
		int blocksize
	);
	/*���ɸ���ͼ���
	* ����1 SARͼ������
	* ����2 ������λ���У�����ֵ��
	* ����3 ʱ�������ϣ�����ֵ, ԭ�ز�����
	* ����4 �ռ�����Ժϣ�����ֵ, ԭ�ز�����
	* ����5 ʱ�������ֵ���꣩
	* ����6 �ռ������ֵ���ף�
	* ����7 ��ͼ�����(���С�ڵ���0����������Ϸ�ʽ����)
	* ����8 �������
	*/
	int PS_gen_interferogram(
		vector<ComplexMat>& SAR_images,
		vector<Mat>& interf_phase,
		Mat& time_baseline,
		Mat& spatial_baseline,
		double time_thresh,
		double spatial_thresh,
		int Mast_index, 
		Mat& interf_combination
	);
	/*�ռ���߹���
	* ����1 ���ǹ����������ֵ��λ�ú��ٶȣ� �ߴ磺n*6��
	* ����2 ������Ƶ���Ϣ��γ���ߣ��ߴ磺n_gcps * 3��
	* ����3 ����
	* ����4 ���߳��ȣ�����ֵ��
	*/
	int PS_spatialbaseline_est(
		vector<Mat>& pos,
		Mat gcps,
		double lambda,
		Mat& MB_effect
	);
	/*Combined Low-pass Adaptive Phase filtering��StaMPS����Ӧ�˲�����
	* ����1 �����λ��������ʽ��
	* ����2 �˲�����λ��������ʽ��
	* ����3 �˲���������һ��Ϊ1��
	* ����4 �˲���������һ��Ϊ0.3��
	* ����5 ���ڴ�С������Ϊż����
	* ����6 ���㳤�ȣ�����Ϊż����
	* ����7 ��ͨ�˲���ϵ��(�ߴ� = ���ڴ�С + ���㳤��)
	*/
	int Clap(
		ComplexMat& phase,
		ComplexMat& phase_filter,
		double alpha,
		double beta,
		int n_win,
		int n_pad,
		Mat& lowpass
	);
	/*topofit
	* ����1 �����λ
	* ����2 ��ֱ���߳���
	* ����3 num_trial_wraps
	* ����4 K0������ֵ��
	* ����5 C0������ֵ��
	* ����6 coh0������ֵ��
	* ����7 ������λ������ֵ��
	*/
	int PS_topofit(
		Mat& dif_phase, Mat& bperp,
		double num_trial_wraps,
		double* K0, double* C0,
		double* coh0,
		Mat& phase_residue
	);
	/*hist������ͳ��ֱ��ͼ������
	* ����1 ��ͳ������
	* ����2 ͳ�Ʊ�׼������������
	* ����3 ͳ�Ʊ�׼������������
	* ����4 ����뾶��n * ����뾶 = ��ͳ�Ʊ�׼������������ - ͳ�Ʊ�׼�����������ģ���
	* ����5 ͳ�����
	*/
	int hist(
		Mat& input,
		double lowercenter,
		double uppercenter,
		double interval,
		Mat& out
	);
	/*��γ��ת�����ֲ�����ϵ
	* ����1 ��γ������
	* ����2 �ֲ����ľ���
	* ����3 �ֲ�����γ��
	* ����4 �ֲ����꣨����ֵ��
	*/
	int llh2local(const Mat& llh, double lon0, double lat0, Mat& xy);
	/*����ѡPS���ز���������������
	* ����1 �ֲ�����ϵ����
	* ����2 �������С���ף�
	* ����3 ��ѡPS���������е����꣨����ֵ��
	* ����4 �ز������������
	* ����5 �ز������������
	*/
	int gen_grid(
		const Mat& xy,
		double grid_size,
		Mat& grid_ij,
		int* rows,
		int* cols
	);
	/*���������λ��ʱ�����ϵ�����ʷֲ�����
	* ����1 ���������������ֵ30000��
	* ����2 ��ָ���ͼ����
	* ����3 ��ֱ����
	* ����4 ��������뾶
	* ����5 ���ʷֲ�������ֵ��
	* ����6 �����ܶȲ�Ϊ�����С������ֵ
	*/
	int gen_CohDistributionOfRandomPhase(
		int nrand,
		int n_ifg,
		const Mat& bperp,
		double num_trial_wraps,
		Mat& Nr,
		int* Nr_max_nz_ix
	);
	/*��һ�ι���PS���ʱ�����ϵ��
	* ����1/����2     �����λ���У�PS��ѡ����ţ��У�����ͼ��ţ� / ������ָ��(������)
	* ����3/����4     PS�����ز��������е����� / ��ֱ���ߣ�������λͬ�ߴ磩
	* ����5/����6     ��ͨ�˲���ϵ�� / �����λʱ�����ϵ���ֲ���������100��1�У�
	* ����7/����8     ����Ӧ�˲���������alpha����ֵ1.0�� beta����ֵ0.3��
	* ����9/����10    �Ż���������뾶 / ����������
	* ����11/����12   Nr���� / ���������ж���ֵ
	* ����13/����14   K_ps / C_ps������ֵ��
	* ����15/����16   coh_ps��ʱ�����ϵ������ֵ��/ fft���ڴ�С
	*/
	int PS_est_gamma_quick(
		const Mat& dif_phase,
		const Mat& D_A,
		const Mat& grid_ij,
		const Mat& bperp_mat,
		Mat& lowpass,
		Mat& Nr,
		double alpha,
		double beta,
		double n_trial_wraps,
		int gamma_max_iterations,
		int Nr_max_nz_ix,
		double gamma_change_convergence,
		Mat& K_ps,
		Mat& C_ps,
		Mat& coh_ps,
		int n_win
	);
	/*�������ʱ�����ϵ����ֵ��D_A�����޳�С����ֵ��PS��ѡ��
	* ����1 D_A��������, �����ţ�
	* ����2 PS��ѡ��ʱ�����ϵ���������ţ�
	* ����3 Nr�������ţ�
	* ����4 �����ֵ������ֵ��
	* ����5 low_coh_thresh
	* ����6 �龯��
	*/
	int coh_thresh_fit(
		const Mat& D_A,
		Mat& coh_ps,
		Mat& Nr,
		Mat& coh_thresh_D_A,
		int low_coh_thresh,
		double false_alarm
	);
	/*��ά������������PS������λģ�����ϵ�����ֵ�㣬���Ƴ�delta_vel��delta_epsilon
	* ����������(1mm/y, 2m)
	* 
	* ����1 ÿ��PS_pair����λ���У������ſ���
	* ����2 ��ʱ�����������صĲ�����4 * pi * T_i / lambda�� �����1������ͬ��
	* ����3 ��ռ����������صĲ�����4 * pi * berp_i / lambda / R_i / sin_theta_i�� �����1������ͬ��
	* ����4 �α����ʲ���������뾶(mm/y)
	* ����5 �̲߳���������뾶(m)
	* ����6 MCֵ������ֵ��
	* ����7 �α����ʲ����ֵ��
	* ����8 �̲߳����ֵ��
	*/
	int PS_topovel_fit_search(
		ComplexMat& ph,
		Mat& coef_delta_vel,
		Mat& coef_delta_height,
		double radius_delta_vel,
		double radius_delta_height,
		double* MC,
		double* delta_vel,
		double* delta_height
	);
	/*��ά��������(������)����PS������λģ�����ϵ�����ֵ�㣬���Ƴ�delta_vel��delta_epsilon
	* ����������(0.1mm/y, 0.2m)
	* 
	* ����1 ÿ��PS_pair����λ���У������ſ���
	* ����2 ��ʱ�����������صĲ�����4 * pi * T_i / lambda�� �����1������ͬ��
	* ����3 ��ռ����������صĲ�����4 * pi * berp_i / lambda / R_i / sin_theta_i�� �����1������ͬ��
	* ����4 �����������delta_vel��
	* ����5 �����������delta_height��
	* ����6 �α����ʲ���������뾶(mm/y)
	* ����7 �̲߳���������뾶(m)
	* ����8 MCֵ������ֵ��
	* ����9 �α����ʲ����ֵ��
	* ����10 �̲߳����ֵ��
	*/
	int PS_topovel_fit_search_2(
		ComplexMat& ph,
		Mat& coef_delta_vel,
		Mat& coef_delta_height,
		double rough_delta_vel_center,
		double rough_delta_height_center,
		double radius_delta_vel,
		double radius_delta_height,
		double* MC,
		double* delta_vel,
		double* delta_height
	);
	/*ͨ��ģ�����ϵ����Model Coherence����PS�߽���ɸѡ��С����ֵ������
	* ����1 PS�ڵ�����
	* ����2 PS�߽ṹ������
	* ����3 PS�߽ṹ����
	* ����4 ģ�����ϵ����ֵ
	*/
	int Dump_unqualified_pairnodes(
		vector<tri_node>& nodes,
		tri_edge* edges,
		int num_edges,
		double MC_thresh
	);
	/*�������ּ��ɣ����ֻ�ȡÿ��PS����α����ʺ͸߳���
	* ����1 PS������
	* ����2 PS�߽ṹ������
	* ����3 PS������
	* ����4 PS���ֱ߳���ֵ����������ֵ��ͨ���˱߻��ּ��ɣ�
	* ����5 MC��ֵ����������ֵ��ͨ���˱߻��ּ��ɣ�
	*/
	int PS_topovel_incre(
		vector<tri_node>& nodes,
		tri_edge* edges,
		int num_edges, 
		double distance_thresh,
		double MC_thresh
	);


	/*
	* ���ǹ����ֵ
	* ����1�����ǹ��������δ��ֵ��
	* ����2����ֵʱ������s��
	* ����3����ֵ���
	*/
	int stateVec_interp(Mat& stateVec, double time_interval, Mat& stateVec_interp);
	/*
	* ��h5��SLC��ͼ���ļ��вü�AOI
	* ����1��h5�ļ�
	* ����2��AOI���ϽǾ���
	* ����3��AOI���Ͻ�γ��
	* ����4��AOI���½Ǿ���
	* ����5��AOI���½�γ��
	* ����6��������Ӹ�ͼ��
	* ����7��AOI���Ͻ���ƫ��������0��ʼ��0����ƫ�ƣ�
	* ����8��AOI���Ͻ���ƫ��������0��ʼ��0����ƫ�ƣ�
	*/
	int get_AOI_from_h5SLC(
		const char* h5_file,
		double lon_topleft,
		double lat_topleft,
		double lon_bottomright,
		double lat_bottomright,
		ComplexMat& slc,
		int* offset_row = NULL,
		int* offset_col = NULL
	);
	/** @brief ��h5��SLC���ļ��вü���AOI����
	
	@param h5_file h5�ļ�
	@param lon_center AOI���ľ���
	@param lat_center AOI����γ��
	@param width AOI��ȣ�m��
	@param height AOI�߶ȣ�m��
	@param slc �ü����slc
	@param offset_row AOI���Ͻ���ԭͼ������ƫ��������0��ʼ��0����ƫ�ƣ�
	@param offset_col AOI���Ͻ���ԭͼ������ƫ��������0��ʼ��0����ƫ�ƣ�
	*/
	int get_AOI_from_h5slc(
		const char* h5_file,
		double lon_center,
		double lat_center,
		double width,
		double height,
		ComplexMat& slc,
		int* offset_row = NULL,
		int* offset_col = NULL
	);
	/** @brief ��h5��SLC���ļ��л�ȡ�ü�AOI����ĳߴ�

	@param h5_file          h5�ļ�
	@param lon_center       AOI���ľ���
	@param lat_center       AOI����γ��
	@param width            AOI��ȣ�m��
	@param height           AOI�߶ȣ�m��
	@param AOI_rows         AOI����
	@param AOI_cols         AOI����
	@param offset_row       AOI���Ͻ���ԭͼ������ƫ��������0��ʼ��0����ƫ�ƣ�
	@param offset_col       AOI���Ͻ���ԭͼ������ƫ��������0��ʼ��0����ƫ�ƣ�
	*/
	int get_AOI_size(
		const char* h5_file,
		double lon_center,
		double lat_center,
		double width,
		double height,
		int* AOI_rows,
		int* AOI_cols,
		int* offset_row = NULL,
		int* offset_col = NULL
	);
	/** @brief ����ת�����ߺ���
	
	@param coefficient       ת��ϵ������
	@param coord_in_1        ԭ�������1(1��2��˳�����Ҫ������/��������ǰ)
	@param coord_in_2        ԭ�������2
	@param coord_out         ת���������
	*/
	int coord_conversion(
		Mat& coefficient,
		Mat& coord_in_1,
		Mat& coord_in_2,
		Mat& coord_out
	);
	/** @brief ���߹���

	@param stateVec1               ���ǹ����δ��ֵ��
	@param stateVec2               ���ǹ����δ��ֵ��
	@param lon_coef                ��������ת��ϵ����ͼ������-->���ȣ�
	@param lat_coef                ��������ת��ϵ����ͼ������-->γ�ȣ�
	@param offset_row              ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param offset_col              ��ͼ�����Ͻ���ԭʼͼ���е���ƫ����
	@param scene_height            �����߶�(��������)
	@param scene_width             �������(��������)
	@param interp_interval1        ���ǹ����ֵʱ������1/prf��
	@param interp_interval2        ���ǹ����ֵʱ������1/prf��
	@param B_effect                ��ֱ���߳��ȣ�����ֵ��
	@param B_parallel              ƽ�л��߳��ȣ�����ֵ��
	@param sigma_B_effect          ��ֱ���߹��Ʊ�׼�����ֵ��
	@param sigma_B_parallel        ƽ�л��߹��Ʊ�׼�����ֵ��
	*/
	int baseline_estimation(
		const Mat& stateVec1,
		const Mat& stateVec2,
		const Mat& lon_coef,
		const Mat& lat_coef,
		int offset_row,
		int offset_col,
		int scene_height,
		int scene_width,
		double interp_interval1,
		double interp_interval2,
		double* B_effect,
		double* B_parallel,
		double* sigma_B_effect = NULL,
		double* sigma_B_parallel = NULL
	);
	/** @brief ͳ��ͬ�ʼ���
	
	@param pixel1            ��������Ԫ1��������(size: n_images��1)
	@param pixel2            ��������Ԫ2��������(size: n_images��1)
	@param homo_flag         �Ƿ�Ϊͬ����Ԫ(����0��Ϊͬ����Ԫ��-1��Ϊ��ͬ����Ԫ)
	@param alpha             ������ˮƽ�������趨��ֵΪ 0.20,0.15,0.10,0.05,0.025,0.01,0.005,0.001��Ĭ��Ϊ0.05��
	@param method            ���鷽����"KS":Kolmogorov-Smirnov���飬"AD":Anderson-Darling����, Ĭ��ΪKS���飩
	@return                  �������з���0��������-1
	*/
	int homogeneous_test(
		const Mat& pixel1,
		const Mat& pixel2,
		int* homo_flag,
		double alpha = 0.05,
		const char* method = "KS"
	);
	/** @brief Hermitian��������ֵ�ֽ�
	
	@param input               ���븴����n��n, double�ͣ�
	@param eigenvalue          ����ֵ��n��1ʵ����,�Ӵ�С���У�
	@param eigenvector         ����������n��n������ ������Ϊ����������
	@return                    �ɹ�����0�����򷵻�-1              
	*/
	int HermitianEVD(
		const ComplexMat& input,
		Mat& eigenvalue,
		ComplexMat& eigenvector
	);
	/** @brief ʱ��SARͼ����ؾ������
	
	@param slc_series               slc���ݶ�ջ
	@param coherence_matrix         ��ؾ��󣨸���, ����ֵ��
	@param est_window_width         ���ƴ��ڿ�ȣ�������
	@param est_window_height        ���ƴ��ڸ߶ȣ�������
	@param ref_row                  ��������ͳ��ͬ�ʼ��飩�ο��������꣬������ͬ�ʼ�������Ҫ�˲���
	@param ref_col                  ��������ͳ��ͬ�ʼ��飩�ο��������꣬������ͬ�ʼ�������Ҫ�˲���
	@param b_homogeneous_test       �Ƿ����ͳ��ͬ�ʼ��飨ͬ�ʼ���ο�����Ĭ��Ϊ�м�����أ�
	@param b_normalize              ������ؾ���ʱslc�����Ƿ��һ������
	@return                         �ɹ�����0�����򷵻�-1 
	*/
	int coherence_matrix_estimation(
		const vector<ComplexMat>& slc_series,
		ComplexMat& coherence_matrix,
		int est_window_width,
		int est_window_height,
		int ref_row,
		int ref_col,
		bool b_homogeneous_test = true,
		bool b_normalize = true
	);
	/** @brief �����ʱ��������λ���ƣ��ֿ��ȡ�����㡢���棩
	
	@param coregis_slc_files              ��׼��SARͼ�����ݶ�ջ���ļ���
	@param phase_files                    ʱ�����и�����λ���ļ�����coregis_slc_files������ͬ����ͼ����λΪ0��
	@param coherence_files                ����ͼ������ͼ��֮������ϵ���ļ����Ƿ�������ϵ��ȡ�����������b_coh_est��
	@param master_indx                    ��ͼ����ţ���1��ʼ��
	@param blocksize_row                  �ӿ�ߴ磨�У��������ͬ�ʼ����������ڰ뾶��
	@param blocksize_col                  �ӿ�ߴ磨�У��������ͬ�ʼ����������ڰ뾶��
	@param out_mask                       ��Ĥ�������Ǿ���EVD�����Ƶ����ص㣬�����thresh_c1_to_c2�йأ�
	@param b_coh_est                      �Ƿ�������ϵ����Ĭ���ǣ�
	@param homogeneous_test_wnd           ͬ�ʼ����������ڴ�С��������homogeneous_test_wnd��homogeneous_test_wnd�� Ĭ��Ϊ21��21��
	@param thresh_c1_to_c2                Э��������2����ֵ���1����ֵ��ֵ��ֵ��0-1֮�䣬Ĭ��Ϊ0.7��
	@param b_flat                         �Ƿ�ȥƽ����λ��Ĭ���ǣ�
	@param b_normalize                    Э��������Ƿ��һ����Ĭ���ǣ�
	*/
	int MB_phase_estimation(
		vector<string> coregis_slc_files,
		vector<string> phase_files,
		vector<string> coherence_files,
		int master_indx,
		int blocksize_row,
		int blocksize_col,
		Mat& out_mask,
		bool b_coh_est = true,
		int homogeneous_test_wnd = 21,
		double thresh_c1_to_c2 = 0.7,
		bool b_flat = true,
		bool b_normalize = true
	);
	/** @brief ���������������delaunay��������
	
	@param nodes                       Delaunay��������ڵ�����
	@param edges                       Delaunay��������߽ṹ������
	@param start_edge                  ������ʼ����ţ���1��ʼ��
	@param distance_thresh             �߳���ֵ����������ֵ��ͨ���˱߻���
	@param quality_thresh              ������ֵ�����ڴ���ֵ��ͨ���˱߻���
	@return �ɹ�����0�����򷵻�-1
	*/
	int unwrap_region_growing(
		vector<tri_node>& nodes,
		const vector<tri_edge>& edges,
		size_t start_edge,
		double distance_thresh,
		double quality_thresh
	);
	/** @brief 3D��λ�����1Dʱ��-->2D�ռ�
	
	@param mask                          ��Ҫ��������ص���Ĥ(int��)
	@param quality_map                   ����ͼ
	@param wrapped_phase_series          �������λʱ������
	@param unwrapped_phase_series        �����λʱ������
	@param delaunay_exe_path             ����Delaunay�������Ŀ�ִ�г���delaunay.exe������·��
	@param tmp_file_path                 ��������ʱ�ļ�����·��
	@param distance_thresh               ���ֽ��������ֵ����������ֵ��ͨ���ñ߻��ֽ��������С��1
	@param quality_thresh                ������ֵ�����ڴ���ֵ��ͨ���˱߻���
	@return �ɹ�����0�����򷵻�-1
	*/
	int unwrap_3D(
		const Mat& mask,
		const vector<Mat>& quality_map,
		vector<Mat>& wrapped_phase_series,
		vector<Mat>& unwrapped_phase_series,
		const char* delaunay_exe_path,
		const char* tmp_file_path,
		double distance_thresh,
		double quality_thresh
	);
	/** @brief 3D��λ�����Delaunay��������С����������
	
	@param mask                          ��Ҫ��������ص���Ĥ(int��)
	@param quality_map                   ����ͼ
	@param wrapped_phase_series          �������λʱ������
	@param unwrapped_phase_series        �����λʱ������
	@param delaunay_exe_path             ����Delaunay�������Ŀ�ִ�г���delaunay.exe������·��
	@param mcf_exe_path                  ��С�������������ִ�г���mcf.exe������·��
	@param tmp_file_path                 ��������ʱ�ļ�����·��
	@param distance_thresh               ���ֽ��������ֵ����������ֵ��ͨ���ñ߻��ֽ��������С��1
	@return �ɹ�����0�����򷵻�-1
	*/
	int unwrap_3D_mcf(
		const Mat& mask,
		const vector<Mat>& quality_map,
		vector<Mat>& wrapped_phase_series,
		vector<Mat>& unwrapped_phase_series,
		const char* delaunay_exe_path,
		const char* mcf_exe_path,
		const char* tmp_file_path,
		double distance_thresh
	);
	/** @brief ����Ӧ�ֿ�3D��λ���
	
	@param mask                          ��Ҫ��������ص���Ĥ(int��)
	@param quality_map                   ����ͼ
	@param wrapped_phase_series          �������λʱ������
	@param unwrapped_phase_series        �����λʱ������
	@param delaunay_exe_path             ����Delaunay�������Ŀ�ִ�г���delaunay.exe������·��
	@param mcf_exe_path                  ��С�������������ִ�г���mcf.exe������·��
	@param tmp_file_path                 ��������ʱ�ļ�����·��
	@param distance_thresh               ���ֽ��������ֵ����������ֵ��ͨ���ñ߻��ֽ��������С��1
	@param quality_thresh                ������ֵ�����ڴ���ֵ��ͨ���˱߻���
	@return �ɹ�����0�����򷵻�-1
	*/
	int unwrap_3D_adaptive_tiling(
		const Mat& mask,
		const vector<Mat>& quality_map,
		vector<Mat>& wrapped_phase_series,
		vector<Mat>& unwrapped_phase_series,
		const char* delaunay_exe_path,
		const char* mcf_exe_path,
		const char* tmp_file_path,
		double distance_thresh,
		double quality_thresh
	);
private:
	char error_head[256];
	char parallel_error_head[256];

};


#endif