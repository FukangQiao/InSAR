#pragma once
#ifndef __FORMATCONVERSION__H__
#include<string>
#include"..\include\Package.h"
#include"..\include\ComplexMat.h"
#include"hdf5.h"
#include"..\include\tinyxml.h"
#define Big2Little32(A) ((uint32_t)(A&0xff000000)>>24|(uint32_t)(A&0x00ff0000)>>8 | (uint32_t)(A&0x0000ff00)<<8|(uint32_t)(A&0x000000ff)<<24)
#define Big2Little16(A) ((uint16_t)(A&0xff00)>>8 | (uint16_t)(A&0x00ff)<<8)
/*********************************************************/
/***************   XML�ļ�������д���    ****************/
/*********************************************************/

class InSAR_API XMLFile
{
public:
	XMLFile();
	~XMLFile();

	/** @brief �����µĹ����ļ�
	
	@param project_path       ����·��
	@param project_name       ������
	@param project_version    �����ļ��汾
	*/
	int XMLFile_creat_new_project(
		const char* project_path,
		const char* project_name,
		const char* project_version
	);
	/** @brief ��ӵ���TSX�ڵ�

	@param node_name      ͼ����
	@param node_path      ͼ��·��
	*/
	int XMLFile_add_origin(
		const char* node_name,
		const char* node_path
	);
	/** @brief ��Ӳü�ͼ��ڵ�

	@param datanode_node  �ü�ͼ��ڵ���
	@param node_name      �ü�ͼ����
	@param node_path      �ü�ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param lon            ���ľ���
	@param lat            ����γ��
	@param width          �ü����
	@param height         �ü��߶�
	*/
	int XMLFile_add_cut(
		const char* datenode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		double lon, double lat,
		double width, double height
	);
	/** @brief �����׼ͼ��ڵ�

	@param datanode_node  ��׼ͼ��ڵ���
	@param node_name      ��׼ͼ����
	@param node_path      ��׼ͼ��·��
	@param Row_offset     ��ƫ����
	@param Col_offset     ��ƫ����
	@param master_index   ��ͼ�����
	@param interp_times   ��ֵ������2��n���ݣ�
	@param block_size     �ӿ�ߴ磨2��n���ݣ�
	@param temporal_baseline ʱ����߹���
	@param B_effect       ��ֱ���߹���
	@param B_parallel     ˮƽ���߹���
	*/
	int XMLFile_add_regis(
		const char* datanode_name,
		const char* node_name,
		const char* node_path,
		int Row_offset,
		int Col_offset,
		int master_index, int interp_times, int block_size,
		const char* temporal_baseline, const char* B_effect, const char* B_parallel
	);
	/** @brief �����ַ���

	@param n			��������ֵ
	*/
	string int2str(int n);
	/** @brief ��������

	@param s			�����ַ���
	*/
	int str2int(const string& s);
	/** @brief ����XML

	@param save_path    ����·��
	*/
	int XMLFile_save(
		const char* save_path
	);




	/*XML�ļ�����
	* ����1���������ļ���
	*/
	int XMLFile_load(const char* xmlFileName);
	/*
	* �����Ʋ��ҽڵ�
	* ����1�����ڵ㣨����ֵ��
	*/
	int get_root(TiXmlElement*& root);
	/*
	* ���ڵ��ѯ�ӽڵ����
	* ����1���ڵ���
	* ����2���ӽڵ�����������ֵ��
	*/
	int get_children_count(TiXmlElement* pRoot, int* count);
	/*
	* �����Ʋ��ҽڵ�
	* ����1���ڵ���
	* ����2���ڵ���
	* ����3���ڵ�ָ�루����ֵ��
	*/
	int _find_node(TiXmlElement* pRoot, const char* node_name, TiXmlElement*& pnode);
	/*
	* �����Ʋ��ҽڵ�
	* ����1���ڵ���
	* ����2���ڵ�ָ�루����ֵ��
	*/
	int find_node(const char* node_name, TiXmlElement*& pnode);
	/*
	* �����Ƽ�����ֵ���ҽڵ�
	* ����1�����ڵ㣨�����ã����ļ����ڵ㣩
	* ����2���ڵ���
	* ����3���ڵ����������ؼ����ԣ�
	* ����4���ڵ�����ֵ
	* ����5���ڵ�ָ�루����ֵ��
	*/
	int find_node_with_attribute(
		TiXmlElement* pRoot,
		const char* node_name,
		const char* attribute_name,
		const char* attribute_value,
		TiXmlElement*& pnode);
	/*
	* ��XML�ļ��ж����ַ�������
	* ����1�����������ڵ�����
	* ����2������ֵ�������
	*/
	int get_str_para(const char* node_name, string& value);
	/*
	* ��XML�ļ��ж���double���Ͳ���
	* ����1�����������ڵ�����
	* ����2������ֵ�������
	*/
	int get_double_para(const char* node_name, double* value);
	/*
	* ��XML�ļ��ж������Ͳ���
	* ����1�����������ڵ�����
	* ����2������ֵ�������
	*/
	int get_int_para(const char* node_name, int* value);



