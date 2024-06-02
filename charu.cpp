#include<stdio.h>
#include<time.h>
#include<stdlib.h>
//��������
void InsertSort(int* a, int n)
{
	for (int i = 0; i < n-1; i++)
	{
		//end�ɿ�������������������һ�������±�
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
		//��ʱtmp��ֵ���ڻ�����±�Ϊend��ֵ�����Բ��������ĺ���
		a[end+1] = tmp;
	}
}

//��ӡ����
void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
} 
//���Բ�������
void TestInsertSort()
{
    //���⽨��һ���������
	int a[100] ;
	int j;
	srand((unsigned)time(NULL));//��֤ÿ�����ɵ��������һ��
    for(j=0;j<=99;j++)
	{
		a[j]=rand()%(1000-99)+99;//������ķ�Χ��a,b)
			//printf("%d ",a[j]);
	}
	printf("\n");
	InsertSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}

int main()
{
	printf("��������\n");
	TestInsertSort();
	return 0;
}

