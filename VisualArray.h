//version 20s01b belongs to VAP_1.3.0 snapshot

#pragma once
#ifndef VISUAL_SORTING
//defination
#define VISUAL_SORTING
#define byINT 0
#define byCHAR 1
//CoordSize
#define Ap_LT 0
#define Ap_LB 1
#define Ap_RT 2
#define Ap_RB 3
//ColorTheme
#define DEFAULT_THEME ColorTheme{ WHITE,BLACK,RED,YELLOW }
//#define DEFAULT_THEME ColorTheme{ 0xFFFFFF,0x212121,0xD32F2F,0xFFEB3B }
#define CHINA_THEME ColorTheme{ WHITE,BLACK,RED,YELLOW }


#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<stdio.h>

class VisualArray;
class VisualVal;
class VisualGrid;
class VisualBox;
class VisualPannel;

struct ColorTheme { COLORREF Back, Fore, Focus, Mark; };
struct Coord { int x, y; }; struct Size { int h, w; }; struct Layout { int t, l, r, b; };
class CoordSize {
public:
	Coord Cd = { 0,0 };//����ԭ��
	Size Sz = { 10,10 };//�ߴ�
	Layout Lt = { 0,0,10,10 };//����
	void setbyLt(int t, int l, int r, int b);
	void setbyCd(int x, int y);
	void setbySz(int h, int w, int Ap = Ap_LT);
	void setbyCS(int x, int y, int h, int w);
	void aPndSz(int dh, int dw, int Ap = Ap_LT);
};

class VisualTime
{
public:
	void Start();//��ʼ ��ʱ
	int Get();//���� �����ʱ��ʼ��ʱ�䣨ʱ����
	int Reset();//��� ʱ�� ������ ��ʼ��ʱ
	void Getf();//Get+��׼�������ʱ XX ms��
	void Resetf();//Reset+��׼���
	void Pause();
	void Continue();
	void TSleep(int ms);
private:
	long t = 0, _t = 0;
	bool awake = true;
};
//���������
//bool operator>(VisualArray& vArr1, VisualArray& vArr2);
//bool operator<(VisualArray& vArr1, VisualArray& vArr2);
//bool operator>=(VisualArray& vArr1, VisualArray& vArr2);
//bool operator<=(VisualArray& vArr1, VisualArray& vArr2);
//bool operator==(VisualArray& vArr1, VisualArray& vArr2);
//void operator+=(VisualArray& vArr1, VisualArray& vArr2);
//void operator-=(VisualArray& vArr1, VisualArray& vArr2);
//int operator+(VisualArray& vArr1, VisualArray& vArr2);
//int operator-(VisualArray& vArr1, VisualArray& vArr2);
//Visual Array
class VisualArray
{
public:
	CoordSize CS;
	VisualBox* pBox = NULL;
	bool marked_ = false;
	int no_ = 0, value_ = 0, maxVal_ = 127, minVal_ = 0;
	//ָ������λ�ã����ڲ����ã�
	virtual void layout(int NO) {};
	void addFocus(VisualBox* pBox);
	virtual void set(int Val) {};
	virtual int get() { return 0; };
	//�������ƣ����ڲ����ã�
	virtual void drawIn(COLORREF C) {};
	//���ƿ��ӻ���ֵ��
	virtual void draw() {};
	//���
	virtual void mark() {};
	//ȡ�����
	virtual void unmark() {};
	virtual void operator=(VisualArray& vArr) {};
};

class VisualVal :public VisualArray
{
public:
	void set(int Val);
	int get();
	void layout(int NO);
	//�������ƣ����ڲ����ã�
	void drawIn(COLORREF C);
	//���ƿ��ӻ���ֵ��
	void draw();
	//���
	void mark();
	//ȡ�����
	void unmark();
	void operator=(VisualVal& V);
};

class VisualGrid :public VisualArray
{
public:
	char visCh_[4];
	void set(int Val);
	int get();
	void layout(int NO);
	//�������ƣ����ڲ����ã�
	void drawIn(COLORREF C);
	//���ƿ��ӻ���ֵ��
	void draw();
	//���
	void mark();
	//ȡ�����
	void unmark();
	void operator=(VisualGrid& V);
};

