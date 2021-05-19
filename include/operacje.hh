#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>

#include "vector.hh"
#include "matrix.hh"
#include "lacze_do_gnuplota.hh"

#define PLIK_WZORCOWEGO_SZESCIANU       "bryly_wzorcowe/szescian.dat"
#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "bryly_wzorcowe/graniastoslup6.dat"
#define PLIK_KORPUSU_DRONA1             "datasets/korpus_drana1.dat"
#define ILOSC_WIERZ_LINII_TWORZACEJ            4

/*!
 * \brief Transformuje współrzędne pojedynczego punktu.
 * 
 * Transformuje współrzędne pojedynczego punktu poprzez ich przeskalowanie i 
 * przesunięcie o zdany wektor translacji. Współczynniki skalowania jak też
 * współrzędne wektora translacji są przekazywane przez parametry tej funkcji.
 *
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona
 *                           jest w stopniach.
 * \param[in,out]  wektor3d - wspolrzedne punkty w postaci wektora, które maja zostać poddane transformacji.
 * \param[in]      skala - współczynniki skalowania wzdłuż osi w postaci wektora.
 * \param[in]      translacji - współrzędne wektora translacji.
 */
void transformuj_punkt
(
				  double  KatObrotu_st,
				  Vector<double,3> &wektor3d,
				  Vector<double,3> &skala,
		          Vector<double,3> &translacji
)
{
Matrix<3> macierz_obr;
macierz_obr.Mobrot3D_tworzenie(KatObrotu_st,'z');
wektor3d=macierz_obr*wektor3d;
wektor3d[0]=wektor3d[0]*skala[0] + translacji[0];
wektor3d[1]=wektor3d[1]*skala[1] + translacji[1];
wektor3d[2]=wektor3d[2]*skala[2] + translacji[2];
}


/*!
 * \brief  Transformuje całą bryłę.
 *
 *  Czyta ze strumienia wejściowego współrzędne wierzchołków bryły, dokonuje 
 *  ich transformacji (skalowanie, obrót i translacja)
 *  Zapisuje do strumienia współrzędne wierzchołków przetransformowanej bryły
 *  w ten sposób, aby mogły korpus mógł być poprawnie narysowany przez program gnuplot.
 *  \param[in,out] StrmWe_DaneWejsciowe - strumień zawierający opis bryły, która ma podlegać
 *                                        transformacji. Współrzędne z tego strumienia są
 *                                        tylko czytane.
 *  \param[in,out] StrmWy_DaneWynikowe - strumień zawierający opis bryły po dokonanej tranformacji.
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona
 *                           jest w stopniach.
 * \param[in]      skala - współczynniki skalowania wzdłuż osi w postaci wektora.
 * \param[in]      translacji - współrzędne wektora translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu
 *                 niepowodzenia odczytu lub zapisu do strumienia.
 */
bool TworzOpisPrzetransformowanejBryly
(
			   std::istream   &StrmWe_DaneWejsciowe,
			   std::ostream   &StrmWy_DaneWynikowe,
			   double KatObrotu_st,
               Vector<double,3> &skala,
		       Vector<double,3> &translacji
)
{
  assert(StrmWe_DaneWejsciowe.good());
  assert(StrmWy_DaneWynikowe.good());

    Vector<double,3> wektor;

    StrmWe_DaneWejsciowe >> wektor;

    while (!StrmWe_DaneWejsciowe.fail()) {

    for (unsigned int IloscWierzcholkow = 0; IloscWierzcholkow < ILOSC_WIERZ_LINII_TWORZACEJ;
	 ++IloscWierzcholkow) {

      transformuj_punkt( KatObrotu_st,
				    wektor,
                    skala,
				    translacji
			        );
      StrmWy_DaneWynikowe << wektor[0] << " " << wektor[1] << " " << wektor[2] << std::endl;
      StrmWe_DaneWejsciowe >> wektor;
      
      assert(IloscWierzcholkow == ILOSC_WIERZ_LINII_TWORZACEJ-1 || !StrmWe_DaneWejsciowe.fail());
    }

    StrmWy_DaneWynikowe << std::endl;
  }
  return !StrmWy_DaneWynikowe.fail();
}

