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
	void Start();//开始 计时
	int Get();//返回 距离计时开始的时间（时长）
	int Reset();//获得 时长 并重新 开始计时
	void Getf();//Get+标准输出（用时 XX ms）
	void Resetf();//Reset+标准输出
private:
	long t;
};

class VisualValue
{
public:
	bool isMarked = false;
	//指定排列位置（供内部调用）
	void layout(int NO);
	//基本绘制操作（供内部调用）
	void drawIn(COLORREF C);
	//普通操作函数
	//绘制可视化数值条
	void draw();
	//标记
	void mark();
	//取消标记
	void unmark();
	//读取 元素的对应值，fast 指定是否跳过延迟执行
	int getVal(bool fast = false);//获取值
	//写入 元素的对应值，fast 指定是否跳过延迟执行
	void setVal(int Val, bool fast = false);//设置值
	void operator=(VisualValue& V);
private:
	int value_ = 0, NO_ = 0;
};

class VisualBox
{
public:
	//创建与销毁可视化沙盒
	void CreateBox(
		VisualValue* vArr,//绑定VisualValue数组
		int arrNum = 128,//指定所绑定的VisualValue数组长度
		int width = 640,//窗口宽度
		int height = 480,//窗口高度
		int maxVal = 128,//VisualValue数组元素最大值
		bool hideC = true//在绘制窗口是否关闭控制台
	);
	void CloseBox();
	//设置可视化沙盒

	//更改窗口大小
	void ReSize(int width, int height, int maxVal);
	//重新绑定VisualValue数组
	void ReBind(VisualValue* vArr, int arrNum, int maxVal);
	//主题设置
	void SetTheme(ColorTheme CT);
	void SetBackColor(COLORREF C = WHITE);
	void SetForeColor(COLORREF C = BLACK);
	void SetFocusColor(COLORREF C = RED);
	void SetMarkColor(COLORREF C = YELLOW);
	//操作常数设置

	//操作延迟，用于降低运行速度以便观察，单位 毫秒
	void SetInterval(int get = 5, int set = 10);
	//可同时存在的最大聚焦数，默认为 4，不超过 25
	void SetFocusNum(int n = 4);
	//快速批量导入数据, m 指示在VisualValue数组中开始导入的位置
	void VisArrMassInput(int Val[], int n, int m);
	//快速批量初始化（随机）
	void VisArrMassRand();
	//快速批量绘制
	void VisArrMassDraw();
private:
	bool ShowC_ = false;
};

class VisualBoxPro
{

};

//内置可视化排序函数
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
