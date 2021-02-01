//内置排序函数
#include"VisualArrayProject.h"
void VisualBubbleSort(VisualVal VisArr[], int n) {
	for (int i = 0; i < n; ++i) {
		int m = 0;
		for (int j = 0; j < n - i - 1; ++j) {
			int a = VisArr[j].get(), b = VisArr[j + 1].get();
			if (a > b) {
				VisArr[j] = b;
				VisArr[j + 1] = a;
				++m;
			}
		}
		if (!m) break;
	}
}
void VisualSelectionSort(VisualVal VisArr[], int n) {
	for (int i = 0; i < n - 1; ++i) {
		VisArr[i].mark();
		int min = i;
		for (int j = i + 1; j < n; ++j)
			if (VisArr[min] > VisArr[j]) 
				min = j;
		int temp = VisArr[i].get();
		VisArr[i] = VisArr[min];
		VisArr[min] = temp;
		VisArr[i].unmark();
	}
}
void VisualInsertionSort(VisualVal VisArr[], int n) {
	
}
void VisualHillSort(VisualVal VisArr[], int n) {

}
void VisualMergeSort(VisualVal VisArr[], int n) {

}
void VisualQuickSort(VisualVal VisArr[], int l, int r) {
	if (l < r)
	{
		int i = l, j = r, x = VisArr[l].get();
		while (i < j)
		{
			while (i < j && VisArr[j] >= x) --j;// 从右向左找第一个小于x的数
			if (i < j) VisArr[i++] = VisArr[j];
			while (i < j && VisArr[i] < x) ++i;// 从左向右找第一个大于等于x的数
			if (i < j) VisArr[j--] = VisArr[i];
		}
		VisArr[i] = x;
		VisualQuickSort(VisArr, l, i - 1); // 递归调用 
		VisualQuickSort(VisArr, i + 1, r);
	}
}
void VisualRadixSort(VisualVal VisArr[], int n) {

}
void VisualHeapSort(VisualVal VisArr[], int n) {

}
void VisualCountingSort(VisualVal VisArr[], int n) {

}
void VisualBucketSort(VisualVal VisArr[], int n) {

}