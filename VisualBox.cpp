#include"VisualArrayProject.h"
//VisualBox
void drawframe(VisualBox* b, COLORREF lc) {
	LINESTYLE LS;
	getlinestyle(&LS);
	LS.thickness = 2;
	setlinestyle(&LS);
	COLORREF c = getlinecolor();
	CoordSize CS = b->CS;
	setlinecolor(lc);
	rectangle(CS.Lt.l, CS.Lt.t, CS.Lt.r + 2, CS.Lt.b + 2);
	setlinecolor(c);
	LS.thickness = 1;
	setlinestyle(&LS);
}
void unfocus(VisualBox* b) {
	Sleep(_IntvalGet >= _IntvalSet ? 2 * _IntvalGet : 2 * _IntvalSet + 10);
	b->focusing--;
	if (!b->focusing) drawframe(b, _FORE);
}
void VisualBox::Focus() {
	if (!focusing) drawframe(this, _FOCUS);
	focusing++;
	std::thread thd(unfocus, this);
	thd.detach();
}
void VisualBox::CreateBox(
	VisualVal visVal[],//绑定VisualVa数组
	int arrNum,//指定所绑定的VisualArray数组长度
	int maxVal,//VisualValue数组元素最大值
	int width,//窗口宽度
	int height//窗口高度
) {
	this->CS.setbySz(height, width);
	kid = visVal;
	_kidNum = arrNum;
	_pWidth = width / arrNum;
	_pHeight = height / maxVal;
	for (int i = 0; i < _kidNum; ++i) kid[i].pBox = this;//初步绑定
	for (int i = 0; i < _FocusNum; ++i) _focusArr[i] = &kid[0];
}
void VisualBox::CreateBox(
	VisualGrid visGrid[],//绑定VisualGrid数组
	int arrNum,//指定所绑定的VisualArray数组长度
	GridMode gridMode,
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
	_gridMode = gridMode;
	for (int i = 0; i < _kidNum; ++i) kid[i].pBox = this;
	for (int i = 0; i < _FocusNum; ++i) _focusArr[i] = &kid[0];
}
void VisualBox::LayOut(Padding pd) {
	CoordSize C = parent->CS;
	switch (pd)
	{
	case TOP_LEFT:
		break;
	case TOP_MID:
		break;
	case TOP_RIGHT:
		break;
	case MID_LEFT:
		break;
	case PD_CENTER:
		CS.setbyCd(
			C.Sz.w / 2 - CS.Sz.w / 2,
			C.Sz.h / 2 - CS.Sz.h / 2
		);
		break;
	case MID_RIGHT:
		break;
	case BOTTOM_LEFT:
		break;
	case BOTTOM_MID:
		break;
	case BOTTOM_RIGHT:
		break;
	default:
		break;
	}
	//根据box位置初始化array位置
	for (int i = 0; i < _kidNum; ++i) kid[i].layout(i);
}
void VisualBox::CloseBox() {
	closegraph();
}
void VisualBox::SetFocusNum(int num) {
	if (num > MaxFocusNum || num > _kidNum)
		num = MaxFocusNum < _kidNum ? MaxFocusNum : _kidNum;
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
void VisualBox::VisArrMassRand(int max, int min) {
	srand((unsigned int)time(0));
	//BeginBatchDraw();
	for (int i = 0; i < _kidNum; ++i) {
		kid[i].set((rand() % (max - min) + min));
	}
	//EndBatchDraw();
}
void VisualBox::VisArrMassDraw() {
	BeginBatchDraw();
	for (int i = 0; i < _kidNum; ++i) {
		kid[i].draw();
	}
	EndBatchDraw();
}
