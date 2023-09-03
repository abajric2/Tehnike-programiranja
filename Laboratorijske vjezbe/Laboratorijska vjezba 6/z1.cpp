/* 
    TP 2018/2019: LV 6, Zadatak 1
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cmath>

template <typename TipElemenata>
TipElemenata *GenerirajStepeneDvojke (int n) {
    if(n<=0) throw std::domain_error("Broj elemenata mora biti pozitivan");
    if(std::numeric_limits<TipElemenata>::max()<powl(2,n-1)) throw std::overflow_error("Prekoracen dozvoljeni opseg");
    try {
        TipElemenata *niz=new TipElemenata[n];
        for(TipElemenata *i=niz; i<niz+n; i++) {
            *i=1;
            for(int j=0; j<i-niz; j++) *i*=2;
        }
        return niz;
    } 
    catch(std::domain_error) {
        throw;
    }
    catch(std::overflow_error) {
        throw;
    }
    catch(std::runtime_error) {
        throw;
    }
}
int main ()
{
    int n;
    std::cout<<"Koliko zelite elemenata: ";
    std::cin>>n;
    long long int *niz=nullptr;
    try {
        niz=GenerirajStepeneDvojke<long long int>(n);
        for(long long int *i=niz; i<niz+n; i++) std::cout<<*i<<" ";
    }
    catch (std::domain_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
    catch(std::overflow_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
    catch (std::runtime_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
    delete[] niz;
	return 0;
}