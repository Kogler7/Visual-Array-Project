#include"VisualArrayProject.h"
InforBar Infor;
//rand
int Rndp(int max, int min) {
	if (min >= max) return 0;
	return rand() % (max - min + 1) + min;
}
//pause
void Pause() { int a = getchar(); }
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
	Lt.r += x;
	Lt.b += y;
}
void CoordSize::setbySz(int h, int w, ApCoord Ap) {
	switch (Ap) {
	case ApCoord::AP_LT:
		Lt.r = Lt.l + w;
		Lt.b = Lt.t + h;
		break;
	case ApCoord::AP_LB:
		Cd.y -= h - Sz.h;
		Lt.t = Cd.y;
		Lt.r = Lt.l + w;
		break;
	case ApCoord::AP_RT:
		Cd.x -= w - Sz.w;
		Lt.l = Cd.x;
		Lt.b = Lt.t + h;
		break;
	case ApCoord::AP_RB:
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
void CoordSize::aPndSz(int dh, int dw, ApCoord Ap) {
	switch (Ap) {
	case ApCoord::AP_LT:
		Lt.r += dw;
		Lt.b += dh;
		break;
	case ApCoord::AP_LB:
		Cd.y -= dh;
		Lt.t = Cd.y;
		Lt.r += dw;
		break;
	case ApCoord::AP_RT:
		Cd.x -= dw;
		Lt.l = Cd.x;
		Lt.b += dh;
		break;
	case ApCoord::AP_RB:
		Cd.x -= dw;
		Cd.y -= dh;
		Lt.l = Cd.x;
		Lt.t = Cd.y;
	}
	Sz.h += dh;
	Sz.w += dw;
}

//TimeTeller
void TimeTeller::Start() { t = clock(); }
int TimeTeller::Get() { return clock() - t; }
int TimeTeller::Reset() { int tt = clock() - t; t = clock(); return tt; }
void TimeTeller::Getf() { printf("\n用时 %d ms\n", clock() - t); }
void TimeTeller::Resetf() { printf("\n用时 %d ms\n", clock() - t); t = clock(); }
void TimeTeller::Pause() { _t = clock(); awake = false; }
void TimeTeller::Continue() { if (!awake) { t -= _t; awake = true; } }
void TimeTeller::TSleep(int ms) {
	this->Pause();
	Sleep(ms);
	this->Continue();
}

//InforBar
void InforBar::enable() {

}
void InforBar::disable() {

}
void InforBar::MsgAppend(char* head, void* body) {

}
void InforBar::ChkAppend() {

}
void InforBar::showInterval() {

}
void InforBar::showFPS(){
}

