#include "Prostopadloscian.hh"

/*!
 * \brief Metoda obrotu prostopadloscianu
 *                                                                  
 *     \param[in] punkt numer punktu                                                                                                                  
 *     \return Dany punkt prostopadloscianu                                                              
 */
vector3d &Prostopadloscian::operator[](const int punkt)
{
  return wektor[punkt];
}
/*!
 * \brief Metoda obrotu prostopadloscianu
 *                                                                  
 *     \param[in] punkt numer punktu                                                                                                                  
 *     \return Dany punkt prostopadloscianu                                                              
 */

vector3d Prostopadloscian::operator[](const int punkt) const
{
  return wektor[punkt];
}

/*!
 * \brief Przeciazenie operatora <<
 *                                                                  
 *     \param[in] out strumien wyjsciowy                                                              
 *     \param[in] prost prostopadloscian                                                               
 *     \return strumien  wyjsciowy                                                               
 */
std::ostream &operator<<(std::ostream &out, Prostopadloscian const &prost)
{
  out << std::fixed << std::setprecision(5);
  for (unsigned int i = 0; i < 8; i++)
  {
    out << prost[i] << std::endl;
    if ((i + 1) % 2 == 0)
    {
      out << std::endl;
    }
  }
  out << prost[0] << std::endl;
  out << prost[1] << std::endl;
  return out;
}

/*!
 * \brief Przeciazenie operatora << do zapisu do pliku
 *                                                                  
 *     \param[in] out strumien plikowy                                                              
 *     \param[in] prost prostopadloscian                                                               
 *     \return strumien  plikowy                                                              
 */
std::ofstream &operator<<(std::ofstream &of, Prostopadloscian const &prost)
{
  of << std::setprecision(5) << std::fixed;
  of << prost[0]<< std::endl;
  of << prost[1]<< std::endl;
  of << prost[2]<< std::endl;
  of << prost[3]<< std::endl;
  of << std::endl;
  of << prost[0]<< std::endl;
  of << prost[4]<< std::endl;
  of << prost[5]<< std::endl;
  of << prost[3]<< std::endl;
  of << std::endl;
  of << prost[0]<< std::endl;
  of << prost[6]<< std::endl;
  of << prost[7]<< std::endl;
  of << prost[3]<< std::endl;
  of << std::endl;
  of << prost[0]<< std::endl;
  of << prost[8]<< std::endl;
  of << prost[9]<< std::endl;
  of << prost[3]<< std::endl;
  of << std::endl;
  of << prost[0]<< std::endl;
  of << prost[1]<< std::endl;
  of << prost[2]<< std::endl;
  of << prost[3]<< std::endl;
  of << std::endl;
  return of;
}

/*!
 * \brief Konstruktor klasy Prostopadloscian
 */
Prostopadloscian::Prostopadloscian()
{
  double tab[3] = {0, 0, 1};
  this->wektor[0].zapeln(tab);

  double tab1[3] = {0, 0, 0};
  this->wektor[1].zapeln(tab1);

  double tab2[3] = {1, 0, 1};
  this->wektor[2].zapeln(tab2);

  double tab3[3] = {1, 0, 0};
  this->wektor[3].zapeln(tab3);

  double tab4[3] = {1, 1, 1};
  this->wektor[4].zapeln(tab4);

  double tab5[3] = {1, 1, 0};
  this->wektor[5].zapeln(tab5);

  double tab6[3] = {0, 1, 1};
  this->wektor[6].zapeln(tab6);

  double tab7[3] = {0, 1, 0};
  this->wektor[7].zapeln(tab7);
}

/*!
 * \brief Metoda obrotu prostopadloscianu
 *                                                                  
 *     \param[in] kat kat obrotu                                                              
 *     \param[in] ilosc ilosc operacji
 *     \param[in] os os obrotu                                                         
 *     \return Obrocony prostopadloscian                                                              
 */
