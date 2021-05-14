#ifndef MATRIX_HH
#define MATRIX_HH

#include "vector.hh"
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>

#define epsilon 0.000001


/*!
 * \file  matrix.hh
 *  
 *  Plik zawiera definicję klasy matrix oraz
 *  jej opisane metody i funkcje.
 *  
 */

/*!
 * \brief Definicja Szablonu macierz.
 * 
 *  Jest ona postaci tablicy dwuwymiarowej.
 */
template <int WYMIAR>
class Matrix{

  double value[WYMIAR][WYMIAR];

  public:
    Matrix(double[WYMIAR][WYMIAR]); // Konstruktor klasy

    Matrix(); // Konstruktor klasy

    Vector<double,WYMIAR> operator*(Vector<double,WYMIAR> tmp); // Operator mnożenia przez wektor

    Matrix operator+(Matrix tmp);

    double &operator()(unsigned int row, unsigned int column);

    const double &operator()(unsigned int row, unsigned int column) const;

    Matrix Mobrot2D_tworzenie(int kat);

    Matrix Mobrot3D_tworzenie(int kat,char os);

    Matrix Mobrot_4x4(double kat[],int os[]);

    Matrix transpozycja() const ;

    bool operator==(const Matrix &tmp) const;
    
    double gauss();    
};





/*!*****************************************************************************
 *  \brief Konstruktor klasy Matrix.                              
 *                                                                                                                                                                                  
 */
template <int WYMIAR>
Matrix<WYMIAR>::Matrix()
{
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            value[i][j] = 0;
        }
    }
}

/*!*****************************************************************************
 * \brief Konstruktor parametryczny klasy Matrix.                              
 *                                                           
 *     \param[in]  tmp - dwuwymiarowa tablica z elementami typu double.             
 *                                                                  
 *     \return Macierz wypelniona wartosciami podanymi w argumencie.              
 */
template <int WYMIAR>
Matrix<WYMIAR>::Matrix(double tmp[WYMIAR][WYMIAR])
{
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            value[i][j] = tmp[i][j];
        }
    }
}

/*!*****************************************************************************
 *  \brief Realizuje mnozenie macierzy przez wektor.                              
 *                                                                 
 *     \param[in] this - macierz, czyli pierwszy skladnik mnozenia,                     
 *     \param[in] v - wektor, czyli drugi skladnik mnozenia.                            
 *                                                                     
 *     \return Iloczyn dwoch skladnikow przekazanych jako wektor.                   
 */
template <int WYMIAR>
Vector<double,WYMIAR> Matrix<WYMIAR>::operator*(Vector<double,WYMIAR> tmp)
{
    Vector<double,WYMIAR> result;
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}

/*!*****************************************************************************
 *  \brief Funktor macierzy                                                          
 *                                                                  
 *     \param[in] row - numer wiersza.                                                  
 *     \param[in] column - numer kolumny.                                               
 *                                                                    
 *     \return Wartosc macierzy w danym miejscu tablicy.                             
 */
