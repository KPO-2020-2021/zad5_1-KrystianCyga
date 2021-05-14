#pragma once

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>

#include "vector.hh"

class brylageo
{
std::string NazwaPlikuBrylyWzorc;
std::string NazwaPlikubryluFinalnej;
Vector<double,3> wektor3d;

public:

Vector<double,3> skaluj(const Vector<double,3>&)const;
std::string& dajnazwe_wzorca();
std::string& dajnazwe_final();

};