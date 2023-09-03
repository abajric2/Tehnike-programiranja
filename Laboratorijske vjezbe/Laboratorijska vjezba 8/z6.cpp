//TP 2021/2022: LV 8, Zadatak 6
#include <iostream>
#include <cmath>

template <typename TipElemenata>
struct Cvor {
    TipElemenata element;
    Cvor<TipElemenata> *veza;
};

template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu (TipElemenata zavrsni) {
    Cvor<TipElemenata> *pocetak=nullptr, *prethodni;
    for(;;) {
        TipElemenata el;
        std::cin>>el;
        if(el==zavrsni) break;
        auto novi=new Cvor<TipElemenata>{el, nullptr};
        if(!pocetak) pocetak=novi;
        else prethodni->veza=novi;
        prethodni=novi;
    }
    return pocetak;
}

template <typename TipElemenata>
int BrojElemenata (Cvor<TipElemenata> *pocetak) {
    int br_el=0;
    for(auto i=pocetak; i!=nullptr; i=i->veza) br_el++;
    return br_el;
}

template <typename TipElemenata>
TipElemenata SumaElemenata (Cvor<TipElemenata> *pocetak) {
    TipElemenata suma=TipElemenata();
    for(auto i=pocetak; i!=nullptr; i=i->veza) suma+=i->element;
    return suma;
}

template <typename TipElemenata>
int BrojVecihOd (Cvor<TipElemenata> *pocetak, TipElemenata prag) {
    int br_vecih=0;
    for(auto i=pocetak; i!=nullptr; i=i->veza) if(i->element>prag) br_vecih++;
    return br_vecih;
}

template <typename TipElemenata>
void UnistiListu (Cvor<TipElemenata> *pocetak) {
    for(auto i=pocetak; i!=nullptr;) {
        auto sljedeci=i->veza;
        delete i;
        i=sljedeci;
    }
}

int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): "<<std::endl;
    auto lista=KreirajPovezanuListu(0.);
    std::cout<<"U slijedu ima "<<BrojVecihOd(lista, SumaElemenata(lista)/BrojElemenata(lista))<<" brojeva vecih od njihove aritmeticke sredine";
    UnistiListu(lista);
	return 0;
}
