#pragma once

#include "brylageo.hh"

class graniastoslup : public brylageo
{
    /*!
    * \brief Wektor bedacy srodkiem symetrii wierzcholkow graniastoslupa 
    */
    vector3d polozenie;
    double orientacja;
    /*!
    * \brief Wektory bedace wierzcholkami graniastoslupa 
    */
    vector3d wierzcholek[14];

    public:

/*!
 *  \brief Konstruktor bezparametryczny klasy graniastoslup.                                                                                                           
 *     \post Zwraca dwanascie wiercholkow  1,1,1                                 
 */
    graniastoslup();
/*!
 *  \brief Metoda ustawiajaca punkt centralny graniastoslupa                                                                                                           
 *                                   
 */
    void ustaw_srodek();
    bool wczytaj(const std::string &nazwa);
    bool zapis(const std::string &nazwa) const;
    graniastoslup owektor(vector3d wek);
    graniastoslup owektor_m(vector3d wek);
    graniastoslup obrot(const double kat);
    graniastoslup rotacja(const double kat);

    vector3d daj_srodek();
};