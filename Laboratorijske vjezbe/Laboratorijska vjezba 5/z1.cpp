/* 
    TP 2018/2019: LV 5, Zadatak 1
	
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

char *IzbaciPrvuRijec(char *recenica) {
    while(*recenica!='\0' && *recenica==' ') recenica++;
    int razmak=0;
    while(*recenica!='\0') {
        if(*recenica!=' ' && razmak) return recenica;
        if(*recenica==' ') razmak=1;
        recenica++;
    }
    return nullptr;
}
int main ()
{
    char recenica[1000];
    std::cout<<"Unesite recenicu: ";
    std::cin.getline(recenica, sizeof recenica);
    char* pocetak=IzbaciPrvuRijec(recenica);
    std::cout<<"Recenica bez prve rijeci glasi: ";
    if(pocetak!=nullptr) while(*pocetak!='\0') std::cout<<*pocetak++;
    std::cout<<std::endl;
	return 0;
}