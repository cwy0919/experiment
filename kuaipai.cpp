#include<stdio.h>
#include<time.h>
#include<stdlib.h>
void swap(int* a, int* b);
void swap(int *a, int *b){
	int temp = *a;
    *a = *b;
    *b = temp;
	}

//三数取中
int GetMid(int *a,int begin, int end)
{
	int mid = (begin + end) / 2;
	if (a[begin] > a[end])
	{
		if (a[end] > a[mid])
			return end;
		else if (a[mid] > a[begin])
			return begin;
		else
			return mid;
	}
	else
	{
		if (a[end] < a[mid])
			return end;
		else if (a[end] < a[begin])
			return begin;
		else
			return mid;
	}
}
void QuickSort_Pointer(int* a, int begin, int end)
{
	if (begin >= end)
	{
		return;
	}
	//数据区间大与10，进行快速排序
    int prev = begin;
	int cur = begin + 1;
	int keyi = begin;
	//三数取中后对keyi位置的值进行交换
	int mid = GetMid(a, begin, end);
	

	while (cur <= end)
	{
		//cur一直往前走，如果碰到小于并且prev++不等于cur则交换，
		//因为如果prev+1 == cur 则会发生自己与自己交换的情况
		if (a[cur] < a[keyi] && ((++prev) != cur))
		{
			swap(&a[cur], &a[prev]);
		}
		cur++;
	}
	swap(&a[prev], &a[keyi]);
	keyi = prev;
	//开始进行递归
	QuickSort_Pointer(a, begin, keyi - 1);
	QuickSort_Pointer(a, keyi + 1, end);
}
//输出数组元素
void print(int a[] ,int n)
{
 for(int i=0;i<n;i++)
   printf("%d ",a[i]);
 printf("\n");
}
//主函数
int main()
{
	int k;
	int a[100];
	srand((unsigned)time(NULL));//保证每次生成的随机数不一样
	for(k=0;k<=99;k++)
	{
		a[k]=rand()%(1000-99)+99;//随机数的范围（a,b)s
	}
	//print(a,9);//输出原数组
    QuickSort_Pointer(a,0,99);//调用排序函数
    print(a,99);//输出排序后的数组
	return 0;
}


