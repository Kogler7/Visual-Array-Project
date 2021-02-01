#include"VisualArrayProject.h"
//VisualBox
void drawframe(VisualBox* b, COLORREF lc) {
	LINESTYLE LS, ls;
	getlinestyle(&LS);
	ls = LS;
	LS.thickness = 2;
	setlinestyle(&LS);
	CoordSize CS = b->CS;
	setlinecolor(lc);
	rectangle(CS.Lt.l, CS.Lt.t, CS.Lt.r + 2, CS.Lt.b + 2);
	setlinecolor(_BACK);
	setlinestyle(&ls);
}
void unfocus(VisualBox* b) {
	Sleep(_IntvalGet >= _IntvalSet ? 2 * _IntvalGet+20 : 2 * _IntvalSet + 20);
	b->focusing--;
	if (!b->focusing) drawframe(b, _FORE);
}
void VisualBox::Focus() {
	if (!focusing) drawframe(this, _FOCUS);
	focusing++;
	std::thread thd(unfocus, this);
	thd.detach();
}
void VisualBox::Initialize(
	VisualVal visVal[],//��VisualVa����
	int arrNum,//ָ�����󶨵�VisualArray���鳤��
	int maxVal,//VisualValue����Ԫ�����ֵ
	int maxWidth,//Box�����ߴ�
	int maxHeight
) {
	kid = visVal;
	_kidNum = arrNum;
	_pWidth = maxWidth / arrNum;
	_pHeight = maxHeight / maxVal;
	this->CS.setbySz(_pHeight * maxVal + 2, _pWidth * arrNum + 2);
	for (int i = 0; i < _kidNum; ++i) kid[i].pBox = this;//������
	for (int i = 0; i < _FocusNum; ++i) _focusArr[i] = &kid[0];
}
void VisualBox::Initialize(
	VisualGrid visGrid[],//��VisualGrid����
	int arrNum,//ָ�����󶨵�VisualArray���鳤��
	GridMode gridMode,
	int gridSize,//�ַ���߳�
	int maxLen//ÿ�����������
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
void VisualBox::Initialize(
	VisualGrid** visMatrix,//�󶨾���
	int order,//�������
	GridMode gridMode,
	int gridSize//�ַ���߳�
) {
	_lines = _maxLen = order;
	this->CS.setbySz(
		gridSize * order,
		gridSize * order
	);
	//������
}
void VisualBox::LayOut(Padding pd) {
	CoordSize C = parent->CS;
	switch (pd)
	{
	case Padding::TOP_LEFT:
		CS.setbyCd(5, 5);
		break;
	case Padding::TOP_MID:
		CS.setbyCd(
			C.Sz.w / 2 - CS.Sz.w / 2,
			5
		);
		break;
	case Padding::TOP_RIGHT:
		CS.setbyCd(
			C.Sz.w - CS.Sz.w-5,
			5
		);
		break;
	case Padding::MID_LEFT:
		CS.setbyCd(
			5,
			C.Sz.h / 2 - CS.Sz.h / 2
		);
		break;
	case Padding::CENTER:
		CS.setbyCd(
			C.Sz.w / 2 - CS.Sz.w / 2,
			C.Sz.h / 2 - CS.Sz.h / 2
		);
		break;
	case Padding::MID_RIGHT:
		CS.setbyCd(
			C.Sz.w - CS.Sz.w-5,
			C.Sz.h / 2 - CS.Sz.h / 2
		);
		break;
	case Padding::BOTTOM_LEFT:
		CS.setbyCd(
			5,
			C.Sz.h - CS.Sz.h-5
		);
		break;
	case Padding::BOTTOM_MID:
		CS.setbyCd(
			C.Sz.w / 2 - CS.Sz.w / 2,
			C.Sz.h - CS.Sz.h-5
		);
		break;
	case Padding::BOTTOM_RIGHT:
		CS.setbyCd(
			C.Sz.w - CS.Sz.w-5,
			C.Sz.h - CS.Sz.h-5
		);
		break;
	default:return;
		break;
	}
	//����boxλ�ó�ʼ��arrayλ��
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
void VisualBox::VisArrMassRand(int max, int min, bool masDraw) {
	srand((unsigned int)time(0));
	int m = _IntvalGet, n = _IntvalSet;
	if (masDraw) {
		_IntvalGet = _IntvalSet = 0;
		BeginBatchDraw();
	}
	for (int i = 0; i < _kidNum; ++i) {
		kid[i].set((rand() % (max - min) + min));
	}
	if (masDraw) {
		EndBatchDraw();
		_IntvalGet = m;
		_IntvalSet = n;
	}
}
void VisualBox::VisArrMassDraw() {
	BeginBatchDraw();
	for (int i = 0; i < _kidNum; ++i) {
		kid[i].drawIn();
	}
	EndBatchDraw();
}
