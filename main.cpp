#include<stdio.h>
#include<stdlib.h>
#include"VisualArrayProject.h"
#define VNUM 60
#define GNUM 32
void sort(VisualVal arr[], int n);
void quick_sort(VisualVal s[], int l, int r);


TimeTeller T;
VisualPanel P;
VisualBox B[2];
VisualVal V[VNUM];
VisualGrid G[GNUM];

void Gtest() {
	while (true)
	{
		G[Rndp(31, 0)].set(Rndp('z', 'a'));
	}
}

void batch() {
	while (true)
	{
		Sleep(1000);
		FlushBatchDraw();
	}
}

int main(void) {
	srand((unsigned)time(NULL));
	
	P.Initialize(B, 2, 1000, 480, false);
	P.SetInterval(100, 100);
	P.SetTheme(NEW_THEME);
	/*BeginBatchDraw();
	std::thread bat(batch);
	bat.detach();*/
	B[0].Initialize(V, VNUM, 128, 640, 360);
	B[0].LayOut(Padding::TOP_LEFT);
	B[0].SetFocusNum(2);

	B[1].Initialize(G, GNUM, GridMode::BY_CHAR, 48, 8);
	B[1].LayOut(Padding::TOP_RIGHT);
	B[1].SetFocusNum(2);
	B[1].VisArrMassRand('z', 'a', false);
	//std::thread Gthd(Gtest);
	//for (int i = 0; i < VNUM; ++i) if (i % 5 == 0) V[i].mark();
	while (true)
	{
		B[0].VisArrMassRand(128, 0, false);
		//std::thread thd(sort, V + VNUM / 2, VNUM / 2);
		//VisualBubbleSort(V, VNUM);
		VisualSelectionSort(V, VNUM);
		//VisualInsertionSort(V, VNUM);
		//thd.join();
		//B[0].VisArrMassRand(128, 0, true);
		//VisualQuickSort(V, 0, VNUM-1);
	}
	//Gthd.join();
	Pause();
	return 0;
}
