#include "View.h"
#include "Control.h"


int main( int argc, char* args[] )
{
	//Erstellt die Initialisierung der SDL
	CView Viewobjekt = CView();
	Viewobjekt.Initialize();

	int Kaestchenanzahl = 201;
	int Kaestchenbreite = 6;
	float Waermeausbreitung = 0.05;
	float Maxtemp = 255;

	CControl Kontrollobjekt(Viewobjekt.SCREEN_WIDTH, Viewobjekt.SCREEN_HEIGHT, Kaestchenanzahl, Kaestchenbreite, Waermeausbreitung, Maxtemp); //Bildschirmbreite, Bildschirmh�he, Anzahl K�stchen in XY, Breite eines K�stchens, W�rmeausbreitungsgradient, heisseste Temperatur
	Kontrollobjekt.handle(Viewobjekt, Kaestchenanzahl);

	return 0;
}
