#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include "string"
#include <unistd.h>

#include "brylageo.hh"
#include "graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"
#include "Prostopadloscian.hh"

#define PLIK_ROBOCZY__DRON1_KORPUS  "../datasets/PlikRoboczy_Dron1_Korpus.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1  "../datasets/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR2  "../datasets/PlikRoboczy_Dron1_Rotor2.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR3  "../datasets/PlikRoboczy_Dron1_Rotor3.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR4  "../datasets/PlikRoboczy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS  "../datasets/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1  "../datasets/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2  "../datasets/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3  "../datasets/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4  "../datasets/PlikWlasciwy_Dron1_Rotor4.dat"

#define PLIK_ROBOCZY__DRON2_KORPUS  "../datasets/PlikRoboczy_Dron2_Korpus.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR1  "../datasets/PlikRoboczy_Dron2_Rotor1.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR2  "../datasets/PlikRoboczy_Dron2_Rotor2.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR3  "../datasets/PlikRoboczy_Dron2_Rotor3.dat"
#define PLIK_ROBOCZY__DRON2_ROTOR4  "../datasets/PlikRoboczy_Dron2_Rotor4.dat"

#define PLIK_WLASCIWY__DRON2_KORPUS  "../datasets/PlikWlasciwy_Dron2_Korpus.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR1  "../datasets/PlikWlasciwy_Dron2_Rotor1.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR2  "../datasets/PlikWlasciwy_Dron2_Rotor2.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR3  "../datasets/PlikWlasciwy_Dron2_Rotor3.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR4  "../datasets/PlikWlasciwy_Dron2_Rotor4.dat"

/*!
 * \file
 * \brief Ten plik zawiera definicję klasy dron
 */

class dron : brylageo
{
    /*!
    * \brief korpus w postaci prostopadloscianu 
    */
    Prostopadloscian korpus;
    /*!
    * \brief tablica rotorow w postaci graniastoslupow 
    */
    graniastoslup rotor[4];
    /*!
    * \brief srodek graniastoslupa i vektor orientacji 
    */
    vector3d srodek,Vorien;
    public:
    /*!
    * \brief Konstruktor klasy dron
    */
    dron();
    /*!
    * \brief Metoda wczytania z pliku korpusu drona
    *      \param[in] numer_drona -  numer drona
    */
    bool oblicz_zapisz_korpus(const int numer_drona);
    /*!
    * \brief Metoda wczytania z pliku rotora drona
    *      \param[in] numer_drona -  numer drona
    *      \param[in] numer_rotora -  numer rotora
    */
    bool oblicz_zapisz_rotor(const int numer_drona ,const int numer_rotora);
    /*!
    * \brief Metoda przesuniecia drona o dany wektor
    *      \param[in] wek -  wektor
    *      \retval poprawnosc operacji
    */
    bool owektor(vector3d wek);
    /*!
    * \brief Metoda przesuniecia drona o przeciwny niz dany wektor
    *      \param[in] wek -  wektor
    *      \retval poprawnosc operacji
    */
    bool owektor_m(vector3d wek);
    /*!
    * \brief Metoda zapisu do pliku korpusu drona
    *      \param[in] numer_drona -  numer drona
    */
    bool zapisz_dopliku(const int numer_drona);
    /*!
    * \brief Metoda zapisu do pliku rotora drona
    *      \param[in] numer_drona -  numer drona
    *      \param[in] numer_rotora - numer rotora
    */
    bool zapisz_dopliku(const int numer_drona,const int numer_rotora);
    /*!
    * \brief Metoda zapisu do pliku drona
    *      \param[in] numer_drona -  numer drona
    */
    void zapisz_drona(const int numer_drona);
    /*!
    * \brief Metoda ustawiająca rotory w rogach korpusu
    */
    bool tworz_drona();
    /*!
    * \brief Metoda ustawiajaca srodek korpusu
    */
    void ustaw_srodek();
    /*!
    * \brief Metoda zwracajaca srodek drona
    */
    vector3d daj_srodek(){return srodek;}
    /*!
    * \brief Metoda zwracajaca wierzcholek korpusu
    *      \param[in] numer -  numer wierzcholka
    */
    vector3d daj_wektor(const int numer){return korpus[numer];}
    /*!
    * \brief Metoda ustawiajaca orientacje drona
    */
    void ustal_orientacje();
    /*!
    * \brief Metoda zwracajaca orientacje drona
    */
    vector3d daj_orien();
    /*!
    * \brief Metoda dodajaca drona do lacza
    * \param[in] Lacze - lacze do gnuplota
    * \param[in] numer_drona - numer drona
    */
    void dodaj_do_lacza(PzG::LaczeDoGNUPlota& Lacze,const int numer_drona);
    /*!
    * \brief Metoda obracajaca drona o dany kat
    * \param[in] kat - kat obrotu
    */
    void obrot(const double kat);

};
    /*!
    * \brief Funkcja lotu dronem w danym kierunku
    * \param[in] Lacze - lacze do gnuplota
    * \param[in] latawiec - dron
    * \param[in] kat - kierunek lotu
    * \param[in] odleglosc - dlugosc lotu
    * \param[in] numer - numer drona
    */
void lot_do_przodu(PzG::LaczeDoGNUPlota& Lacze,dron &latawiec,const double kat,const double odleglosc,int numer);
    /*!
    * \brief Funkcja lotu dronem w gore
    * \param[in] Lacze - lacze do gnuplota
    * \param[in] latawiec - dron
    * \param[in] wysokosc - wysokosc wznoszenia
    * \param[in] numer - numer drona
    */
void wznoszenie(PzG::LaczeDoGNUPlota& Lacze,dron &latawiec,const double wysokosc,const int numer);
    /*!
    * \brief Funkcja lotu dronem w dol
    * \param[in] Lacze - lacze do gnuplota
    * \param[in] latawiec - dron
    * \param[in] wysokosc - wysokosc opadania
    * \param[in] numer - numer drona
    */
void opadanie(PzG::LaczeDoGNUPlota& Lacze,dron &latawiec,const double wysokosc,const int numer);


