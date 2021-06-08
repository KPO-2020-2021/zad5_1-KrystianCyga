#include <graniastoslup6.hh>


graniastoslup::graniastoslup(){
  
  double tab[3] = {1, 1,1};
  vector3d tmp(tab);

  for(int i;i<12;++i)
  {
    wierzcholek[i]=tmp;
  }
  orientacja=1;
  polozenie=tmp;
}


void graniastoslup::ustaw_srodek(){

  double tab[3] = {1, 1,1};
  vector3d tmp(tab);

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



graniastoslup graniastoslup::obrot(const double kat[], const unsigned int ilosc, const double os[]){
Matrix<4> obrotu;
obrotu.Mobrot_4x4(kat,os);

for(unsigned int i=0;i<ilosc;++i){
  for(int k=0;k<13;++k){
    obrotu*wierzcholek[k];
  }
}
return *this;
}

graniastoslup graniastoslup::owektor(vector3d &wek){
  if (wek.modul() == 0) std::cerr<<"Modul = 0\n";
    
  for (unsigned int i = 0; i < 13; i++)
  {
    wierzcholek[i] = wierzcholek[i] + wek;
  }
  polozenie=polozenie+wek;

  double kat[3]={0,0,5};
  double pozycja[3];
  pozycja[0]=polozenie[0];
  pozycja[1]=polozenie[1];
  pozycja[2]=polozenie[2];
  this->obrot(kat,1,pozycja);

  return *this;
}