/*!
 * \brief  Transformuje całą bryłę.
 *
 *  Czyta z pliku wejściowego współrzędne wierzchołków bryły, dokonuje 
 *  ich transformacji (skalowanie, obrót i translacja)
 *  Zapisuje do drugiego pliku współrzędne wierzchołków przetransformowanej bryły
 *  w ten sposób, aby mogły korpus mógł być poprawnie narysowany przez program gnuplot.
 *  \param[in,out] NazwaPliku_DaneWejsciowe - nazwa pliku zawierający opis bryły, która ma podlegać
 *                                        transformacji. Współrzędne z tego strumienia są
 *                                        tylko czytane.
 *  \param[in,out] NazwaPliku_DaneWynikowe - nazwa pliku, który ma zawierać opis bryły
 *                                         po dokonanej tranformacji.
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona
 *                           jest w stopniach.
 * \param[in]      skala - współczynniki skalowania wzdłuż osi w postaci wektora.
 * \param[in]      translacji - współrzędne wektora translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool TworzOpisPrzetranformowanejBryly(
		      const char*   NazwaPliku_DaneWejsciowe,
  		      const char*   NazwaPliku_DaneWynikowe,
		      double KatObrotu_st,
               Vector<double,3> &skala,
		       Vector<double,3> &translacji
		     )
{
 std::ifstream  Plik_BrylaWzorcowa(NazwaPliku_DaneWejsciowe);
 std::ofstream  Plik_KorpusuDrona(NazwaPliku_DaneWynikowe);

  
  if (!Plik_BrylaWzorcowa.is_open()) {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << NazwaPliku_DaneWejsciowe << std::endl
	 << std::endl;
    return false;
  }

  if (!Plik_KorpusuDrona.is_open()) {
    std::cerr << std::endl
	 << " Blad otwarcia do odczytu pliku: " << NazwaPliku_DaneWynikowe << std::endl
	 << std::endl;
    return false;
  }
  
  return TworzOpisPrzetransformowanejBryly(
				Plik_BrylaWzorcowa,
				Plik_KorpusuDrona,
				KatObrotu_st,
			    skala,
			    translacji
                                            );
}

/*!
 * \brief Tworzy plik z wierzchołkami były modelującej rotor drona.
 *
 * Tworzy plik, w którym zostają zapise współrzędne wierzchołków
 * tworzących pojedynczy rotor drona. Zapisane one są w ten sposób, aby program gnuplot
 * mógł wyświetlić graniastosłubp Tworzona bryła zostaje obrócona
 * względem swojej pierwotnej orientacji o zadany kąt oraz przesunięta o wektor
 * translacji, którego współrzędne podane są jako parametry tej funkcji.
 *
 * \param[in] NazwPliku_RotorWDronie - nazwa pliku, w którym zostaną zapisane współrzędne
 *                                       wierzchołków bryły tworzącej rotor drona.
 * \param[in] KatObrotuRotora_st - kąt obrotu korpusu. Jego wartość wyrażona jest w stopniach.
 * \param[in] translacji - współrzędne wektora translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool TworzRotor(const char*  NazwPliku_RotorWDronie,
                double    KatObrotuRotora_st,
		        Vector<double,3> &translacji
	            )
{
Vector<double,3> skala_rotora;
skala_rotora[0]=8;
skala_rotora[1]=8;
skala_rotora[2]=2;
 return TworzOpisPrzetranformowanejBryly(PLIK_WZORCOWEGO_GRANIASTOSLUPA6,
                                        NazwPliku_RotorWDronie,
					KatObrotuRotora_st,
				    skala_rotora,
					translacji);
}

/*!
 * \brief Tworzy plik z wierzchołkami były modelującej korpus drona.
 *
 * Tworzy plik, w którym zostają zapise współrzędne wierzchołków
 * tworzących korpus drona. Zapisane one są w ten sposób, aby program gnuplot
 * mógł wyświetlić prostopadłościan. Tworzona bryła zostaje obrócona
 * względem swojej pierwotnej orientacji o zadany kąt oraz przesunięta o wektor
 * translacji, którego współrzędne podane są jako parametry tej funkcji.
 *
 * \param[in] NazwPliku_KorpusuWDronie - nazwa pliku, w którym zostaną zapisane współrzędne
 *                                       wierzchołków bryły tworzącej korpus drona.
 * \param[in] KatObrotuKorpusu_st - kąt obrotu korpusu. Jego wartość wyrażona jest w stopniach.
 * \param[in] translacji - współrzędne wektora translacji.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku. 
 */
