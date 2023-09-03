/* 
    TP 2018/2019: LV 5, Zadatak 6
	
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
#include <vector>

int SumaCifara(int x) {
    if(x<0) x=-x;
    if(x==0) return 0;
    return x%10+SumaCifara(x/10);   
}
bool ManjiPoSumiCifara (int x, int y) {
    if(SumaCifara(x)==SumaCifara(y) && x<y) return true;
    return SumaCifara(x)<SumaCifara(y);
}
int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata: "<<std::endl;
    std::cin>>n;
    std::vector<int> v(n);
    std::cout<<"Unesite elemente: "<<std::endl;
    std::for_each(v.begin(), v.end(), [](int &x){std::cin>>x;});
    std::sort(v.begin(), v.end(), ManjiPoSumiCifara);
    std::cout<<"Niz sortiran po sumi cifara glasi: "<<std::endl;
    std::for_each(v.begin(), v.end(), [](int x){std::cout<<x<<" ";});
    int broj;
    std::cout<<std::endl<<"Unesite broj koji trazite: "<<std::endl;
    std::cin>>broj;
    std::vector<int>::iterator it=std::lower_bound(v.begin(), v.end(), broj, ManjiPoSumiCifara);
    if(*it!=broj) std::cout<<"Trazeni broj ne nalazi se u nizu!";
    else std::cout<<"Trazeni broj nalazi se na poziciji "<<it-v.begin();
	return 0;
}