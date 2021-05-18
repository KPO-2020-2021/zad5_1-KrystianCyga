#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>

#include "vector.hh"
#include "matrix.hh"

#define PLIK_WZORCOWEGO_SZESCIANU       "bryly_wzorcowe/szescian.dat"
#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "bryly_wzorcowe/graniastoslup6.dat"
#define PLIK_KORPUSU_DRONA1             "datasets/korpus_drana1.dat"

/*!
 * \brief Transformuje współrzędne pojedynczego punktu.
 * 
 * Transformuje współrzędne pojedynczego punktu poprzez ich przeskalowanie i 
 * przesunięcie o zdany wektor translacji. Współczynniki skalowania jak też
 * współrzędne wektora translacji są przekazywane przez parametry tej funkcji.
 *
 * \param[in] KatObrotu_st - kąt, o jaki ma być dokonany obrót. Wartość kąta wyrażona
 *                           jest w stopniach.
 * \param[in,out]  x_wierz - współrzędna x-owa punktu, która ma zostać poddana transformacji.
 * \param[in,out]  y_wierz - współrzędna y-owa punktu, która ma zostać poddana transformacji.
 * \param[in,out]  z_wierz - współrzędna z-owa punktu, która ma zostać poddana transformacji.
 * \param[in]      sx_skala - współczynnik skalowania wzdłuż osi OX.
 * \param[in]      sy_skala - współczynnik skalowania wzdłuż osi OY.
 * \param[in]      sz_skala - współczynnik skalowania wzdłuż osi OZ.
 * \param[in]      tx_trans - współrzędna x-owa wektora translacji.
 * \param[in]      ty_trans - współrzędna y-owa wektora translacji.
 * \param[in]      tz_trans - współrzędna z-owa wektora translacji.
 */
void transformuj_punkt
(
				  double  KatObrotu_st,
				  Vector<double,3> &wektor3d,
				  double  sx_skala, double  sy_skala, double  sz_skala,
		          double  tx_trans, double  ty_trans, double  tz_trans
)
{
Matrix<3> macierz_obr;
macierz_obr.Mobrot3D_tworzenie(KatObrotu_st,'z');
wektor3d=macierz_obr*wektor3d;
wektor3d[0]=wektor3d[0]*sx_skala + tx_trans;
wektor3d[1]=wektor3d[1]*sy_skala + ty_trans;
wektor3d[2]=wektor3d[2]*sz_skala + tz_trans;
}

bool TworzOpisPrzetransformowanejBryly(){}

