#include"VisualArray.h"
COLORREF _BACK = WHITE, _FORE = BLACK, _FOCUS = RED, _MARK = YELLOW;
int _IntvalGet = 5, _IntvalSet = 10;
//CoordSize
void CoordSize::setbyLt(int t, int l, int r, int b) {
	Cd = Coord{ l,t };
	Sz = Size{ b - t,r - l };
	Lt = Layout{ t,l,r,b };
}
void CoordSize::setbyCd(int x, int y) {
	Cd = Coord{ x,y };
	Lt.l = x;
	Lt.t = y;
}
void CoordSize::setbySz(int h, int w, int Ap) {
	switch (Ap) {
	case 0:
		Lt.r = Lt.l + w;
		Lt.b = Lt.t + h;
		break;
	case 1:
		Cd.y -= h - Sz.h;
		Lt.t = Cd.y;
		Lt.r = Lt.l + w;
		break;
	case 2:
		Cd.x -= w - Sz.w;
		Lt.l = Cd.x;
		Lt.b = Lt.t + h;
		break;
	case 3:
		Cd.x -= w - Sz.w;
		Cd.y -= h - Sz.h;
		Lt.l = Cd.x;
		Lt.t = Cd.y;
	}
	Sz = Size{ h,w };
}
void CoordSize::setbyCS(int x, int y, int h, int w) {
	Cd = Coord{ x,y };
	Sz = Size{ h,w };
	Lt = Layout{ y,x,x + w,y + h };
}
void CoordSize::aPndSz(int dh, int dw, int Ap) {
	switch (Ap) {
	case 0:
		Lt.r += dw;
		Lt.b += dh;
		break;
	case 1:
		Cd.y -= dh;
		Lt.t = Cd.y;
		Lt.r += dw;
		break;
	case 2:
		Cd.x -= dw;
		Lt.l = Cd.x;
		Lt.b += dh;
		break;
	case 3:
		Cd.x -= dw;
		Cd.y -= dh;
		Lt.l = Cd.x;
		Lt.t = Cd.y;
	}
	Sz.h += dh;
	Sz.w += dw;
}
//VisualTime
void VisualTime::Start() { t = clock(); }
int VisualTime::Get() { return clock() - t; }
int VisualTime::Reset() { int tt = clock() - t; t = clock(); return tt; }
void VisualTime::Getf() { printf("\n用时 %d ms\n", clock() - t); }
void VisualTime::Resetf() { printf("\n用时 %d ms\n", clock() - t); t = clock(); }
void VisualTime::Pause() { _t = clock(); awake = false; }
void VisualTime::Continue() { if (!awake) { t -= _t; awake = true; } }
void VisualTime::TSleep(int ms) {
	this->Pause();
	Sleep(ms);
	this->Continue();
}

//重载运算符
//bool operator>(VisualArray& vArr1, VisualArray& vArr2) {
//	return vArr1.get() > vArr2.get() ? true : false;
//}
//bool operator<(VisualArray& vArr1, VisualArray& vArr2) {
//	return vArr1.get() < vArr2.get() ? true : false;
//}
//bool operator>=(VisualArray& vArr1, VisualArray& vArr2) {
//	return vArr1.get() >= vArr2.get() ? true : false;
//}
//bool operator<=(VisualArray& vArr1, VisualArray& vArr2) {
//	return vArr1.get() <= vArr2.get() ? true : false;
//}
//bool operator==(VisualArray& vArr1, VisualArray& vArr2) {
//	return vArr1.get() == vArr2.get() ? true : false;
//}
//void operator+=(VisualArray& vArr1, VisualArray& vArr2) {
//	vArr1.set(vArr1.get() + vArr2.get());
//}
//void operator-=(VisualArray& vArr1, VisualArray& vArr2) {
//	vArr1.set(vArr1.get() - vArr2.get());
//}
//int operator+(VisualArray& vArr1, VisualArray& vArr2) {
//	return vArr1.get() + vArr2.get();
//}
//int operator-(VisualArray& vArr1, VisualArray& vArr2) {
//	return vArr1.get() - vArr2.get();
//}

//VisualArray
void VisualArray::addFocus(VisualBox* pBox) {
	bool flag = true;
	for (int i = 0; i < pBox->_FocusNum; ++i) if (no_ == pBox->_focusArr[i]->no_) flag = false;
	if (flag) {
		for (int i = pBox->_FocusNum; i > 0; i--) {
			pBox->_focusArr[i] = pBox->_focusArr[i - 1];
			pBox->_focusArr[i]->drawIn(_FOCUS);
		}
		pBox->_focusArr[0] = this;
		pBox->_focusArr[pBox->_FocusNum]->draw();
		this->drawIn(_FOCUS);
	}
	else {
		for (int i = 0; i < pBox->_FocusNum; i++) {
			pBox->_focusArr[i]->drawIn(_FOCUS);
		}
	}
}


