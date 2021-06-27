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
#include <unistd.h>
#include <math.h>

void menu();
double kat_miedzy_wektorami(vector3d pierwszy, dron &wiatrak);
bool zapisz_sciezke(const vector3d sciezka, dron &wiatrak);

dron drony[2];
vector3d sciezka, versor;
PzG::LaczeDoGNUPlota Lacze;
int numer_aktywnego, a;
vector3d tmp, pom, pom2,srodek;
double kat;

int main()
{
  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();

  Lacze.UstawZakresX(-10, 120);
  Lacze.UstawZakresY(-10, 120);
  Lacze.UstawZakresZ(-10, 120);

  Lacze.UstawRotacjeXZ(64, 65); // Tutaj ustawiany jest widok

  vector3d wektor2;
  wektor2[0] = 100;
  wektor2[1] = 100;
  wektor2[2] = 0;

  drony[0].oblicz_zapisz_korpus(1);
  drony[0].oblicz_zapisz_rotor(1, 0);
  drony[0].oblicz_zapisz_rotor(1, 1);
  drony[0].oblicz_zapisz_rotor(1, 2);
  drony[0].oblicz_zapisz_rotor(1, 3);

  drony[1].oblicz_zapisz_korpus(2);
  drony[1].oblicz_zapisz_rotor(2, 0);
  drony[1].oblicz_zapisz_rotor(2, 1);
  drony[1].oblicz_zapisz_rotor(2, 2);
  drony[1].oblicz_zapisz_rotor(2, 3);

  drony[0].tworz_drona();
  drony[1].tworz_drona();
  drony[1].owektor(wektor2);

  drony[0].zapisz_dopliku(1);
  drony[0].zapisz_dopliku(1, 0);
  drony[0].zapisz_dopliku(1, 1);
  drony[0].zapisz_dopliku(1, 2);
  drony[0].zapisz_dopliku(1, 3);

  drony[1].zapisz_dopliku(2);
  drony[1].zapisz_dopliku(2, 0);
  drony[1].zapisz_dopliku(2, 1);
  drony[1].zapisz_dopliku(2, 2);
  drony[1].zapisz_dopliku(2, 3);

  Lacze.DodajNazwePliku("../datasets/trasa_przelotu.dat");
  Lacze.DodajNazwePliku("../datasets/plaszczyzna.dat");
  drony[0].dodaj_do_lacza(Lacze, 1);
  drony[1].dodaj_do_lacza(Lacze, 2);

  drony[0].ustaw_srodek();
  drony[1].ustaw_srodek();

  menu();
}

