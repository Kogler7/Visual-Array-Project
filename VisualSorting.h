#pragma once
#ifndef VISUAL_SORTING
#define VISUAL_SORTING
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<stdio.h>
struct ColorTheme { COLORREF Back, Fore, Focus, Mark; };

class VisualTime
{
public:
	VisualTime();
	void Start();//��ʼ ��ʱ
	int Get();//���� �����ʱ��ʼ��ʱ�䣨ʱ����
	int Reset();//��� ʱ�� ������ ��ʼ��ʱ
	void Getf();//Get+��׼�������ʱ XX ms��
	void Resetf();//Reset+��׼���
private:
	long t;
};

class VisualValue
{
public:
	bool isMarked = false;
	//ָ������λ�ã����ڲ����ã�
	void layout(int NO);
	//�������Ʋ��������ڲ����ã�
	void drawIn(COLORREF C);
	//��ͨ��������
	//���ƿ��ӻ���ֵ��
	void draw();
	//���
	void mark();
	//ȡ�����
	void unmark();
	//��ȡ Ԫ�صĶ�Ӧֵ��fast ָ���Ƿ������ӳ�ִ��
	int getVal(bool fast = false);//��ȡֵ
	//д�� Ԫ�صĶ�Ӧֵ��fast ָ���Ƿ������ӳ�ִ��
	void setVal(int Val, bool fast = false);//����ֵ
	void operator=(VisualValue& V);
private:
	int value_ = 0, NO_ = 0;
};

class VisualBox
{
public:
	//���������ٿ��ӻ�ɳ��
	void CreateBox(
		VisualValue* vArr,//��VisualValue����
		int arrNum = 128,//ָ�����󶨵�VisualValue���鳤��
		int width = 640,//���ڿ��
		int height = 480,//���ڸ߶�
		int maxVal = 128,//VisualValue����Ԫ�����ֵ
		bool hideC = true//�ڻ��ƴ����Ƿ�رտ���̨
	);
	void CloseBox();
	//���ÿ��ӻ�ɳ��

	//���Ĵ��ڴ�С
	void ReSize(int width, int height, int maxVal);
	//���°�VisualValue����
	void ReBind(VisualValue* vArr, int arrNum, int maxVal);
	//��������
	void SetTheme(ColorTheme CT);
	void SetBackColor(COLORREF C = WHITE);
	void SetForeColor(COLORREF C = BLACK);
	void SetFocusColor(COLORREF C = RED);
	void SetMarkColor(COLORREF C = YELLOW);
	//������������

	//�����ӳ٣����ڽ��������ٶ��Ա�۲죬��λ ����
	void SetInterval(int get = 5, int set = 10);
	//��ͬʱ���ڵ����۽�����Ĭ��Ϊ 4�������� 25
	void SetFocusNum(int n = 4);
	//����������������, m ָʾ��VisualValue�����п�ʼ�����λ��
	void VisArrMassInput(int Val[], int n, int m);
	//����������ʼ���������
	void VisArrMassRand();
	//������������
	void VisArrMassDraw();
private:
	bool ShowC_ = false;
};

class VisualBoxPro
{

};

//���ÿ��ӻ�������
void VisualBubbleSort(VisualValue VisArr[], int n);
void VisualSelectionSort(VisualValue VisArr[], int n);
void VisualInsertionSort(VisualValue VisArr[], int n);
void VisualHillSort(VisualValue VisArr[], int n);
void VisualMergeSort(VisualValue VisArr[], int n);
void VisualQuickSort(VisualValue VisArr[], int l, int r, bool fast = false);
void VisualRadixSort(VisualValue VisArr[], int n);
void VisualHeapSort(VisualValue VisArr[], int n);
void VisualCountingSort(VisualValue VisArr[], int n);
void VisualBucketSort(VisualValue VisArr[], int n);
#endif 
