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
	double Zeit_Vor_Berechnung;
	double Gesamtzeit;
	//Event handler
	SDL_Event e;
	SDL_Rect fillRect;

	void Mainloop(CView &Viewobjekt, float Kaestchenanzahl_der_Quadratseiten);

	//Löscht das gerenderte Bild
	void ErasePicture(SDL_Renderer *Renderer);
	void CalculateSquares(CView &Viewobjekt);

public:
	void handle(CView &Viewobjekt, float Kaestchenanzahl_der_Quadratseiten);
	CControl(int SCREEN_WIDTH, int SCREEN_HEIGHT, float Kaestchenanzahl_der_Quadratseiten, int Kaestchenbreite,  float Waermeausbreitung, float Toptemp);
	~CControl(void);
};

