#pragma once
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;


class CHeatfield
{
private:

	//Struct und Vektor Kästchen
	struct sKaestchen
	{
		int X;
		int Y;
		float Wert;
	};

	sKaestchen Kastenstruct;
	vector<sKaestchen> m_vKastenvektor; // Struct Vektor für die Kästen
	vector<sKaestchen> m_vKastenvektornew;
	vector<sKaestchen> Vektorobenrechts;
	vector<sKaestchen> Vektoruntenlinks;
	vector<sKaestchen> Tempvektor;
	vector<sKaestchen>::iterator iWaerme;

	int Redbox;
	int Breite;
	float Waermeausbreitungsgradient; //c
	float heisseste_temp; 
	float Subtraktionstemp;
	int Mittelwert;
	int AndereKaestchen;
	float Elementehintereinanderobenlinks;
	float Elementehintereinanderobenrechts; 
	int cursor;
	int position;
	int Token;

	void initialize(int SCREEN_WIDTH, int SCREEN_HEIGHT, float Kaestchenanzahl_der_Quadratseiten);
	void Calculate(vector<sKaestchen> &Kasten, float Kaestchenanzahl_der_Quadratseiten, vector<sKaestchen> &andererKasten);
	void showvalues(vector<sKaestchen> &Kasten);

public:
	CHeatfield();
	CHeatfield(int SCREEN_WIDTH, int SCREEN_HEIGHT, float Kaestchenanzahl_der_Quadratseiten, int Kaestchenbreite, float Waermeausbreitung, float Toptemp);
	~CHeatfield(void);
	void Newvalue(float Kaestchenanzahl_der_Quadratseiten);

	int getVectorsize();
	int getRedbox();
	int getXVector(int i);
	int getYVector(int i);
	int getValue(int i);
	void setValue(int i, int Wert);
	int getBreite();
	int getTopTemp();
};

