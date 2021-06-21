#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include "string"
#include <unistd.h>

#include "brylageo.hh"
#include "graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"
#include "Prostopadloscian.hh"

#define PLIK_ROBOCZY__DRON1_KORPUS  "../datasets/PlikRoboczy_Dron1_Korpus.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1  "../datasets/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR2  "../datasets/PlikRoboczy_Dron1_Rotor2.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR3  "../datasets/PlikRoboczy_Dron1_Rotor3.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR4  "../datasets/PlikRoboczy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS  "../datasets/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1  "../datasets/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2  "../datasets/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3  "../datasets/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4  "../datasets/PlikWlasciwy_Dron1_Rotor4.dat"

#define PLIK_ROBOCZY__DRON2_KORPUS  "../datasets/PlikRoboczy_Dron2_Korpus.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR1  "../datasets/PlikRoboczy_Dron2_Rotor1.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR2  "../datasets/PlikRoboczy_Dron2_Rotor2.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR3  "../datasets/PlikRoboczy_Dron2_Rotor3.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR4  "../datasets/PlikRoboczy_Dron2_Rotor4.dat"

#define PLIK_WLASCIWY__DRON2_KORPUS  "../datasets/PlikWlasciwy_Dron2_Korpus.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR1  "../datasets/PlikWlasciwy_Dron2_Rotor1.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR2  "../datasets/PlikWlasciwy_Dron2_Rotor2.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR3  "../datasets/PlikWlasciwy_Dron2_Rotor3.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR4  "../datasets/PlikWlasciwy_Dron2_Rotor4.dat"

class dron : brylageo
{

    Prostopadloscian korpus;
    graniastoslup rotor[4];

    public:

    dron();

    bool oblicz_zapisz_korpus(const int numer_drona);
    bool oblicz_zapisz_rotor(const int numer_drona ,const int numer_rotora);
    bool owektor(vector3d &wek);
    bool zapisz_dopliku(const int numer_drona);
    bool zapisz_dopliku(const int numer_drona,const int numer_rotora);
    void zapisz_drona(const int numer_drona);
    bool tworz_drona();
    void ustaw_srodek();
    vector3d daj_srodek(){return trans;}

    void dodaj_do_lacza(PzG::LaczeDoGNUPlota& Lacze,const int numer_drona);

    
    void obrot(const double kat);
    void opadanie();

};

void wznoszenie(PzG::LaczeDoGNUPlota& Lacze,dron &latawiec,const double wysokosc,const int numer);



