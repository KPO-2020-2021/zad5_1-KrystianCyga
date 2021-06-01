#include "sciezka.hh"

/*!
 * \brief Metoda wczytania sciezki z pliku
 *                                                                  
 *     \param[in] nazwa nazwa/sciezka do pliku   
 *     \param[in] this sciezka                                                                                                                
 *     \return poprawnosc operacji                                                              
 */
bool Sciezka::wczytaj(const std::string &nazwa){
std::fstream plik;

  plik.open(nazwa);
  if (plik.is_open() == false)
  {
    return false;
  }

  for (unsigned int i = 0; i < 4; i++)
  {
    plik >> punkty[i];
    if (plik.fail())
    {
      plik.close();
      return false;
    }
  }
  plik.close();
  return true;
}

/*!
 * \brief Metoda zapisu sciezki drona do pliku
 *                                                                  
 *     \param[in] nazwa nazwa/sciezka do pliku
*      \param[in] this sciezka                                                                                                                   
 *     \return poprawnosc operacji                                                              
 */
bool Sciezka::zapis(const std::string &nazwa) const{
  std::ofstream plik;

  plik.open(nazwa, std::ofstream::out);
  if (plik.is_open() == false)
  {
    return false;
  }


  plik << this->punkty[0];
  plik << this->punkty[1];
  plik << this->punkty[2];
  plik << this->punkty[3];
  plik << std::endl;

  if (plik.fail())
  {
    plik.close();
    return false;
  }
  plik.close();
  return true;
}


/*!
 * \brief Dodaje trasę przelotu.
 *
 * Tworzony jest plik z trasę przelotu w postaci łamanej.
 * Nazwa pliku zostaje dodana do łącza do gnuplota.
 * Dzięki temu dane zawarte w tym pliku zostaną użyte przez
 * gnuplota do narysowania łamanej.
 * przelotu drona, lub niepowodzenia zapisu do tego pliku.
 */
void Sciezka::dodajSciezke(PzG::LaczeDoGNUPlota &Lacze,const char* &trasa){
  Lacze.DodajNazwePliku(trasa);
}

