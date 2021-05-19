// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

#include <iostream>
#include <stdlib.h>
#include "operacje.hh"

int main()
{
  PzG::LaczeDoGNUPlota  Lacze;

  Lacze.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR4);

  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.

  Lacze.UstawZakresX(0, 200);
  Lacze.UstawZakresY(0, 200);
  Lacze.UstawZakresZ(0, 120);


  Lacze.UstawRotacjeXZ(64,65); // Tutaj ustawiany jest widok

  Vector<double,3> Pozycja_drona;
  Pozycja_drona[0]=20;Pozycja_drona[1]=20;Pozycja_drona[2]=0;

  if (!PrzemiescDrona(0,Pozycja_drona)) return 0;


  Lacze.Rysuj();        // Teraz powinno pojawic sie okienko gnuplota
                        // z rysunkiem, o ile istnieje plik "prostopadloscian1.pow"
  std::cout << "Nacisnij ENTER, aby pokazac sciezke przelotu drona " << std::flush;
  std::cin.ignore(10000,'\n');


  if (!DodajTrasePrzelotu(Lacze)) return 1;
  Lacze.Rysuj();


  std::cout << "Nacisnij ENTER, aby wykonac animacje lotu drona " << std::flush;
  std::cin.ignore(10000,'\n');
  if (!AnimacjaLotuDrona(Lacze)) return 1;

  std::cout << std::endl << "Nacisnij ENTER, aby usunac sciezke ... " << std::flush;
  std::cin.ignore(10000,'\n');

  Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
  Lacze.Rysuj();
  
  std::cout << "Nacisnij ENTER, aby zakonczyc ... " << std::flush;
  std::cin.ignore(10000,'\n');
  
}


