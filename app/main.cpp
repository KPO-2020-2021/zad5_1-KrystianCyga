#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <stdlib.h>
#include "../include/dron.hh"
#include <string>
#include "lacze_do_gnuplota.hpp"
#include "vector3d.hh"
#include "Prostopadloscian.hh"

int main()
{
PzG::LaczeDoGNUPlota  Lacze;
Lacze.ZmienTrybRys(PzG::TR_3D);
Lacze.Inicjalizuj();

  Lacze.UstawZakresX(0, 50);
  Lacze.UstawZakresY(0, 50);
  Lacze.UstawZakresZ(0, 50);


  Lacze.UstawRotacjeXZ(64,65); // Tutaj ustawiany jest widok


dron dron1;


dron1.oblicz_zapisz_korpus("../datasets/PlikRoboczy_Dron1_Korpus.dat");
dron1.oblicz_zapisz_rotor("../datasets/PlikRoboczy_Dron1_Rotor1.dat",0);
dron1.oblicz_zapisz_rotor("../datasets/PlikRoboczy_Dron1_Rotor2.dat",1);
dron1.oblicz_zapisz_rotor("../datasets/PlikRoboczy_Dron1_Rotor3.dat",2);
dron1.oblicz_zapisz_rotor("../datasets/PlikRoboczy_Dron1_Rotor4.dat",3);

dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Korpus_modyf.dat");
dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Rotor1_modyf.dat",0);
dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Rotor2_modyf.dat",1);
dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Rotor3_modyf.dat",2);
dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Rotor4_modyf.dat",3);

Lacze.DodajNazwePliku("../datasets/plaszczyzna.dat");
Lacze.DodajNazwePliku("../datasets/PlikRoboczy_Dron1_Korpus.dat");
Lacze.DodajNazwePliku("../datasets/PlikRoboczy_Dron1_Rotor1.dat");
Lacze.DodajNazwePliku("../datasets/PlikRoboczy_Dron1_Rotor2.dat");
Lacze.DodajNazwePliku("../datasets/PlikRoboczy_Dron1_Rotor3.dat");
Lacze.DodajNazwePliku("../datasets/PlikRoboczy_Dron1_Rotor4.dat");

/*
std::cin.ignore(10000,'\n');
Lacze.Rysuj();
vector3d wektor;
wektor[0]=10;
wektor[1]=10;
wektor[2]=10;
std::cin.ignore(10000,'\n');
dron1.owektor(wektor);

dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Korpus_modyf.dat");
dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Rotor1_modyf.dat",0);
dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Rotor2_modyf.dat",1);
dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Rotor3_modyf.dat",2);
dron1.zapisz_dopliku("../datasets/PlikRoboczy_Dron1_Rotor4_modyf.dat",3);
*/

Lacze.Rysuj();

std::cin.ignore(10000,'\n');



}