bool TworzKorpus(const char*  NazwPliku_KorpusuWDronie,
                 double       KatObrotuKorpusu_st,
		         Vector<double,3> &translacji
	        )
{
Vector<double,3> skala_korpusu;
skala_korpusu[0]=8;
skala_korpusu[1]=8;
skala_korpusu[2]=2;
  
 return TworzOpisPrzetranformowanejBryly(PLIK_WZORCOWEGO_SZESCIANU,
                                        NazwPliku_KorpusuWDronie,
					KatObrotuKorpusu_st,
				        skala_korpusu,
				        translacji);
}

#define PLIK_ROBOCZY__DRON1_KORPUS  "dat/PlikRoboczy_Dron1_Korpus.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1  "dat/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR2  "dat/PlikRoboczy_Dron1_Rotor2.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR3  "dat/PlikRoboczy_Dron1_Rotor3.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR4  "dat/PlikRoboczy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS  "dat/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1  "dat/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2  "dat/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3  "dat/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4  "dat/PlikWlasciwy_Dron1_Rotor4.dat"

/*!
 * \brief Tworzy pliku pozwalające na wizualizację drona.
 * 
 * Zapisuje do odpwiednich plików opisy brył tworzących wizualizację drona.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - gdy operacja nie powiedzie się z powodu braku możliwości 
 *                 otwarcia jednego z plików lub niepowodzenia odczytu lub zapisu do pliku.
 */
bool TworzDrona()
{
  static double KatObrotuRotora_st = 0; 
Vector<double,3> wektor_trans_LP,wektor_trans_PP,wektor_trans_LT,wektor_trans_PT,wektor_trans_korpusu;
wektor_trans_LP[0]=5; wektor_trans_LP[1]=4;wektor_trans_LP[2]=5;
wektor_trans_PP[0]=5; wektor_trans_PP[1]=-4;wektor_trans_PP[2]=5;
wektor_trans_LT[0]=-5; wektor_trans_LT[1]=4;wektor_trans_LT[2]=5;
wektor_trans_PT[0]=-5; wektor_trans_PT[1]=-4;wektor_trans_PT[2]=5;  

  //----------------------------------------------------------
  // Korpus drona jest podniesiony o 4. Dzięki temu początek układu
  // współrzędnych drona jest na środku dolnej podstawy korpusu.
  //
  wektor_trans_korpusu[0]=0;wektor_trans_korpusu[1]=0;wektor_trans_korpusu[2]=2;

  if (!TworzKorpus(PLIK_ROBOCZY__DRON1_KORPUS,0,wektor_trans_korpusu)) return false;

  if (!TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR1,
		    KatObrotuRotora_st,wektor_trans_LP)) return false;
  if (!TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR2,
		    -KatObrotuRotora_st,wektor_trans_PP)) return false;
  if (!TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR3,
		    -KatObrotuRotora_st,wektor_trans_LT)) return false;
  if (!TworzRotor(PLIK_ROBOCZY__DRON1_ROTOR4,
		     KatObrotuRotora_st,wektor_trans_PT)) return false;
#define SKOK_OBROTU_ROTOROW_stopnie  10
  KatObrotuRotora_st += SKOK_OBROTU_ROTOROW_stopnie;
  return true;
}

/*!
 * \brief Ustawia dron w żądanej pozycji i orientacji.
 *
 * Dron zostaje przeniesiony do wskazanej pozycji. Jego orientacja zostaje zmieniona
 * zgodnie z zadanym kątem.
 *
 * \param[in] KatOrDrona_st - kąta orientacji drona. Jest to kąt względem osi OZ.
 *                            Wartość orientacji drona wyrażona jest w stopniach.
 * \param[in] Pozycja_drona - współrzędne pozycji drona.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy niepowiedzie się otwarcie jednego z plików,
 *                 z których korzysta ta funkcja,
 *                 lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
 */
bool PrzemiescDrona(double KatOrDrona_st, Vector<double,3> &Pozycja_drona)
{
Vector<double,3> wektor_jednostkowy;
  wektor_jednostkowy[0]=1; wektor_jednostkowy[1]=1;wektor_jednostkowy[2]=1;

  if (!TworzDrona()) return false;
  //--------------------------------------------------
  // Transformacja elementów drona do właściwej pozycji
  //
  const char *NazwyPlikowRoboczych[] = { PLIK_ROBOCZY__DRON1_KORPUS, PLIK_ROBOCZY__DRON1_ROTOR1,
					 PLIK_ROBOCZY__DRON1_ROTOR2, PLIK_ROBOCZY__DRON1_ROTOR3,
					 PLIK_ROBOCZY__DRON1_ROTOR4, nullptr
                                        };
  const char *NazwyPlikowWlasciwych[] = { PLIK_WLASCIWY__DRON1_KORPUS, PLIK_WLASCIWY__DRON1_ROTOR1,
					 PLIK_WLASCIWY__DRON1_ROTOR2, PLIK_WLASCIWY__DRON1_ROTOR3,
					 PLIK_WLASCIWY__DRON1_ROTOR4, nullptr
                                        };
  
  assert(sizeof(NazwyPlikowRoboczych) == sizeof(NazwyPlikowWlasciwych));

  for (unsigned int Idx = 0; NazwyPlikowRoboczych[Idx] != nullptr; ++Idx) {
    if (!TworzOpisPrzetranformowanejBryly(NazwyPlikowRoboczych[Idx],
					 NazwyPlikowWlasciwych[Idx],
					 KatOrDrona_st,
				     wektor_jednostkowy,
				     Pozycja_drona)) return false;
  }
  return true;
}


