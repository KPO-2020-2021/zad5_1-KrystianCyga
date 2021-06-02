
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

bool dron::zapisz_dopliku(const char* nazwa ){
return korpus.zapis(nazwa);
}

bool dron::zapisz_dopliku(const char* nazwa,const int numer){
return rotor[numer].zapis(nazwa);
}

bool dron::owektor(vector3d &wek){
    bool ok;
    ok=korpus.owektor(wek);
    for(int i=0;i<4;++i){
        rotor[i]=rotor[i].owektor(wek);
    }
    return ok;
}




