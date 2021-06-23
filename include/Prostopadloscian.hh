#pragma once

#include "vector3d.hh"
#include <iostream>
#include <cstdlib>
#include "matrix.hh"
#include <stdexcept>
#include <string>
#include <fstream>
#include <iomanip>

/*!
 * \file  Prostopadloscian.hh
 *  
 *  Plik zawiera definicję klasy Prostopadloscian oraz
 *  jej opisane metody i funkcje.
 *  
 */

/*!
 * \brief Definicja Szablonu Prostopadloscianu.
 * 
 *  Jest on postaci 8 wektorow.
 */
class Prostopadloscian
{

  vector3d wektor[10];
  vector3d polozenie;

public:
  Prostopadloscian();
  void boki();
  Prostopadloscian rotacja(const double kat);
  Prostopadloscian obrot(const double kat);
  Prostopadloscian obrot2(const double kat,vector3d &polozenie);
  vector3d operator[](const int punkt) const;
  vector3d &operator[](const int punkt);
  bool zapis(const std::string &nazwa) const;
  bool owektor(vector3d &wek);
  bool owektor_m(vector3d &wek);
  bool wczytaj(const std::string &nazwa);
  void ustal_srodek();
  vector3d daj_srodek();
};
