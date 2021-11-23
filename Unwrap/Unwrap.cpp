// Unwrap.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include"..\include\Unwrap.h"
#include<tchar.h>
#include <atlconv.h>
#include<queue>
#define CHECK_RETURN(detail_info) \
{ \
	if (ret < 0) \
	   strncpy( &message[40], detail_info, 150); \
	   fprintf(stderr, "%s\n\n", message); \
	   return -1; \
}
#ifdef _DEBUG
#pragma comment(lib, "ComplexMat_d.lib")
#pragma comment(lib, "Utils_d.lib")
#else
#pragma comment(lib, "ComplexMat.lib")
#pragma comment(lib, "Utils.lib")
#endif // _DEBUG
using namespace cv;
inline bool return_check(int ret, const char* detail_info, const char* error_head)
{
	if (ret < 0)
	{
		fprintf(stderr, "%s %s\n\n", error_head, detail_info);
		return true;
	}
	else
	{
		return false;
	}
}

inline bool parallel_check(volatile bool parallel_flag, const char* detail_info, const char* parallel_error_head)
{
	if (!parallel_flag)
	{
		fprintf(stderr, "%s %s\n\n", parallel_error_head, detail_info);
		return true;
	}
	else
	{
		return false;
	}
}

inline bool parallel_flag_change(volatile bool parallel_flag, int ret)
{
	if (ret < 0)
	{
		parallel_flag = false;
		return true;
	}
	else
	{
		return false;
	}
}
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

int Unwrap::MCF(
	Mat& wrapped_phase,
	Mat& unwrapped_phase,
	Mat& coherence,
	Mat& residue,
	const char* MCF_problem_file,
	const char* MCF_EXE_PATH
)

{
	if (wrapped_phase.rows < 2 ||
		wrapped_phase.cols < 2 ||
		(wrapped_phase.rows - residue.rows) != 1 ||
		((wrapped_phase.cols - residue.cols)) != 1 ||
		wrapped_phase.rows != coherence.rows ||
		wrapped_phase.cols != coherence.cols ||
		wrapped_phase.type() != CV_64F||
		coherence.type() != CV_64F||
		residue.type() != CV_64F)
	{
		fprintf(stderr, "MCF(): input check failed!\n\n");
		return -1;
	}
	USES_CONVERSION;
	Utils util;
	int ret;
	ret = util.write_DIMACS(MCF_problem_file, residue, coherence, 0.7);
	if (return_check(ret, "write_DIMACS(*, *, *)", error_head)) return -1;
	//////////////////////////������������С������������///////////////////////////////
	LPWSTR szCommandLine = new TCHAR[256];
	wcscpy(szCommandLine, A2W(MCF_EXE_PATH));
	wcscat(szCommandLine, L"\\mcf.exe ");
	wcscat(szCommandLine, A2W(MCF_problem_file));
	STARTUPINFO si;
	PROCESS_INFORMATION p_i;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&p_i, sizeof(p_i));
	si.dwFlags = STARTF_USESHOWWINDOW;  
	si.wShowWindow = FALSE;          
	BOOL bRet = ::CreateProcess(
		NULL,           // ���ڴ�ָ����ִ���ļ����ļ���
		szCommandLine,      // �����в���
		NULL,           // Ĭ�Ͻ��̰�ȫ��
		NULL,           // Ĭ���̰߳�ȫ��
		FALSE,          // ָ����ǰ�����ڵľ�������Ա��ӽ��̼̳�
		CREATE_NEW_CONSOLE, // Ϊ�½��̴���һ���µĿ���̨����
		NULL,           // ʹ�ñ����̵Ļ�������
		NULL,           // ʹ�ñ����̵���������Ŀ¼
		&si,
		&p_i);
	if (bRet)
	{
		HANDLE hd = CreateJobObjectA(NULL, "MCF");
		if (hd)
		{
			JOBOBJECT_EXTENDED_LIMIT_INFORMATION extLimitInfo;
			extLimitInfo.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
			BOOL retval = SetInformationJobObject(hd, JobObjectExtendedLimitInformation, &extLimitInfo, sizeof(extLimitInfo));
			if (retval)
			{
				if (p_i.hProcess)
				{
					retval = AssignProcessToJobObject(hd, p_i.hProcess);
				}
			}
		}
		WaitForSingleObject(p_i.hProcess, INFINITE);
		if (szCommandLine != NULL) delete[] szCommandLine;
		::CloseHandle(p_i.hThread);
		::CloseHandle(p_i.hProcess);
	}
	else
	{
		fprintf(stderr, "MCF(): create mcf.exe process failed!\n\n");
		if (szCommandLine != NULL) delete[] szCommandLine;
		return -1;
	}
	Mat k1, k2;
	string solution(MCF_problem_file);
	solution.append(".sol");
	ret = util.read_DIMACS(solution.c_str(), k1, k2, wrapped_phase.rows, wrapped_phase.cols);
	if (return_check(ret, "read_DIMACS(*, *, *)", error_head)) return -1;
	Mat diff_1, diff_2;
	ret = util.diff(wrapped_phase, diff_1, diff_2, false);
	if (return_check(ret, "diff(*, *, *, *)", error_head)) return -1;
	ret = util.wrap(diff_1, diff_1);
	if (return_check(ret, "wrap(*, *)", error_head)) return -1;
	ret = util.wrap(diff_2, diff_2);
	if (return_check(ret, "wrap(*, *)", error_head)) return -1;
	double pi = 3.1415926535;
	diff_1 = diff_1 / (2 * pi);
	diff_2 = diff_2 / (2 * pi);
	diff_1 = diff_1 - k1;
	diff_2 = diff_2 - k2;
	Mat tmp = diff_2(Range(0, 1), Range(0, diff_2.cols));
	copyMakeBorder(tmp, tmp, 0, 0, 1, 0, BORDER_CONSTANT, Scalar(0.0));
	ret = util.cumsum(tmp, 2);
	if (return_check(ret, "cumsum(*, *)", error_head)) return -1;
	copyMakeBorder(diff_1, diff_1, 1, 0, 0, 0, BORDER_CONSTANT, Scalar(0));
	for (int i = 0; i < diff_1.cols; i++)
	{
		diff_1.at<double>(0, i) = tmp.at<double>(0, i);
	}
	ret = util.cumsum(diff_1, 1);
	/*Mat tmp = diff_1(Range(0, diff_1.rows), Range(0, 1));
	copyMakeBorder(tmp, tmp, 1, 0, 0, 0, BORDER_CONSTANT, Scalar(0.0));
	ret = util.cumsum(tmp, 1);
	if (return_check(ret, "cumsum(*, *)", error_head)) return -1;
	copyMakeBorder(diff_2, diff_2, 0, 0, 1, 0, BORDER_CONSTANT, Scalar(0));
	for (int i = 0; i < diff_2.rows; i++)
	{
		diff_2.at<double>(i, 0) = tmp.at<double>(i, 0);
	}
	ret = util.cumsum(diff_2, 2);*/
	if (return_check(ret, "cumsum(*, *)", error_head)) return -1;
	unwrapped_phase = (diff_1)* 2 * pi;
	unwrapped_phase = unwrapped_phase + wrapped_phase.at<double>(0, 0);
	return 0;
}