void menu()
{

  char wyb;
  double stopnie, odleglosc, wysokosc;
  std::cout << "\n"
            << "************************MENU************************\n";
  std::cout << "  w-wybor drona\n";
  std::cout << "  s-podanie sciezki drona\n";
  std::cout << "  l-lot drona\n";
  std::cout << "  z-lot zwiadowczy (modyfikacja)\n";
  std::cout << "  m-powrot do menu\n";
  std::cout << "  k-koniec dzialania programu\n";
  std::cout << "  Twoj wybor -> :";
  std::cin >> wyb;
  std::cout << "\n";

  switch (wyb)
  {

  case 'w':
    std::cout << "Dron numer 1 na pozycji (x,y,z):  " << drony[0].daj_srodek();
    std::cout << "\nDron numer 2 na pozycji (x,y,z):  " << drony[1].daj_srodek();
    std::cout << "\n\nPodaj numer drona: ";
    std::cin >> a;
    if (a == 1)
    {
      numer_aktywnego = 0;
    }
    else
      numer_aktywnego = 1;
    drony[numer_aktywnego].ustaw_srodek();
    drony[numer_aktywnego].ustal_orientacje();
    break;

  case 's':
    std::cout << "\nPodaj sciezke drona (x,y,z) :";
    std::cin >> sciezka[0] >> sciezka[1] >> sciezka[2];
    zapisz_sciezke(sciezka, drony[numer_aktywnego]);

    break;

  case 'l':

    wysokosc = sciezka[2];
    Lacze.Rysuj();

    drony[numer_aktywnego].zapisz_drona(numer_aktywnego + 1);

    wznoszenie(Lacze, drony[numer_aktywnego], wysokosc, numer_aktywnego);

    drony[numer_aktywnego].ustaw_srodek();
    drony[numer_aktywnego].ustal_orientacje();

    kat = kat_miedzy_wektorami(sciezka, drony[numer_aktywnego]) - M_PI / 2;
    stopnie = kat * 360 / M_PI;
    pom2 = drony[numer_aktywnego].daj_srodek();

    for (int i = 0; i < stopnie / 2; i++)
    {

      drony[numer_aktywnego].owektor_m(pom2);
      drony[numer_aktywnego].obrot(1);
      drony[numer_aktywnego].owektor(pom2);
      usleep(80000);
      drony[numer_aktywnego].zapisz_drona(numer_aktywnego + 1);
      usleep(80000);
      Lacze.Rysuj();
    }

    sciezka[2] = 0;
    odleglosc = sciezka.modul();

    lot_do_przodu(Lacze, drony[numer_aktywnego], kat, odleglosc, numer_aktywnego);

    opadanie(Lacze, drony[numer_aktywnego], wysokosc, numer_aktywnego);

    drony[(numer_aktywnego)].zapisz_drona((numer_aktywnego + 1));
    usleep(150000);
    Lacze.Rysuj();

    std::cin.ignore(10000, '\n');
    Lacze.UsunNazwePliku("../datasets/trasa_przelotu.dat");
    std::cout << "Sciezka usunieta\n";
    Lacze.Rysuj();

    break;

  case 'z':
    Lacze.UsunNazwePliku("../datasets/trasa_przelotu.dat");
    tmp = drony[numer_aktywnego].daj_srodek();
    pom[0] = (50+20*sqrt(2)) - tmp[0];
    pom[1] = (50+20*sqrt(2)) - tmp[1];
    pom[2] = 50;

    odleglosc=pom.modul();

    kat = kat_miedzy_wektorami(pom, drony[numer_aktywnego]) - M_PI / 2;

    wznoszenie(Lacze, drony[numer_aktywnego], pom[2], numer_aktywnego);
    stopnie = kat * 360 / M_PI;
    pom2 = drony[numer_aktywnego].daj_srodek();

    for (int i = 0; i < stopnie / 2; i++)
    {

      drony[numer_aktywnego].owektor_m(pom2);
      drony[numer_aktywnego].obrot(1);
      drony[numer_aktywnego].owektor(pom2);
      usleep(80000);
      drony[numer_aktywnego].zapisz_drona(numer_aktywnego + 1);
      usleep(80000);
      Lacze.Rysuj();
    }
    lot_do_przodu(Lacze, drony[numer_aktywnego], kat, odleglosc, numer_aktywnego);

    drony[numer_aktywnego].ustaw_srodek();
    pom2 = drony[numer_aktywnego].daj_srodek();
    for (int i = 0; i < 90; i++)
    {

      drony[numer_aktywnego].owektor_m(pom2);
      drony[numer_aktywnego].obrot(1);
      drony[numer_aktywnego].owektor(pom2);
      usleep(80000);
      drony[numer_aktywnego].zapisz_drona(numer_aktywnego + 1);
      usleep(80000);
      Lacze.Rysuj();
    }

    srodek[0]=50;srodek[1]=50;srodek[1]=50;
    for (int i = 0; i < 360; i++)
    {

      drony[numer_aktywnego].owektor_m(srodek);
      drony[numer_aktywnego].obrot(1);
      drony[numer_aktywnego].owektor(srodek);
      usleep(40000);
      drony[numer_aktywnego].zapisz_drona(numer_aktywnego + 1);
      usleep(40000);
      Lacze.Rysuj();
    }

    opadanie(Lacze, drony[numer_aktywnego], pom[2], numer_aktywnego);

    drony[(numer_aktywnego)].zapisz_drona((numer_aktywnego + 1));
    usleep(150000);
    Lacze.Rysuj();
    std::cout << "Koniec lotu zwiadowczego \nWnioski: brak zoltkow na horyzoncie \n";

    break;

  case 'm':

    return menu();

    break;

  case 'k':
    std::cout << "Aktywne wektory: " << vector3d::daj_aktywne() << std::endl;
    std::cout << "Powstałe wektory: " << vector3d::daj_powstale() << std::endl;
    std::cout << "Koniec dzialania programu.\n ";
    return;

    break;

  default:
    std::cout << "Zly wybor !!! \n";
    std::cout << "Mozliwe to w,s,l,m,k,z\n";
    break;
  }
  return menu();
}

double kat_miedzy_wektorami(vector3d sciezka, dron &wiatrak)
{
  double pom1, pom2;
  vector3d v1, v2;
  v1 = wiatrak.daj_wektor(0);
  v2 = wiatrak.daj_wektor(3);

  pom1 = v1[1] - v2[1];
  pom2 = v1[0] - v2[0];

  return (atan(sciezka[1] / sciezka[0]) - atan(pom1 / pom2));
}

bool zapisz_sciezke(const vector3d sciezka, dron &wiatrak)
{
  std::ofstream plik;
  pom = wiatrak.daj_srodek();

  plik.open("../datasets/trasa_przelotu.dat", std::ios::out);
  if (plik.is_open() == false)
  {
    return false;
  }
  plik << pom << "\n";
  pom[2] = sciezka[2];
  plik << pom << "\n";
  pom[2] = pom[2] - sciezka[2];
  pom = sciezka + pom;
  plik << pom << "\n";
  pom[2] = 0;
  plik << pom << "\n";
  pom[0] = 0;
  pom[1] = 0;

  if (plik.fail())
  {
    plik.close();
    return false;
  }
  plik.close();
  return true;
}