class VisualPannel 
{
private:
	bool ShowC_ = false;
public:
	VisualBox* kid[32] = { NULL };
	int _kidNum = 1;
	CoordSize CS;
	void CreatePannel(
		VisualBox vBox[],//��
		int boxNum = 128,//ָ�����󶨵�
		int width = 640,//���ڿ��
		int height = 480,//���ڸ߶�
		bool hideC = true//�ڻ��ƴ����Ƿ�رտ���̨
	);
	void CreatePannel(
		VisualBox vBox,//��
		int width = 640,//���ڿ��
		int height = 480,//���ڸ߶�
		bool hideC = true//�ڻ��ƴ����Ƿ�رտ���̨
	);
	void ClosePannel();
	//���Ĵ��ڴ�С
	void ReSize(int width, int height);
	//���°�VisualValue����
	void ReBind(VisualBox vBox[], int boxNum);
	void ReBind(VisualBox vBox);
	//��������
	void SetTheme(ColorTheme CT);
	void SetBackColor(COLORREF C = WHITE);
	void SetForeColor(COLORREF C = BLACK);
	void SetFocusColor(COLORREF C = RED);
	void SetMarkColor(COLORREF C = YELLOW);
	//�����ӳ٣����ڽ��������ٶ��Ա�۲죬��λ ����
	void SetInterval(int get = 5, int set = 10);
	//��ͬʱ���ڵ����۽�����Ĭ��Ϊ 2�������� 25
	void SetFocusNum(int n = 2);
};

class VisualBox
{
private:
	VisualPannel* parent = NULL;
	VisualArray* kid = NULL;
	int _kidNum = 1;
public:
	VisualArray* _focusArr[65] = { NULL };
	int _FocusNum = 2;
	bool _gridMode = byINT;
	int _pWidth = 0, _pHeight = 0;//��С��λsize
	int _maxLen = 15, _lines = 1;
	CoordSize CS;
	//���������ٿ��ӻ�ɳ��
	void CreateBox(
		VisualVal visVal[],//��VisualVa����
		int arrNum = 128,//ָ�����󶨵�VisualArray���鳤��
		int maxVal = 128,//VisualValue����Ԫ�����ֵ
		int width = 640,//���ڿ��
		int height = 480//���ڸ߶�
	);
	void CreateBox(
		VisualGrid visGrid[],//��VisualGrid����
		int arrNum = 32,//ָ�����󶨵�VisualArray���鳤��
		int gridSize = 32,//�ַ���߳�
		int maxLen = 15//ÿ�����������
	);
	void CloseBox();
	void LayOut(int x, int y, bool mode);
	void Resize();
	void ReBind();
	void SetFocusNum(int num);
	//����������������, m ָʾ��VisualValue�����п�ʼ�����λ��
	void VisArrMassInput(int Val[], int n, int m);
	//����������ʼ���������
	void VisArrMassRand(int maxValue);
	//������������
	void VisArrMassDraw();
	void Infor();
};

class VisualMatrix
{

};

class FastDeveloper 
{
	VisualPannel P;
	VisualBox B;
	VisualVal I[128];
	VisualGrid C[64];
};

//���ÿ��ӻ�������
void VisualBubbleSort(VisualVal VisArr[], int n);
void VisualSelectionSort(VisualVal VisArr[], int n);
void VisualInsertionSort(VisualVal VisArr[], int n);
void VisualHillSort(VisualVal VisArr[], int n);
void VisualMergeSort(VisualVal VisArr[], int n);
void VisualQuickSort(VisualVal VisArr[], int l, int r);
void VisualRadixSort(VisualVal VisArr[], int n);
void VisualHeapSort(VisualVal VisArr[], int n);
void VisualCountingSort(VisualVal VisArr[], int n);
void VisualBucketSort(VisualVal VisArr[], int n);
#endif