#include "brylageo.hh"
#include <fstream>
#include "lacze_do_gnuplota.hh"

class Sciezka : public brylageo
{
    vector3d punkty[4];

public:
    
    void dodajSciezke(PzG::LaczeDoGNUPlota &Lacze,const char* &nazwa);

    bool wczytaj(const std::string &nazwa);
    bool zapis(const std::string &nazwa) const;
};