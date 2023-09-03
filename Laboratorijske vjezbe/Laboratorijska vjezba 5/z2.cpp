/* 
    TP 2018/2019: LV 5, Zadatak 2
	
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
#include <string>

template<typename IterTip1, typename IterTip2>
IterTip2 RazmijeniBlokove(IterTip1 pocetak1, IterTip1 kraj1, IterTip2 pocetak2) {
    while(pocetak1!=kraj1) {
        auto pomocna=std::move(*pocetak1);
        *pocetak1=std::move(*pocetak2);
        *pocetak2=std::move(pomocna);
        pocetak1++; pocetak2++;
    }
    return pocetak2;
}
void Ispisi(int *pocetak, int* kraj) {
    while(pocetak!=kraj) std::cout<<*pocetak++<<" ";
}
void Ispisi(std::string::iterator pocetak, std::string::iterator kraj) {
    while(pocetak!=kraj) std::cout<<*pocetak++;
}
int main ()
{
    int niz1[5]{1,2,3,4,5};
    int niz2[5]{6,7,8,9,10};
    std::cout<<"Prije razmjene: "<<std::endl;
    std::cout<<"Prvi niz: "<<std::endl;
    Ispisi(std::begin(niz1), std::end(niz1));
    std::cout<<std::endl<<"Drugi niz: "<<std::endl;
    Ispisi(std::begin(niz2), std::end(niz2));
    int *kraj2=RazmijeniBlokove(std::begin(niz1), std::end(niz1), std::begin(niz2));
    std::cout<<std::endl<<"Nakon razmjene: "<<std::endl;
    std::cout<<"Prvi niz: "<<std::endl;
    Ispisi(std::begin(niz1), std::end(niz1));
    std::cout<<std::endl<<"Drugi niz: "<<std::endl;
    Ispisi(std::begin(niz2), kraj2);
    std::string s1="Recenica za provjeru.";
    std::string s2="Za provjeru recenica.";
    std::cout<<std::endl<<"Prije razmjene: "<<std::endl;
    std::cout<<"Prvi string: "<<std::endl;
    Ispisi(s1.begin(), s1.end());
    std::cout<<std::endl<<"Drugi string: "<<std::endl;
    Ispisi(s2.begin(), s2.end());
    std::string::iterator kraj=RazmijeniBlokove(s1.begin(), s1.end(), s2.begin());
    std::cout<<std::endl<<"Nakon razmjene: "<<std::endl;
    std::cout<<"Prvi string: "<<std::endl;
    Ispisi(s1.begin(), s1.end());
    std::cout<<std::endl<<"Drugi string: "<<std::endl;
    Ispisi(s2.begin(), kraj);
	return 0;
}