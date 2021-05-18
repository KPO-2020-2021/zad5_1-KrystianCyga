#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>

#include "vector.hh"
#include "matrix.hh"

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




