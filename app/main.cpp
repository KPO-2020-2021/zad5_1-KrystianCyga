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

void menu();

dron drony[2];
vector3d sciezka,versor;
PzG::LaczeDoGNUPlota Lacze;

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

  Lacze.DodajNazwePliku("../datasets/plaszczyzna.dat");
  //Lacze.DodajNazwePliku("../datasets/trasa_przelotu.dat");
  drony[0].dodaj_do_lacza(Lacze,1);
  drony[1].dodaj_do_lacza(Lacze,2);

    menu();

        /*
  std::cin.ignore(10000, '\n');
  Lacze.Rysuj();

  std::cin.ignore(10000, '\n');
  Lacze.Rysuj();
  usleep(200000);

    vector3d jednosciZ;
    jednosciZ[0] = 0;
    jednosciZ[1] = 0;
    jednosciZ[2] = 1;

    usleep(200000);

    for (int i; i < 10; i++)
    {
        drony[0].owektor(jednosciZ);
        drony[0].zapisz_drona(1);
        
        usleep(150000);
      
        Lacze.Rysuj();
    }  
    jednosciZ[0] = 1;
    jednosciZ[1] = 1;
    jednosciZ[2] = 0;

    for (int i; i < 10; i++)
    {
        drony[0].owektor(jednosciZ);
        drony[0].zapisz_drona(1);
        
        usleep(150000);
      
        Lacze.Rysuj();
    } 

    std::cin.ignore(10000, '\n');
    drony[0].ustaw_srodek();
    vector3d poloz,trans,mtrans;
    
    trans[0]=-10;mtrans[0]=trans[0]*-1;
    trans[1]=-10;mtrans[1]=trans[1]*-1;
    trans[2]=-10;mtrans[2]=trans[2]*-1;

    drony[0].owektor(trans);
    drony[0].obrot(30);
    drony[0].owektor(mtrans);
    
    drony[0].zapisz_drona(1);
    Lacze.Rysuj();
    std::cin.ignore(10000, '\n');
  
  std::cin.ignore(10000, '\n');
        */
}

void menu()
{ 
      int numer_aktywnego;
      
       char wyb;
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
              break;

       case 's':
              std::cout << "\nPodaj sciezke drona (x,y,z) :";
              std::cin>>sciezka[0]>>sciezka[1]>>sciezka[2];
              break;

       case 'l':
              Lacze.Rysuj();
              if (numer_aktywnego==1)
              {wznoszenie(Lacze,drony[0],sciezka[2],1);}
              else 
              {wznoszenie(Lacze,drony[1],sciezka[2],2);}
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

