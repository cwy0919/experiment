#include <stdio.h>
#include <stdlib.h>
#include<time.h>
//选择排序函数
void selectSort( int data[] ,int n )
{

 /*----begin------*/
 int min;//定义一个变量来储存最小值下标
 for(int i=0;i<n-1;i++)//外循环控制比较次数，有n个数就比较n-1次
 {
   min=i;// 假设最小值是data[i],即data[0]
   for(int j=i+1;j<n;j++)//用最小值跟最小值后面的数data[i+1]~data[n-1]比较
   {
   	  //在这些数中通过与制定的最小值data[min]比较找到最小值
      if(data[j]<data[min])
      {
      	//如果有比最小值还小的
        min=j;//记录下最小值的下标
      }
   }
   //退出内循环，判断是否有比最小值还小的
   //如果有就交换
   if(data[i]!=data[min])
   {
   	  //这是没有借用第三方变量交换的方式
      data[i]=data[min]+data[i];
      data[min]=data[i]-data[min];
      data[i]=data[i]-data[min];
   }
 }
 /*-----end------*/
}

//输出数组元素
void print(int data[] ,int n)
{
 for(int i=0;i<n;i++)
   printf("%d ",data[i]);
 printf("\n");
}
//主函数
int main()
{
	int k;
	int data[100];
	srand((unsigned)time(NULL));//保证每次生成的随机数不一样
	for(k=0;k<=99;k++)
	{
		data[k]=rand()%(1000-99)+99;//随机数的范围（a,b)s
	}
//	print(data,10);//输出原数组
    selectSort(data,100);//调用选择排序函数
    print(data,100);//输出排序后的数组
	return 0;
}


 
