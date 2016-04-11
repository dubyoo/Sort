#pragma once

////////////////////////////////////////////////////////////////
// 选择排序，不稳定，平均时间复杂度 O(n^2)
////////////////////////////////////////////////////////////////

void slelct_sort(int * arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		if (min != i)
			std::swap(arr[i], arr[min]);
	}
}



////////////////////////////////////////////////////////////////
// 插入排序，稳定，平均时间复杂度 O(n^2)
////////////////////////////////////////////////////////////////

/*
 * 插入算法把要排序的数组分成两部分：
 *		第一部分包含了这个数组的所有元素，但将最后一个元素除外（让数组多一个空间才有插入的位置），
 *		而第二部分就只包含这一个元素（即待插入元素）。
 * 在第一部分排序完成后，再将这个最后元素插入到已排好序的第一部分中。
 */
void insert_sort(int * arr, int len)
{
	for (int i = 1; i < len; i++)
	{
		int j = i;
		for (; j > 0; j--)
			if (arr[j - 1] < arr[i])
				break;
		
		if (j == i)
			continue;

		int tmp = arr[i];
		int k = i;
		for (; k > j; k--)
			arr[k] = arr[k - 1];
		arr[k] = tmp;
	}
}



////////////////////////////////////////////////////////////////
// 冒泡排序，稳定，平均时间复杂度 O(n^2)
////////////////////////////////////////////////////////////////

void bubble_sort(int * arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		bool changed = false;
		for (int j = i; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				changed = true;
			}
		}
		if (!changed)
			break;
	}
}



////////////////////////////////////////////////////////////////
// 快速排序，不稳定，平均时间复杂度 O(nlgn)
////////////////////////////////////////////////////////////////

/*
* 分治Partition，
* 两个下标分别从首尾向中间扫描
*/
int partition(int * arr, int len)
{
	int left = 0, right = len - 1;
	int pivot = arr[0];					// 以当前表中第一个元素为枢轴值进行划分

	while (left < right)				// 结束条件
	{
		while (left < right && arr[right] >= pivot)
			right--;
		arr[left] = arr[right];			// 比枢轴值小的元素移动到左端
		while (left < right && arr[left] < pivot)
			left++;
		arr[right] = arr[left];			// 比枢轴值大的元素移动到右端
	}
	arr[left] = pivot;					// 枢轴元素放到最终位置
	return left;						// 返回最终位置
}

void quick_sort(int * arr, int len)
{
	if (len > 0)
	{
		int part = partition(arr, len);
		quick_sort(arr, part);
		quick_sort(arr + part + 1, len - part - 1);
	}
}



////////////////////////////////////////////////////////////////
// 堆排序，不稳定，平均时间复杂度 O(nlgn)
////////////////////////////////////////////////////////////////

/* 
 * 本函数功能是：根据数组 arr 构建大根堆
 *      arr 是待调整的堆数组，
 *      i 是待调整的数组元素的位置，
 *      len 是数组的长度
 */
void heap_adjust(int* arr, int i, int len)
{
	int child;
	for (; 2 * i + 1 < len; i = child)
	{
		child = 2 * i + 1;					// 子结点的位置 = 2*(父结点位置)+1
		if (child < len - 1 && arr[child + 1] > arr[child])
			++child;						// 得到子结点中较大的结点
		if (arr[i] < arr[child])			// 如果较大的子结点大于父结点
			std::swap(arr[i], arr[child]);	// 把较大的子结点往上移动，替换它的父结点
		else
			break;
	}
}

void heap_sort(int* arr, int len)
{
	// 调整序列的前半部分元素，调整完之后第一个元素是序列的最大的元素
	// length/2-1 是最后一个非叶节点
	for (int i = len / 2 - 1; i >= 0; --i)
		heap_adjust(arr, i, len);
	
	// 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
	for (int i = len - 1; i > 0; --i)
	{
		std::swap(arr[0], arr[i]);	// 把第一个元素和当前的最后一个元素交换，保证当前的最后一个位置的元素都是在现在的这个序列之中最大的
		heap_adjust(arr, 0, i);		// 不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
	}
}



////////////////////////////////////////////////////////////////
// 归并排序，稳定，平均时间复杂度 O(nlgn)
////////////////////////////////////////////////////////////////

/*
* 归并：
*    将有两个有序数组
*		a[first ... mid],
*		a[mid ... last]
*	  合并
*/
void merge_two_array(int arr[], int first, int mid, int last, int temp[])
{
	int i = first, j = mid + 1;
	int k = 0;

	while (i <= mid && j <= last)	// 两边都有元素时，进行比较，将较小元素存入临时数组
	{
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	while (i <= mid)				// 剩下一个数组可能还存在多余元素，直接存入临时数组
		temp[k++] = arr[i++];

	while (j <= last)				// 同上
		temp[k++] = arr[j++];

	for (i = 0; i < k; i++)			// 将临时数组中的有序数赋给原数组
		arr[first + i] = temp[i];
}

void merge_sort(int arr[], int first, int last, int temp[])
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		merge_sort(arr, first, mid, temp);				//左边有序
		merge_sort(arr, mid + 1, last, temp);			//右边有序
		merge_two_array(arr, first, mid, last, temp);	//再将两个有序数列合并
	}
}

void merge_sort(int * arr, int len)
{
	int *p = new int[len];		// 在此处开辟临时数组，防止在算法中多次开辟和删除临时数组造成的开销（耗时）过大
	
	if (p != NULL)
		merge_sort(arr, 0, len - 1, p);

	delete[] p;
}

