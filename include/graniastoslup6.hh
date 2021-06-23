#pragma once

#include "brylageo.hh"

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy graniastoslup
 */
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
    /*!
    *       \brief Metoda wczytujaca rotor z danego pliku
    *      \param[in] nazwa - nazwa pliku
    */
    bool wczytaj(const std::string &nazwa);
    /*!
    *       \brief Metoda zapisujaca rotor do danego pliku
    *      \param[in] nazwa - nazwa pliku
    */
    bool zapis(const std::string &nazwa) const;
    /*!
    * \brief Metoda przesuniecia graniastoslupa o dany wektor
    *      \param[in] wek -  wektor
    *      \retval graniastoslup
    */
    graniastoslup owektor(vector3d wek);
    /*!
    * \brief Metoda przesuniecia graniastoslupa przeciwny niz dany wektor
    *      \param[in] wek -  wektor
    *      \retval graniastoslup
    */
    graniastoslup owektor_m(vector3d wek);
    /*!
    * \brief Metoda obrotu graniastoslupa o dany kat
    *      \param[in] kat -  kat obrotu
    *      \retval graniastoslup
    */
    graniastoslup obrot(const double kat);
    graniastoslup rotacja(const double kat);
    /*!
    * \brief Metoda zwracajaca srodek graniastoslupa
    */
    vector3d daj_srodek();
};