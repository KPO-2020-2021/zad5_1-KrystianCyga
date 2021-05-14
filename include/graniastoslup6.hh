#pragma once

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>

#include "vector.hh"
#include "brylageo.hh"

class graniastoslup : public brylageo
{
    Vector<double,3> polozenie;
    double orientacja;

    public:

    Vector<double,3> transDo(const  Vector<double,3> &wierz) const;

};