#include"VisualArrayProject.h"
COLORREF _BACK, _FORE, _FOCUS, _MARK;
int _IntvalGet = 5, _IntvalSet = 10;

//VisualArray
void VisualArray::addFocus(VisualBox* pBox) {
	printf("AddFocus: %p,%d\n", this, this->no_);
	this->pBox->Focus();
	bool flag = true;
	//检查所加焦点是否已存在于原队列中
	for (int i = 0; i < pBox->_FocusNum; ++i)
		if (no_ == pBox->_focusArr[i]->no_) flag = false;
	if (flag) {
		//更新队列并解除队列末端的焦点
		for (int i = pBox->_FocusNum; i > 0; i--) {
			pBox->_focusArr[i] = pBox->_focusArr[i - 1];
			pBox->_focusArr[i]->drawIn(RFOCUS);
		}
		pBox->_focusArr[pBox->_FocusNum]->draw();
		pBox->_focusArr[0] = this;
		this->drawIn(RFOCUS);
	}
	else {
		for (int i = 0; i < pBox->_FocusNum; i++) {
			pBox->_focusArr[i]->drawIn(RFOCUS);
		}
	}
}


//VisualVal
void VisualVal::set(int Val) {
	Sleep(_IntvalSet);
	CS.aPndSz((Val - value_) * pBox->_pHeight, 0, AP_LB);
	value_ = Val;
	addFocus(pBox);
}
int VisualVal::get() {
	Sleep(_IntvalGet);
	addFocus(pBox);
	return value_;
}
void VisualVal::layout(int NO) {
	no_ = NO;
	CS.setbyCS(
		pBox->CS.Cd.x + pBox->_pWidth * NO,
		pBox->CS.Cd.y+pBox->CS.Sz.h,
		0,
		pBox->_pWidth
	);
}
void VisualVal::drawIn(ColrRef C = RNORM) {
	if (value_ == _visVal && C == _visColr) return;
	COLORREF C_;
	switch (C)
	{
	case RNORM: C_ = _FORE; _visState = NORM;
		break;
	case RFOCUS: C_ = _FOCUS; _visState = FOCUSED;
		break;
	case RMARK: C_ = _MARK; _visState = MARKED;
		break;
	default:
		return;
	}
	clearrectangle(
		CS.Lt.l,
		pBox->CS.Lt.t,
		CS.Lt.r,
		CS.Lt.b
	);
	setfillcolor(C_);
	fillrectangle(
		CS.Lt.l,
		CS.Lt.t,
		CS.Lt.r,
		CS.Lt.b
	);
	_visVal = value_;
	_visColr = C;
}
void VisualVal::draw() {
	if (_visState == MARKED) drawIn(RMARK);
	else drawIn();
}
void VisualVal::mark() {
	drawIn(RMARK);
}
void VisualVal::unmark() {
	drawIn();
}
void VisualVal::operator=(VisualVal& V) {
	set(V.get());
}


//VisualGrid
void VisualGrid::set(int Val) {
	Sleep(_IntvalSet);
	value_ = Val;
	if (pBox->_gridMode == BY_INT) {
		int v[3] = { value_ / 100,value_ % 100 / 10,value_ % 10 }, a;
		for (int i = 0; i < 4; ++i) {
			a = '0';
			visCh_[i] = v[0] > 0 ? (a += v[0], v[0] = 0, a) 
				: v[1] > 0 ? (a += v[1], v[1] = 0, a) 
				: v[2] >= 0 ? (a += v[2], v[2] = -1, a) 
				: '\0';
		}
	}
	else *visCh_ = (char)value_;
	addFocus(pBox);
}
int VisualGrid::get() {
	Sleep(_IntvalGet);
	addFocus(pBox);
	return value_;
}
void VisualGrid::layout(int NO) {
	no_ = NO;
	int i, j;
	i = NO / pBox->_maxLen;
	if (pBox->_lines > 1) j = NO % pBox->_maxLen;
	else j = NO;
	CS.setbyCS(
		pBox->CS.Cd.x + pBox->_pWidth * j+1,
		pBox->CS.Cd.y + pBox->_pWidth * i+1,
		pBox->_pWidth-1,
		pBox->_pWidth-1
	);
	printf("GLayout: (%d) %d,%d,%d,%d\n", 
		no_, CS.Lt.l/64, CS.Lt.t/64, CS.Lt.r/64, CS.Lt.b/64);
}
void VisualGrid::drawIn(ColrRef C = RNORM) {
	if (value_ == _visVal && C == _visColr) return;
	COLORREF C_;
	switch (C)
	{
	case RNORM: C_ = _FORE; _visState = NORM;
		break;
	case RFOCUS: C_ = _FOCUS; _visState = FOCUSED;
		break;
	case RMARK: C_ = _MARK; _visState = MARKED;
		break;
	default:
		return;
	}
	printf("GDrawIn: (%d) %d,%d,%d,%d,%c\n",
		no_, CS.Lt.l / 64, CS.Lt.t / 64, CS.Lt.r / 64, CS.Lt.b / 64,
		_visState > 1 ? 'M' : _visState > 0 ? 'F' : 'N');
	RECT r = {
		CS.Lt.l,
		CS.Lt.t,
		CS.Lt.r,
		CS.Lt.b
	};
	clearrectangle(
		CS.Lt.l,
		CS.Lt.t,
		CS.Lt.r,
		CS.Lt.b
	);
	setfillcolor(C_);
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
	setbkmode(TRANSPARENT);
	printf("DrawText: \"%s\"\n", visCh_);
	wchar_t ch_[4];
	for (int i = 0; i < 4; ++i) ch_[i] = visCh_[i];
	drawtext((LPCTSTR)ch_, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	_visVal = value_;
	_visColr = C;
}
void VisualGrid::draw() {
	if (_visState == MARKED) drawIn(RMARK);
	else drawIn();
}
void VisualGrid::mark() {
	drawIn(RMARK);
}
void VisualGrid::unmark() {
	drawIn();
}
void VisualGrid::operator=(VisualGrid& V) {
	set(V.get());
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