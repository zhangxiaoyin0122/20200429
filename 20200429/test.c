#include <stdio.h>
#include <stdlib.h>
void Swap(int* array, int l, int r) {
	int tmp = array[l];
	array[l] = array[r];
	array[r] = tmp;
}
//hora法获取基准值
int partion(int* array, int begin, int end) {
	int key = array[begin];//基准值
	int start = begin;
	while (begin < end) {
		while (begin < end && array[end] >= key)
			end--;
		while (begin < end && array[begin] <= key)
			begin++;
		Swap(array, begin, end);
	}
	Swap(array, start, begin);
	return begin;
}
//挖坑法
int partion1(int* array, int begin, int end) {
	int key = array[begin];
	while (begin < end) {
		while (begin < end && array[end] >= key) {
			end--;
		}
		//填坑
		array[begin] = array[end];
		while (begin < end && array[begin] <= key) {
			begin++;
		}
		//填坑
		array[end] = array[begin];
	}
	//填基准值的坑
	array[begin] = key;
	return begin;
}
//双指针(索引)法获取基准值
int partion2(int* array, int begin, int end) {
	int prev = begin;
	int cur = prev + 1;
	int key = array[begin];
	while (cur <= end) {
		/*if (array[cur] < key && ++prev != cur ) {//先自增再判断
			Swap(array, prev , cur);
		}
		cur++;*/
		if (array[cur] < key && prev + 1 != cur) {
			Swap(array, prev + 1, cur);
			cur++;
			prev++;
		}
		else if (array[cur] < key && prev + 1 == cur) {
			prev++;
			cur++;
		}
		else
			cur++;
	}
	Swap(array, begin, prev);
	return prev;
}
void quickSort(int* array, int begin, int end) {
	if (begin >= end)
		return;
	int keyPos = partion2(array, begin, end);
	quickSort(array, begin, keyPos-1);
	quickSort(array, keyPos + 1, end);
}
//向下调整算法   前提:子树已经是堆
void shiftDown(int* array, int n, int parent) {
	int child = parent * 2 + 1;
	while (child < n) {
		if (child + 1 < n && array[child + 1] > array[child])
			child++;
		if (array[parent] < array[child]) {
			Swap(array, parent, child);
			parent = child;//更新父节点
			child = parent * 2 + 1; //更新子节点
		}
		else
			break;//建大堆,当 array[child] < array[parent]时,停止调整
	}

}
void shiftup(int* array, int n, int child) {
	int parent = (child - 1) / 2;
	while (child > 0) {
		if (array[child] > array[parent]) {
			Swap(array, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break; //建大堆,当array[child] < array[parent]时,停止向上调整
	}
}
//堆排序
void heapSort(int* array, int n) {
	//向下调整建堆
	for (int i = (n - 2) / 2; i >= 0; i--) {
		shiftDown(array, n, i);
	}
	while (n) {
		Swap(array, 0, n - 1);
		n--;
		shiftDown(array, n, 0);
	}
}
//向后冒泡
void bubbleSort(int* array, int n) {
	while (n) {
		int flag = 1;
		for (int i = 0; i < n - 1; i++) {
			if (array[i] > array[i + 1]) {
				Swap(array, i, i + 1);
				flag = 0;
			}
		}
		if (flag)
			break;
		n--;
	}
}
//向前冒泡
void bubbleSort1(int* array, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j > i;j--) {
			if (array[j] < array[j - 1])
				Swap(array, j, j - 1);
		}
	}
}
//直接插入排序 
void insertSort(int* array, int n) {	
		for (int i = 0; i < n - 1; i++) {
			int end = i;
			int key = array[end + 1];
			while (end >= 0 && array[end] > key) {
				array[end + 1] = array[end];
				end--;
			}
			array[end + 1] = key;
		}
}
//希尔排序
void shellSort(int* array, int n) {
	int gap = n;
	while (gap) {
		gap = gap / 2;
		for (int i = 0; i < n - gap; i++) {
			int end = i;
			int key = array[end + gap];
			while (end >= 0 && array[end] > key) {
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = key;
		}
	}
}
//选择排序
void selectSort(int* array, int n) {
	for (int j = 0; j < n; j++) {
		int min = j;
		int start = min;
		for (int i = 1+j; i < n; i++) {
			if (array[i] < array[min])
				min = i;
		}
		Swap(array, min, start);
	}
}
void selectSort1(int* array, int n) {
	int begin = 0;
	int end = n - 1;
	while (begin < end) {
		int min = begin;
		int max = begin;
		for (int i = begin+1; i <= end; i++) {
			if (array[i] < array[min])
				min = i;
			if (array[i] >= array[max])
				max = i;
		}
		Swap(array, begin, min);
		if (max == begin)
			max = min;
		Swap(array, end, max);
		begin++;
		end--;
	}
}
int main() {
	int array[] = { 10,9,6,7,6,5,7,3,2,8 };
	int size = sizeof(array) / sizeof(array[0]);
	//快排
	//quickSort(array, 0, size - 1);
	//堆排序
	//heapSort(array, size);
	//直接插入排序
	//insertSort(array, size);
	//冒泡排序
	//bubbleSort1(array, size);
	//希尔排序
	//shellSort(array, size);
	//直接选择排序
	selectSort1(array, size);
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}