//VisualVal
void VisualVal::set(int Val) {
	CS.aPndSz((Val - value_) * pBox->_pHeight, 0, Ap_LB);
	value_ = Val;
	addFocus(pBox);
}
int VisualVal::get() {
	addFocus(pBox);
	return value_;
}
void VisualVal::layout(int NO) {
	CS.setbyCS(
		pBox->CS.Cd.x + pBox->_pWidth * NO,
		pBox->CS.Cd.y+pBox->CS.Sz.h,
		0,
		pBox->_pWidth
	);
	no_ = NO;
}
void VisualVal::drawIn(COLORREF C = _FORE) {
	clearrectangle(
		CS.Lt.l,
		pBox->CS.Lt.t,
		CS.Lt.r,
		CS.Lt.b
	);
	setfillcolor(C);
	fillrectangle(
		CS.Lt.l,
		CS.Lt.t,
		CS.Lt.r,
		CS.Lt.b
	);
}
void VisualVal::draw() {
	if (marked_) drawIn(_MARK);
	else drawIn();
}
void VisualVal::mark() {
	marked_ = true;
	drawIn(_MARK);
}
void VisualVal::unmark() {
	marked_ = false;
	drawIn();
}
void VisualVal::operator=(VisualVal& V) {
	set(V.get());
}


