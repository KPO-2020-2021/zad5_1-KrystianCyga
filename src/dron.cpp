
#include "dron.hh"

dron::dron()
{
    double tab[3] = {1, 1, 1};
    vector3d tmp(tab);

    trans = tmp;
    KatOrientacji_st = 1;
}

void dron::ustaw_srodek(){
    trans=korpus.daj_srodek();
}

bool dron::oblicz_zapisz_korpus(const int numer_drona)
{

    if (numer_drona == 1)
    {
        return korpus.wczytaj(PLIK_WLASCIWY__DRON1_KORPUS);
    }
    else
        return korpus.wczytaj(PLIK_WLASCIWY__DRON2_KORPUS);
}

bool dron::oblicz_zapisz_rotor(const int numer_drona, const int numer_rotora)
{
    std::string nazwa;

    if (numer_drona == 1)
    {
        switch (numer_rotora)
        {
        case 0:
            nazwa = PLIK_WLASCIWY__DRON1_ROTOR1;
            break;
        case 1:
            nazwa = PLIK_WLASCIWY__DRON1_ROTOR2;
            break;
        case 2:
            nazwa = PLIK_WLASCIWY__DRON1_ROTOR3;
            break;
        case 3:
            nazwa = PLIK_WLASCIWY__DRON1_ROTOR4;
            break;

        default:
            break;
        }
    }
    else
    {
        switch (numer_rotora)
        {
        case 0:
            nazwa = PLIK_WLASCIWY__DRON2_ROTOR1;
            break;
        case 1:
            nazwa = PLIK_WLASCIWY__DRON2_ROTOR2;
            break;
        case 2:
            nazwa = PLIK_WLASCIWY__DRON2_ROTOR3;
            break;
        case 3:
            nazwa = PLIK_WLASCIWY__DRON2_ROTOR4;
            break;

        default:
            break;
        }
    }
    return (rotor[numer_rotora].wczytaj(nazwa));
}

bool dron::zapisz_dopliku(const int numer_drona)
{

    if (numer_drona == 1)
    {
        return korpus.zapis(PLIK_ROBOCZY__DRON1_KORPUS);
    }
    else
        return korpus.zapis(PLIK_ROBOCZY__DRON2_KORPUS);
}

bool dron::zapisz_dopliku(const int numer_drona, const int numer_rotora)
{
    std::string nazwa;

    if (numer_drona == 1)
    {
        switch (numer_rotora)
        {
        case 0:
            nazwa = PLIK_ROBOCZY__DRON1_ROTOR1;
            break;
        case 1:
            nazwa = PLIK_ROBOCZY__DRON1_ROTOR2;
            break;
        case 2:
            nazwa = PLIK_ROBOCZY__DRON1_ROTOR3;
            break;
        case 3:
            nazwa = PLIK_ROBOCZY__DRON1_ROTOR4;
            break;

        default:
            break;
        }
    }
    else if (numer_drona == 2)
    {
        switch (numer_rotora)
        {
        case 0:
            nazwa = PLIK_ROBOCZY__DRON2_ROTOR1;
            break;
        case 1:
            nazwa = PLIK_ROBOCZY__DRON2_ROTOR2;
            break;
        case 2:
            nazwa = PLIK_ROBOCZY__DRON2_ROTOR3;
            break;
        case 3:
            nazwa = PLIK_ROBOCZY__DRON2_ROTOR4;
            break;

        default:
            break;
        }
    }
    return rotor[numer_rotora].zapis(nazwa);
}

bool dron::owektor(vector3d &wek)
{
    bool ok;
    ok = korpus.owektor(wek);
    for (int i = 0; i < 4; ++i)
    {
        rotor[i] = rotor[i].owektor(wek);
    }
    return ok;
}

bool dron::tworz_drona()
{
    vector3d tmp2, tmp1;
    bool ok;

    tmp2 = korpus[8] * (-1);
    ok = korpus.owektor(tmp2);

    tmp1 = korpus[4] - rotor[0].daj_srodek();
    rotor[0].owektor(tmp1);

    tmp1 = korpus[5] - rotor[1].daj_srodek();
    rotor[1].owektor(tmp1);

    tmp1 = korpus[1] - rotor[2].daj_srodek();
    rotor[2].owektor(tmp1);

    tmp1 = korpus[2] - rotor[3].daj_srodek();
    rotor[3].owektor(tmp1);
    return ok;
}

void dron::dodaj_do_lacza(PzG::LaczeDoGNUPlota &Lacze, const int numer_drona)
{
    if (numer_drona == 1)
    {
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON1_KORPUS);
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON1_ROTOR1);
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON1_ROTOR2);
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON1_ROTOR3);
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON1_ROTOR4);
    }
    else if (numer_drona == 2)
    {
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON2_KORPUS);
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON2_ROTOR1);
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON2_ROTOR2);
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON2_ROTOR3);
        Lacze.DodajNazwePliku(PLIK_ROBOCZY__DRON2_ROTOR4);
    }
}

void dron::zapisz_drona(const int numer_drona)
{
    zapisz_dopliku(numer_drona);
    zapisz_dopliku(numer_drona, 0);
    zapisz_dopliku(numer_drona, 1);
    zapisz_dopliku(numer_drona, 2);
    zapisz_dopliku(numer_drona, 3);
}

void wznoszenie(PzG::LaczeDoGNUPlota& Lacze,dron &latawiec,const double wysokosc,const int numer){
    vector3d jednosciZ;
    jednosciZ[0] = 0;
    jednosciZ[1] = 0;
    jednosciZ[2] = 1;
    Lacze.Rysuj();
    usleep(1000000);
    std::cout<<"\nWznoszenie Trwa\n";
    usleep(200000);

    for (int i; i < wysokosc; i++)
    {
        latawiec.owektor(jednosciZ);
        latawiec.zapisz_drona(numer);

        usleep(150000);
        Lacze.Rysuj();
    }  
}


    void dron::obrot(const double kat){

        korpus.obrot(kat);
        
        rotor[0].obrot(kat);
        
        rotor[1].obrot(kat);
        
        rotor[2].obrot(kat);
        
        rotor[3].obrot(kat);
    }



    //void opadanie();


