#include "View.h"
#include "Control.h"


int main( int argc, char* args[] )
{
	//Erstellt die Initialisierung der SDL
	CView Viewobjekt = CView();
	Viewobjekt.Initialize();

	int Kaestchenanzahl_der_Quadratseiten = 101;
	int Kaestchenbreite = 6;
	float Waermeausbreitung = 0.05;
	float Maxtemp = 255;

	CControl Kontrollobjekt(Viewobjekt.SCREEN_WIDTH, Viewobjekt.SCREEN_HEIGHT, Kaestchenanzahl_der_Quadratseiten, Kaestchenbreite, Waermeausbreitung, Maxtemp);
	Kontrollobjekt.handle(Viewobjekt, Kaestchenanzahl_der_Quadratseiten);

	return 0;
}
