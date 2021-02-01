#include"VisualArrayProject.h"
COLORREF _BACK, _FORE, _FOCUS, _MARK;
int _IntvalGet = 50, _IntvalSet = 100;
int _FlashCount = 0;
mutex _drawMutex;
void fillRecIn(COLORREF c, int l, int t, int r, int b) {
	_drawMutex.lock();
	COLORREF cc = getfillcolor();
	setfillcolor(c);
	fillrectangle(l, t, r, b);
	setfillcolor(cc);
	_drawMutex.unlock();
	_FlashCount++;
}
void fps() {
	while (true)
	{
		int c = _FlashCount = 0;
		Sleep(1000);
		//system("cls");
		std::cout << "FPS: " << _FlashCount - c << "\n";
	}
}
std::thread showfps(fps);
//VisualArray
void VisualArray::addFocus(VisualBox* pBox) {
	//printf("AddFocus: %p,%d\n", this, this->no_);
	this->pBox->Focus();
	bool isIn = false;//检查新焦点是否已存在于焦点队列中
	for (int i = 0; i < pBox->_FocusNum; ++i)
		if (no_ == pBox->_focusArr[i]->no_) {
			isIn = true;
			break;
		}
	if(! isIn) {//若新焦点不在原队列中，更新队列
		for (int i = pBox->_FocusNum; i > 0; i--) 
			pBox->_focusArr[i] = pBox->_focusArr[i - 1];
		pBox->_focusArr[pBox->_FocusNum]->drawIn(ColrRef::NORM);//踢出队列
		pBox->_focusArr[0] = this;
	}
	this->drawIn(ColrRef::FOCUS);
}
//VisualVal
void VisualVal::set(int Val) {
	Sleep(_IntvalSet);
	CS.aPndSz((Val - value_) * pBox->_pHeight, 0, ApCoord::AP_LB);
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
		pBox->CS.Cd.x + pBox->_pWidth * NO+1,
		pBox->CS.Cd.y+pBox->CS.Sz.h,
		0,
		pBox->_pWidth
	);
}
void VisualVal::drawIn(ColrRef ref) {
	if (value_ == _updVal && ref == _updColr) return;//没有绘制的必要
	//根据colrref确定要绘制的颜色，不影响marked的颜色
	COLORREF newColr_;
	switch (ref)
	{
	case ColrRef::NORM: 
		if (_isMarked) newColr_ = _MARK;
		else newColr_ = _FORE;
		break;
	case ColrRef::FOCUS: newColr_ = _FOCUS; break;
	case ColrRef::MARK: newColr_ = _MARK; break;
	default: return;
	}
	//根据需要灵活绘制
	if (_updVal <= value_) 
		fillRecIn(newColr_, CS.Lt.l, CS.Lt.t, CS.Lt.r, CS.Lt.b);
	else {
		fillRecIn(_BACK, CS.Lt.l, pBox->CS.Lt.t + 2, CS.Lt.r, CS.Lt.b - value_ * pBox->_pHeight);
		if (_updColr != ref)
			fillRecIn(newColr_, CS.Lt.l, CS.Lt.t, CS.Lt.r, CS.Lt.b);
	}
	//更新绘制状态，以便下次绘制检查
	_updVal = value_;
	_updColr = ref;
}
void VisualVal::mark() {
	_isMarked = true;
	drawIn(ColrRef::MARK);
}
void VisualVal::unmark() {
	_isMarked = false;
	drawIn(ColrRef::NORM);
}
void VisualVal::operator=(VisualVal& V) {
	set(V.get());
}
void VisualVal::operator=(int& val) {
	set(val);
};


//VisualGrid
void VisualGrid::set(int Val) {
	Sleep(_IntvalSet);
	value_ = Val;
	if (pBox->_gridMode == GridMode::BY_INT) {
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
	/*printf("GLayout: (%d) %d,%d,%d,%d\n", 
		no_, CS.Lt.l/64, CS.Lt.t/64, CS.Lt.r/64, CS.Lt.b/64);*/
}
void VisualGrid::drawIn(ColrRef ref) {
	if (value_ == _updVal && ref == _updColr) return;
	COLORREF newColr_;
	switch (ref)
	{
	case ColrRef::NORM:
		if (_isMarked) newColr_ = _MARK;
		else newColr_ = _FORE;
		break;
	case ColrRef::FOCUS: newColr_ = _FOCUS; break;
	case ColrRef::MARK: newColr_ = _MARK; break;
	default: return;
	}
	/*printf("GDrawIn: (%d) %d,%d,%d,%d,%c\n",
		no_, CS.Lt.l / 64, CS.Lt.t / 64, CS.Lt.r / 64, CS.Lt.b / 64,
		_visState ==VisState::MARKED ? 'M' : _visState ==VisState::FOCUSED ? 'F' : 'N');*/
	RECT r = { CS.Lt.l,CS.Lt.t,CS.Lt.r,CS.Lt.b };
	fillRecIn(newColr_, CS.Lt.l, CS.Lt.t, CS.Lt.r, CS.Lt.b);
	settextcolor(_BACK);
	LOGFONT f;
	gettextstyle(&f);	
	f.lfHeight = CS.Sz.h / 3 * 2;
	_tcscpy_s(f.lfFaceName, _T("微软雅黑"));		// 设置字体为“黑体”
	f.lfQuality = PROOF_QUALITY;		// 设置输出效果为抗锯齿  
	f.lfWeight = FW_BOLD;
	settextstyle(&f);	
	setbkmode(TRANSPARENT);
	//printf("DrawText: \"%s\"\n", visCh_);
	wchar_t ch_[4];
	for (int i = 0; i < 4; ++i) ch_[i] = visCh_[i];
	drawtext((LPCTSTR)ch_, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	_updVal = value_;
	_updColr = ref;
}
void VisualGrid::mark() {
	_isMarked = true;
	drawIn(ColrRef::MARK);
}
void VisualGrid::unmark() {
	_isMarked = false;
	drawIn(ColrRef::NORM);
}
void VisualGrid::operator=(VisualGrid& V) {
	set(V.get());
}
void VisualGrid::operator=(int& val) {
	set(val);
};