Prostopadloscian Prostopadloscian::obrot(const double kat)
{
  Matrix<3> Mrotacji;

  Mrotacji.Mobrot3D_tworzenie(kat,'z');

    for (unsigned int i = 0; i < 10; i++)
    {
      this->wektor[i] = Mrotacji * this->wektor[i];
    }
  

  return *this;
}

Prostopadloscian Prostopadloscian::rotacja(const double kat){
  vector3d pom=daj_srodek();
  owektor_m(pom);
  obrot(kat);
  owektor(pom);
  return *this;
}

bool Prostopadloscian::owektor_m(vector3d &wek){
  vector3d pom;
  pom[0]=-wek[0];
  pom[1]=-wek[1];
  return owektor(pom);
}

Prostopadloscian Prostopadloscian::obrot2(const double kat,vector3d &polozenie){
  
  vector3d WynikObrotu;
  WynikObrotu[2]=0;
  double Kat_rad = (kat * M_PI / 180);
  double sn = sin(Kat_rad), cn = cos(Kat_rad);
  WynikObrotu[0] = polozenie[0] * cn - polozenie[1] * sn;
  WynikObrotu[1] = polozenie[0] * sn + polozenie[1] * cn;
  polozenie[0] = WynikObrotu[0];
  polozenie[1] = WynikObrotu[1];

  for (unsigned int i = 0; i < 10; i++)
    {
      wektor[i] = wektor[i] + WynikObrotu;
    } 
    return *this;
}

/*!
 * \brief Metoda obliczajaca i porownujaca boki prostopadloscianu.
 * Wyswietla ona te dlugosci i okresla czy sa rowne.
 *      \param[in] this Prostopadloscian 
 */
void Prostopadloscian::boki()
{
  double A0, A1, A2, A3, B0, B1, B2, B3, C0, C1, C2, C3;

  A0 = wektor[0].dlugosc(wektor[1]);
  A1 = wektor[2].dlugosc(wektor[3]);
  A2 = wektor[4].dlugosc(wektor[5]);
  A3 = wektor[6].dlugosc(wektor[7]);
  B0 = wektor[1].dlugosc(wektor[3]);
  B1 = wektor[0].dlugosc(wektor[2]);
  B2 = wektor[5].dlugosc(wektor[7]);
  B3 = wektor[4].dlugosc(wektor[6]);
  C0 = wektor[0].dlugosc(wektor[6]);
  C1 = wektor[1].dlugosc(wektor[7]);
  C2 = wektor[2].dlugosc(wektor[4]);
  C3 = wektor[3].dlugosc(wektor[5]);

  

  std::string dlugosc1= "Poprzeczne", dlugosc2= "Krotsze", dlugosc3= "Dluzsze";

  if (A0 > B0 && A0 > C0)
  {
    dlugosc1 = "Dluzsze";
    if (B0 > C0)
    {
      dlugosc2 = "Poprzeczne";
      dlugosc3 = "Krotsze";
    }
    else
    {
      dlugosc3 = "Poprzeczne";
      dlugosc2 = "Krotsze";
    }
  }
  if (B0 > A0 && B0 > C0)
  {
    dlugosc2 = "Dluzsze";
    if (A0 > C0)
    {
      dlugosc1 = "Poprzeczne";
      dlugosc3 = "Krotsze";
    }
    else
    {
      dlugosc3 = "Poprzeczne";
      dlugosc1 = "Krotsze";
    }
  }
  if (C0 > A0 && C0 > C0)
  {
    dlugosc3 = "Dluzsze";
    if (A0 > B0)
    {
      dlugosc1 = "Poprzeczne";
      dlugosc2 = "Krotsze";
    }
    else
    {
      dlugosc2 = "Poprzeczne";
      dlugosc1 = "Krotsze";
    }
  }
  
  if ((abs(A0 - A1) < epsilon) && (abs(A0 - A2) < epsilon) && (abs(A0 - A3) < epsilon))
  {
    std::cout << "  " << dlugosc1 << " boki sa sobie rowne.\n";
  }
  
  std::cout<<std::fixed<<std::setprecision(10);
  std::cout << "   Dlugosc pierwszego boku: " << A0 << "\n";
  std::cout << "   Dlugosc drugiego boku:   " << A1 << "\n";
  std::cout << "   Dlugosc trzeciego boku:  " << A2 << "\n";
  std::cout << "   Dlugosc czwartego boku:  " << A3 << "\n";

  if ((abs(B0 - B1) < epsilon) && (abs(B0 - B2) < epsilon) && (abs(B0 - B3) < epsilon))
  {
    std::cout << "  " << dlugosc2 << " boki sa sobie rowne.\n";
  }
  std::cout << "   Dlugosc pierwszego boku: " << B0 << "\n";
  std::cout << "   Dlugosc drugiego boku:   " << B1 << "\n";
  std::cout << "   Dlugosc trzeciego boku:  " << B2 << "\n";
  std::cout << "   Dlugosc czwartego boku:  " << B3 << "\n";

  if ((abs(C0 - C1) < epsilon) && (abs(C0 - C2) < epsilon) && (abs(C0 - C3) < epsilon))
  {
    std::cout << "  " << dlugosc3 << " boki sa sobie rowne.\n";
  }
  std::cout << "   Dlugosc pierwszego boku: " << C0 << "\n";
  std::cout << "   Dlugosc drugiego boku:   " << C1 << "\n";
  std::cout << "   Dlugosc trzeciego boku:  " << C2 << "\n";
  std::cout << "   Dlugosc czwartego boku:  " << C3 << "\n";
}
/*!
 * \brief Metoda zapisu Prostopadloscianu do pliku
 *                                                                  
 *     \param[in] nazwa nazwa/sciezka do pliku
*      \param[in] this Prostopadloscian                                                                                                                   
 *     \return poprawnosc operacji                                                              
 */
