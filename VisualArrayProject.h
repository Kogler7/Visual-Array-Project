/*
*version 21s01a belongs to VAP_1.4.0 snapshot
* 
*Developed by Kogler
*/
#pragma once
#ifndef VISUAL_ARRAY_PROJECT
#define VISUAL_ARRAY_PROJECT
#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<time.h>
#include<thread>
#include<mutex>
#define MaxFocusNum 32
//ColorTheme
#define DEFAULT_THEME ColorTheme{ WHITE,BLACK,RED,BLUE }
#define NEW_THEME ColorTheme{ BGR(0xF44336),0xFFFFFF,BGR(0xFFEB3B),BGR(0x03A9F4) }
#define CHINA_THEME ColorTheme{ WHITE,BLACK,RED,YELLOW }
using namespace std;
extern COLORREF _BACK, _FORE, _FOCUS, _MARK;
extern int _IntvalGet, _IntvalSet;
//enum classes
enum class ColrRef { RNULL, NORM, FOCUS, MARK };
enum class ApCoord { AP_LT, AP_LB, AP_RT, AP_RB };
enum class GridMode { BY_INT, BY_CHAR };
enum class Padding { 
	TOP_LEFT,			TOP_MID,				TOP_RIGHT,
	MID_LEFT,				CENTER,				MID_RIGHT, 
	BOTTOM_LEFT,		BOTTOM_MID,		BOTTOM_RIGHT
};
//struct declaration
struct ColorTheme { COLORREF Back, Fore, Focus, Mark; };
struct Coord { int x, y; }; struct Size { int h, w; }; struct Layout { int t, l, r, b; };
//class declaration
class CoordSize;
class TimeTeller;
class InforBar;
class VisualArray;
class VisualVal;
class VisualGrid;
class VisualBox;
class VisualPanel;
class VisualCanvas;
//����Ĭ�϶���
extern VisualCanvas Canvas;
extern VisualPanel _Panel;
extern VisualBox _Box[2];
extern InforBar Infor;
//�����ඨ��
class CoordSize {
public:
	Coord Cd = { 0,0 };//����ԭ��
	Size Sz = { 10,10 };//�ߴ�
	Layout Lt = { 0,0,10,10 };//����
	void setbyLt(int t, int l, int r, int b);
	void setbyCd(int x, int y);
	void setbySz(int h, int w, ApCoord Ap = ApCoord::AP_LT);
	void setbyCS(int x, int y, int h, int w);
	void aPndSz(int dh, int dw, ApCoord Ap = ApCoord::AP_LT);
};
class TimeTeller
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
class InforBar
{
	CoordSize _frame, _msgBar, _chkBar;
	bool enabled = false;
	void enable();
	void disable();
	void MsgAppend(char* head, void* body);
	void ChkAppend();
	void showInterval();
	void showFPS();
};
//Visual Array
class VisualArray
{
public:
	CoordSize CS;
	VisualBox* pBox = NULL;
	int no_ = 0, value_ = 0,
		maxVal_ = 127, minVal_ = 0;
	char visCh_[4] = { '\0' };
	bool _isMarked = false;
	//�ѻ���
	int _updVal = 0;
	ColrRef _updColr = ColrRef::RNULL;
	//ָ������λ�ã����ڲ����ã�
	virtual void layout(int NO) {};
	void addFocus(VisualBox* pBox);
	virtual void set(int Val) {};
	virtual int get() { return 0; };
	//����
	virtual void drawIn(ColrRef ref = ColrRef::NORM) {};
	//���
	virtual void mark() {};
	//ȡ�����
	virtual void unmark() {};
	virtual void operator=(VisualArray& vArr) {};
	virtual void operator=(int& val) {};//=����з���ֵ
	//���������
	bool operator >(VisualArray& op) { return get() > op.get(); }
	bool operator <(VisualArray& op) { return get() < op.get(); }
	bool operator >=(VisualArray& op) { return get() >= op.get(); }
	bool operator <=(VisualArray& op) { return get() <= op.get(); }
	bool operator ==(VisualArray& op) { return get() == op.get(); }
	bool operator !=(VisualArray& op) { return get() != op.get(); }
	bool operator >(const int& op) { return get() > op; }
	bool operator <(const int& op) { return get() < op; }
	bool operator >=(const int& op) { return get() >= op; }
	bool operator <=(const int& op) { return get() <= op; }
	bool operator ==(const int& op) { return get() == op; }
	bool operator !=(const int& op) { return get() != op; }
	int operator ++() { set(++value_); return value_; }
	int operator ++(int) { int temp = value_; set(++value_); return temp; }
	int operator --() { set(--value_); return value_; }
	int operator --(int) { int temp = value_; set(--value_); return temp; }
	void operator +=(VisualArray& op) { set(value_ + op.value_); }
	void operator +=(int& op) { set(value_ + op); }
	void operator -=(VisualArray& op) { set(value_ - op.value_); }
	void operator -=(int& op) { set(value_ - op); }
	void operator *=(VisualArray& op) { set(value_ * op.value_); }
	void operator *=(int& op) { set(value_ * op); }
	void operator /=(VisualArray& op) { set(value_ / op.value_); }
	void operator /=(int& op) { set(value_ / op); }
	int operator +(VisualArray& op) { return get() + op.value_; }
	int operator +(int& op) { return get() + op; }
	int operator -(VisualArray& op) { return get() - op.value_; }
	int operator -(int& op) { return get() + op; }
	int operator *(VisualArray& op) { return get() * op.value_; }
	int operator *(int& op) { return get() + op; }
	int operator /(VisualArray& op) { return get() / op.value_; }
	int operator /(int& op) { return get() + op; }
};

