// sortClass.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<random>
#include<crtdbg.h>
#include<vector>
using namespace std;

//QuickSort
int Partition(int data[], int start, int end, int length);
void QuickSortWithRecursion(int data[], int start, int end, int length);

//BubbleSort
void BubbleSort(int data[], int length);
//SelectSort
void SelectSort(int data[], int length);
//HeapSort
void adjust(int arr[], int len, int index);
void heapSort(int arr[], int size);
//MergeSort
void merge(vector<int>& vc, int l1, int r1, int l2, int r2);
void MergeSort(vector<int>& vc, int start, int end);
void MergeSort1(vector<int>& nums, int start, int end);


int main()
{
	int data[15] = { 33,23,555,342,1245,445,8878,222,1,21,1,34,27,789,2222 };
	//test for QuickSort
	//QuickSortWithRecursion(data, 0, 14, 15);
	//test for BubbleSort
	//BubbleSort(data,15);
	//test for SelectSort
	//SelectSort(data, 15);
	//test for heapSort
	//heapSort(data, 15);
	//test for MergeSort;
	vector<int> data1;
	for (auto i:data )
	{
		data1.push_back(i);
	}
	
	MergeSort(data1,0,14);

	int count = 0;
	for (int x:data1)
	{
		count++;
		cout << x<<" ";
	}
	cout << endl << count<<endl;
    return 0;
}

int Partition(int data[], int start, int end, int length)
{
	if (data == nullptr || length <= 0 || start > end || start < 0)
		throw new exception("Shit!");
	else
	{
		srand(0);
		int select = rand() % (end - start) + start;
		swap(data[end],data[select]);
		int small =start-1;
		for (select = start; select < end; select++)
		{
			if (data[select]<data[end])
			{
				++small;
				if (select!=small)
				{
					swap(data[select], data[small]);
				}
			}
		}
		++small;
		swap(data[end], data[small]);
		return small;
	}
	
}

void QuickSortWithRecursion(int data[], int start, int end, int length)
{
	if (start == end)
		return;
	int index = Partition(data, start, end, length);
	if (index > start)
		QuickSortWithRecursion(data, start, index-1, length);
	if (index<end)
	{
		QuickSortWithRecursion(data, index + 1, end,length);
	}
}

void BubbleSort(int data[], int length)
{
	bool change = true;
	for ( int i = length-1; i >= 0&&change; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (data[j] > data[j + 1])
			{
				swap(data[j], data[j + 1]);
				change = true;
			}
		}
	}
}

void SelectSort(int data[], int length)
{	
	for (int i = length-1; i >=0; i--)
	{
		int max = 0;
		for (int j = 0; j<=i; j++)
		{
			if (data[j] >data[max])
				max = j;
		}
		if(i!=max)
		swap(data[max], data[i]);
	}
}
void adjust(int arr[], int len, int index)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int maxIdx = index;
	if (left<len && arr[left] > arr[maxIdx]) maxIdx = left;
	if (right<len && arr[right] > arr[maxIdx]) maxIdx = right;  // maxIdx是3个数中最大数的下标
	if (maxIdx != index)                 // 如果maxIdx的值有更新
	{
		swap(arr[maxIdx], arr[index]);
		adjust(arr, len, maxIdx);       // 递归调整其他不满足堆性质的部分
	}

}
void heapSort(int arr[], int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)  // 对每一个非叶结点进行堆调整(从最后一个非叶结点开始)
	{
		adjust(arr, size, i);
	}
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);           // 将当前最大的放置到数组末尾
		adjust(arr, i, 0);              // 将未完成排序的部分继续进行堆排序
	}
}
void merge(vector<int>& nums, int l1, int r1, int l2, int r2) {
	int i = l1;                                               //左半部分起始位置
	int j = l2;                                               //右半部分起始位置
	int n = (r1 - l1 + 1) + (r2 - l2 + 1);                    //要合并的元素个数
	vector<int> temp(n);                                      //辅助数组
	int k = 0;	                                          //辅助数组其起始位置
	while (i <= r1 && j <= r2) {                                //挑选两部分中最小的元素放入辅助数组中
		if (nums[i] < nums[j])
			temp[k++] = nums[i++];
		else
			temp[k++] = nums[j++];
	}
	//如果还有剩余，直接放入到辅助数组中
	while (i <= r1)
		temp[k++] = nums[i++];
	while (j <= r2)
		temp[k++] = nums[j++];
	//更新原始数组元素
	for (int i = 0; i < n; i++)
	{
		nums[l1 + i] = temp[i];
	}
}

/*二路归并排序（递归实现）*/
void MergeSort(vector<int>& nums, int start, int end) {
	if (start < end) {
		int mid = (start + end) >> 1;				//分割序列
		MergeSort(nums, start, mid);				//对序列左半部分进行规并排序
		MergeSort(nums, mid + 1, end);				//对序列右半部分进行规并排序
		merge(nums, start, mid, mid + 1, end);                  //合并已经有序的两个序列
	}
}
/*二路归并排序（迭代实现）*/
void MergeSort1(vector<int>& nums, int start, int end)
{
	int n = nums.size();
	if (start < end) {
		//step为组内元素个数，step/2为左子区间元素个数
		for (int step = 2; step / 2 < n; step *= 2) {
			//每step个元素一组，组内前step/2和后step/2个元素进行合并
			for (int i = 0; i < n; i += step) {
				int mid = i + step / 2 - 1;					//左子区间元素个数为step/2
				if (mid + 1 < n)							//右子区间存在元素个数则合并
					//左子区间为[i,mid]，右子区间为[mid+1, min(i+step-1, n-1)]
					merge(nums, i, mid, mid + 1, min(i + step - 1, n - 1));
			}
		}
	}
}
