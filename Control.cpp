#include "Control.h"


CControl::CControl(int SCREEN_WIDTH, int SCREEN_HEIGHT, float Kaestchenanzahl_der_Quadratseiten, int Kaestchenbreite,  float Waermeausbreitung, float Toptemp) : Hitzeobjekt(SCREEN_WIDTH, SCREEN_HEIGHT, Kaestchenanzahl_der_Quadratseiten, Kaestchenbreite, Waermeausbreitung, Toptemp)
{
	t=0;
	quit = false;
	fillRect.x=0;
	fillRect.y=0;
	fillRect.h=0;
	fillRect.w=0;
	gedrueckt = false;
	startzeit = omp_get_wtime();
	Zeit_Vor_Berechnung = 0;
	Gesamtzeit = 0;
}


CControl::~CControl(void)
{
}

void CControl::handle(CView &Viewobjekt, float Kaestchenanzahl_der_Quadratseiten)
{
	Mainloop(Viewobjekt, Kaestchenanzahl_der_Quadratseiten);
}

void CControl::Mainloop(CView &Viewobjekt, float Kaestchenanzahl_der_Quadratseiten)
{

    fstream f;
    f.open("test.dat", ios::out);
    f << "t\t\tBerechnungsdauer" << endl;
    f.close();

	//Solange die Applikation l�uft
	while( !quit )
	{
		//Bearbeite die Elemente in der Elementschlange
		while( SDL_PollEvent( &e ) != 0 )
		{
			//Benutzer m�chte das Programm beenden
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			else if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP ) // Events f�r die Maus, wurde sie bewegt, wurde sie gedr�ckt, oder wurde die gedr�ckte Taste losgelassen?
			{
				//Bekommen der Mausposition
				int x, y;
				SDL_GetMouseState( &x, &y );

				switch( e.type )
				{
					/*case SDL_MOUSEMOTION:						
					mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
					break;*/
			
					//Maustaste gedr�ckt
					case SDL_MOUSEBUTTONDOWN:
					gedrueckt = true;
					break;
				
					//Maustaste losgelassen
					case SDL_MOUSEBUTTONUP:
					gedrueckt = false;
					break;
				}

				//Maus ist links vom K�stchen
				for(int i = 0; i < Hitzeobjekt.getRedbox(); i++)
				{
					if( x < Hitzeobjekt.getXVector(i))
					{}
				
					//Maus ist rechts vom K�stchen
					else if( x > Hitzeobjekt.getXVector(i) + Hitzeobjekt.getBreite() )
					{}
				
					//Maus ist �ber den K�stchen
		 			else if( y < Hitzeobjekt.getYVector(i) )
					{}
	
					//Maus unter dem K�stchen
					else if( y > Hitzeobjekt.getYVector(i) + Hitzeobjekt.getBreite() )
					{}
		
					//Maus ist im K�stchen
					else
					{
						if(gedrueckt == true)
						{
							Hitzeobjekt.setValue(i, Hitzeobjekt.getTopTemp());
						}
					}			
				}
			}
		}
		
		if(t%25 == 0)
		{
			//�bermalen des letzten Bildes
			ErasePicture(Viewobjekt.oRenderer);

			CalculateSquares(Viewobjekt);

			//Update des Bildschirms
			SDL_RenderPresent( Viewobjekt.oRenderer );
		}
		
		f.open("test.dat", ios::app);
		f << t << "\t\t";
		f.close();	
	
		Zeit_Vor_Berechnung = omp_get_wtime() - startzeit;
		Hitzeobjekt.Newvalue(Kaestchenanzahl_der_Quadratseiten);	
		
		Gesamtzeit = Gesamtzeit + (omp_get_wtime() - startzeit - Zeit_Vor_Berechnung);
		f.open("test.dat", ios::app);
		f << Gesamtzeit << endl;
		f.close();

		if(t == 200)
		{
			quit = true;
		}
		else
		{
			t++;
		}
	}
}

void CControl::ErasePicture (SDL_Renderer *Renderer)
{
	// Bild l�schen, mit wei� �bermalen
	SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear( Renderer );
}

void CControl::CalculateSquares(CView &Viewobjekt)
{
	for(int i = 0; i < Hitzeobjekt.getRedbox(); i++)
	{
		//Zum malen der K�stchen		
		fillRect.x = Hitzeobjekt.getXVector(i);
		fillRect.y = Hitzeobjekt.getYVector(i);
		fillRect.w = Hitzeobjekt.getBreite();
		fillRect.h = Hitzeobjekt.getBreite();
		SDL_SetRenderDrawColor( Viewobjekt.oRenderer, Hitzeobjekt.getValue(i), 0x00, 0x00, 0xFF );		
		SDL_RenderFillRect( Viewobjekt.oRenderer, &fillRect );
	}

	for(int i = Hitzeobjekt.getRedbox(); i < Hitzeobjekt.getVectorsize(); i++)
	{
		//Zum malen der R�nder
		fillRect.x = Hitzeobjekt.getXVector(i);
		fillRect.y = Hitzeobjekt.getYVector(i);
		fillRect.w = (Hitzeobjekt.getBreite())/5;
		fillRect.h = (Hitzeobjekt.getBreite())/5;
		SDL_SetRenderDrawColor( Viewobjekt.oRenderer, 0x00, 0x00, 0x00, 0xFF );		
		SDL_RenderFillRect( Viewobjekt.oRenderer, &fillRect );
	}
}
