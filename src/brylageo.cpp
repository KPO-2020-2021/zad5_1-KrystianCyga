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