	/*************************************************/
	/**********   Sensor-specific functions **********/
	/*************************************************/


	/*
	* ��TerraSAR-X GEOREF.xml�ļ��ж������Ƶ����
	* ����1�����Ƶ���������ֵ��N��6����ÿ�зֱ�Ϊ������γ���ߣ��У��У����ӽǣ�
	*/
	int get_gcps_from_TSX(Mat& gcps);
	/*
	* ��TerraSAR-X����XML�ļ��ж����������
	* ����1��������������ֵ��N��7����ÿ�зֱ��ǣ�GPSʱ�䣬λ�ã��ٶȣ�
	*/
	int get_stateVec_from_TSX(Mat& stateVec);
	/*
	* ��TerraSAR-X��xml�ļ��ж�������������Ƶ�ʲ�������ϵ��
	* ����1������������Ƶ�ʣ����ֵ�� N��(N_order+2)����NΪ���������Ĺ�������N_orderΪб���������������Ͻ���, �������������ϵ���Ͳο��������ʱ�䣩
	*/
	int get_dopplerCentroid_from_TSX(Mat& doppler);


	/*
	* ��sentinel1��������xml�ļ��ж���������Ƶ�����
	* ����1�����Ƶ����ݣ����ֵ��N��6����ÿ�зֱ�Ϊ������γ���ߣ��У��У����ӽǣ�
	*/
	int get_gcps_from_sentinel(Mat& gcps);
	/*
	* ��sentinel1��������xml�ļ��ж�������������Ƶ�ʲ���
	* ����1������������Ƶ�ʣ����ֵ�� N��(N_order+2)����NΪ���������Ĺ�������N_orderΪб���������������Ͻ���, �������������ϵ���Ͳο��������ʱ�䣩
	*/
	int get_dopplerCentroid_from_sentinel(Mat& doppler);
	/*
	* ��sentinel1��������xml�ļ��ж����������
	* ����1��������������ֵ��N��7����ÿ�зֱ��ǣ�GPSʱ�䣬λ�ã��ٶȣ�
	*/
	int get_stateVec_from_sentinel(Mat& stateVec);
	

private:
	char m_xmlFileName[2048];
	TiXmlDocument doc;
	int data_node_count;
	char error_head[256];


	
};



/**************************************************/
/*********           ��ʽת�����        **********/
/**************************************************/

class InSAR_API FormatConversion
{
public:
	FormatConversion();
	~FormatConversion();

