#pragma once
#include<stdio.h>
#include<stdlib.h>
struct Heap //����С�����Դ������ڽӵ�����
{
	int size;
	int* x = (int*)malloc(sizeof(int) * 100000000);
	int* y = (int*)malloc(sizeof(int) * 100000000);
	double* queue = (double*)malloc(sizeof(double) * 100000000);
public:
	Heap()         //��ʼ�� 
	{
		size = 0;
		/*for (int i = 0; i < 1000000; i++)
		{
			queue[i] = 0;
			x[i] = 0;
			y[i] = 0;
		}*/
	}
	~Heap()
	{
	}

	void shift_up(int i)  //�ϸ� 
	{
		while (i > 1)
		{
			if (queue[i] < queue[i >> 1])
			{
				double temp = queue[i];
				queue[i] = queue[i >> 1];
				queue[i >> 1] = temp;
				int temp2 = x[i];
				x[i] = x[i >> 1];
				x[i >> 1] = temp2;
				temp2 = y[i];
				y[i] = y[i >> 1];
				y[i >> 1] = temp2;
			}
			i >>= 1;
		}
	}
	void shift_down(int i)   //�³� 
	{
		while ((i << 1) <= size)
		{
			int next = i << 1;
			if (next < size && queue[next + 1] < queue[next])
				next++;
			if (queue[i] > queue[next])
			{
				double temp = queue[i];
				queue[i] = queue[next];
				queue[next] = temp;
				int temp2 = x[i];
				x[i] = x[next];
				x[next] = temp2;
				temp2 = y[i];
				y[i] = y[next];
				y[next] = temp2;
				i = next;
			}
			else return;
		}
	}
	int push(double v, int map_x, int map_y)   //����Ԫ�� 
	{
		if (v < 0 ||
			map_x < 0 ||
			map_y < 0)
		{
			fprintf(stderr, "Heap::push(): input check failed!\n\n");
			return -1;
		}
		queue[++size] = v;
		x[size] = map_x;
		y[size] = map_y;
		shift_up(size);
		return 0;
	}
	int pop()         //�������� 
	{
		if (size <= 0)
		{
			fprintf(stderr, "Heap::pop(): no data!\n\n");
			return -1;
		}
		double temp = queue[1];
		queue[1] = queue[size];
		queue[size] = temp;
		int temp2 = x[1];
		x[1] = x[size];
		x[size] = temp2;
		temp2 = y[1];
		y[1] = y[size];
		y[size] = temp2;
		size--;
		shift_down(1);
		return 0;
	}
	int top(int* x0, int* y0)			//������ڵ�����
	{
		if (size <= 0)
		{
			fprintf(stderr, "Heap::top(): no data!\n\n");
			return -1;
		}
		*x0 = x[1];
		*y0 = y[1];
		return 1;
	}
	bool empty()
	{
		return size;
	}
};