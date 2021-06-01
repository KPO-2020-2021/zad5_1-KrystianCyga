#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <stdlib.h>
#include "../include/dron.hh"
#include <string>
#include "lacze_do_gnuplota.hh"

int main()
{
PzG::LaczeDoGNUPlota  Lacze;
Lacze.ZmienTrybRys(PzG::TR_3D);

  Lacze.UstawZakresX(0, 50);
  Lacze.UstawZakresY(0, 50);
  Lacze.UstawZakresZ(0, 50);


  Lacze.UstawRotacjeXZ(64,65); // Tutaj ustawiany jest widok

graniastoslup gran;
Prostopadloscian<double> korpus;

dron dron1;



korpus.wczytaj("../datasets/PlikRoboczy_Dron1_Korpus.dat");
korpus.zapis("../datasets/PlikRoboczy_Dron1_Korpus_modyf.dat");

gran.wczytaj("../datasets/PlikRoboczy_Dron1_Rotor1.dat");
gran.zapis("../datasets/PlikRoboczy_Dron1_Rotor1_modyf.dat");


Lacze.DodajNazwePliku("../datasets/PlikRoboczy_Dron1_Rotor1_modyf.dat");
Lacze.DodajNazwePliku("../datasets/PlikRoboczy_Dron1_Korpus_modyf.dat");
Lacze.Rysuj();

std::cin.ignore(10000,'\n');
}
