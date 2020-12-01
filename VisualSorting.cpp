#include"VisualSorting.h"
COLORREF BACK, FORE, FOCUS, MARK;
VisualValue* pVal;
int num_ = 128, pWidth_ = 5, tHeight_ = 480, maxValue_ = 128;
int IntvalGet = 5, IntvalSet = 10;
int focusArr[35] = { 0 }, enabledFusNum = 5;
bool skipIntval = 0;
//VisualTime
VisualTime::VisualTime() { t = 0; }
void VisualTime::Start() { t = clock(); }
int VisualTime::Get() { return clock() - t; }
int VisualTime::Reset() { int tt = clock() - t; t = clock(); return tt; }
void VisualTime::Getf() { printf("\n用时 %d ms\n", clock() - t); }
void VisualTime::Resetf() { printf("\n用时 %d ms\n", clock() - t); t = clock(); }

void AddFocus(int _NO) {
	bool flag = true;
	for (int i = 0; i < enabledFusNum; ++i) if (_NO == focusArr[i]) flag = false;
	if (flag) {
		for (int i = enabledFusNum; i > 0; i--) {
			focusArr[i] = focusArr[i - 1];
			pVal[focusArr[i]].drawIn(FOCUS);
		}
		focusArr[0] = _NO;
		pVal[focusArr[enabledFusNum]].draw();
		pVal[_NO].drawIn(FOCUS);
	}
	else {
		for (int i = 0; i < enabledFusNum; i++) {
			pVal[focusArr[i]].drawIn(FOCUS);
		}
	}
}
//VisualValue
void VisualValue::layout(int NO) {
	NO_ = NO;
}
void VisualValue::drawIn(COLORREF C = FORE) {
	clearrectangle(
		NO_ * pWidth_,
		0,
		(NO_ + 1) * pWidth_,
		tHeight_
	);
	setfillcolor(C);
	fillrectangle(
		NO_ * pWidth_,
		(int)(tHeight_ * (1 - (float)value_ / (float)maxValue_)),
		(NO_ + 1) * pWidth_,
		tHeight_
	);
}
void VisualValue::draw() {
	if (isMarked) drawIn(MARK);
	else drawIn();
}
void VisualValue::mark() {
	isMarked = true;
	drawIn(MARK);
}
void VisualValue::unmark() {
	isMarked = false;
	drawIn();
}
int VisualValue::getVal(bool _fast) {
	//if (!_fast || skipIntval) Sleep(IntvalGet);
	AddFocus(NO_);
	return value_;
}
void VisualValue::setVal(int Val, bool _fast) {
	//if (!_fast || skipIntval) Sleep(IntvalSet);
	value_ = Val;
	AddFocus(NO_);
}
void VisualValue::operator=(VisualValue &V) {
	setVal(V.getVal());
}
//VisualBox
void VisualBox::CreateBox(VisualValue* vArr, int arrNum, int width, int height, int maxVal, bool hideC) {
	ShowC_ = !hideC;
	maxValue_ = maxVal;
	num_ = arrNum;
	pWidth_ = width / arrNum;
	tHeight_ = height;
	ShowC_ = true;
	pVal = vArr;
	initgraph(width, height, ShowC_);
	SetBackColor();
	floodfill(1, 1, BACK);
	SetForeColor();
	SetFocusColor();
	SetMarkColor();
	for (int i = 0; i < num_; ++i) {
		vArr[i].layout(i);
	}
}
void VisualBox::ReSize(int width, int height, int maxVal) {
	pWidth_ = width / num_;
	tHeight_ = height;
	initgraph(width, height, ShowC_);
}
void VisualBox::ReBind(VisualValue* vArr, int arrNum, int maxVal) {
	num_ = arrNum;
	pVal = vArr;
	maxValue_ = maxVal;
}
void VisualBox::SetTheme(ColorTheme CT) {
	BACK = CT.Back;
	setbkcolor(BACK);
	FORE = CT.Fore;
	FOCUS = CT.Focus;
	MARK = CT.Mark;
}
void VisualBox::SetBackColor(COLORREF C) {BACK = C; setbkcolor(BACK); floodfill(1, 1, BACK);}
void VisualBox::SetForeColor(COLORREF C) {FORE = C;}
void VisualBox::SetFocusColor(COLORREF C) {FOCUS = C;}
void VisualBox::SetMarkColor(COLORREF C) {MARK = C;}
void VisualBox::SetInterval(int get, int set) { IntvalGet = get; IntvalSet = set; }
void VisualBox::SetFocusNum(int n) { 
	if (n) {
		enabledFusNum = n;
		for (int i = 0; i < n; ++i) focusArr[i] = 0;
	}
}
void VisualBox::CloseBox() {
	closegraph();
}
void VisualBox::VisArrMassInput(int Val[], int n, int m) {
	BeginBatchDraw();
	for (int i = 0; i < num_ && i < n; ++i) {
		pVal[i].setVal(Val[i], true);
	}
	EndBatchDraw();
}
void VisualBox::VisArrMassRand() {
	srand((unsigned)time(0));
	BeginBatchDraw();
	for (int i = 0; i < num_; ++i) {
		pVal[i].setVal((rand() % maxValue_), true);
	}
	EndBatchDraw();
}
void VisualBox::VisArrMassDraw() {
	BeginBatchDraw();
	for (int i = 0; i < num_; ++i) {
		pVal[i].draw();
	}
	EndBatchDraw();
}

//内置排序函数

void VisualBubbleSort(VisualValue VisArr[], int n) {

}
void VisualSelectionSort(VisualValue VisArr[], int n) {

}
void VisualInsertionSort(VisualValue VisArr[], int n) {

}
void VisualHillSort(VisualValue VisArr[], int n) {

}
void VisualMergeSort(VisualValue VisArr[], int n) {

}
void VisualQuickSort(VisualValue VisArr[], int l, int r, bool fast){
	skipIntval = fast;
	if (l < r)
	{
		int i = l, j = r, x = VisArr[l].getVal();
		while (i < j)
		{
			while (i < j && VisArr[j].getVal() >= x) j--;// 从右向左找第一个小于x的数
			if (i < j) VisArr[i++].setVal(VisArr[j].getVal());
			while (i < j && VisArr[i].getVal() < x) i++;// 从左向右找第一个大于等于x的数
			if (i < j) VisArr[j--].setVal(VisArr[i].getVal());
		}
		VisArr[i].setVal(x);
		VisualQuickSort(VisArr, l, i - 1, fast); // 递归调用 
		VisualQuickSort(VisArr, i + 1, r, fast);
	}
	if (fast) skipIntval = false;
}
void VisualRadixSort(VisualValue VisArr[], int n) {

}
void VisualHeapSort(VisualValue VisArr[], int n) {

}
void VisualCountingSort(VisualValue VisArr[], int n) {

}
void VisualBucketSort(VisualValue VisArr[], int n) {

}