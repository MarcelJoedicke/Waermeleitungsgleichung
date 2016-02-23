#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class CView
{
private:

	bool bSuccess;
	bool InitializeVideo();
	bool InitializeWindow();
	bool InitializeRenderer();
	bool InitializeRenderColor();
	bool InitializePNGLoading();
	bool SetLinearTextureFiltering();

public:
	//Das Fenster in das gerendert wird
	SDL_Window *oWindow;

	//Konstanten der Bildschirmdimensionen
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

	// Der Fenster Renderer, für die Arbeit mit Texturen
	SDL_Renderer *oRenderer;

	CView();
	CView(int width, int height);
	~CView(void);

	//Initialisierung der SDL Library
	bool Initialize();

};

