#include "../include/brylageo.hh"

brylageo::brylageo(){
    NazwaPlikuBrylyWzorc="";
    NazwaPlikubryluFinalnej="";
    vector3d elo;
    skala=elo;
}

brylageo::brylageo(const std::string &nazwa1,const std::string &nazwa2,const vector3d &skala_uzyt){
    NazwaPlikuBrylyWzorc=nazwa1;
    NazwaPlikubryluFinalnej=nazwa2;
    skala=skala_uzyt;
}

void brylageo::skaluj(const vector3d &skala_uzyt) {
    skala=skala_uzyt;
}

void brylageo::pobierz_nazwe_wzorca(const std::string &nazwa1){
    NazwaPlikuBrylyWzorc=nazwa1;
}

void brylageo::pobierz_nazwe_final(const std::string &nazwa2){
    NazwaPlikubryluFinalnej=nazwa2;
}
/*!
 * \brief Dokonuje obrotu wokół osi OZ.
 *
 * Transformuje współrzędne \p x i \p y dokonując obrót o zadany kąt.
 * \param[in] KatObrotu_st - kąt, o który ma być zrealizowany obrót.
 * \param[in,out] Polozenie - współrzędne punktu, które zostają przetransformowane.
 */
void brylageo::ObrocWzgledemOsiOZ(double KatObrotu_st, vector3d &Polozenie)
{
  vector3d WynikObrotu;
  double Kat_rad = (KatObrotu_st * M_PI / 180);
  double sn = sin(Kat_rad), cn = cos(Kat_rad);
  WynikObrotu[0] = Polozenie[0] * cn - Polozenie[1] * sn;
  WynikObrotu[1] = Polozenie[0] * sn + Polozenie[1] * cn;
  Polozenie[0] = WynikObrotu[0];
  Polozenie[1] = WynikObrotu[1];
}

/*!
 * \brief Skaluje wektor
 *
 * Skaluje Wektor3D mnożąc jego wartości przez Wektor3D Skala
 * \param[in] Polozenie - wartość kąta wyrażona w stopniach.
 */
void brylageo::Skaluj(vector3d &Polozenie)
{
  Polozenie[0] *= skala[0];
  Polozenie[1] *= skala[1];
  Polozenie[2] *= skala[2];
}

/*!
 * \brief Transformuje współrzędne pojedynczego punktu.
 * 
 * Transformuje współrzędne pojedynczego punktu poprzez ich przeskalowanie i 
 * przesunięcie o zadany wektor translacji. Współczynniki skalowania jak też
 * współrzędne wektora translacji są zapisane w klasie.
 *
 * \param[in,out]  Polozenie - współrzędne punktu, który ma zostać poddany transformacji.
 */
void brylageo::TransformujWspolrzednePunktu(vector3d &Polozenie)
{
  vector3d wynik;
  ObrocWzgledemOsiOZ(KatOrientacji_st, Polozenie);
  Skaluj(Polozenie);
  wynik = Polozenie + trans;
  Polozenie = wynik;
}