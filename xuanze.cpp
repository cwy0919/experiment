#include <stdio.h>
#include <stdlib.h>
#include<time.h>
//ѡ��������
void selectSort( int data[] ,int n )
{

 /*----begin------*/
 int min;//����һ��������������Сֵ�±�
 for(int i=0;i<n-1;i++)//��ѭ�����ƱȽϴ�������n�����ͱȽ�n-1��
 {
   min=i;// ������Сֵ��data[i],��data[0]
   for(int j=i+1;j<n;j++)//����Сֵ����Сֵ�������data[i+1]~data[n-1]�Ƚ�
   {
   	  //����Щ����ͨ�����ƶ�����Сֵdata[min]�Ƚ��ҵ���Сֵ
      if(data[j]<data[min])
      {
      	//����б���Сֵ��С��
        min=j;//��¼����Сֵ���±�
      }
   }
   //�˳���ѭ�����ж��Ƿ��б���Сֵ��С��
   //����оͽ���
   if(data[i]!=data[min])
   {
   	  //����û�н��õ��������������ķ�ʽ
      data[i]=data[min]+data[i];
      data[min]=data[i]-data[min];
      data[i]=data[i]-data[min];
   }
 }
 /*-----end------*/
}

//�������Ԫ��
void print(int data[] ,int n)
{
 for(int i=0;i<n;i++)
   printf("%d ",data[i]);
 printf("\n");
}
//������
int main()
{
	int k;
	int data[100];
	srand((unsigned)time(NULL));//��֤ÿ�����ɵ��������һ��
	for(k=0;k<=99;k++)
	{
		data[k]=rand()%(1000-99)+99;//������ķ�Χ��a,b)s
	}
//	print(data,10);//���ԭ����
    selectSort(data,100);//����ѡ��������
    print(data,100);//�������������
	return 0;
}


 