int Unwrap::MCF(
	Mat& wrapped_phase,
	Mat& unwrapped_phase,
	Mat& mask,
	vector<tri_node>& nodes,
	tri_edge* edges,
	int num_edges, 
	int start,
	bool pass,
	double thresh
)
{
	if (wrapped_phase.rows < 2 ||
		wrapped_phase.cols < 2 ||
		wrapped_phase.type() != CV_64F ||
		wrapped_phase.channels() != 1||
		mask.rows != wrapped_phase.rows||
		mask.cols != wrapped_phase.cols||
		mask.type() != CV_32S||
		mask.channels() != 1||
		nodes.size() < 3||
		edges == NULL||
		num_edges < 1||
		start < 1||
		start > nodes.size()
		)
	{
		fprintf(stderr, "MCF(): input check failed!\n\n");
		return -1;
	}
	wrapped_phase.copyTo(unwrapped_phase);
	int num_nodes = nodes.size();
	int num_neigh, number, ret, end2;
	double distance, grad, phi1, phi2, gain, tt, min, max;
	min = 1000000000.0;
	max = -1000000000.0;
	if (pass) tt = 0.5;
	else
	{
		tt = 100000.0;
	}
	long* ptr_neigh = NULL;
	queue<int> que;
	//int start = 1;//��ʼ��Ĭ��Ϊ��һ���㣬���������Լ��趨
	ret = nodes[start - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
	if (return_check(ret, "tri_node::get_neigh_ptr(*, *)", error_head)) return -1;
	nodes[start - 1].set_status(true);
	for (int i = 0; i < num_neigh; i++)
	{
		if (*(ptr_neigh + i) < 1 || *(ptr_neigh + i) > num_edges)
		{
			fprintf(stderr, "MCF(): edge index exceed legal range!\n");
			return -1;
		}
		end2 = (edges + *(ptr_neigh + i) - 1)->end1 == start ? (edges + *(ptr_neigh + i) - 1)->end2 : (edges + *(ptr_neigh + i) - 1)->end1;
		if (end2 < 1 || end2 > num_nodes)
		{
			fprintf(stderr, "MCF(): node index exceed legal range!\n");
			return -1;
		}
		nodes[start - 1].get_distance(nodes[end2 - 1], &distance);
		if (!nodes[end2 - 1].get_status() &&
			distance <= thresh &&
			fabs((edges + *(ptr_neigh + i) - 1)->gain) < tt &&
			nodes[end2 - 1].get_balance() &&
			!((edges + *(ptr_neigh + i) - 1)->isBoundry && fabs((edges + *(ptr_neigh + i) - 1)->gain) > 0.5)
			)
		{
			que.push(end2);
			//���
			nodes[start - 1].get_phase(&phi1);
			nodes[end2 - 1].get_phase(&phi2);
			grad = phi2 - phi1;
			grad = atan2(sin(grad), cos(grad));
			gain = start > end2 ? 2 * PI * (edges + *(ptr_neigh + i) - 1)->gain : -2 * PI * (edges + *(ptr_neigh + i) - 1)->gain;
			nodes[end2 - 1].set_phase(grad + phi1 + gain);
			min = min > (grad + phi1 + gain) ? (grad + phi1 + gain) : min;
			max = max < (grad + phi1 + gain) ? (grad + phi1 + gain) : max;
			nodes[end2 - 1].set_status(true);
		}
	}
	while (que.size() != 0)
	{
		number = que.front();
		que.pop();
		if (number < 1 || number > num_nodes)
		{
			fprintf(stderr, "MCF(): node index exceed legal range!\n");
			return -1;
		}
		ret = nodes[number - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
		if (return_check(ret, "tri_node::get_neigh_ptr(*, *)", error_head)) return -1;
		for (int i = 0; i < num_neigh; i++)
		{
			if (*(ptr_neigh + i) < 1 || *(ptr_neigh + i) > num_edges)
			{
				fprintf(stderr, "MCF(): edge index exceed legal range!\n");
				return -1;
			}
			end2 = (edges + *(ptr_neigh + i) - 1)->end1 == number ? (edges + *(ptr_neigh + i) - 1)->end2 : (edges + *(ptr_neigh + i) - 1)->end1;
			if (end2 < 1 || end2 > num_nodes)
			{
				fprintf(stderr, "MCF(): node index exceed legal range!\n");
				return -1;
			}
			nodes[number - 1].get_distance(nodes[end2 - 1], &distance);
			if (!nodes[end2 - 1].get_status() &&
				distance <= thresh &&
				fabs((edges + *(ptr_neigh + i) - 1)->gain) < tt &&
				nodes[end2 - 1].get_balance()&&
				!((edges + *(ptr_neigh + i) - 1)->isBoundry && fabs((edges + *(ptr_neigh + i) - 1)->gain) > 0.5)
				)
			{
				que.push(end2);
				//���
				nodes[number - 1].get_phase(&phi1);
				nodes[end2 - 1].get_phase(&phi2);
				grad = phi2 - phi1;
				grad = atan2(sin(grad), cos(grad));
				gain = number > end2 ? 2 * PI * (edges + *(ptr_neigh + i) - 1)->gain : -2 * PI * (edges + *(ptr_neigh + i) - 1)->gain;
				min = min > (grad + phi1 + gain) ? (grad + phi1 + gain) : min;
				max = max < (grad + phi1 + gain) ? (grad + phi1 + gain) : max;
				nodes[end2 - 1].set_phase(grad + phi1 + gain);
				nodes[end2 - 1].set_status(true);
			}
		}
	}
	int rows, cols;
	int nr = unwrapped_phase.rows;
	int nc = unwrapped_phase.cols;
	double phi;
	Mat _mask = Mat::zeros(nr, nc, CV_32S);
	for (int i = 0; i < num_nodes; i++)
	{
		if (nodes[i].get_status())
		{
			ret = nodes[i].get_pos(&rows, &cols);
			if (rows > nr - 1 || cols > nc - 1 || rows < 0 || cols < 0)
			{
				fprintf(stderr, "MCF(): node posistion exceed legal range!\n");
				return -1;
			}
			ret = nodes[i].get_phase(&phi);
			unwrapped_phase.at<double>(rows, cols) = phi;
			_mask.at<int>(rows, cols) = 1;
		}
	}
#pragma omp parallel for schedule(guided)
	for (int i = 0; i < nr; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			if (_mask.at<int>(i, j) < 1)
			{
				unwrapped_phase.at<double>(i, j) = min - 0.1*(max - min);
			}
		}
	}
	_mask.copyTo(mask);
	return 0;
}

int Unwrap::MCF(
	const Mat& wrapped_phase,
	Mat& unwrapped_phase,
	Mat& out_mask,
	const Mat& mask,
	vector<tri_node>& nodes,
	vector<tri_edge>& edges,
	int start,
	bool pass,
	double thresh
)
{
	if (wrapped_phase.rows < 2 ||
		wrapped_phase.cols < 2 ||
		wrapped_phase.type() != CV_64F ||
		wrapped_phase.channels() != 1 ||
		mask.rows != wrapped_phase.rows ||
		mask.cols != wrapped_phase.cols ||
		mask.type() != CV_32S ||
		mask.channels() != 1 ||
		nodes.size() < 3 ||
		edges.size() < 3 ||
		start < 1 ||
		start > nodes.size()
		)
	{
		fprintf(stderr, "MCF(): input check failed!\n\n");
		return -1;
	}
	wrapped_phase.copyTo(unwrapped_phase);
	int num_nodes = nodes.size();
	int num_neigh, number, ret, end2;
	double distance, grad, phi1, phi2, gain, tt, min, max;
	min = 1000000000.0;
	max = -1000000000.0;
	if (pass) tt = 0.5;
	else
	{
		tt = 100000.0;
	}
	int num_edges = edges.size();
	long* ptr_neigh = NULL;
	queue<int> que;
	ret = nodes[start - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
	if (return_check(ret, "tri_node::get_neigh_ptr(*, *)", error_head)) return -1;
	nodes[start - 1].set_status(true);
	for (int i = 0; i < num_neigh; i++)
	{
		if (*(ptr_neigh + i) < 1 || *(ptr_neigh + i) > num_edges)
		{
			fprintf(stderr, "MCF(): edge index exceed legal range!\n");
			return -1;
		}
		end2 = edges[*(ptr_neigh + i) - 1].end1 == start ? edges[*(ptr_neigh + i) - 1].end2 : edges[*(ptr_neigh + i) - 1].end1;
		if (end2 < 1 || end2 > num_nodes)
		{
			fprintf(stderr, "MCF(): node index exceed legal range!\n");
			return -1;
		}
		nodes[start - 1].get_distance(nodes[end2 - 1], &distance);
		if (!nodes[end2 - 1].get_status() &&
			distance <= thresh &&
			!edges[*(ptr_neigh + i) - 1].isBoundry &&
			/*!(edges[*(ptr_neigh + i) - 1].isBoundry && fabs(edges[*(ptr_neigh + i) - 1].gain) > 0.5) &&*/
			fabs(edges[*(ptr_neigh + i) - 1].gain) < tt &&
			nodes[end2 - 1].get_balance()
			)
		{
			que.push(end2);
			//���
			nodes[start - 1].get_phase(&phi1);
			nodes[end2 - 1].get_phase(&phi2);
			grad = phi2 - phi1;
			grad = atan2(sin(grad), cos(grad));
			gain = start < end2 ? 2 * PI * edges[*(ptr_neigh + i) - 1].gain : -2 * PI * edges[*(ptr_neigh + i) - 1].gain;
			nodes[end2 - 1].set_phase(grad + phi1 + gain);
			min = min > (grad + phi1 + gain) ? (grad + phi1 + gain) : min;
			max = max < (grad + phi1 + gain) ? (grad + phi1 + gain) : max;
			nodes[end2 - 1].set_status(true);
		}
	}
	while (que.size() != 0)
	{
		number = que.front();
		que.pop();
		if (number < 1 || number > num_nodes)
		{
			fprintf(stderr, "MCF(): node index exceed legal range!\n");
			return -1;
		}
		ret = nodes[number - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
		if (return_check(ret, "tri_node::get_neigh_ptr(*, *)", error_head)) return -1;
		for (int i = 0; i < num_neigh; i++)
		{
			int end1_row, end2_row, end1_col, end2_col;
			if (*(ptr_neigh + i) < 1 || *(ptr_neigh + i) > num_edges)
			{
				fprintf(stderr, "MCF(): edge index exceed legal range!\n");
				return -1;
			}
			end2 = edges[*(ptr_neigh + i) - 1].end1 == number ? edges[*(ptr_neigh + i) - 1].end2 : edges[*(ptr_neigh + i) - 1].end1;
			if (end2 < 1 || end2 > num_nodes)
			{
				fprintf(stderr, "MCF(): node index exceed legal range!\n");
				return -1;
			}
			nodes[number - 1].get_distance(nodes[end2 - 1], &distance);
			if (!nodes[end2 - 1].get_status() &&
				distance <= thresh &&
				!edges[*(ptr_neigh + i) - 1].isBoundry &&
				/*!(edges[*(ptr_neigh + i) - 1].isBoundry && fabs(edges[*(ptr_neigh + i) - 1].gain) > 0.5) &&*/
				fabs(edges[*(ptr_neigh + i) - 1].gain) < tt &&
				nodes[end2 - 1].get_balance() 
				)
			{
				que.push(end2);
				//���
				nodes[number - 1].get_phase(&phi1);
				nodes[end2 - 1].get_phase(&phi2);
				grad = phi2 - phi1;
				grad = atan2(sin(grad), cos(grad));
				gain = number < end2 ? 2 * PI * edges[*(ptr_neigh + i) - 1].gain : -2 * PI * edges[*(ptr_neigh + i) - 1].gain;
				min = min > (grad + phi1 + gain) ? (grad + phi1 + gain) : min;
				max = max < (grad + phi1 + gain) ? (grad + phi1 + gain) : max;
				nodes[end2 - 1].set_phase(grad + phi1 + gain);
				nodes[end2 - 1].set_status(true);
			}
		}
	}
	int rows, cols;
	int nr = unwrapped_phase.rows;
	int nc = unwrapped_phase.cols;
	double phi;
	Mat _mask = Mat::zeros(nr, nc, CV_32S);
	for (int i = 0; i < num_nodes; i++)
	{
		if (nodes[i].get_status())
		{
			ret = nodes[i].get_pos(&rows, &cols);
			if (rows > nr - 1 || cols > nc - 1 || rows < 0 || cols < 0)
			{
				fprintf(stderr, "MCF(): node posistion exceed legal range!\n");
				return -1;
			}
			ret = nodes[i].get_phase(&phi);
			unwrapped_phase.at<double>(rows, cols) = phi;
			_mask.at<int>(rows, cols) = 1;
		}
	}
#pragma omp parallel for schedule(guided)
	for (int i = 0; i < nr; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			if (_mask.at<int>(i, j) < 1)
			{
				unwrapped_phase.at<double>(i, j) = min - 0.01 * (max - min);
			}
		}
	}
	_mask.copyTo(out_mask);
	return 0;
}

int Unwrap::MCF_second(Mat& unwrapped_phase, vector<tri_node>& nodes, tri_edge* edges, int num_edges, bool pass, double thresh)
{
	if (unwrapped_phase.rows < 2 ||
		unwrapped_phase.cols < 2 ||
		unwrapped_phase.type() != CV_64F ||
		unwrapped_phase.channels() != 1 ||
		nodes.size() < 3 ||
		edges == NULL ||
		num_edges < 3
		)
	{
		fprintf(stderr, "MCF_second(): input check failed!\n\n");
		return -1;
	}
	int num_nodes = nodes.size();
	int num_neigh, number, ret, end2, row_start, col_start;
	double distance, grad, phi1, phi2, gain, tt;
	if (pass) tt = 100000.0;
	else
	{
		tt = 100000.0;
	}
	long* ptr_neigh = NULL;
	queue<int> que;
	queue<int> start_que;
	int nr = unwrapped_phase.rows;
	int nc = unwrapped_phase.cols;
	//δ������кž���

	//Mat wrapped_num = Mat::zeros(nr, nc, CV_32S);
	//Mat wrapped_mask = Mat::zeros(nr, nc, CV_32S);
	//Mat grad_updown, grad_leftright;
	//int wrapped_row, wrapped_col;
	//int row_unwrap_start, col_unwrap_start;
	//for (int i = 0; i < num_nodes; i++)
	//{
	//	nodes[i].get_pos(&wrapped_row, &wrapped_col);
	//	wrapped_num.at<int>(wrapped_row, wrapped_col) = i + 1;
	//	wrapped_mask.at<int>(wrapped_row, wrapped_col) = 1;
	//}
	//grad_updown = wrapped_mask(cv::Range(1, nr), cv::Range(0, nc)) - wrapped_mask(cv::Range(0, nr - 1), cv::Range(0, nc));
	//grad_leftright = wrapped_mask(cv::Range(0, nr), cv::Range(1, nc)) - wrapped_mask(cv::Range(0, nr), cv::Range(0, nc - 1));
	//for (int i = 0; i < grad_updown.rows; i++)
	//{
	//	for (int j = 0; j < grad_updown.cols; j++)
	//	{
	//		if (grad_updown.at<int>(i, j) > 0)
	//		{
	//			start_que.push(wrapped_num.at<int>(i + 1, j));
	//		}
	//		if (grad_updown.at<int>(i, j) < 0)
	//		{
	//			start_que.push(wrapped_num.at<int>(i, j));
	//		}
	//	}
	//}
	//for (int i = 0; i < grad_leftright.rows; i++)
	//{
	//	for (int j = 0; j < grad_leftright.cols; j++)
	//	{
	//		if (grad_leftright.at<int>(i, j) > 0)
	//		{
	//			start_que.push(wrapped_num.at<int>(i, j + 1));
	//		}
	//		if (grad_leftright.at<int>(i, j) < 0)
	//		{
	//			start_que.push(wrapped_num.at<int>(i, j));
	//		}
	//	}
	//}
	//int row_search_start, col_search_start, row_search_end, col_search_end;
	//bool b_continue = true;
	//while (start_que.size() != 0)
	//{
	//	number = start_que.front();
	//	start_que.pop();
	//	if (!nodes[number - 1].get_status())
	//	{
	//		nodes[number - 1].get_pos(&row_unwrap_start, &col_unwrap_start);
	//		nodes[number - 1].get_phase(&phi1);
	//		row_search_start = row_unwrap_start - 1 >= 0 ? row_unwrap_start - 1 : row_unwrap_start;
	//		col_search_start = col_unwrap_start - 1 >= 0 ? col_unwrap_start - 1 : col_unwrap_start;
	//		row_search_end = row_unwrap_start + 1 < nr ? row_unwrap_start - 1 : row_unwrap_start;
	//		col_search_end = col_unwrap_start + 1 < nc ? col_unwrap_start - 1 : col_unwrap_start;
	//		b_continue = true;
	//		for (int i = row_search_start; i <= row_search_end; i++)
	//		{
	//			if (b_continue)
	//			{
	//				for (int j = col_search_start; j <= col_search_end; j++)
	//				{
	//					if (wrapped_num.at<int>(i, j) == 0)//�ҵ������Ѿ�����ĵ�
	//					{
	//						grad = atan2(sin(phi1 - unwrapped_phase.at<double>(i, j)), cos(phi1 - unwrapped_phase.at<double>(i, j)));
	//						phi1 = unwrapped_phase.at<double>(i, j) + grad;
	//						nodes[number - 1].set_phase(phi1);
	//						nodes[number - 1].set_status(true);
	//						b_continue = false;
	//						que.push(number);
	//						break;
	//					}
	//				}
	//			}
	//			else
	//			{
	//				break;
	//			}
	//		}
	//	}
	//	
	//}

	//�ҵ��ѽ���ڽӽڵ㣬�����ѽ���ڽӽڵ�Ϊ��ʼ�㿪ʼ���

	for (int i = 0; i < num_nodes; i++)
	{
		if (nodes[i].get_status())
		{
			que.push(i + 1);
		}
	}
	while (que.size() != 0)
	{
		number = que.front();
		que.pop();
		nodes[number - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
		for (int i = 0; i < num_neigh; i++)
		{
			end2 = (edges + *(ptr_neigh + i) - 1)->end1 == number ?
				(edges + *(ptr_neigh + i) - 1)->end2 : (edges + *(ptr_neigh + i) - 1)->end1;
			nodes[number - 1].get_distance(nodes[end2 - 1], &distance);
			if (!nodes[end2 - 1].get_status() &&
				distance <= thresh &&
				fabs((edges + *(ptr_neigh + i) - 1)->gain) < tt &&
				!(edges + *(ptr_neigh + i) - 1)->isResidueEdge /*�ǳ�����ֵ�Ĳв��*/
				)
			{
				que.push(end2);
				nodes[number - 1].get_phase(&phi1);
				nodes[end2 - 1].get_phase(&phi2);
				grad = phi2 - phi1;
				grad = atan2(sin(grad), cos(grad));
				gain = number > end2 ? 2 * PI * (edges + *(ptr_neigh + i) - 1)->gain : -2 * PI * (edges + *(ptr_neigh + i) - 1)->gain;
				nodes[end2 - 1].set_phase(grad + phi1 + gain);
				nodes[end2 - 1].set_status(true);
			}
		}
	}
	
	int row, col;
	for (int i = 0; i < num_nodes; i++)
	{
		if (nodes[i].get_status())
		{
			ret = nodes[i].get_pos(&row, &col);
			ret = nodes[i].get_phase(&phi1);
			unwrapped_phase.at<double>(row, col) = phi1;
		}
	}

	return 0;
}

int Unwrap::mcf_delaunay(const char* MCF_problem_file, const char* MCF_EXE_PATH)
{
	if (MCF_problem_file == NULL ||
		MCF_EXE_PATH == NULL
		)
	{
		fprintf(stderr, "mcf_delaunay(): input check failed!\n\n");
		return -1;
	}
	USES_CONVERSION;
	Utils util;
	//////////////////////////������������С������������///////////////////////////////
	LPWSTR szCommandLine = new TCHAR[256];
	wcscpy(szCommandLine, A2W(MCF_EXE_PATH));
	wcscat(szCommandLine, L"\\mcf.exe ");
	wcscat(szCommandLine, A2W(MCF_problem_file));
	STARTUPINFO si;
	PROCESS_INFORMATION p_i;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&p_i, sizeof(p_i));
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = FALSE;
	BOOL bRet = ::CreateProcess(
		NULL,           // ���ڴ�ָ����ִ���ļ����ļ���
		szCommandLine,      // �����в���
		NULL,           // Ĭ�Ͻ��̰�ȫ��
		NULL,           // Ĭ���̰߳�ȫ��
		FALSE,          // ָ����ǰ�����ڵľ�������Ա��ӽ��̼̳�
		CREATE_NEW_CONSOLE, // Ϊ�½��̴���һ���µĿ���̨����
		NULL,           // ʹ�ñ����̵Ļ�������
		NULL,           // ʹ�ñ����̵���������Ŀ¼
		&si,
		&p_i);
	if (bRet)
	{
		HANDLE hd = CreateJobObjectA(NULL, "MCF");
		if (hd)
		{
			JOBOBJECT_EXTENDED_LIMIT_INFORMATION extLimitInfo;
			extLimitInfo.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
			BOOL retval = SetInformationJobObject(hd, JobObjectExtendedLimitInformation, &extLimitInfo, sizeof(extLimitInfo));
			if (retval)
			{
				if (p_i.hProcess)
				{
					retval = AssignProcessToJobObject(hd, p_i.hProcess);
				}
			}
		}
		WaitForSingleObject(p_i.hProcess, INFINITE);
		if (szCommandLine != NULL) delete[] szCommandLine;
		::CloseHandle(p_i.hThread);
		::CloseHandle(p_i.hProcess);
	}
	else
	{
		fprintf(stderr, "MCF(): create mcf.exe process failed!\n\n");
		if (szCommandLine != NULL) delete[] szCommandLine;
		return -1;
	}
	return 0;
}

int Unwrap::QualityMap_MCF(Mat& wrapped_phase, Mat& unwrapped_phase, Mat& mask, vector<tri_node>& nodes, tri_edge* edges, int num_edges, int start, bool pass, double thresh)
{
	if (wrapped_phase.rows < 2 ||
		wrapped_phase.cols < 2 ||
		wrapped_phase.type() != CV_64F ||
		wrapped_phase.channels() != 1 ||
		mask.rows != wrapped_phase.rows ||
		mask.cols != wrapped_phase.cols ||
		mask.type() != CV_32S ||
		mask.channels() != 1 ||
		nodes.size() < 3 ||
		edges == NULL ||
		num_edges < 1 ||
		start < 1 ||
		start > nodes.size()
		)
	{
		fprintf(stderr, "MCF(): input check failed!\n\n");
		return -1;
	}
	wrapped_phase.copyTo(unwrapped_phase);
	int num_nodes = nodes.size();
	int num_neigh, number, ret, end2;
	double distance, grad, phi1, phi2, gain, tt, min, max;
	min = 1000000000.0;
	max = -1000000000.0;
	if (pass) tt = 0.5;
	else
	{
		tt = 100000.0;
	}
	long* ptr_neigh = NULL;
	//queue<int> que;
	priority_queue<edge_index> neighbour_que;
	edge_index tmp_edge_index;
	bool early_break = false;
	//int start = 1;//��ʼ��Ĭ��Ϊ��һ���㣬���������Լ��趨
	if (start > num_nodes) start = 1;
	//////////Ѱ�����ϵ�����ı�Ϊ��ʼ��////////////
	int ix = 0;
	double qua = 100000.0;
	for (int i = 0; i < num_edges; i++)
	{
		if ((edges + i)->quality < qua)
		{
			ix = i;
			qua = (edges + i)->quality;
		}
	}
	start = (edges + ix)->end1;
	ret = nodes[start - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
	if (return_check(ret, "tri_node::get_neigh_ptr(*, *)", error_head)) return -1;
	nodes[start - 1].set_status(true);
	for (int i = 0; i < num_neigh; i++)
	{
		end2 = (edges + *(ptr_neigh + i) - 1)->end1 == start ? (edges + *(ptr_neigh + i) - 1)->end2 : (edges + *(ptr_neigh + i) - 1)->end1;
		nodes[start - 1].get_distance(nodes[end2 - 1], &distance);
		if (!nodes[end2 - 1].get_status() &&
			distance <= thresh &&
			fabs((edges + *(ptr_neigh + i) - 1)->gain) < tt &&
			nodes[end2 - 1].get_balance() /*&&
			!nodes[end2 - 1].is_residue_node()*/
			)
		{
			tmp_edge_index.num = *(ptr_neigh + i);
			tmp_edge_index.quality = (edges + *(ptr_neigh + i) - 1)->quality;
			neighbour_que.push(tmp_edge_index);
		}
	}


	while (neighbour_que.size() != 0)
	{
		tmp_edge_index = neighbour_que.top();
		neighbour_que.pop();
		if (nodes[(edges + tmp_edge_index.num - 1)->end1 - 1].get_status())
		{
			number = (edges + tmp_edge_index.num - 1)->end1;
			end2 = (edges + tmp_edge_index.num - 1)->end2;
		}
		else
		{
			number = (edges + tmp_edge_index.num - 1)->end2;
			end2 = (edges + tmp_edge_index.num - 1)->end1;
		}
		//number = nodes[(edges + tmp_edge_index.num - 1)->end1 - 1].get_status() ? (edges + tmp_edge_index.num - 1)->end2 : (edges + tmp_edge_index.num - 1)->end1;
		//end2 = (edges + tmp_edge_index.num - 1)->end1 == number ? (edges + tmp_edge_index.num - 1)->end2 : (edges + tmp_edge_index.num - 1)->end1;
		nodes[number - 1].get_phase(&phi1);
		nodes[end2 - 1].get_phase(&phi2);
		grad = phi2 - phi1;
		if (!nodes[end2 - 1].get_status() &&
			fabs((edges + tmp_edge_index.num - 1)->gain) < tt &&
			nodes[end2 - 1].get_balance()/*&&
			!nodes[end2 - 1].is_residue_node()*/
			)
		{
			grad = atan2(sin(grad), cos(grad));
			gain = 0.0;
			//gain = number > end2 ? 2 * PI * (edges + tmp_edge_index.num - 1)->gain : -2 * PI * (edges + tmp_edge_index.num - 1)->gain;
			min = min > (grad + phi1 + gain) ? (grad + phi1 + gain) : min;
			max = max < (grad + phi1 + gain) ? (grad + phi1 + gain) : max;
			nodes[end2 - 1].set_phase(grad + phi1 + gain);
			nodes[end2 - 1].set_status(true);


			ret = nodes[end2 - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
			if (return_check(ret, "tri_node::get_neigh_ptr(*, *)", error_head)) return -1;
			number = end2;
			for (int i = 0; i < num_neigh; i++)
			{

				end2 = (edges + *(ptr_neigh + i) - 1)->end1 == number ? (edges + *(ptr_neigh + i) - 1)->end2 : (edges + *(ptr_neigh + i) - 1)->end1;
				nodes[number - 1].get_distance(nodes[end2 - 1], &distance);
				if (!nodes[end2 - 1].get_status() &&
					distance <= thresh &&
					fabs((edges + *(ptr_neigh + i) - 1)->gain) < tt &&
					nodes[end2 - 1].get_balance()/*&&
					!nodes[end2 - 1].is_residue_node()*/
					)
				{
					tmp_edge_index.num = *(ptr_neigh + i);
					tmp_edge_index.quality = (edges + *(ptr_neigh + i) - 1)->quality;
					neighbour_que.push(tmp_edge_index);
				}
			}
		}
		/*else
		{
			nodes[number - 1].get_distance(nodes[end2 - 1], &distance);
			if (nodes[end2 - 1].get_status() && fabs(grad) >= 2 * PI && distance < 1.5)
			{
				early_break = true;
				break;
			}
		}*/
		
	}

	int rows, cols;
	int nr = unwrapped_phase.rows;
	int nc = unwrapped_phase.cols;
	double phi;
	Mat _mask = Mat::zeros(nr, nc, CV_32S);
	for (int i = 0; i < num_nodes; i++)
	{
		if (nodes[i].get_status())
		{
			ret = nodes[i].get_pos(&rows, &cols);
			if (rows > nr - 1 || cols > nc - 1 || rows < 0 || cols < 0)
			{
				fprintf(stderr, "MCF(): node posistion exceed legal range!\n");
				return -1;
			}
			ret = nodes[i].get_phase(&phi);
			unwrapped_phase.at<double>(rows, cols) = phi;
			_mask.at<int>(rows, cols) = 1;
		}
	}
#pragma omp parallel for schedule(guided)
	for (int i = 0; i < nr; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			if (_mask.at<int>(i, j) < 1)
			{
				unwrapped_phase.at<double>(i, j) = min - 0.1 * (max - min);
			}
		}
	}
	_mask.copyTo(mask);
	return 0;
}

int Unwrap::_QualityGuided_MCF_1(
	const Mat& wrapped_phase, 
	Mat& unwrapped_phase,
	Mat& out_mask,
	vector<tri_node>& nodes,
	vector<tri_edge>& edges,
	double distance_thresh, 
	bool pass
)
{
	if (wrapped_phase.empty() ||
		wrapped_phase.type() != CV_64F ||
		nodes.size() < 3 ||
		edges.size() < 3 ||
		distance_thresh < 1.0
		)
	{
		fprintf(stderr, "_Quality_MCF_1(): input check failed!\n");
		return -1;
	}

	wrapped_phase.copyTo(unwrapped_phase);
	int num_nodes = nodes.size();
	int num_neigh, number, ret, end2, start;
	double distance, grad, phi1, phi2, gain, tt, min, max;
	min = 1000000000.0;
	max = -1000000000.0;
	long* ptr_neigh = NULL;
	priority_queue<edge_index> neighbour_que;
	edge_index tmp_edge_index;
	bool early_break = false;
	size_t num_edges = edges.size();
	//////////Ѱ�����ϵ�����ı�Ϊ��ʼ��(��Ӧquality��С�ı�)////////////
	int ix = 0;
	double qua = 100000.0;
	for (int i = 0; i < num_edges; i++)
	{
		if (edges[i].quality < qua)
		{
			ix = i;
			qua = edges[i].quality;
		}
	}
	start = edges[ix].end1;

	ret = nodes[start - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
	if (return_check(ret, "tri_node::get_neigh_ptr(*, *)", error_head)) return -1;
	nodes[start - 1].set_status(true);
	for (int i = 0; i < num_neigh; i++)
	{
		end2 = edges[*(ptr_neigh + i) - 1].end1 == start ? edges[*(ptr_neigh + i) - 1].end2 : edges[*(ptr_neigh + i) - 1].end1;
		nodes[start - 1].get_distance(nodes[end2 - 1], &distance);
		if (!nodes[end2 - 1].get_status() &&
			distance <= distance_thresh &&
			!edges[*(ptr_neigh + i) - 1].isBoundry &&
			nodes[end2 - 1].get_balance() &&
			!edges[*(ptr_neigh + i) - 1].isResidueEdge
			)
		{
			tmp_edge_index.num = *(ptr_neigh + i);
			tmp_edge_index.quality = edges[*(ptr_neigh + i) - 1].quality;
			neighbour_que.push(tmp_edge_index);
		}
	}


	while (neighbour_que.size() != 0)
	{
		tmp_edge_index = neighbour_que.top();
		neighbour_que.pop();
		if (nodes[edges[tmp_edge_index.num - 1].end1 - 1].get_status())
		{
			number = edges[tmp_edge_index.num - 1].end1;
			end2 = edges[tmp_edge_index.num - 1].end2;
		}
		else
		{
			number = edges[tmp_edge_index.num - 1].end2;
			end2 = edges[tmp_edge_index.num - 1].end1;
		}
		if (!nodes[end2 - 1].get_status() &&
			!edges[tmp_edge_index.num - 1].isBoundry &&
			nodes[end2 - 1].get_balance() && 
			!edges[tmp_edge_index.num - 1].isResidueEdge
			)
		{
			nodes[number - 1].get_phase(&phi1);
			nodes[end2 - 1].get_phase(&phi2);
			grad = phi2 - phi1;
			grad = atan2(sin(grad), cos(grad));
			gain = 0.0;
			//min = min > (grad + phi1 + gain) ? (grad + phi1 + gain) : min;
			//max = max < (grad + phi1 + gain) ? (grad + phi1 + gain) : max;
			nodes[end2 - 1].set_phase(grad + phi1 + gain);
			nodes[end2 - 1].set_status(true);


			ret = nodes[end2 - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
			if (return_check(ret, "tri_node::get_neigh_ptr(*, *)", error_head)) return -1;
			number = end2;
			for (int i = 0; i < num_neigh; i++)
			{

				end2 = edges[*(ptr_neigh + i) - 1].end1 == number ? edges[*(ptr_neigh + i) - 1].end2 : edges[*(ptr_neigh + i) - 1].end1;
				nodes[number - 1].get_distance(nodes[end2 - 1], &distance);
				if (!nodes[end2 - 1].get_status() &&
					distance <= distance_thresh &&
					!edges[*(ptr_neigh + i) - 1].isBoundry &&
					nodes[end2 - 1].get_balance()&&
					!edges[*(ptr_neigh + i) - 1].isResidueEdge
					)
				{
					tmp_edge_index.num = *(ptr_neigh + i);
					tmp_edge_index.quality = edges[*(ptr_neigh + i) - 1].quality;
					neighbour_que.push(tmp_edge_index);
				}
			}
		}


	}

	
	int nr = unwrapped_phase.rows;
	int nc = unwrapped_phase.cols;
	double phi;
	Mat _mask = Mat::zeros(nr, nc, CV_32S);
#pragma omp parallel for schedule(guided)
	for (int i = 0; i < num_nodes; i++)
	{
		int rows, cols; double phi3;
		if (nodes[i].get_status())
		{
			nodes[i].get_pos(&rows, &cols);
			nodes[i].get_phase(&phi3);
			unwrapped_phase.at<double>(rows, cols) = phi3;
			_mask.at<int>(rows, cols) = 1;
		}
	}
//#pragma omp parallel for schedule(guided)
//	for (int i = 0; i < nr; i++)
//	{
//		for (int j = 0; j < nc; j++)
//		{
//			if (_mask.at<int>(i, j) < 1)
//			{
//				unwrapped_phase.at<double>(i, j) = min - 0.1 * (max - min);
//			}
//		}
//	}
	_mask.copyTo(out_mask);

	return 0;
}

int Unwrap::_QualityGuided_MCF_2(
	Mat& unwrapped_phase,
	vector<tri_node>& nodes, 
	vector<tri_edge>& edges,
	double distance_thresh
)
{
	if (unwrapped_phase.rows < 2 ||
		unwrapped_phase.cols < 2 ||
		unwrapped_phase.type() != CV_64F ||
		unwrapped_phase.channels() != 1 ||
		nodes.size() < 3 ||
		edges.size() < 3 
		)
	{
		fprintf(stderr, "_QualityGuided_MCF_2(): input check failed!\n\n");
		return -1;
	}
	int num_nodes = nodes.size();
	int num_neigh, number, ret, end2, row_start, col_start;
	double distance, grad, phi1, phi2, gain, tt;
	long* ptr_neigh = NULL;
	queue<int> que;
	//queue<int> start_que;
	int nr = unwrapped_phase.rows;
	int nc = unwrapped_phase.cols;

	//�ҵ��ѽ���ڽӽڵ㣬�����ѽ���ڽӽڵ�Ϊ��ʼ�㿪ʼ���

	for (int i = 0; i < num_nodes; i++)
	{
		if (nodes[i].get_status())
		{
			que.push(i + 1);
		}
	}
	while (que.size() != 0)
	{
		number = que.front();
		que.pop();
		nodes[number - 1].get_neigh_ptr(&ptr_neigh, &num_neigh);
		for (int i = 0; i < num_neigh; i++)
		{
			end2 = edges[*(ptr_neigh + i) - 1].end1 == number ?
				edges[*(ptr_neigh + i) - 1].end2 : edges[*(ptr_neigh + i) - 1].end1;
			nodes[number - 1].get_distance(nodes[end2 - 1], &distance);
			if (!nodes[end2 - 1].get_status() &&
				distance <= distance_thresh &&
				!edges[*(ptr_neigh + i) - 1].isBoundry
				)
			{
				que.push(end2);
				nodes[number - 1].get_phase(&phi1);
				nodes[end2 - 1].get_phase(&phi2);
				grad = phi2 - phi1;
				grad = atan2(sin(grad), cos(grad));
				gain = number < end2 ? 2 * PI * edges[*(ptr_neigh + i) - 1].gain : -2 * PI * edges[*(ptr_neigh + i) - 1].gain;
				nodes[end2 - 1].set_phase(grad + phi1 + gain);
				nodes[end2 - 1].set_status(true);
			}
		}
	}

#pragma omp parallel for schedule(guided)
	for (int i = 0; i < num_nodes; i++)
	{
		int row, col; double phi3;
		if (nodes[i].get_status())
		{
			ret = nodes[i].get_pos(&row, &col);
			ret = nodes[i].get_phase(&phi3);
			unwrapped_phase.at<double>(row, col) = phi3;
		}
	}

	return 0;
}

int Unwrap::QualityGuided_MCF(
	const Mat& wrapped_phase,
	Mat& unwrapped_phase, 
	double coherence_thresh,
	double distance_thresh,
	const char* tmp_path, 
	const char* EXE_path
)
{
	if (wrapped_phase.empty() ||
		tmp_path == NULL ||
		EXE_path == NULL ||
		coherence_thresh < 0.0 ||
		coherence_thresh > 1.0
		)
	{
		fprintf(stderr, "QualityGuided_MCF(): input check failed!\n");
		return -1;
	}
	distance_thresh = distance_thresh < 2.0 ? 2.0 : distance_thresh;
	Mat coherence, phase, mask, quality_index;
	Utils util;
	int ret, nr, nc, count = 0;
	nr = wrapped_phase.rows; nc = wrapped_phase.cols;
	wrapped_phase.copyTo(phase);
	ret = util.phase_coherence(phase, 3, 3, coherence);
	if (return_check(ret, "phase_coherence()", error_head)) return -1;
	quality_index = 1 - coherence;
	mask = Mat::zeros(nr, nc, CV_32S);


	for (int i = 0; i < nr; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			if (coherence.at<double>(i, j) > coherence_thresh)
			{
				mask.at<int>(i, j) = 1; count++;
			}
		}
	}
	if (count < 100)
	{
		Mat residue;
		ret = util.residue(phase, residue);
		if (return_check(ret, "residue()", error_head)) return -1;
		string mcf_problem_file(tmp_path);
		mcf_problem_file.append("\\mcf_problem.net");
		ret = MCF(phase, unwrapped_phase, coherence, residue, mcf_problem_file.c_str(), EXE_path);
		if (return_check(ret, "MCF()", error_head)) return -1;
		return 0;
	}

	string folder(tmp_path);
	string node_file = folder + "\\triangle.node";
	string edge_file = folder + "\\triangle.1.edge";
	string ele_file = folder + "\\triangle.1.ele";
	string neigh_file = folder + "\\triangle.1.neigh";
	string mcf_problem = folder + "\\mcf_delaunay.net";
	string mcf_solution = folder + "\\mcf_delaunay.net.sol";
	vector<tri_node> nodes; vector<tri_edge> edges; vector<triangle> tri;
	vector<int> node_neighbour;
	long num_nodes = count;
	ret = util.write_node_file(node_file.c_str(), mask);
	if (return_check(ret, "write_node_file()", error_head)) return -1;
	ret = util.gen_delaunay(node_file.c_str(), EXE_path);
	if (return_check(ret, "gen_delaunay()", error_head)) return -1;
	ret = util.read_edges(edge_file.c_str(), edges, node_neighbour, num_nodes);
	if (return_check(ret, "read_edges()", error_head)) return -1;
	ret = util.init_tri_node(nodes, phase, mask, edges, node_neighbour, num_nodes);
	if (return_check(ret, "init_tri_node()", error_head)) return -1;
	ret = util.init_edges_quality(quality_index, edges, nodes);
	if (return_check(ret, "init_edges_quality()", error_head)) return -1;
	ret = util.read_triangle(ele_file.c_str(), neigh_file.c_str(), tri, nodes, edges);
	if (return_check(ret, "read_triangle()", error_head)) return -1;
	ret = util.residue(tri, nodes, edges, distance_thresh);
	if (return_check(ret, "residue()", error_head)) return -1;

	Mat out_mask;
	ret = _QualityGuided_MCF_1(phase, unwrapped_phase, out_mask, nodes, edges, distance_thresh);
	if (return_check(ret, "residue()", error_head)) return -1;

	out_mask.convertTo(out_mask, CV_64F);
	util.cvmat2bin("E:\\working_dir\\projects\\software\\InSAR\\bin\\out_mask.bin", out_mask);
	out_mask.convertTo(out_mask, CV_32S);
	util.cvmat2bin("E:\\working_dir\\projects\\software\\InSAR\\bin\\unwrapped_phase1.bin", unwrapped_phase);

	Mat mask_2 = Mat::zeros(nr, nc, CV_32S);
	count = 0;
	for (int i = 0; i < nr; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			if (out_mask.at<int>(i, j) == 0)
			{
				mask_2.at<int>(i, j) = 1; count++;
			}
		}
	}

	//�ҳ��ڽ��ѽ���ڵ�
	Mat grad_updown, grad_leftright;
	grad_updown = mask_2(cv::Range(1, nr), cv::Range(0, nc)) - mask_2(cv::Range(0, nr - 1), cv::Range(0, nc));
	grad_leftright = mask_2(cv::Range(0, nr), cv::Range(1, nc)) - mask_2(cv::Range(0, nr), cv::Range(0, nc - 1));
	for (int i = 0; i < grad_updown.rows; i++)
	{
		for (int j = 0; j < grad_updown.cols; j++)
		{
			if (grad_updown.at<int>(i, j) > 0)
			{
				mask_2.at<int>(i, j) = 2;//2�����ڽ��ѽ���ڵ�
			}
			if (grad_updown.at<int>(i, j) < 0)
			{
				mask_2.at<int>(i + 1, j) = 2;
			}
		}
	}
	for (int i = 0; i < grad_leftright.rows; i++)
	{
		for (int j = 0; j < grad_leftright.cols; j++)
		{
			if (grad_leftright.at<int>(i, j) > 0)
			{
				mask_2.at<int>(i, j) = 2;
			}
			if (grad_leftright.at<int>(i, j) < 0)
			{
				mask_2.at<int>(i, j + 1) = 2;
			}
		}
	}

	num_nodes = cv::countNonZero(mask_2);
	ret = util.write_node_file(node_file.c_str(), mask_2);
	if (return_check(ret, "write_node_file()", error_head)) return -1;
	ret = util.gen_delaunay(node_file.c_str(), EXE_path);
	if(return_check(ret, "gen_delaunay()", error_head)) return -1;
	ret = util.read_edges(edge_file.c_str(), edges, node_neighbour, num_nodes);
	if (return_check(ret, "read_edges()", error_head)) return -1;
	ret = util.init_tri_node(nodes, unwrapped_phase, mask_2, edges, node_neighbour, num_nodes);
	if (return_check(ret, "init_tri_node()", error_head)) return -1;
	ret = util.read_triangle(ele_file.c_str(), neigh_file.c_str(), tri, nodes, edges);
	if (return_check(ret, "read_triangle()", error_head)) return -1;
	ret = util.residue(tri, nodes, edges, distance_thresh);
	if (return_check(ret, "residue()", error_head)) return -1;
	ret = util.write_DIMACS(mcf_problem.c_str(), tri, nodes, edges, coherence);
	if (return_check(ret, "write_DIMACS()", error_head)) return -1;
	ret = mcf_delaunay(mcf_problem.c_str(), EXE_path);
	if (return_check(ret, "mcf_delaunay()", error_head)) return -1;
	ret = util.read_DIMACS(mcf_solution.c_str(), edges, nodes, tri);
	if (return_check(ret, "read_DIMACS()", error_head)) return -1;
	ret = _QualityGuided_MCF_2(unwrapped_phase, nodes, edges, distance_thresh);
	if (return_check(ret, "_QualityGuided_MCF_2()", error_head)) return -1;


	return 0;
}
