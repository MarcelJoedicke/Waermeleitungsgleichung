#include "Heatfield.h"
//Hier anschauen
CHeatfield::CHeatfield()
{
	Redbox=0;
	Kastenstruct.X = 0;
	Kastenstruct.Y = 0;
	Kastenstruct.Wert = 0.0;
	initialize(800, 600, 100);
	Breite = 10;
	cursor = 0;
	position = 0;
	Waermeausbreitungsgradient = 0.1;
	heisseste_temp=40;
	Token = false;

	AndereKaestchen = (100 - 1)/2;
	Subtraktionstemp = -(heisseste_temp/AndereKaestchen);
	Mittelwert = 100/2+0.5;
	Elementehintereinanderobenlinks = 100/2+0.5;
	Elementehintereinanderobenrechts = 100-Elementehintereinanderobenlinks;
}

CHeatfield::CHeatfield(int SCREEN_WIDTH, int SCREEN_HEIGHT, float Kaestchenanzahl_der_Quadratseiten, int Kaestchenbreite, float Waermeausbreitung, float Toptemp)
{
	Redbox=0;
	Kastenstruct.X = 0;
	Kastenstruct.Y = 0;
	if (Kaestchenbreite < 5)
	{
		Breite = 5;
	}
	else
	{
		Breite = Kaestchenbreite;
	}
	if(static_cast<int> (Kaestchenanzahl_der_Quadratseiten) % 2 == 0) // Wenn die Kaestchenanzahl gerade ist, wird eine 1 aufaddiert um sie ungerade zu machen.
	{
		Kaestchenanzahl_der_Quadratseiten = Kaestchenanzahl_der_Quadratseiten + 1; //Es wird nur eine ungerade Menge an Kaestchen erlaubt, damit man immer eine Mitte hat.
	}
		

	cursor = 0;
	position = 0;
	Token = false;
	Waermeausbreitungsgradient = Waermeausbreitung;
	heisseste_temp=Toptemp;

	AndereKaestchen = (Kaestchenanzahl_der_Quadratseiten - 1)/2; // ist die Anzahl der Kästchen links bzw. rechts von der Mitte
	Subtraktionstemp = -(heisseste_temp/AndereKaestchen); //Die Temperatur die die anderen Kästchen abgezogen bekommen abseits der Mitte
	Mittelwert = Kaestchenanzahl_der_Quadratseiten/2+0.5; //Kaestchen der Mitte
	Elementehintereinanderobenlinks = Kaestchenanzahl_der_Quadratseiten/2+0.5; //Wie viele Kaestchen im oberen linken Bereich 
	Elementehintereinanderobenrechts = Kaestchenanzahl_der_Quadratseiten-Elementehintereinanderobenlinks; //Wie viele Kästchen im oberen Rechten Bereich
	initialize(SCREEN_WIDTH, SCREEN_HEIGHT, Kaestchenanzahl_der_Quadratseiten);
}


CHeatfield::~CHeatfield(void)
{
}