//VisualGrid
void VisualGrid::set(int Val) {
	value_ = Val;
	if (pBox->_gridMode == byINT) {
		int v[3] = { value_ / 100,value_ % 100 / 10,value_ % 10 }, a = -48;
		for (int i = 0; i < 4; ++i)
			visCh_[i] = v[0] > 0 ? (a += v[0], v[0] = 0, a) : v[1] > 0 ? (a += v[1], v[1] = 0, a) : v[2] > 0 ? (a += v[2], v[2] = 0, a) : '\0';
	}
	else {
		visCh_[0] = (char)value_;
		visCh_[1] = '\0';
	}
	addFocus(pBox);
}
int VisualGrid::get() {
	addFocus(pBox);
	return value_;
}
void VisualGrid::layout(int NO) {
	int i, j;
	i = NO / pBox->_lines;
	if (pBox->_lines > 1) j = NO % pBox->_maxLen;
	else j = NO;
	CS.setbyCS(
		pBox->CS.Cd.x + pBox->_pWidth * j,
		pBox->CS.Cd.y + pBox->_pWidth * i,
		pBox->_pWidth,
		pBox->_pWidth
	);
}
void VisualGrid::drawIn(COLORREF C = _FORE) {
	RECT r = {
		CS.Lt.l,
		CS.Lt.t,
		CS.Lt.r,
		CS.Lt.b
	};
	setfillcolor(C);
	fillrectangle(
		CS.Lt.l,
		CS.Lt.t,
		CS.Lt.r,
		CS.Lt.b
	);
	settextcolor(_BACK);
	LOGFONT f;
	gettextstyle(&f);	
	f.lfHeight = CS.Sz.h / 3 * 2;
	_tcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);	
	drawtext(LPCTSTR(visCh_), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void VisualGrid::draw() {
	if (marked_) drawIn(_MARK);
	else drawIn();
}
void VisualGrid::mark() {
	marked_ = true;
	drawIn(_MARK);
}
void VisualGrid::unmark() {
	marked_ = false;
	drawIn();
}
void VisualGrid::operator=(VisualGrid& V) {
	set(V.get());
}

//VisualPannel
void VisualPannel::CreatePannel(
	VisualBox vBox[],//绑定
	int boxNum,//box数量，默认2个，最多32个
	int width,//窗口宽度
	int height,//窗口高度
	bool hideC//在绘制窗口时是否关闭控制台
) {
	ShowC_ = !hideC;
	CS.setbySz(height, width);
	initgraph(width, height, ShowC_);
	SetTheme(DEFAULT_THEME);
	for (int i = 0; i<32 && i < boxNum; _kidNum=++i) kid[i] = &vBox[i];
}
void VisualPannel::CreatePannel(
	VisualBox vBox,//绑定
	int width,//窗口宽度
	int height,//窗口高度
	bool hideC//在绘制窗口是否关闭控制台
) {
	ShowC_ = !hideC;
	CS.setbySz(height, width);
	initgraph(width, height, ShowC_);
	SetTheme(DEFAULT_THEME);
	kid[0] = &vBox;
	_kidNum = 1;
}
void VisualPannel::ClosePannel() {
	closegraph();
}
//更改窗口大小
void VisualPannel::ReSize(int width, int height) {
	CS.setbySz(height, width);
	initgraph(width, height, ShowC_);
}
//重新绑定VisualBox
void VisualPannel::ReBind(VisualBox vBox[], int boxNum) {
	for (int i = 0; i < 32 && i < boxNum; _kidNum = ++i) kid[i] = &vBox[i];
}
void VisualPannel::ReBind(VisualBox vBox) {
	kid[0] = &vBox;
	_kidNum = 1;
}
//主题设置
void VisualPannel::SetTheme(ColorTheme CT) {
	_BACK = CT.Back;
	setbkcolor(_BACK);
	floodfill(1, 1, _BACK);
	_FORE = CT.Fore;
	_FOCUS = CT.Focus;
	_MARK = CT.Mark;
}
void VisualPannel::SetBackColor(COLORREF C) { _BACK = C; setbkcolor(_BACK); floodfill(1, 1, _BACK); }
void VisualPannel::SetForeColor(COLORREF C) { _FORE = C; }
void VisualPannel::SetFocusColor(COLORREF C) { _FOCUS = C; }
void VisualPannel::SetMarkColor(COLORREF C) { _MARK = C; }
void VisualPannel::SetInterval(int get, int set) { _IntvalGet = get; _IntvalSet = set; }
void VisualPannel::SetFocusNum(int n) {
	if (n) {
		for (int i = 0; i < _kidNum; ++i) {
			kid[i]->_FocusNum = n;
			for (int j = 0; i < n; ++i) kid[i]->_focusArr[j] = NULL;
		}
	}
}


//VisualBox
void VisualBox::CreateBox(
	VisualVal visVal[],//绑定VisualVa数组
	int arrNum,//指定所绑定的VisualArray数组长度
	int maxVal,//VisualValue数组元素最大值
	int width,//窗口宽度
	int height//窗口高度
) {
	this->CS.setbySz(height, width);
	kid =visVal;
	_kidNum = arrNum;
	_pWidth = width / arrNum;
	_pHeight = height / maxVal;
	for (int i = 0; i < _kidNum; ++i) kid[i].pBox = this;//初步绑定
	for (int i = 0; i < _FocusNum; ++i) _focusArr[i] = &kid[0];
}
void VisualBox::CreateBox(
	VisualGrid visGrid[],//绑定VisualGrid数组
	int arrNum,//指定所绑定的VisualArray数组长度
	int gridSize,//字符格边长
	int maxLen//每行最大容纳量
) {
	_lines = arrNum / maxLen + bool(arrNum % maxLen);
	_maxLen = maxLen;
	this->CS.setbySz(
		_lines * gridSize,
		gridSize * maxLen
	);
	kid = visGrid;
	_kidNum = arrNum;
	_pWidth = _pHeight = gridSize;
	for (int i = 0; i < _kidNum; ++i) kid[i].pBox = this;//初步绑定
	for (int i = 0; i < _FocusNum; ++i) _focusArr[i] = &kid[0];
}
void VisualBox::LayOut(int x, int y, bool mode) {
	for (int i = 0; i < _kidNum; ++i) kid[i].layout(i);
}
void VisualBox::CloseBox() {
	closegraph();
}
void VisualBox::SetFocusNum(int num) {
	if (num >= 65) num = 64;
	_FocusNum = num;
	for (int i = 0; i < _FocusNum; ++i) _focusArr[i] = &kid[0];
}
void VisualBox::VisArrMassInput(int Val[], int n, int m) {
	BeginBatchDraw();
	for (int i = 0; i < _kidNum && i < n; ++i) {
		kid[i].set(Val[i]);
	}
	EndBatchDraw();
}
void VisualBox::VisArrMassRand(int maxValue) {
	srand((unsigned int)time(0));
	BeginBatchDraw();
	for (int i = 0; i < _kidNum; ++i) {
		kid[i].set((rand() % maxValue));
	}
	EndBatchDraw();
}
void VisualBox::VisArrMassDraw() {
	BeginBatchDraw();
	for (int i = 0; i < _kidNum; ++i) {
		kid[i].draw();
	}
	EndBatchDraw();
}

//FastDeveloper


//内置排序函数

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
void VisualQuickSort(VisualVal VisArr[], int l, int r){
	if (l < r)
	{
		int i = l, j = r, x = VisArr[l].get();
		while (i < j)
		{
			while (i < j && VisArr[j].get() >= x) j--;// 从右向左找第一个小于x的数
			if (i < j) VisArr[i++].set(VisArr[j].get());
			while (i < j && VisArr[i].get() < x) i++;// 从左向右找第一个大于等于x的数
			if (i < j) VisArr[j--].set(VisArr[i].get());
		}
		VisArr[i].set(x);
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