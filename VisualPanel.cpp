#include"VisualArrayProject.h"
//VisualPanel
void VisualPanel::CreatePanel(
	VisualBox vBox[],//��
	int boxNum,//box������Ĭ��2�������32��
	int width,//���ڿ��
	int height,//���ڸ߶�
	bool hideC//�ڻ��ƴ���ʱ�Ƿ�رտ���̨
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
	VisualBox &vBox,//��
	int width,//���ڿ��
	int height,//���ڸ߶�
	bool hideC//�ڻ��ƴ����Ƿ�رտ���̨
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
//���Ĵ��ڴ�С
void VisualPanel::ReSize(int width, int height) {
	CS.setbySz(height, width);
	initgraph(width, height, ShowC_);
}
//���°�VisualBox
void VisualPanel::ReBind(VisualBox vBox[], int boxNum) {
	for (int i = 0; i < 32 && i < boxNum; _kidNum = ++i) kid[i] = &vBox[i];
}
void VisualPanel::ReBind(VisualBox vBox) {
	kid[0] = &vBox;
	_kidNum = 1;
}
//��������
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
