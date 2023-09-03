/* 
    TP 2018/2019: LV 5, Zadatak 7
	
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
#include <stdexcept>
#include <deque>
#include <string>
#include <algorithm>

template <typename NekiTip>
auto SumaBloka (NekiTip pocetak, NekiTip kraj) -> decltype(*pocetak+*pocetak) {
    if(pocetak==kraj) throw std::range_error("Blok je prazan");
    decltype(*pocetak+*pocetak) suma=*pocetak++;
    while(pocetak!=kraj) suma+=*pocetak++;
    return suma;
}
int main ()
{   
    int n;
    std::cout<<"Unesite broj elemenata: "<<std::endl;
    std::cin>>n;
    std::deque<double> dek(n);
    std::cout<<"Unesi elemente: "<<std::endl;
    std::for_each(dek.begin(), dek.end(), [](double &x){std::cin>>x;});
    try {
        auto suma=SumaBloka(dek.begin(), dek.end());
        std::cout<<"Suma bloka je "<<suma;
    }
    catch(std::range_error izuzetak) {
        std::cout<<izuzetak.what();
    }
	return 0;
}