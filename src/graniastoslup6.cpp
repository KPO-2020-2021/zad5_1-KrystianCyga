#include <graniastoslup6.hh>

void graniastoslup::ustaw_srodek()
{
  polozenie[0] = (wierzcholek[8][0] + wierzcholek[1][0]) / 2;
  polozenie[1] = (wierzcholek[8][1] + wierzcholek[1][1]) / 2;
  polozenie[2] = wierzcholek[2][2] / 2;
}

graniastoslup::graniastoslup()
{

  double tab[3] = {0, 0, 0};
  vector3d tmp(tab);

  for (int i; i < 13; ++i)
  {
    wierzcholek[i] = tmp;
  }
    skala[0] = 8;
    skala[1] = 8;
    skala[2] = 2;
  orientacja = 1;
  ustaw_srodek();
}

/*!
 * \brief Metoda wczytania Graniastoslupa z pliku
 *                                                                  
 *     \param[in] nazwa nazwa/sciezka do pliku   
 *     \param[in] this Graniastoslup                                                                                                                
 *     \return poprawnosc operacji                                                              
 */
bool graniastoslup::wczytaj(const std::string &nazwa)
{

  std::ifstream plik;

  plik.open(nazwa);
  if (plik.is_open() == false)
  {
    return false;
  }
  vector3d elo;

  plik >> wierzcholek[0];
  plik >> wierzcholek[1];
  plik >> wierzcholek[2];
  plik >> wierzcholek[3];

  plik >> elo;
  plik >> wierzcholek[4];
  plik >> wierzcholek[5];
  plik >> elo;

  plik >> elo;
  plik >> wierzcholek[6];
  plik >> wierzcholek[7];
  plik >> elo;

  plik >> elo;
  plik >> wierzcholek[8];
  plik >> wierzcholek[9];
  plik >> elo;

  plik >> elo;
  plik >> wierzcholek[10];
  plik >> wierzcholek[11];
  plik >> elo;

  plik >> elo;
  plik >> wierzcholek[12];
  plik >> wierzcholek[13];
  plik >> elo;

  plik >> elo;
  plik >> elo;
  plik >> elo;
  plik >> elo;

  if (plik.fail())
  {
    plik.close();
    return false;
  }
  ustaw_srodek();

  plik.close();
  ustaw_srodek();
  return true;
}

/*!
 * \brief Metoda zapisu graniastoslupa do pliku
 *                                                                  
 *     \param[in] nazwa nazwa/sciezka do pliku
*      \param[in] this Graniastoslup                                                                                                                   
 *     \return poprawnosc operacji                                                              
 */
bool graniastoslup::zapis(const std::string &nazwa) const
{
  std::ofstream plik;

  plik.open(nazwa, std::ofstream::out);
  plik << std::setprecision(5) << std::fixed;
  if (plik.is_open() == false)
  {
    return false;
  }

  plik << wierzcholek[0] << std::endl;
  plik << wierzcholek[1] << std::endl;
  plik << wierzcholek[2] << std::endl;
  plik << wierzcholek[3] << std::endl;
  plik << std::endl;

  plik << wierzcholek[0] << std::endl;
  plik << wierzcholek[4] << std::endl;
  plik << wierzcholek[5] << std::endl;
  plik << wierzcholek[3] << std::endl;
  plik << std::endl;

  plik << wierzcholek[0] << std::endl;
  plik << wierzcholek[6] << std::endl;
  plik << wierzcholek[7] << std::endl;
  plik << wierzcholek[3] << std::endl;
  plik << std::endl;

  plik << wierzcholek[0] << std::endl;
  plik << wierzcholek[8] << std::endl;
  plik << wierzcholek[9] << std::endl;
  plik << wierzcholek[3] << std::endl;
  plik << std::endl;

  plik << wierzcholek[0] << std::endl;
  plik << wierzcholek[10] << std::endl;
  plik << wierzcholek[11] << std::endl;
  plik << wierzcholek[3] << std::endl;
  plik << std::endl;

  plik << wierzcholek[0] << std::endl;
  plik << wierzcholek[12] << std::endl;
  plik << wierzcholek[13] << std::endl;
  plik << wierzcholek[3] << std::endl;
  plik << std::endl;

  if (plik.fail())
  {
    plik.close();
    return false;
  }
  plik << wierzcholek[0] << std::endl;
  plik << wierzcholek[1] << std::endl;
  plik << wierzcholek[2] << std::endl;
  plik << wierzcholek[3] << std::endl;
  plik << std::endl;

  if (plik.fail())
  {
    plik.close();
    return false;
  }

  plik.close();
  return true;
}

graniastoslup graniastoslup::obrot(const double kat)
  {
  Matrix<3> Mrotacji;
  ustaw_srodek();
  Mrotacji.Mobrot3D_tworzenie(kat,'z');

    for (unsigned int i = 0; i < 14; i++)
    {
      wierzcholek[i] = Mrotacji *wierzcholek[i];
    }
    return *this;
}

graniastoslup graniastoslup::rotacja(const double kat){
  ustaw_srodek();
  vector3d pom=daj_srodek();
  pom[2]=0;
  owektor_m(pom);
  obrot(kat);
  owektor(pom);
  return *this;
}

graniastoslup graniastoslup::owektor(vector3d wek)
{
  for (unsigned int i = 0; i < 14; i++)
  {
    wierzcholek[i] = wierzcholek[i] + wek;
  }
  polozenie = polozenie + wek;
  return *this;
}

graniastoslup graniastoslup::owektor_m(vector3d wek){
  vector3d pom;
  pom[0]=-wek[0];
  pom[1]=-wek[1];
  return owektor(pom);
}


vector3d graniastoslup::daj_srodek()
{
  ustaw_srodek();
  return polozenie;
}