	/*
	* ���ܣ����ַ�����ʽ��UTCʱ��ת��ΪGPSʱ��
	* ����1��UTCʱ��
	* ����2��GPSʱ��
	*/
	int utc2gps(const char* utc_time, double* gps_time);
	/** @brief �����µ�h5�ļ������ļ��Ѵ����򸲸ǣ�
	
	@param filename     �ļ���
	*/
	int creat_new_h5(const char* filename);
	/*
	* ���ܣ���h5�ļ���д��ʵ�����󣨸�����λ�����ϵ���ȣ�,input_array������16λ���ͻ���double/float��
	* ����1���ļ���
	* ����2��dataset��
	* ����3 ��д�����
	*/
	int write_array_to_h5(const char* filename, const char* dataset_name, const Mat& input_array);
	/*
	* ���ܣ���h5�ļ��ж���ʵ������(��������Ϊdouble�͡�16λ���ͻ���32λ����)
	* ����1���ļ���
	* ����2��dataset��
	* ����3���������
	*/
	int read_array_from_h5(const char* filename, const char* dataset_name, Mat& out_array);
	/*
	* ���ܣ���h5�ļ��ж�ȡ���������Ӽ�
	* ����1��h5�ļ���
	* ����2��dataset��
	* ����3����ƫ����(��0��ʼ)
	* ����4����ƫ��������0��ʼ��
	* ����5���Ӽ�����
	* ����6���Ӽ�����
	* ����7������Ӽ�����
	*/
	int read_subarray_from_h5(
		const char* filename,
		const char* dataset_name,
		int offset_row,
		int offset_col,
		int rows_subarray,
		int cols_subarray,
		Mat& out_array
	);
	/** @brief �����е�H5�ļ�ָ�����ݼ������е�ָ��λ��д���Ӿ���
	
	@param h5_filename                   h5�ļ���
	@param dataset_name                  ���ݼ�����
	@param subarray                      �Ӿ�������
	@param offset_row                    ��ƫ��������0��ʼ��
	@param offset_col                    ��ƫ��������0��ʼ��
	@param rows_subarray                 �Ӽ�����������
	@param cols_subarray                 �Ӽ�����������
	@return �ɹ�����0�� ���򷵻�-1
	*/
	int write_subarray_to_h5(
		const char* h5_filename,
		const char* dataset_name,
		Mat& subarray,
		int offset_row,
		int offset_col,
		int rows_subarray,
		int cols_subarray
	);
	/*
	* ���ܣ���h5�ļ�д���ַ�������
	* ����1���ļ���
	* ����2��dataset��
	* ����3����д���ַ�������
	*/
	int write_str_to_h5(const char* filename, const char* dataset_name, const char* str);
	/*
	* ���ܣ���h5�ļ��ж����ַ�������
	* ����1���ļ���
	* ����2��dataset��
	* ����3������ַ�������
	*/
	int read_str_from_h5(const char* filename, const char* dataset_name, string& string);
	/*
	* ���ܣ���h5�ļ�д�븴ͼ�����ݣ�SLC��������Ѿ�������д�롣
	* ����1���ļ���
	* ����2��������
	*/
	int write_slc_to_h5(const char* filename, const ComplexMat& slc);
	/*
	* ���ܣ���h5�ļ��ж���slc����
	* ����1���ļ���
	* ����2�����slc
	*/
	int read_slc_from_h5(const char* filename, ComplexMat& slc);


	/*------------------------------------------------*/
	/*            TerraSAR-X��Ʒ���ݵ��빤��          */
	/*------------------------------------------------*/

	/*
	* ��TerraSAR-X���ǵ�.cos�����ж���slc����(���ı����ͣ���Ȼ��16λ����)
	* ����1��.cos�ļ���
	* ����2�������ݾ������ֵ��
	*/
	int read_slc_from_TSXcos(const char* filename, ComplexMat& slc);
	/** @brief ��TerraSAR-X�������ݸ�ʽת��Ϊ�Զ����h5��ʽ
	
	@param cosar_filename                     TerraSAR-X .cos�ļ���
	@param xml_filename                       TerraSAR-X ��xml�ļ���
	@param GEOREF_filename                    TerraSAR-X GEOREF.xml�ļ���
	@param dst_h5_filename                    Ŀ��h5�ļ������ļ��Ѿ������򸲸ǣ�
	@return �ɹ�����0�����򷵻�-1
	*/
	int TSX2h5(
		const char* cosar_filename,
		const char* xml_filename,
		const char* GEOREF_filename,
		const char* dst_h5_filename
	);
	/** @brief ��TerraSAR-X�������ݸ�ʽת��Ϊ�Զ����h5��ʽ
	
	@param xml_filename                       TerraSAR-X ��xml�ļ���
	@param dst_h5_filename                    Ŀ��h5�ļ�
	@return �ɹ�����0�����򷵻�-1
	*/
	int TSX2h5(
		const char* xml_filename,
		const char* dst_h5_filename
	);





