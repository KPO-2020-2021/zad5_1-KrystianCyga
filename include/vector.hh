#ifndef VECTOR_HH
#define VECTOR_HH

#include <iostream>
#include <iostream>
#include <stdexcept>
#include <math.h>
#include <cassert>
#define epsilon 0.000001


/*!
 * \file  vector.hh
 *  
 *  Plik zawiera definicję klasy vector oraz
 *  jej opisane metody i funkcje.
 *  
 */

/*!
 *  \brief Szablon klasy wektor.
 * 
 *  Jest on tablicą wspolrzednych.
 *
 */
template <typename T,unsigned int ROZMIAR>
class Vector
{

    T wspolrzedne[ROZMIAR]; //Tablica wektora

public:
    Vector();

    Vector(T[ROZMIAR]);

    double dlugosc(const Vector<double,ROZMIAR> &drugi) const ;

    Vector operator+(const Vector<T,ROZMIAR> &v);

    Vector operator-(const Vector<T,ROZMIAR> &v);

    Vector operator*(const T &tmp);

    Vector operator/(const T &tmp);

    T operator[](unsigned int index) const {assert(index<ROZMIAR);return wspolrzedne[index];};

    T &operator[](unsigned int index) {assert(index<ROZMIAR);return wspolrzedne[index];};

    bool operator==(const Vector<T,ROZMIAR> &drugi) const;

    void zapeln(T argu[ROZMIAR]);

    T modul();
};

/*!
 * \brief Przeciazenie operatora >>
 *                                                                               
 *      \param[in] in strumien wyjsciowy                                              
 *      \param[in] tmp  wektor  
 */
template <typename T,unsigned int ROZMIAR>
inline std::istream &operator>>(std::istream &in, Vector<T,ROZMIAR> &tmp)
{
    for (unsigned int i = 0; i < ROZMIAR; ++i)
    {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}

/*!
 * \brief Przeciazenie operatora <<                                                  
 *                                                                 
 *      \param[in] out  strumien wejsciowy                                             
 *      \param[in] tmp  wektor
 */
template <typename T,unsigned int ROZMIAR>
inline std::ostream &operator<<(std::ostream &out, const Vector<T,ROZMIAR> &tmp)
{
    for (unsigned int i = 0; i < ROZMIAR; ++i)
    {
        out << tmp[i] << " ";
    }
    return out;
}

/*!
 * \brief Konstruktor klasy Vector.
 *                                                                   
 *      \ Wypelnia on wektor zerami 
 */
template <typename T,unsigned int ROZMIAR>
Vector<T,ROZMIAR>::Vector()
{
    {
        for (T &wsp1 : wspolrzedne)
        {
            wsp1 = 0;
        }
    }
}

/*!
 * \brief Konstruktor parametryczny klasy Vector
 *                                                                
 *      \param[in] Tablica typu t.                                                       
 *                                                                     
 *     \return Tablice  wypelniona wartoscia tablicy
 */
template <typename T,unsigned int ROZMIAR>
Vector<T,ROZMIAR>::Vector(T tmp[ROZMIAR])
{
    for (unsigned int i = 0; i < ROZMIAR; ++i)
    {
        wspolrzedne[i] = tmp[i];
    }
}

/*!
 * \brief Metoda zwracająca dlugosc wektora
 *                                                               
 *      \param[in] Wektor                                                                                                                                   
 *      \return Dlugosc wektora 
 */
template <typename T,unsigned int ROZMIAR>
double Vector<T,ROZMIAR>::dlugosc(const Vector<double,ROZMIAR> &drugi) const
{
    double tmp=0;
    for (unsigned int i = 0; i < ROZMIAR; i++)
    {
        tmp += std::pow(drugi.wspolrzedne[i] - this->wspolrzedne[i], 2);
    }
    return std::sqrt(tmp);
}


/*!
 * \brief Operator porownania
 *                                                                 
 *     \param[in] Wektory                                                                                                                                  
 *     \return bool 
 */
template <typename T,unsigned int ROZMIAR>
bool Vector<T,ROZMIAR>::operator==(const Vector<T,ROZMIAR> &drugi) const
{
    int tmp = 0;
    for (unsigned int i = 0; i < ROZMIAR; ++i)
    {
        tmp += (int)(abs(wspolrzedne[i] - drugi.wspolrzedne[i]) <= epsilon);
    }
    if (tmp == ROZMIAR)
    {
        return true;
    }
    else
        return false;
}

/*!
 * \brief Zapelnia wektor tablica typu T
 *                                                                                                                                   
 */
template <typename T,unsigned int ROZMIAR>
void Vector<T,ROZMIAR>::zapeln(T argu[ROZMIAR])
{
    for (unsigned int i = 0; i < ROZMIAR; i++)
    {
       wspolrzedne[i]=argu[i]; 
    }
}
/*!
 * \brief Oblicza modul
 *                                                                  
 *     \param[in] Wektor                                                               
 *                                                                     
 *     \return modul                                                                  
 */
template <typename T,unsigned int ROZMIAR>
T Vector<T,ROZMIAR>::modul()
{   
    T tmp;
    for(unsigned int i=0;i<ROZMIAR;i++)
    {
        tmp+=(wspolrzedne[i] * wspolrzedne[i]);
    }
    return std::sqrt(tmp);
}

/*!
 * \brief Oblicza sume wektorow
 *                                                                  
 *     \param[in] Wektory this i v                                                               
 *                                                                     
 *     \return Sume wektorow                                                                  
 */
template <typename T,unsigned int ROZMIAR>
Vector<T,ROZMIAR> Vector<T,ROZMIAR>::operator+(const Vector<T,ROZMIAR> &v)
{
    Vector result;
    for (unsigned int i = 0; i < ROZMIAR; ++i)
    {
        result[i] = wspolrzedne[i] += v[i];
    }
    return result;
}
/*!
 * \brief Oblicza roznice wektorow
 *                                                                  
 *     \param[in] Wektory this i v                                                               
 *                                                                     
 *     \return Roznice wektorow                                                                  
 */
template <typename T,unsigned int ROZMIAR>
Vector<T,ROZMIAR> Vector<T,ROZMIAR>::operator-(const Vector<T,ROZMIAR> &v)
{
    Vector result;
    for (unsigned int i = 0; i < ROZMIAR; ++i)
    {
        result[i] = wspolrzedne[i] -= v[i];
    }
    return result;
}

/*!
 * \brief Oblicza iloczyn wektorow
 *                                                                  
 *     \param[in] Wektory this i tmp                                                               
 *                                                                     
 *     \return iloczyn wektorow                                                                  
 */
template <typename T,unsigned int ROZMIAR>
Vector<T,ROZMIAR> Vector<T,ROZMIAR>::operator*(const T &tmp)
{
    Vector result;
    for (unsigned int i = 0; i < ROZMIAR; ++i)
    {
        result[i] = wspolrzedne[i] *= tmp;
    }
    return result;
}

/*!
 * \brief Oblicza iloczyn wektorow
 *                                                                  
 *     \param[in] Wektor                                                              
 *     \param[in] stala                                                               
 *     \return Iloczyn wektora przez stala                                                                 
 */
template <typename T,unsigned int ROZMIAR>
Vector<T,ROZMIAR> Vector<T,ROZMIAR>::operator/(const T &tmp)
{
    Vector result;
    
    for (unsigned int i = 0; i < ROZMIAR; ++i)
    {
        result[i] = wspolrzedne[i] / tmp;
    }

    return result;
}



#endif
