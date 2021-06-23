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
double kat_miedzy_wektorami (vector3d &pierwszy,vector3d &drugi);
bool zapisz_sciezke(const vector3d sciezka,dron &wiatrak);

dron drony[2];
vector3d sciezka,versor;
PzG::LaczeDoGNUPlota Lacze;
unsigned int numer_aktywnego;
vector3d tmp,pom,pom2;
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
  drony[0].dodaj_do_lacza(Lacze,1);
  drony[1].dodaj_do_lacza(Lacze,2);
  

  drony[0].ustaw_srodek();
  drony[1].ustaw_srodek();

    menu();

}

void menu()
{ 
      
      
       char wyb;
       double stopnie,odleglosc,wysokosc;
       std::cout << "\n"
                 << "************************MENU************************\n";
       std::cout << "  w-wybor drona\n";
       std::cout << "  s-podanie sciezki drona\n";
       std::cout << "  l-lot drona\n";
       std::cout << "  m-powrot do menu\n";
       std::cout << "  k-koniec dzialania programu\n";
       std::cout << "  Twoj wybor -> :";
       std::cin >> wyb;
       std::cout << "\n";

       switch (wyb)
       {

       case 'w':
              std::cout << "Podaj numer drona: ";
              std::cin>>numer_aktywnego;
              numer_aktywnego=numer_aktywnego-1;
              drony[numer_aktywnego].ustaw_srodek();
              drony[numer_aktywnego].ustal_orientacje();
              break;

       case 's':
              std::cout << "\nPodaj sciezke drona (x,y,z) :";
              std::cin>>sciezka[0]>>sciezka[1]>>sciezka[2];
              zapisz_sciezke(sciezka,drony[numer_aktywnego]);
              
              pom=drony[numer_aktywnego].daj_orien();
              kat=kat_miedzy_wektorami(pom,sciezka);
              std::cout <<kat*360/M_PI;

              break;

       case 'l':
       
              wysokosc=sciezka[2];
              Lacze.Rysuj();
              if (numer_aktywnego==0)
              {wznoszenie(Lacze,drony[0],wysokosc,1);}
              else if(numer_aktywnego==1)
              {wznoszenie(Lacze,drony[1],wysokosc,2);}

              
              pom=drony[numer_aktywnego].daj_orien();
              kat=kat_miedzy_wektorami(pom,sciezka);
              tmp[0]=sciezka[0];
              tmp[1]=sciezka[1];
              stopnie = kat*360/M_PI;
              
              pom2=drony[numer_aktywnego].daj_srodek();

              for (int i = 0; i < stopnie; i++)
              {
              drony[numer_aktywnego].owektor_m(pom2);
              drony[numer_aktywnego].obrot(5);
              drony[numer_aktywnego].owektor(pom2);
              drony[numer_aktywnego].zapisz_drona(numer_aktywnego);
              usleep(150000);
              Lacze.Rysuj();
              }

              sciezka[2]=0;
              odleglosc=sciezka.modul();
              lot_do_przodu(Lacze,drony[numer_aktywnego],kat,odleglosc,numer_aktywnego-1);
              
              opadanie(Lacze,drony[numer_aktywnego],wysokosc,numer_aktywnego-1);
              

              drony[numer_aktywnego].zapisz_drona(numer_aktywnego);
              usleep(150000);
              Lacze.Rysuj();
              
              
        break;



       case 'm':

              return menu();

              break;

       case 'k':
              std::cout << "Koniec dzialania programu.\n ";
              return;

              break;

       default:
              std::cout << "Zly wybor !!! \n";
              std::cout << "Mozliwe to w,s,l,m,k\n";
              break;
       }
       return menu();
}

double kat_miedzy_wektorami (vector3d &pierwszy,vector3d &drugi){
  double kat,pom1,pom2;
  pom1=pierwszy[0]*drugi[0];
  pom2=pierwszy[1]*drugi[1];
  kat=(pom1+pom2)/(pierwszy.modul()*drugi.modul());
  return acos(kat);

}

bool zapisz_sciezke(const vector3d sciezka,dron &wiatrak){
std::ofstream plik;
pom=wiatrak.daj_srodek();

plik.open("../datasets/trasa_przelotu.dat",std::ios::out);
if (plik.is_open() == false)
  {
    return false;
  }
plik<<pom<<"\n";
pom[2]=sciezka[2];
plik<<pom<<"\n";
pom[2]=pom[2]-sciezka[2];
pom=sciezka+pom;
plik<<pom<<"\n";
pom[2]=0;
plik<<pom<<"\n";
pom[0]=0;
pom[1]=0;


if (plik.fail())
  {
    plik.close();
    return false;
  }
  plik.close();
  return true;

}

