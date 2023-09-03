//TP 2021/2022: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>

template <typename Tip>
int BrojElemenata (Tip pocetak, Tip iza_kraja) {
    int br_el=0;
    while(pocetak!=iza_kraja) {
        br_el++;
        pocetak++;
    }
    return br_el;
}

template <typename Tip1, typename Tip2>
auto SaberiSaPodrazumijevanim (Tip1, Tip2 y) {
    return Tip1()+y;
}

template <typename Tip1, typename Tip2>
auto ZbirKontejnera (Tip1 kontejner1, Tip2 kontejner2) {
    auto pocetak1=std::begin(kontejner1);
    auto iza_kraja1=std::end(kontejner1);
    auto pocetak2=std::begin(kontejner2);
    auto iza_kraja2=std::end(kontejner2);
    int br_el1=BrojElemenata(pocetak1, iza_kraja1);
    int br_el2=BrojElemenata(pocetak2, iza_kraja2);
    int n;
    if(br_el1<br_el2) n=br_el2;
    else n=br_el1;
    std::vector<decltype(*pocetak1+*pocetak2)> v(n);
    for(int i=0; i<n; i++) {
        if(i>=br_el1) {
            v.at(i)=SaberiSaPodrazumijevanim(*std::begin(kontejner1), *pocetak2);
            pocetak2++;
            continue;
        }
        if(i>=br_el2) {
            v.at(i)=SaberiSaPodrazumijevanim(*std::begin(kontejner2), *pocetak1);
            pocetak1++;
            continue;
        }
        v.at(i)=*pocetak1+*pocetak2;
        pocetak1++; pocetak2++;
    }
    return v;
}

int main ()
{
    int n1;
    std::cout<<"Duzina prvog kontejnera: ";
    std::cin>>n1;
    std::vector<double> v1(n1);
    std::cout<<"Elementi prvog kontejnera: ";
    for(int i=0; i<n1; i++) std::cin>>v1.at(i);
    int n2;
    std::cout<<"Duzina drugog kontejnera: ";
    std::cin>>n2;
    std::vector<double> v2(n2);
    std::cout<<"Elementi drugog kontejnera: ";
    for(int i=0; i<n2; i++) std::cin>>v2.at(i);
    auto zbir=ZbirKontejnera(v1, v2);
    std::cout<<"Zbir kontejnera: ";
    for(int i=0; i<zbir.size(); i++) std::cout<<zbir.at(i)<<" ";
	return 0;
}