	/*------------------------------------------------*/
	/*            Sentinel1��Ʒ���ݵ��빤��           */
	/*------------------------------------------------*/

	/*
	* ��sentinel1���Ǿ��ܹ�������ļ��ж������ܹ������
	* ����1�����ܹ�������ļ�
	* ����2���ֹ��������ʼʱ��
	* ����3���ֹ�����ݽ���ʱ��
	* ����4��Ŀ��h5�ļ�
	*/
	int read_POD(const char* POD_filename, double start_time, double stop_time, const char* dst_h5_filename);
	/*
	* ���ܣ���sentinel1���������ж���slc���ݣ�������������Ϊ16λ���ͣ�
	* ����1��sentinel1���������ļ���
	* ����2��xml�����ļ�
	* ����3�������󣨶�����slc���ݣ�
	*/
	int read_slc_from_Sentinel(const char* filename, const char* xml_filename, ComplexMat& slc);
	/*
	* ���ܣ�sentinel1����deburst(��������Ϊ16λ����)
	* ����1������deburst��xml�����ļ�
	* ����2��������slc���ݣ�ԭ�ز�����
	* ����3����Ч�л��۱�־����(CV_32S��)
	*/
	int sentinel_deburst(const char* xml_filename, ComplexMat& slc, Mat& sentinel);
	/*
	* ��sentinel1�������ݸ�ʽת��Ϊ�Զ����h5��ʽ
	* ����1��tiff��ʽ�ļ���������SLCͼ��
	* ����2��xml�ļ���
	* ����3��Ŀ��h5�ļ���
	* ����4�����ܹ�������ļ�
	*/
	int sentinel2h5(
		const char* tiff_filename,
		const char* xml_filename,
		const char* dst_h5_filename,
		const char* POD_file = NULL
	);



	/*------------------------------------------------*/
	/*              ALOS1/2��Ʒ���ݵ��빤��               */
	/*------------------------------------------------*/

	/*
	* ��ALOS1/2 CEOS��ʽLevel-1.1��Ʒ�ж�ȡslc����(float��)
	* ����1��ͼ���ļ�
	* ����2��slc����
	*/
	int read_slc_from_ALOS(const char* img_file, ComplexMat& slc);
	/*
	* ��ALOS1/2 CEOS��ʽLevel-1.1��Ʒ�ж�ȡ���ǹ������
	* ����1��ALOS LED�ļ�
	* ����2���������
	*/
	int read_stateVec_from_ALOS(const char* LED_file, Mat& stateVec);
	/*
	* ��ALOS1/2 CEOS��ʽLevel-1.1��Ʒ�ж�ȡ��γ������ͼ������֮���ת����ϵϵ��
	* ����1��ALOS LED�ļ�
	* ����2��ͼ�����꣨�С��У��뾭��֮���ת����ϵ������-->���ȣ�
	* ����3��ͼ�����꣨�С��У���γ��֮���ת����ϵ������-->γ�ȣ�
	* ����4����γ����������֮���ת����ϵ����γ��-->������
	* ����5����γ����������֮���ת����ϵ����γ��-->������
	*/
	int read_conversion_coefficient_from_ALOS(
		const char* LED_file,
		Mat& lon_coefficient,
		Mat& lat_coefficient,
		Mat& row_coefficient,
		Mat& col_coefficient
	);
	/*
	* ��ALOS1/2 CEOS��ʽLevel-1.1��Ʒ���ݶ������Զ����hdf5�ļ���
	* ����1��ALOS IMG�ļ�
	* ����2��ALOS LED�ļ�
	* ����3���Զ���h5�ļ�
	*/
	int ALOS2h5(const char* IMG_file, const char* LED_file, const char* dst_h5);
	/** @brief ��ԭh5�ļ��еĲ�����Ϣ��������һ��h5��
	
    @param Input_file        ԭʼh5�ļ�
	@param Output_file       ���h5�ļ�
	*/
	int Copy_para_from_h5_2_h5(const char* Input_file, const char* Output_file);

private:
	char error_head[256];
	char parallel_error_head[256];

};

















#endif // !__FORMATCONVERSION__H__
