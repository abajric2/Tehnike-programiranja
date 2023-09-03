/* 
    TP 16/17 (LV 12, Zadatak 5)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main ()
{
    int n;
    std::cout<<"Koliko zelite elemenata: "<<std::endl;
    std::cin>>n;
    std::vector<double> v(n);
    std::cout<<"Unesite elemente: "<<std::endl;
    for(int i=0; i<n; i++) std::cin>>v[i];
    std::transform(v.begin(), v.end(), v.begin(), std::bind(std::divides<double>(), 1, std::placeholders::_1));
    std::cout<<"Transformirani elementi: ";
    for(int i=0; i<n; i++) std::cout<<v[i]<<" ";
	return 0;
}