class VisualVal :public VisualArray
{
public:
	void set(int Val);
	int get();
	void layout(int NO);
	//����
	void drawIn(ColrRef ref = ColrRef::NORM);
	//���
	void mark();
	//ȡ�����
	void unmark();
	void operator=(VisualVal& V);
	void operator=(int& val);
};

class VisualGrid :public VisualArray
{
public:
	void set(int Val);
	int get();
	void layout(int NO);
	//����
	void drawIn(ColrRef ref = ColrRef::NORM);
	//���
	void mark();
	//ȡ�����
	void unmark();
	void operator=(VisualGrid& V);
	void operator=(int& val);
};

class VisualPanel 
{
private:
	bool ShowC_ = false;
public:
	CoordSize CS;
	VisualBox* kid[32] = { NULL };
	int _kidNum = 1;
	void Initialize(
		VisualBox vBox[],//��
		int boxNum = 128,//ָ�����󶨵�
		int width = 640,//���ڿ��
		int height = 480,//���ڸ߶�
		bool hideC = true//�ڻ��ƴ����Ƿ�رտ���̨
	);
	void Initialize(
		VisualBox &vBox,//��
		int width = 640,//���ڿ��
		int height = 480,//���ڸ߶�
		bool hideC = true//�ڻ��ƴ����Ƿ�رտ���̨
	);
	void ClosePanel();
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
	void SetMarkColor(COLORREF C = BLUE);
	//�����ӳ٣����ڽ��������ٶ��Ա�۲죬��λ ����
	void SetInterval(int get = 5, int set = 10);
	//��ͬʱ���ڵ����۽�����Ĭ��Ϊ 2�������� 25
	void SetFocusNum(int n = 2);
};

class VisualBox
{
private:
	VisualArray* kid = NULL;
	int _kidNum = 1;
public:
	VisualPanel* parent = NULL;
	VisualArray* _focusArr[MaxFocusNum+1] = { NULL };
	int _FocusNum = 2;
	GridMode _gridMode = GridMode::BY_CHAR;
	int _pWidth = 0, _pHeight = 0;//��С��λsize
	int _maxLen = 8, _lines = 1;
	CoordSize CS;
	int focusing = 0;
	void Focus();
	//���������ٿ��ӻ�ɳ��
	void Initialize(
		VisualVal visVal[],//��VisualVa����
		int arrNum = 128,//ָ�����󶨵�VisualArray���鳤��
		int maxVal = 128,//VisualValue����Ԫ�����ֵ
		int maxWidth = 640,//���ڿ��
		int maxHeight = 480//���ڸ߶�
	);
	void Initialize(
		VisualGrid visGrid[],//��VisualGrid����
		int arrNum = 32,//ָ�����󶨵�VisualArray���鳤��
		GridMode gridMode = GridMode::BY_CHAR,
		int gridSize = 48,//�ַ���߳�
		int maxLen = 8//ÿ�����������
	);
	void Initialize(
		VisualGrid **visMatrix,//�󶨾���
		int order,//�������
		GridMode gridMode = GridMode::BY_CHAR,
		int gridSize = 48//�ַ���߳�
	);
	void CloseBox();
	void LayOut(Padding pd);
	void Resize();
	void ReBind();
	void SetFocusNum(int num);
	//����������������, m ָʾ��VisualValue�����п�ʼ�����λ��
	void VisArrMassInput(int Val[], int n, int m);
	//����������ʼ���������
	void VisArrMassRand(int max, int min = 0, bool masDraw = false);
	//������������
	void VisArrMassDraw();
};

class VisualCanvas
{
public:
	VisualPanel* dftPanel;
	VisualPanel* Initialize();
};

/*���ÿ��ӻ�������*/
//���ӻ�ð������
void VisualBubbleSort(VisualVal VisArr[], int n);
/*���ӻ�ѡ������*/
void VisualSelectionSort(VisualVal VisArr[], int n);
//���ӻ���������
void VisualInsertionSort(VisualVal VisArr[], int n);
/*���ӻ�ϣ������*/
void VisualHillSort(VisualVal VisArr[], int n);
//
void VisualMergeSort(VisualVal VisArr[], int n);
/*���ӻ���������l��r�ֱ�Ϊ����������������ұ߽磩*/
void VisualQuickSort(VisualVal VisArr[], int l, int r);
//
void VisualRadixSort(VisualVal VisArr[], int n);
/**/
void VisualHeapSort(VisualVal VisArr[], int n);
//
void VisualCountingSort(VisualVal VisArr[], int n);
/*���ӻ�Ͱ����*/
void VisualBucketSort(VisualVal VisArr[], int n);

//����

//��ͣ�ȴ�
void Pause();
//ǿ���������
int Rndp(int max = 10, int min = 0);
#endif