#define PLIK_TRASY_PRZELOTU "dat/trasa_przelotu.dat"

/*!
 * \brief Dodaje trasę przelotu.
 *
 * Tworzony jest plik z trasę przelotu w postaci łamanej.
 * Nazwa pliku zostaje dodana do łącza do gnuplota.
 * Dzięki temu dane zawarte w tym pliku zostaną użyte przez
 * gnuplota do narysowania łamanej.
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy niepowiedzie się otwarcie plików,
 *                 do którego zapisywane są współrzędne łamanej modelującej ścieżkę
 *                 przelotu drona, lub niepowodzenia zapisu do tego pliku.
 */
bool DodajTrasePrzelotu(PzG::LaczeDoGNUPlota &Lacze)
{
  std::ofstream  StrmWy(PLIK_TRASY_PRZELOTU);

  if (!StrmWy.is_open()) {
    std::cerr << std::endl
	 << " Nie mozna otworzyc do zapisu pliku: " << PLIK_TRASY_PRZELOTU << std::endl
	 << std::endl;
    return false;
  }

  StrmWy << "20  20   0" << std::endl
	 << "20  20  80" << std::endl
	 << "150 150 80" << std::endl
	 << "150 150  0" << std::endl;
  Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
  return !StrmWy.fail();
}

/*!
 * \brief Anicja przelotu drona.
 *
 * Animacja przelotu drona.
 * Animacja ta jest robiona na "sztywno"
 *
 * \retval true - gdy operacja powiedzie się,
 * \retval false - w przypadku przeciwnym.
 *                 Może się to zdarzyć, gdy niepowiedzie się otwarcie jednego z plików,
 *                 z których korzysta ta funkcja,
 *                 lub niepowodzenia odczytu lub zapisu do wspomnianych plików.
 */
bool AnimacjaLotuDrona(PzG::LaczeDoGNUPlota &Lacze)
{
  Vector<double,3> pozycja_drona;
  pozycja_drona[0] = 20; pozycja_drona[1] = 20; pozycja_drona[2] = 0;
  double KatOr_st = 0;

  //-------------------------------------
  // Wznoszenie ...
  //
  std::cout << std::endl << "Wznoszenie ... " << std::endl;
  for (; pozycja_drona[2] <= 80; pozycja_drona[2] += 2) {
    if (!PrzemiescDrona(KatOr_st,pozycja_drona)) return false;
    usleep(100000); // 0.1 ms
    Lacze.Rysuj();
  }
  pozycja_drona[2] -= 2;
  
  std::cout << "Zmiana orientacji ... " << std::endl;
  for (; KatOr_st <= 45; KatOr_st += 5) {
    if (!PrzemiescDrona(KatOr_st,pozycja_drona)) return false;
    usleep(100000);
    Lacze.Rysuj();
  }
  KatOr_st -= 5;

  //-------------------------------------
  // Lot do przodu ...
  //  
  std::cout << "Lot do przodu ... " << std::endl;
  for (; pozycja_drona[0] <= 150; pozycja_drona[0] += 1, pozycja_drona[2] += 1) {
    if (!PrzemiescDrona(KatOr_st,pozycja_drona)) return false;
    usleep(100000);
    Lacze.Rysuj();
  }  
  pozycja_drona[0] -= 1, pozycja_drona[2] -= 1;


  //-------------------------------------
  // Opadanie ...
  //
  std::cout << "Opadanie ... " << std::endl;
  for (; pozycja_drona[2] >= 0; pozycja_drona[2] -= 2) {
    if (!PrzemiescDrona(KatOr_st,pozycja_drona)) return false;
    usleep(100000); // 0.1 ms
    Lacze.Rysuj();
  }

  return true;
}