bool Prostopadloscian::zapis(const std::string &nazwa) const
{
  std::ofstream plik;

  plik.open(nazwa, std::ofstream::out);
  if (plik.is_open() == false)
  {
    return false;
  }

  plik << *this;
  if (plik.fail())
  {
    plik.close();
    return false;
  }
  plik.close();
  return true;
}
/*!
 * \brief Metoda wczytania Prostopadlosscianu z pliku
 *                                                                  
 *     \param[in] nazwa nazwa/sciezka do pliku   
 *     \param[in] this Prostopadloscian                                                                                                                
 *     \return poprawnosc operacji                                                              
 */
bool Prostopadloscian::wczytaj(const std::string &nazwa)
{
  std::fstream plik;

  plik.open(nazwa);
  if (plik.is_open() == false)
  {
    return false;
  }

  plik >> wektor[0];
  plik >> wektor[1];
  plik >> wektor[2];
  plik >> wektor[3];
  plik >> wektor[0];
  plik >> wektor[4];
  plik >> wektor[5];
  plik >> wektor[3];
  plik >> wektor[0];
  plik >> wektor[6];
  plik >> wektor[7];
  plik >> wektor[3];
  plik >> wektor[0];
  plik >> wektor[8];
  plik >> wektor[9];
  plik >> wektor[3];

    if (plik.fail())
    {
      plik.close();
      return false;
    }


  plik.close();
  return true;
}

/*!
 * \brief Metoda przesuniecia Prostopadloscianu 
 *                                                                  
 *     \param[in] wek wektor przesuniecia 
 *     \param[in] this Prostopadloscian                                                                                                                 
 *     \return poprawnosc operacji                                                              
 */
bool Prostopadloscian::owektor(vector3d &wek)
{
  if (wek.modul() == 0)
    return false;
  for (unsigned int i = 0; i < 10; i++)
  {
    wektor[i] = wektor[i] + wek;
  }
  return true;
}

void Prostopadloscian::ustal_srodek(){
vector3d tmp;
tmp[0]=0;tmp[1]=0;tmp[2]=0;

    tmp[0] = (wektor[0][0] + wektor[3][0]) / 2;
    tmp[1] = (wektor[0][1] + wektor[3][1]) / 2;
    tmp[2] = wektor[2][2];

polozenie=tmp;
}

vector3d Prostopadloscian::daj_srodek(){
  return polozenie;
}