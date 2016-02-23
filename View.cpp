#pragma once
#include "View.h"
//Setzt die Bildeinstellung
CView::CView() : SCREEN_WIDTH(800), SCREEN_HEIGHT(600)
{
	//Initialisierungsflag
	bSuccess = true;

	//Renderer
	oRenderer = NULL;
}

CView::CView(int width, int height) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{	
	bSuccess = true;
	oRenderer = NULL;
}


CView::~CView(void)
{
	// Zerstört den Renderer
	SDL_DestroyRenderer( oRenderer );
	oRenderer = NULL;

	//Zerstört das Fenster und das Surface innerhalb dessen. 
	SDL_DestroyWindow( oWindow );
	oWindow = NULL;

	//Schließt die SDL Untersysteme
	IMG_Quit();
	SDL_Quit();
}

bool CView::Initialize()
{
	bSuccess = InitializeVideo();
	bSuccess = SetLinearTextureFiltering();
	bSuccess = InitializeWindow();
	bSuccess = InitializeRenderer();
	bSuccess = InitializeRenderColor();
	bSuccess = InitializePNGLoading();

	return bSuccess;
}

bool CView::InitializeVideo()
{
	//Initialisiere SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL konnte nicht initialisiert werden! SDL_Fehler: \n" << SDL_GetError();
		bSuccess = false;
	}
	return bSuccess;
}

bool CView::SetLinearTextureFiltering()
{
	//Setze die Textur Filterung nach Linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) //Sowohl Windows als auch Linux Kompatibel, gibt SDL_FALSE zurück bei Fehlschlag
	{
		cout << "Achtung: Lineare Texturfilterung nicht aktiviert!" << endl;
		bSuccess = false;
	}
	return bSuccess;
}

bool CView::InitializeWindow()
{
	//Erstelle Fenster
	oWindow = SDL_CreateWindow( "Waermeleitungsgleichung",
								SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( oWindow == NULL )
	{
		cout << "Fenster konnte nicht erstellt werden! SDL_Fehler: " << SDL_GetError() << endl;
		bSuccess = false;
	}
	return bSuccess;
}

bool CView::InitializeRenderer()
{
	//Erstelle einen VSynced Renderer für das Fenster
	oRenderer = SDL_CreateRenderer( oWindow, -1, 
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( oRenderer == NULL )
	{
		cout << "Renderer konnte nicht erstellt werden! SDL Fehler: " << SDL_GetError() << endl;
		bSuccess = false;
	}
	return bSuccess;
}

bool CView::InitializeRenderColor()
{
	//Initialisiere Renderer Farbe
	if( SDL_SetRenderDrawColor( oRenderer, 0xFF, 0xFF, 0xFF, 0xFF))
	{
		cout << "Fehler beim setzen der Farbe des Renderers! SDL_Fehler: " << SDL_GetError() << endl;
		bSuccess = false;
	}
	return bSuccess;
}


bool CView::InitializePNGLoading()
{
	// Initialisiere laden des PNGs
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		cout << "SDL_image konnte nicht initialisiert werden! SDL_image Fehler: " << IMG_GetError() << endl;
		bSuccess = false;
	}
	return 0;
}