void CHeatfield::initialize(int SCREEN_WIDTH, int SCREEN_HEIGHT, float Kaestchenanzahl_der_Quadratseiten)
{
	for(int y=0; y< ((Kaestchenanzahl_der_Quadratseiten*(Breite+Breite/5))+1); y++)
	{
		for(int x=0;x< ((Kaestchenanzahl_der_Quadratseiten*(Breite+Breite/5))+1); x++)
		{
			//Für die Kaestchen in SDL
			if((x == (Kaestchenanzahl_der_Quadratseiten*(Breite+Breite/5))) || (y == (Kaestchenanzahl_der_Quadratseiten*(Breite+Breite/5)))) // Korrekturwert, damit er zum Schluss außerhalb des Feldes kein neues Kästchen zeichnet, aber die Aussenumrandung
			{}
			else if (x%(Breite+Breite/5)== 0 && y%(Breite+Breite/5) == 0)
			{
				Kastenstruct.X = x+Breite/5;
				Kastenstruct.Y = y+Breite/5;
				m_vKastenvektor.insert(m_vKastenvektor.begin()+Redbox, Kastenstruct);
				Redbox++; //Ein Kaestchen eins weniger als Redbox groß ist (Redbox = 4, Kaestchen von (0-3))
			}
			else{}

			//Für die Ränder in SDL
			if(x%(Breite+Breite/5) == 0 || (y%(Breite+Breite/5) == 0))
			{
				Kastenstruct.X = x;
				Kastenstruct.Y = y;
				m_vKastenvektor.push_back(Kastenstruct);
			}
			else{}
		}
	}
	
	for(int y=0; y <= Kaestchenanzahl_der_Quadratseiten-1 ; y++)
	{
		for( int x=0; x <= Kaestchenanzahl_der_Quadratseiten-1; x++)
		{
			Kastenstruct.X = x;
			Kastenstruct.Y = y;
			if((Kastenstruct.X > Mittelwert-1) && (Kastenstruct.Y < Mittelwert-1)) //schließen aus was oben rechts ist
			{}
			else if((Kastenstruct.X < Mittelwert-1) && (Kastenstruct.Y > Mittelwert-1)) //schließen aus was unten links ist
			{}
			else
			{
				if(Kastenstruct.Y == 0 || Kastenstruct.Y == Kaestchenanzahl_der_Quadratseiten-1) //die Raender werden 0 gesetzt 0-e stelle und letzte stelle von y
				{
					Kastenstruct.Wert = 0.0;
				}
			
				else if(Kastenstruct.X == 0 || Kastenstruct.X == Kaestchenanzahl_der_Quadratseiten-1) //die Raender von x achse werden 0 gesetzt
				{
					Kastenstruct.Wert = 0.0;
				}

				else if((Kastenstruct.X == Mittelwert-1) && (Kastenstruct.Y == Mittelwert-1))//die mitte wird bestimmt und heißeste temp zugeordnet
				{
					Kastenstruct.Wert = heisseste_temp;
				}
				else
				{
					if(Kastenstruct.Y < Mittelwert-1  || Kastenstruct.X <Mittelwert-1) //fuer die elemente links oben
					{
						if(Kastenstruct.X<Kastenstruct.Y)
						{
							Kastenstruct.Wert = heisseste_temp + (AndereKaestchen - x) * (Subtraktionstemp);
						}
						else if(Kastenstruct.X>Kastenstruct.Y)
						{
							Kastenstruct.Wert = heisseste_temp + (AndereKaestchen - y) * (Subtraktionstemp);
						}
						else if(Kastenstruct.X==Kastenstruct.Y)
						{
							Kastenstruct.Wert = heisseste_temp + (AndereKaestchen - y) * (Subtraktionstemp);
						}
					}
					else if(Kastenstruct.Y > Mittelwert-1 || Kastenstruct.X >= Mittelwert-1) //Für die Elemente rechts unten
					{
						if(Kastenstruct.X>Kastenstruct.Y)
						{
							Kastenstruct.Wert = heisseste_temp + (x - AndereKaestchen) * (Subtraktionstemp);
						}
						else if(Kastenstruct.X<Kastenstruct.Y)
						{
							Kastenstruct.Wert = heisseste_temp + (y - AndereKaestchen) * (Subtraktionstemp);
						}
						else if(Kastenstruct.X==Kastenstruct.Y)
						{
							Kastenstruct.Wert = heisseste_temp + (y - AndereKaestchen) * (Subtraktionstemp);
						}
					}
					else
					{}
				}
				Tempvektor.push_back(Kastenstruct);
			}
		}
	}
	
	for(int x=0; x < static_cast<int> (Tempvektor.size()); x++)
	{
		//Zum bestimmen der Werte von oben rechts im Feld
		if((Tempvektor.at(x).X < Mittelwert-1) && (Tempvektor.at(x).Y < Mittelwert-1))
		{
			Kastenstruct.X = (Kaestchenanzahl_der_Quadratseiten-1) - Tempvektor.at(x).X;			
			Kastenstruct.Y = Tempvektor.at(x).Y;	
			Kastenstruct.Wert = Tempvektor.at(x).Wert;	
			Vektorobenrechts.insert(Vektorobenrechts.begin(),Kastenstruct);
		}
		//Zum bestimmen der Werte unten links im Feld
		else if((Tempvektor.at(x).X > Mittelwert-1) && (Tempvektor.at(x).Y > Mittelwert-1)) 
		{
			Kastenstruct.X = (Kaestchenanzahl_der_Quadratseiten-1) - Tempvektor.at(x).X;
			Kastenstruct.Y = Tempvektor.at(x).Y;
			Kastenstruct.Wert = Tempvektor.at(x).Wert;	
			Vektoruntenlinks.insert(Vektoruntenlinks.begin(),Kastenstruct);
		}
	}


	do
	{
		//Sortiert die Werte oben rechts der Reihenfolge nach und führt sie mit den Werten von unten rechts und oben links zusammen
		cursor = cursor+Elementehintereinanderobenlinks;
		position = static_cast<int> (Vektorobenrechts.size())-Elementehintereinanderobenrechts;
		iWaerme = Tempvektor.begin()+cursor;
		for(position; position < static_cast<int> (Vektorobenrechts.size());position++)
		{
			Tempvektor.insert(iWaerme,Vektorobenrechts[position]);
			cursor++;
			iWaerme = Tempvektor.begin()+cursor;
		}
		for(int x = 0; x < Elementehintereinanderobenrechts; x++)
		{
			Vektorobenrechts.pop_back();
		}

	} while(static_cast<int> (Vektorobenrechts.size()) != 0);

	cursor = cursor+Elementehintereinanderobenlinks-1;

	do
	{
		//Sortiert die Werte unten links der Reihenfolge nach und führt sie mit den Werten von oben links, oben rechts und unten rechts zusammen
		cursor = cursor+Elementehintereinanderobenlinks;
		position = static_cast<int> (Vektoruntenlinks.size())-Elementehintereinanderobenrechts;
		iWaerme = Tempvektor.begin()+cursor;
		for(position; position < static_cast<int> (Vektoruntenlinks.size());position++)
		{
			Tempvektor.insert(iWaerme,Vektoruntenlinks[position]);
			cursor++;
			iWaerme = Tempvektor.begin()+cursor;
		}
		for(int x = 0; x < Elementehintereinanderobenrechts; x++)
		{
			Vektoruntenlinks.pop_back();
		}
	
	} while(static_cast<int> (Vektoruntenlinks.size()) != 0);
	
	#pragma omp parallel for
	for(int i = 0; i<static_cast<int> (Tempvektor.size()); i++)
	{
		m_vKastenvektor.at(i).Wert = Tempvektor.at(i).Wert;
	}
	Token = true;
}

