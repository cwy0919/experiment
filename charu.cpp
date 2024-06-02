#include<stdio.h>
#include<time.h>
#include<stdlib.h>
//插入排序
void InsertSort(int* a, int n)
{
	for (int i = 0; i < n-1; i++)
	{
		//end可看作从左至右有序的最后一个数的下标
		int end = i;
		int tmp = a[end + 1];
		
		while (end >= 0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
			}
			else
			{
				break;
			}
			end--;
		}
		//此时tmp的值大于或等于下标为end的值，所以插入在它的后面
		a[end+1] = tmp;
	}
}

//打印数组
void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
} 
//测试插入排序
void TestInsertSort()
{
    //任意建立一组无序的数
	int a[100] ;
	int j;
	srand((unsigned)time(NULL));//保证每次生成的随机数不一样
    for(j=0;j<=99;j++)
	{
		a[j]=rand()%(1000-99)+99;//随机数的范围（a,b)
			//printf("%d ",a[j]);
	}
	printf("\n");
	InsertSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

int main()
{
	printf("插入排序：\n");
	TestInsertSort();
	return 0;
}

