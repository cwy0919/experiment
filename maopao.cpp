#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int i,j,x,a[100];//���������
	srand((unsigned)time(NULL));//��֤ÿ�����ɵ��������һ��
	for(i=0;i<=99;i++)
	{
		a[i]=rand()%(10000-99)+99;//������ķ�Χ��a,b)
	//printf("%d ",a[i]);
	}
	printf("\n");
	for(i=0;i<=98;i++)//ð������
		for(j=i+1;j<=99;j++)
		{
			if(a[i]>a[j])
			{
				x=a[i];
				a[i]=a[j];
				a[j]=x;
			}
		}
		for(i=0;i<=99;i++)
			printf("%d ",a[i]);
			printf("\n");
			
			
		return 0;
 
}
