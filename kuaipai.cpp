#include<stdio.h>
#include<time.h>
#include<stdlib.h>
void swap(int* a, int* b);
void swap(int *a, int *b){
	int temp = *a;
    *a = *b;
    *b = temp;
	}

//����ȡ��
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
	//�����������10�����п�������
    int prev = begin;
	int cur = begin + 1;
	int keyi = begin;
	//����ȡ�к��keyiλ�õ�ֵ���н���
	int mid = GetMid(a, begin, end);
	

	while (cur <= end)
	{
		//curһֱ��ǰ�ߣ��������С�ڲ���prev++������cur�򽻻���
		//��Ϊ���prev+1 == cur ��ᷢ���Լ����Լ����������
		if (a[cur] < a[keyi] && ((++prev) != cur))
		{
			swap(&a[cur], &a[prev]);
		}
		cur++;
	}
	swap(&a[prev], &a[keyi]);
	keyi = prev;
	//��ʼ���еݹ�
	QuickSort_Pointer(a, begin, keyi - 1);
	QuickSort_Pointer(a, keyi + 1, end);
}
//�������Ԫ��
void print(int a[] ,int n)
{
 for(int i=0;i<n;i++)
   printf("%d ",a[i]);
 printf("\n");
}
//������
int main()
{
	int k;
	int a[100];
	srand((unsigned)time(NULL));//��֤ÿ�����ɵ��������һ��
	for(k=0;k<=99;k++)
	{
		a[k]=rand()%(1000-99)+99;//������ķ�Χ��a,b)s
	}
	//print(a,9);//���ԭ����
    QuickSort_Pointer(a,0,99);//����������
    print(a,99);//�������������
	return 0;
}


