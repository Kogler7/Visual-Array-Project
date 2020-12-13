#include"VisualArrayProject.h"
//VisualPanel
void VisualPanel::CreatePanel(
	VisualBox vBox[],//绑定
	int boxNum,//box数量，默认2个，最多32个
	int width,//窗口宽度
	int height,//窗口高度
	bool hideC//在绘制窗口时是否关闭控制台
) {
	ShowC_ = !hideC;
	CS.setbySz(height, width);
	initgraph(width, height, ShowC_);
	SetTheme(DEFAULT_THEME);	//following creating
	for (int i = 0; i < 32 && i < boxNum; _kidNum = ++i) {
		kid[i] = &vBox[i];
		vBox[i].parent = this;
	}
}
void VisualPanel::CreatePanel(
	VisualBox &vBox,//绑定
	int width,//窗口宽度
	int height,//窗口高度
	bool hideC//在绘制窗口是否关闭控制台
) {
	ShowC_ = !hideC;
	CS.setbySz(height, width);
	initgraph(width, height, ShowC_);
	SetTheme(DEFAULT_THEME);
	kid[0] = &vBox;
	kid[0]->parent = this;
	_kidNum = 1;
}
void VisualPanel::ClosePanel() {
	closegraph();
}
//更改窗口大小
void VisualPanel::ReSize(int width, int height) {
	CS.setbySz(height, width);
	initgraph(width, height, ShowC_);
}
//重新绑定VisualBox
void VisualPanel::ReBind(VisualBox vBox[], int boxNum) {
	for (int i = 0; i < 32 && i < boxNum; _kidNum = ++i) kid[i] = &vBox[i];
}
void VisualPanel::ReBind(VisualBox vBox) {
	kid[0] = &vBox;
	_kidNum = 1;
}
//主题设置
void VisualPanel::SetTheme(ColorTheme CT) {
	_BACK = CT.Back;
	setbkcolor(_BACK);
	floodfill(1, 1, _BACK);
	_FORE = CT.Fore;
	_FOCUS = CT.Focus;
	_MARK = CT.Mark;
}
void VisualPanel::SetBackColor(COLORREF C) { _BACK = C; setbkcolor(_BACK); floodfill(1, 1, _BACK); }
void VisualPanel::SetForeColor(COLORREF C) { _FORE = C; }
void VisualPanel::SetFocusColor(COLORREF C) { _FOCUS = C; }
void VisualPanel::SetMarkColor(COLORREF C) { _MARK = C; }
void VisualPanel::SetInterval(int get, int set) { _IntvalGet = get; _IntvalSet = set; }
void VisualPanel::SetFocusNum(int n) {
	if (n) {
		for (int i = 0; i < _kidNum; ++i) {
			kid[i]->_FocusNum = n;
			for (int j = 0; i < n; ++i) kid[i]->_focusArr[j] = NULL;
		}
	}
}
