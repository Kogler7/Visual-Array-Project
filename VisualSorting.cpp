//����������
#include"VisualArrayProject.h"
void VisualBubbleSort(VisualVal VisArr[], int n) {

}
void VisualSelectionSort(VisualVal VisArr[], int n) {

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
			while (i < j && VisArr[j].get() >= x) j--;// ���������ҵ�һ��С��x����
			if (i < j) VisArr[i++].set(VisArr[j].get());
			while (i < j && VisArr[i].get() < x) i++;// ���������ҵ�һ�����ڵ���x����
			if (i < j) VisArr[j--].set(VisArr[i].get());
		}
		VisArr[i].set(x);
		VisualQuickSort(VisArr, l, i - 1); // �ݹ���� 
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