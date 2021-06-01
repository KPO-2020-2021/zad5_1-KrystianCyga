#pragma once

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>
#include <fstream>

#include "vector.hh"


class brylageo
{
protected:
    /*!
    * \brief Zmienna zliczająca aktualnie istniejące obiketu typu brylageo.
    */
    static int ObAkt;

   /*!
    * \brief Zmienna zliczająca ogólnie stworzone obiekty typu brylageo.
    */
    static int ObOgol;

std::string NazwaPlikuBrylyWzorc;
std::string NazwaPlikubryluFinalnej;
/*! 
* \brief Skala figury w postaci wektora
*/
Vector<double,3> skala;

public:
/*!
 * \brief Konstruktor bezparamereyczny klasy brylageo
 * ustawia nazwy na null
 * skale na 1,1,1
 */
brylageo();
/*!
 * \brief Konstruktor paramereyczny klasy brylageo
 *      \param[in] nazwa1 -  nazwa pliku wzorcowego z klasy brylageo
 *      \param[in] nazwa1 -  nazwa pliku bryfy filanej z klasy brylageo
 *      \param[in] skala -  skala z klasy brylageo
 *      \post Ustawia nazwy na odpowiednie podane przez uzytkownika
 */
brylageo(const std::string &nazwa1,const std::string &nazwa2,const Vector<double,3>&skala);
/*!
 *  \brief Metoda zapisujaca skale                                            
 *                                                                    
 *      \param[in] skala - Vector3D zawierajacy skale                                                  
 *                                                                        
 *     \post Zmiana skali na te podana przez uzytkownika                                
 */
void skaluj(const Vector<double,3> &skala);
/*!
 *  \brief Metoda zapisujaca nazwe pliku wzorcowego bryly                                            
 *                                                                    
 *      \param[in] nazwa1 - nazwa pliku                                                     
 *                                                                        
 *     \post Zmiana NazwaPlikubryluWzorc na ta podana przez uzytkownika                                
 */
void pobierz_nazwe_wzorca(const std::string &nazwa1);
/*!
 *  \brief Metoda zapisujaca nazwe pliku finalnej bryly                                            
 *                                                                    
 *      \param[in] nazwa2 - nazwa pliku  bryly finalnej                                                   
 *                                                                        
 *     \post Zmiana NazwaPlikubryluWzorc na ta podana przez uzytkownika                                
 */
void pobierz_nazwe_final(const std::string &nazwa2);

};