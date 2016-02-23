#pragma once

#include <omp.h>
#include <fstream>
#include <SDL.h>
#include "View.h"
#include "Heatfield.h"

class CControl
{
private:
	CHeatfield Hitzeobjekt;
	bool quit;
	int t;
	bool gedrueckt;
	double startzeit;
	//Event handler
	SDL_Event e;
	SDL_Rect fillRect;

	void Mainloop(CView &Viewobjekt, float KaestchenXundY);

	//L�scht das gerenderte Bild
	void ErasePicture(SDL_Renderer *Renderer);
	void CalculateSquares(CView &Viewobjekt);

public:
	void handle(CView &Viewobjekt, float KaestchenXundY);
	CControl(int SCREEN_WIDTH, int SCREEN_HEIGHT, float KaestchenXundY, int Kaestchenbreite,  float Waermeausbreitung, float Toptemp);
	~CControl(void);
};

