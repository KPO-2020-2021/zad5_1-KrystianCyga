
#include "dron.hh"

dron::dron(){
double tab[3] = {1, 1,1};
vector3d tmp(tab);

polozenie=tmp;
orientacja=1;
}

bool dron::oblicz_zapisz_korpus(const char* nazwa){
    
    korpus.wczytaj(nazwa);
    return true ;
}

bool dron::oblicz_zapisz_rotor(const char* nazwa,const int numer){

    return (rotor[numer].wczytaj(nazwa));
}




