#pragma once

#include "brylageo.hh"

class graniastoslup : public brylageo
{
    /*!
    * \brief Wektor bedacy srodkiem symetrii wierzcholkow graniastoslupa 
    */
    Vector<double,3> polozenie;
    double orientacja;
    /*!
    * \brief Wektory bedace wierzcholkami graniastoslupa 
    */
    Vector<double,3> wierzcholek[14];

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

};