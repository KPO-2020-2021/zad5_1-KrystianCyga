#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include "string"


#include "brylageo.hh"
#include "cuboid.hh"
#include "graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"

class dron : brylageo
{
    Vector<double,3> polozenie;
    double orientacja;

    cuboid korpus;
    graniastoslup rotor[4];


    public:

    dron();

    bool oblicz_zapisz_korpus(const char* nazwa );
    bool oblicz_zapisz_rotor(const char* nazwa,const int numer);

};