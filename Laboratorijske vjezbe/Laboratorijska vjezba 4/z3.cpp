//TP 2021/2022: LV 4, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>

typedef std::vector<std::string> VektorStringova;

void PretvoriUVelikaSlova (VektorStringova &v) {
    for(int i=0; i<v.size(); i++) {
        for(int j=0; j<v[i].size(); j++) {
            if(v[i][j]>='a' && v[i][j]<='z') v[i][j]+='A'-'a';
        }
    }
}
void NadjiIndexeRijeci(const VektorStringova &pomocni, int &index_prve_rijeci, int &index_posljednje_rijeci) {
    std::string prva_rijec=pomocni[0];
    std::string posljednja_rijec=pomocni[0];
    index_prve_rijeci=0;
    index_posljednje_rijeci=0;
    for(int i=1; i<pomocni.size(); i++) {
        if(pomocni[i]<prva_rijec) {
            index_prve_rijeci=i;
            prva_rijec=pomocni[i];
        }
        if(pomocni[i]>posljednja_rijec) {
            index_posljednje_rijeci=i;
            posljednja_rijec=pomocni[i];
        }
    }
}
void IzdvojiKrajnjeRijeci (const VektorStringova &v, std::string &prva_rijec, std::string &posljednja_rijec) {
    if(v.size()==0)  {
        std::string s;
        prva_rijec=s;
        posljednja_rijec=s;
        return;
    }
    VektorStringova pomocni=v;
    PretvoriUVelikaSlova(pomocni);
    int index_prve_rijeci, index_posljednje_rijeci;
    NadjiIndexeRijeci(pomocni, index_prve_rijeci, index_posljednje_rijeci);
    prva_rijec=v[index_prve_rijeci];
    posljednja_rijec=v[index_posljednje_rijeci];  
}
void ZadrziDuplikate(VektorStringova &v) {
    VektorStringova ponavljajuce_rijeci;
    for(int i=0; i<v.size(); i++) {
        for(int j=i+1; j<v.size(); j++) {
            if(v[j]==v[i]) {
                int ista_rijec=0;
                for(int k=0; k<ponavljajuce_rijeci.size(); k++) {
                    if(v[i]==ponavljajuce_rijeci[k]) ista_rijec=1;
                }
                if(ista_rijec) break;
                ponavljajuce_rijeci.push_back(v[i]);
                break;
            }
        }
    }
    v=ponavljajuce_rijeci;
}
int main ()
{
    int n;
    std::cout<<"Koliko zelite unijeti rijeci: "<<std::endl;
    std::cin>>n;
    VektorStringova v(n);
    std::cout<<"Unesite rijeci: "<<std::endl;
    for(int i=0; i<n; i++) std::cin>>v[i];
    std::string prva_rijec, posljednja_rijec;
    IzdvojiKrajnjeRijeci(v, prva_rijec, posljednja_rijec);
    std::cout<<"Prva rijec po abecednom poretku je: "<<prva_rijec<<std::endl;
    std::cout<<"Posljednja rijec po abecednom poretku je: "<<posljednja_rijec<<std::endl;
    ZadrziDuplikate(v);
    std::cout<<"Rijeci koje se ponavljaju su: ";
    for(int i=0; i<v.size(); i++) std::cout<<v[i]<<" ";
	return 0;
}
