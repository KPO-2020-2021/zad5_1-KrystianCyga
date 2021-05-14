#pragma once

#include "dron.hh"

class scena
{

dron dragon[2];
PzG::LaczeDoGNUPlota Lacze;

public:

dron &uzyj_aktywnego();
const dron wez_aktywnego() const;

};