/* 
    TP 2018/2019: LV 6, Zadatak 6
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <new>
#include <type_traits>
#include <vector>
#include <deque>

template <typename Struktura2D> 
auto KreirajDinamickuKopiju2D (Struktura2D matrica) {
    std::remove_reference_t<decltype(matrica[0][0])> **dinamicka{};
    try {
        dinamicka=new std::remove_reference_t<decltype(matrica[0][0])>*[matrica.size()];
        int br_el=0;
        for(int i=0; i<matrica.size(); i++) br_el+=matrica[i].size();
        dinamicka[0]=new std::remove_reference_t<decltype(matrica[0][0])>[br_el];
        for(int i=1; i<matrica.size(); i++) dinamicka[i]=dinamicka[i-1]+matrica[i-1].size();
        for(int i=0; i<matrica.size(); i++) 
            for(int j=0;j<matrica[i].size(); j++) dinamicka[i][j]=matrica[i][j];
    }
    catch(std::bad_alloc) {
        if(dinamicka) delete[] dinamicka;
        throw;
    }
    return dinamicka;
}

int main ()
{
    int n;
    std::cout<<"Unesite broj redova kvadratne matrice: ";
    std::cin>>n;
    try {
    std::vector<std::deque<int>> matrica(n);
    std::cout<<"Unesite elemente matrice: ";
    for(int i=0; i<n; i++) {
        matrica[i].resize(n);
        for(int j=0; j<n; j++) {
            std::cin>>matrica[i][j];
        }
    }
    int **dinamicka{};
    try {
        dinamicka=KreirajDinamickuKopiju2D(matrica);
            for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) std::cout<<dinamicka[i][j]<<" ";
                std::cout<<std::endl;
            }
    }
    catch(std::bad_alloc) {
        std::cout<<"Nedovoljno memorije";
    }
    if(dinamicka) delete[] dinamicka[0];
    delete[] dinamicka;
    }
    catch(std::bad_alloc) {
        std::cout<<"Nedovoljno memorije";
    }
	return 0;
}