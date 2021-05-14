#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>

#include "vector.hh"
#include "brylageo.hh"
#include "prostop2.hh"
#include "graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"

class dron : brylageo
{
    Vector<double,3> polozenie;
    double orientacja;

    prostop korpus;
    graniastoslup rotor[4];

    bool oblicz_zapisz_korpus()const;
    bool oblicz_zapisz_rotor()const;

    protected:

    Vector<double,3> transDo(const  Vector<double,3> &wierz) const;

    public:

    void planuj_sciezke(double kat_skretu,double dlugosc_Lotu,Vector<double,3> &punkty_sciezki);
    bool wykonaj_lot_pionowy(double dlugosc_lotu,PzG::LaczeDoGNUPlota &Lacze);
    bool wykonaj_lot_poziomy(double dlugosc_lotu,PzG::LaczeDoGNUPlota &Lacze);

    bool oblicz_zapisz_drona()const;
    


};