int CHeatfield::getVectorsize()
{
	return static_cast<int> (m_vKastenvektor.size());
}

int CHeatfield::getRedbox()
{
	return Redbox;
}

int CHeatfield::getXVector(int i)
{
	return m_vKastenvektor.at(i).X;
}

int CHeatfield::getYVector(int i)
{
	return m_vKastenvektor.at(i).Y;
}

int CHeatfield::getValue(int i)
{
	return m_vKastenvektor.at(i).Wert;
}

int CHeatfield::getTopTemp()
{
	return heisseste_temp;
}

void CHeatfield::setValue(int i, int Wert)
{
	m_vKastenvektor.at(i).Wert = Wert;
}

int CHeatfield::getBreite()
{
	return Breite;
}

void CHeatfield::Newvalue(float Kaestchenanzahl_der_Quadratseiten)
{
	if(Token == true)
	{
		m_vKastenvektornew = m_vKastenvektor;
		Calculate(m_vKastenvektornew, Kaestchenanzahl_der_Quadratseiten, m_vKastenvektor);

	}
	else
	{
		m_vKastenvektor = m_vKastenvektornew;
		Calculate(m_vKastenvektor,Kaestchenanzahl_der_Quadratseiten, m_vKastenvektornew);
	}
}

void CHeatfield::Calculate(vector<sKaestchen> &Kasten, float Kaestchenanzahl_der_Quadratseiten, vector<sKaestchen> &andererKasten)
{
	#pragma omp parallel for
	for(int x = 0; x < Redbox; x++)
	{
		if( (andererKasten.at(x).Y == Breite/5) || //Wenn Y unten unter dem Rand, X egal
			(andererKasten.at(x).X == Breite/5) || //Wenn X rechts neben dem Rand, Y egal
			(andererKasten.at(x).X == (Breite/5 + ((Kaestchenanzahl_der_Quadratseiten-1) * (Breite+Breite/5)))) || // Breite/5 ist der äußere Rand, um zum Kaestchen rechts oder ganz unten zu kommen muss man die Anzahl der (Kästchen - 1 * der Breite der Kästchen Rechnen. Da es auch Ränder gibt, muss man diese in die Rechnung einbauen, daher Kästchen - 1 * (Breite + Breite/5). Also X ganz rechts das Kästchen, Y ist egal
			(andererKasten.at(x).Y == (Breite/5 + ((Kaestchenanzahl_der_Quadratseiten-1) * (Breite+Breite/5)))) // Y ganz unten, X ist egal 
		  )
		{
			Kasten.at(x).Wert = 0;
		}

		else
		{
		//Alles was nicht Rand ist, erhält einen Wert
			Kasten.at(x).Wert = andererKasten.at(x).Wert + Waermeausbreitungsgradient * (andererKasten.at(x+1).Wert + andererKasten.at(x-1).Wert - 2 * andererKasten.at(x).Wert)
													+ Waermeausbreitungsgradient * (andererKasten.at(x + Kaestchenanzahl_der_Quadratseiten).Wert + andererKasten.at(x - Kaestchenanzahl_der_Quadratseiten).Wert - 2 * andererKasten.at(x).Wert);
		}
	}
	Token = !Token;
	//showvalues(Kasten);
}

void CHeatfield::showvalues(vector<sKaestchen> &Kasten)
{
	#pragma omp parallel for
	for(int x=0; x<Redbox; x++)
	{
		cout << "X-Wert: " << m_vKastenvektor.at(x).X << endl;
		cout << "Y-Wert: " << m_vKastenvektor.at(x).Y << endl;
		cout << "Wert: " << m_vKastenvektor.at(x).Wert << endl;
	}
}
