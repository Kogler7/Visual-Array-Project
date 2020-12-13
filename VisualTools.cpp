#include"VisualArrayProject.h"
//rand
int Rndp(int max, int min) {
	if (min >= max) return 0;
	return rand() % (max - min + 1) + min;
}
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

//FastDeveloper


