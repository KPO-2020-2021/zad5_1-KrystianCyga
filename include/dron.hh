#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include "string"

#include "brylageo.hh"
#include "graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"
#include "Prostopadloscian.hh"

class dron : brylageo
{
    vector3d polozenie;
    double orientacja;

    Prostopadloscian korpus;
    graniastoslup rotor[4];


    public:

    dron();

    bool oblicz_zapisz_korpus(const char* nazwa );
    bool oblicz_zapisz_rotor(const char* nazwa,const int numer);

};