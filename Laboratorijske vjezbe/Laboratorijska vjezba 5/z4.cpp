/* 
    TP 2018/2019: LV 5, Zadatak 4
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje dek1.begin()[i] ili simulacija indeksiranja
			  npr. *(dek1.begin() + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include <algorithm>
#include <deque>
#include <cmath>

int main ()
{
    int n1;
    std::cout<<"Unesite broj elemenata: "<<std::endl;
    std::cin>>n1;
    std::cout<<"Unesite elemente: "<<std::endl;
    std::deque<int> dek1(n1);
    std::for_each(dek1.begin(), dek1.end(), [](int &x){std::cin>>x;});
    std::cout<<"Najveci element deka je "<<*std::max_element(dek1.begin(), dek1.end())<<std::endl;
    int min=*std::min_element(dek1.begin(), dek1.end());
    std::cout<<"Najmanji element deka se pojavljuje "<<std::count(dek1.begin(), dek1.end(), min)<<" puta u deku"<<std::endl;
    std::cout<<"U deku ima "<<std::count_if(dek1.begin(), dek1.end(), [](double x){return sqrt(x)==int(sqrt(x));})<<" brojeva koji su potpuni kvadrati"<<std::endl;
    std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*std::min_element(dek1.begin(), dek1.end(), [](int x, int y){return int(floor(log10(abs(x)+1)))<floor(log10(abs(y)+1));})<<std::endl;
    int n2=std::count_if(dek1.begin(), dek1.end(), [](int x){return int(floor(log10(abs(x))+1))==3;});
    std::deque<int> dek2(n1-n2);
    std::deque<int>::iterator it=std::remove_copy_if(dek1.begin(), dek1.end(), dek2.begin(), [](int x){return floor(log10(abs(x))+1)==3;});
    std::cout<<"Elementi koji nisu trocifreni su: ";
    std::for_each(dek2.begin(), it, [](int x){std::cout<<x<<" ";});
	return 0;
}