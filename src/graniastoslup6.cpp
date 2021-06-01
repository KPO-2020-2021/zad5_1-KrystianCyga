#include <graniastoslup6.hh>

graniastoslup::graniastoslup(){
  
  double tab[3] = {1, 1,1};
  Vector<double,3> tmp(tab);

  for(int i;i<12;++i)
  {
    wierzcholek[i]=tmp;
  }
  orientacja=1;
  polozenie=tmp;
}


void graniastoslup::ustaw_srodek(){

  double tab[3] = {1, 1,1};
  Vector<double,3> tmp(tab);

  tmp=wierzcholek[8]-wierzcholek[0];
  polozenie=wierzcholek[0]+tmp*0.5;
  }

/*!
 * \brief Metoda wczytania Graniastoslupa z pliku
 *                                                                  
 *     \param[in] nazwa nazwa/sciezka do pliku   
 *     \param[in] this Graniastoslup                                                                                                                
 *     \return poprawnosc operacji                                                              
 */
bool  graniastoslup::wczytaj(const std::string &nazwa){

  std::ifstream plik;

  plik.open(nazwa);
  if (plik.is_open() == false)
  {
    return false;
  }
  
    plik >> wierzcholek[0];
    plik >> wierzcholek[1];
    plik >> wierzcholek[2];
    plik >> wierzcholek[3];

  for (unsigned int i = 4; i < 14; ++++i)
  {
    
    plik >> wierzcholek[0];
    plik >> wierzcholek[i];
    plik >> wierzcholek[i+1];
    plik >> wierzcholek[3];

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
  if (plik.is_open() == false)
  {
    return false;
  }

    plik << wierzcholek[0]<<std::endl;
    plik << wierzcholek[1]<<std::endl;
    plik << wierzcholek[2]<<std::endl;
    plik << wierzcholek[3]<<std::endl;
    plik << std::endl;

  for (unsigned int i = 2; i < 14; ++++i)
  {
    plik << wierzcholek[0]<<std::endl;
    plik << wierzcholek[i]<<std::endl;
    plik << wierzcholek[i+1]<<std::endl;
    plik << wierzcholek[3]<<std::endl;
    plik << std::endl;

    if (plik.fail())
    {
      plik.close();
      return false;
    }
  }
    plik << wierzcholek[0]<<std::endl;
    plik << wierzcholek[1]<<std::endl;
    plik << wierzcholek[2]<<std::endl;
    plik << wierzcholek[3]<<std::endl;
    plik << std::endl;

    if (plik.fail())
    {
      plik.close();
      return false;
    }

  plik.close();
  return true;
}