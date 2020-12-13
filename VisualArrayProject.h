//version 20s02a belongs to VAP_1.3.0 snapshot
#pragma once
#ifndef VISUAL_ARRAY_PROJECT
#define VISUAL_ARRAY_PROJECT
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<stdio.h>
#include<thread>
#define MaxFocusNum 32
extern COLORREF _BACK, _FORE, _FOCUS, _MARK;
extern int _IntvalGet, _IntvalSet;
enum VisState { NORM, FOCUSED, MARKED };
enum ColrRef { RNULL, RNORM, RFOCUS, RMARK };
enum ApCoord { AP_LT, AP_LB, AP_RT, AP_RB };
enum GridMode { BY_INT, BY_CHAR };
enum Padding { 
	TOP_LEFT,			TOP_MID,				TOP_RIGHT,
	MID_LEFT,				PD_CENTER,			MID_RIGHT, 
	BOTTOM_LEFT,		BOTTOM_MID,		BOTTOM_RIGHT
};
//ColorTheme
#define DEFAULT_THEME ColorTheme{ WHITE,BLACK,RED,BLUE }
//#define DEFAULT_THEME ColorTheme{ 0xFFFFFF,0x212121,0xD32F2F,0xFFEB3B }
#define CHINA_THEME ColorTheme{ WHITE,BLACK,RED,YELLOW }

class VisualArray;
class VisualVal;
class VisualGrid;
class VisualBox;
class VisualPanel;

struct ColorTheme { COLORREF Back, Fore, Focus, Mark; };
struct Coord { int x, y; }; struct Size { int h, w; }; struct Layout { int t, l, r, b; };
class CoordSize {
public:
	Coord Cd = { 0,0 };//绘制原点
	Size Sz = { 10,10 };//尺寸
	Layout Lt = { 0,0,10,10 };//布局
	void setbyLt(int t, int l, int r, int b);
	void setbyCd(int x, int y);
	void setbySz(int h, int w, int Ap = AP_LT);
	void setbyCS(int x, int y, int h, int w);
	void aPndSz(int dh, int dw, int Ap = AP_LT);
};

class VisualTime
{
public:
	void Start();//开始 计时
	int Get();//返回 距离计时开始的时间（时长）
	int Reset();//获得 时长 并重新 开始计时
	void Getf();//Get+标准输出（用时 XX ms）
	void Resetf();//Reset+标准输出
	void Pause();
	void Continue();
	void TSleep(int ms);
private:
	long t = 0, _t = 0;
	bool awake = true;
};
//重载运算符
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
	int _visState = NORM;
	int no_ = 0, value_ = 0,
		maxVal_ = 127, minVal_ = 0;
	char visCh_[4] = { '\0' };
	//已绘制的值
	int _visVal = 0;
	ColrRef _visColr = RNULL;
	//指定排列位置（供内部调用）
	virtual void layout(int NO) {};
	void addFocus(VisualBox* pBox);
	virtual void set(int Val) {};
	virtual int get() { return 0; };
	//基本绘制（供内部调用）
	virtual void drawIn(ColrRef C) {};
	//绘制可视化数值条
	virtual void draw() {};
	//标记
	virtual void mark() {};
	//取消标记
	virtual void unmark() {};
	virtual void operator=(VisualArray& vArr) {};
};

class VisualVal :public VisualArray
{
public:
	void set(int Val);
	int get();
	void layout(int NO);
	//基本绘制（供内部调用）
	void drawIn(ColrRef C);
	//绘制可视化数值条
	void draw();
	//标记
	void mark();
	//取消标记
	void unmark();
	void operator=(VisualVal& V);
};

class VisualGrid :public VisualArray
{
public:
	void set(int Val);
	int get();
	void layout(int NO);
	//基本绘制（供内部调用）
	void drawIn(ColrRef C);
	//绘制可视化数值条
	void draw();
	//标记
	void mark();
	//取消标记
	void unmark();
	void operator=(VisualGrid& V);
};

class VisualPanel 
{
private:
	bool ShowC_ = false;
public:
	CoordSize CS;
	VisualBox* kid[32] = { NULL };
	int _kidNum = 1;
	void CreatePanel(
		VisualBox vBox[],//绑定
		int boxNum = 128,//指定所绑定的
		int width = 640,//窗口宽度
		int height = 480,//窗口高度
		bool hideC = true//在绘制窗口是否关闭控制台
	);
	void CreatePanel(
		VisualBox &vBox,//绑定
		int width = 640,//窗口宽度
		int height = 480,//窗口高度
		bool hideC = true//在绘制窗口是否关闭控制台
	);
	void ClosePanel();
	//更改窗口大小
	void ReSize(int width, int height);
	//重新绑定VisualValue数组
	void ReBind(VisualBox vBox[], int boxNum);
	void ReBind(VisualBox vBox);
	//主题设置
	void SetTheme(ColorTheme CT);
	void SetBackColor(COLORREF C = WHITE);
	void SetForeColor(COLORREF C = BLACK);
	void SetFocusColor(COLORREF C = RED);
	void SetMarkColor(COLORREF C = BLUE);
	//操作延迟，用于降低运行速度以便观察，单位 毫秒
	void SetInterval(int get = 5, int set = 10);
	//可同时存在的最大聚焦数，默认为 2，不超过 25
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
	bool _gridMode = BY_CHAR;
	int _pWidth = 0, _pHeight = 0;//最小单位size
	int _maxLen = 8, _lines = 1;
	CoordSize CS;
	int focusing = 0;
	void Focus();
	//创建与销毁可视化沙盒
	void CreateBox(
		VisualVal visVal[],//绑定VisualVa数组
		int arrNum = 128,//指定所绑定的VisualArray数组长度
		int maxVal = 128,//VisualValue数组元素最大值
		int width = 640,//窗口宽度
		int height = 480//窗口高度
	);
	void CreateBox(
		VisualGrid visGrid[],//绑定VisualGrid数组
		int arrNum = 32,//指定所绑定的VisualArray数组长度
		GridMode gridMode = BY_CHAR,
		int gridSize = 48,//字符格边长
		int maxLen = 8//每行最大容纳量
	);
	void CloseBox();
	void LayOut(Padding pd);
	void Resize();
	void ReBind();
	void SetFocusNum(int num);
	//快速批量导入数据, m 指示在VisualValue数组中开始导入的位置
	void VisArrMassInput(int Val[], int n, int m);
	//快速批量初始化（随机）
	void VisArrMassRand(int max, int min = 0);
	//快速批量绘制
	void VisArrMassDraw();
	void Infor();
};

class VisualMatrix
{

};

class FastDeveloper 
{
	VisualPanel P;
	VisualBox B;
	VisualVal I[128];
	VisualGrid C[64];
};

//内置可视化排序函数
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
//其他

//强化随机函数
int Rndp(int max = 10, int min = 0);
#endif