#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

// 生成有n个元素的随机数组，每个元素的随机范围为[rangeL, rangeR]
int *generateRandomArr(int n, int rangeL, int rangeR)
{
    int i = 0;
    int *arr = (int *)malloc(n * sizeof(int));

    assert(rangeL <= rangeR);

    srand(time(NULL));
    for (i = 0; i < n; i++)
        arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
    return arr;
}

//打印数组中所有元素
void printArr(int *arr, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//检查数组是否已被排序
int isSorted(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i+1])
            return -1;
    }
    return 0;
}

void __merge(int *arr, int l, int mid, int r)
{
    int *su = (int *)malloc((r- l + 1) * sizeof(int));

    for (int i = l; i <=r; i++) {
        su[i- l] = arr[i];
    }
    
    for (int k = l, i = l, j = mid + 1; k <= r; k++) {
        if (i > mid) {  //左半元素已被全部处理
            arr[k] = su[j++ - l];
        } else if (j > r) {
            arr[k] = su[i++ - l];
        } else if (su[i - l] < su[j - l] || j > r) {
            arr[k] = su[i++ - l];
        } else {
            arr[k] = su[j++ - l];
        }
    }
    free(su);
}

void __mergeSort(int *arr, int l, int r)
{
    if(l >= r)
        return;
    //优化思路，在归并到比较少元素时，可以使用插入排序进行优化
    int mid = (l + r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);
    if (arr[mid] > arr[mid + 1])
        __merge(arr, l, mid, r);
}

//归并排序
void mergeSort(int *arr, int n)
{
    __mergeSort(arr, 0, n - 1);
}

int main()
{
    int *arr = generateRandomArr(100, 2, 99);
    //printArr(arr, 100000);
    mergeSort(arr, 100);
    if (0 == isSorted(arr, 100)) {
        printf("排序正确\n");
        printArr(arr, 100);
    } else {
        printf("排序错误\n");
    }
}
