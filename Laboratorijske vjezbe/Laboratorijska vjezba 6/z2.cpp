/* 
    TP 2018/2019: LV 6, Zadatak 2
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <new>
#include <vector>

template<typename IterTip>
auto KreirajIzvrnutiNiz(IterTip pocetak, IterTip kraj) {
    int br_el=0;
    IterTip pomocna=pocetak;
    while(pomocna!=kraj) {
        br_el++; 
        pomocna++;
    }
    try {
        auto niz=new std::remove_reference_t<decltype(*pocetak)>[br_el];
        for(int i=br_el-1; i>=0; i--) niz[i]=*pocetak++;
        return niz;
    }
    catch(std::bad_alloc) {
        throw;
    }
}
int main ()
{
    int n;
    std::cout<<"Koliko zelite elemenata: ";
    std::cin>>n;  
    double *niz=nullptr;
    try {
        std::vector<double> v(n);
        std::cout<<"Unesite elemente: ";
        for(double &x : v) std::cin>>x;
        niz=KreirajIzvrnutiNiz(v.begin(), v.end());
        std::cout<<"Kreirani niz: ";
        for(double *i=niz; i<niz+n; i++) std::cout<<*i<<" ";
    }
    catch(...) {
        std::cout<<"Nedovoljno memorije!";
    }
    delete[] niz;
	return 0;
}