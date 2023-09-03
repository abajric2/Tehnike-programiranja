//TP 2021/2022: Zadaća 2, Zadatak 4
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

template <typename TipElemenata>
using Matrica=std::vector<std::vector<TipElemenata>>;

template <typename TipElemenata>
TipElemenata SumaReda (std::vector<TipElemenata> x) {
    TipElemenata suma=TipElemenata();
    for(auto i=std::begin(x); i!=std::end(x); i++) suma+=*i;
    return suma;
}

template <typename TipElemenata>
bool Kriterij (std::vector<TipElemenata> x, std::vector<TipElemenata> y) {
    if(SumaReda(x)==SumaReda(y)) return x<y;
    return SumaReda(x)>SumaReda(y);
}

template <typename TipElemenata>
void SortirajPoSumiRedova (Matrica<TipElemenata> &m) {
    std::sort(std::begin(m), std::end(m), Kriterij<TipElemenata>);
}

Matrica<int> UnesiMatricu() {
    Matrica<int> m;
    int br_redova=0;
    bool kraj_reda;
    for(;;) {
        int element;
        if(std::cin>>element) {
            if(br_redova==0 || kraj_reda)  {
                m.resize(br_redova+1); 
                br_redova++; 
                kraj_reda=false;
            }
            m.at(br_redova-1).push_back(element);
        }
        else {
            if(br_redova==0 || kraj_reda) return m;
            kraj_reda=true;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } 
    }
}

template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> m) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m.at(i).size(); j++) std::cout<<m.at(i).at(j)<<" ";
        std::cout<<std::endl;
    }
}

int main ()
{
    std::cout<<"Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): "<<std::endl;
    Matrica<int> m;
    m=UnesiMatricu();
    SortirajPoSumiRedova(m);
    std::cout<<"Matrica nakon sortiranja: "<<std::endl;
    IspisiMatricu(m);
	return 0;
}