template <int WYMIAR>
double &Matrix<WYMIAR>::operator()(unsigned int row, unsigned int column)
{

    if (row >= WYMIAR)
    {
        std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    if (column >= WYMIAR)
    {
        std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    return value[row][column];
}

/*!*****************************************************************************
 *  \brief Funktor macierzy                                                          
 *                                                                 
 *     \param[in] row - numer wiersza.                                                  
 *     \param[in] column - numer kolumny.                                               
 *                                                                   
 *    \return  Wartosc macierzy w danym miejscu tablicy jako stala.                  
 */
template <int WYMIAR>
const double &Matrix<WYMIAR>::operator()(unsigned int row, unsigned int column) const
{

    if (row >= WYMIAR)
    {
        std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    if (column >= WYMIAR)
    {
        std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    return value[row][column];
}

/*! *****************************************************************************
 *  \brief Przeciążenie dodawania macierzy                                           
 *                                                                  
 *     \param[in] this - macierz, czyli pierwszy skladnik dodawania,                    
 *     \param[in] tmp - macierz czyli drugi skladnik dodawania.                           
 *                                                                     
 *     \param[in] Macierz - sume macierzy.                            
 */
template <int WYMIAR>
Matrix<WYMIAR> Matrix<WYMIAR>::operator+(Matrix<WYMIAR> tmp)
{
    Matrix result;
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}

/*! *****************************************************************************
 *  \brief Przeciazenie operatora >>                                                 
 *                                                                  
 *    \param[in]  in - strumien wyjsciowy,                                              
 *    \param[in]  mat - macierz.                                                        
 */
template <int WYMIAR>
std::istream &operator>>(std::istream &in, Matrix<WYMIAR> &mat)
{

    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            in >> mat(i, j);
        }
    }
    return in;
}

/*! *****************************************************************************
 *  \brief Przeciazenie operatora <<                                                 
 *                                                                  
 *    \param[in]  out - strumien wejsciowy,                                             
 *    \param[in] mat - macierz.                                                        
 */
template <int WYMIAR>
std::ostream &operator<<(std::ostream &out, const Matrix<WYMIAR> &mat)
{
    out<<std::fixed<<std::setprecision(10);
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}

/*! *****************************************************************************
 *  \brief Tworzy macierz obrotu  2D                                                 
 *                                                                
 *    \param[in]  kat - kat obrotu,                                                   
 *                                                                   
 *     \return Macierz obrotu                                                      
 */
template <int WYMIAR>
Matrix<WYMIAR> Matrix<WYMIAR>::Mobrot2D_tworzenie(int kat)
{
    double rad = kat * M_PI / 180;
    value[0][0] = cos(rad);
    value[0][1] = -sin(rad);
    value[1][0] = sin(rad);
    value[1][1] = cos(rad);
    return *this;
}

/*! *****************************************************************************
 *  \brief Tworzy macierz obrotu  3D                                                 
 *                                                                
 *     \param[in] kat - kat obrotu,                                                   
 *     \param[in]  os - os obrotu
 *                                                                   
 *     \return Macierz obrotu                                                      
 */
template <int WYMIAR>
Matrix<WYMIAR> Matrix<WYMIAR>::Mobrot3D_tworzenie(int kat,char os)
{
    double rad = kat * M_PI / 180;
    do
    {
    switch (os)
    {
    case 'z':
    value[0][0] = cos(rad);
    value[0][1] = -sin(rad);
    value[1][0] = sin(rad);
    value[1][1] = cos(rad);
    value[2][0] = 0.0;
    value[2][1] = 0.0;
    value[2][2] = 1.0;
    value[0][2] = 0.0;
    value[1][2] = 0.0;
        break;
    
    
    case 'y':
    value[0][0] = cos(rad);
    value[0][2] = -sin(rad);
    value[2][0] = sin(rad);
    value[2][2] = cos(rad);
    value[1][0] = 0;
    value[2][1] = 0;
    value[1][1] = 1;
    value[0][1] = 0;
    value[1][2] = 0;
    break;
    case 'x':
    value[1][1] = cos(rad);
    value[1][2] = -sin(rad);
    value[2][1] = sin(rad);
    value[2][2] = cos(rad);
    value[2][0] = 0;
    value[0][1] = 0;
    value[0][0] = 1;
    value[0][2] = 0;
    value[1][0] = 0;
    break;

    default:
    std::cout<<"Blednie podana os! Mozliwe to x,y,z\nPodaj os: ";
    std::cin>>os;
    break;
    }
    }
    while (os!='z'&&os!='x'&&os!='y');

    return *this;
}
/*!
 * \brief Operator porownania
 *                                                                  
 *     \param[in] Macierze                                                               
 *                                                                     
 *    \return  bool 
 */
template <int WYMIAR>
bool Matrix<WYMIAR>::operator==(const Matrix<WYMIAR> &tmp) const
{
    int prawdy = 0;
    for (int i = 0; i < WYMIAR; i++)
    {
        for (int j = 0; j < WYMIAR; j++)
        {
            prawdy += (int)(abs(this->value[i][j] - tmp.value[i][j]) <= epsilon);
        }
    }
    if (prawdy==WYMIAR*WYMIAR)
    {
        return true;
    }
    else
        return false;
}

/*!*****************************************************************************
 *  \brief Metoda liczenia wyznacznika Gaussem                                       
 *                                                             
 *     \param[in] Macierz                                                               
 *                                                                     
 *    \return  Wyznacznik typu double                                                
 */
template <int WYMIAR>
double Matrix<WYMIAR>::gauss()
{
    int i, j, k;
    double temp, x[WYMIAR];
    for (j = 0; j < WYMIAR - 1; j++)
    {
        for (i = j + 1; i < WYMIAR; i++)
        {
            temp = value[i][j] / value[j][j];
            for (k = 0; k < WYMIAR; k++)
            {
                value[i][k] -= value[j][k] * temp;
            }
        }
    }
    for (int i = 0; i < WYMIAR; i++)
    {
        x[i] = value[i][i];
    }
    double wyznacznik = 1;
    for (i = 0; i < WYMIAR; i++)
    {
        wyznacznik *= x[i];
    }
    return wyznacznik;
}
/*!*****************************************************************************
 *  \brief Metoda Transpozycji Macierzy                                       
 *                                                             
 *     \param[in] Macierz                                                               
 *                                                                     
 *    \return  Transponowana macierz                                                
 */
template<int WYMIAR>
Matrix<WYMIAR> Matrix<WYMIAR>::transpozycja() const
{
    Matrix<WYMIAR> mat;

    for (int i = 0; i < WYMIAR; i++)
    {
        for (int k = 0; k < WYMIAR; k++)
        {
            mat.value[k][i]=this->value[i][k];
        }
    }
    return mat;    
}

/*!*****************************************************************************
 *  \brief Metoda tworzenia macierzy obrotu 4x4                                       
 *                                                             
 *     \param[in] Macierz                                                               
 *                                                                     
 *    \return  Macierz obrotu 4x4                                                
 */
template<int WYMIAR>
Matrix<WYMIAR> Matrix<WYMIAR>::Mobrot_4x4(double kat[],int os[])
{
    double rad[3] ={0,0,0};
    for (int i = 0; i < 3; i++)
    {
        rad[i] = kat[i] * M_PI / 180;
    }

    value[0][0] = cos(rad[0])*cos(rad[1]);
    value[0][1] = cos(rad[0])*sin(rad[1])*sin(rad[2])-cos(rad[2])*sin(rad[0]);
    value[0][2] = cos(rad[0])*sin(rad[1])*cos(rad[2])+sin(rad[2])*sin(rad[0]);
    value[0][3] = os[0];

    value[1][0] = sin(rad[0])*cos(rad[1]);
    value[1][1] = sin(rad[0])*sin(rad[1])*sin(rad[2])+cos(rad[2])*cos(rad[0]);
    value[1][2] = sin(rad[0])*sin(rad[1])*cos(rad[2])-sin(rad[2])*cos(rad[0]);
    value[1][3] = os[1];

    value[2][0] = -sin(rad[1]);
    value[2][1] = sin(rad[2])*cos(rad[1]);
    value[2][2] = cos(rad[1])*cos(rad[2]);
    value[2][3] = os[2];

    value[3][0] = 0;
    value[3][1] = 0;
    value[3][2] = 0;
    value[3][3] = 1;

    return *this;
}



#endif
