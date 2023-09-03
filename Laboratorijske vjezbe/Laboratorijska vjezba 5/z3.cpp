/* 
    TP 2018/2019: LV 5, Zadatak 3
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include <algorithm>
#include <cmath>

bool PotpunKvadrat(double x) {
    return sqrt(x)==int(sqrt(x));
}
int BrojCifara (int x) {
    if(x==0) return 1;
    if(x<0) x=-x;
    return int(log10(x)+1);
}
bool NajmanjiBrojCifara(int x, int y) {
    return BrojCifara(x)<BrojCifara(y);
}
void Unesi(int &x) {
    std::cin>>x;
}
bool Trocifren (int x) {
    return BrojCifara(x)==3;
}
void Ispisi (int x) {
    std::cout<<x<<" ";
}
int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata (max. 1000): "<<std::endl;
    std::cin>>n;
    std::cout<<"Unesite elemente: "<<std::endl;
    int niz[1000];
    std::for_each(niz, niz+n, Unesi);
    std::cout<<"Najveci element niza je "<<*std::max_element(niz, niz+n)<<std::endl;
    int min=*std::min_element(niz, niz+n);
    std::cout<<"Najmanji element niza se pojavljuje "<<std::count(niz, niz+n, min)<<" puta u nizu"<<std::endl;
    std::cout<<"U nizu ima "<<std::count_if(niz, niz+n, PotpunKvadrat)<<" brojeva koji su potpuni kvadrati"<<std::endl;
    std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*std::min_element(niz, niz+n, NajmanjiBrojCifara)<<std::endl;
    int niz2[1000];
    int *kraj=std::remove_copy_if(niz, niz+n, niz2, Trocifren);
    std::cout<<"Elementi koji nisu trocifreni su: ";
    std::for_each(niz2, kraj, Ispisi);
	return 0;
}