//TP 2021/2022: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <array>
#include <stdexcept>
#include <cctype>

typedef std::vector<std::string> VektorStringova;

bool AlfanumerickiZnak (char znak) {
    if((znak>='0' && znak<='9') || (znak>='A' && znak<='Z') || (znak>='a' && znak<='z')) return true;
    else return false;
}

std::array <VektorStringova, 100> RazvrstajRijeciPoDuzini (std::string s) {
    std::array <VektorStringova, 100> niz;
    for(int i=0; i<s.length(); i++) {
        std::string rijec;
        if(AlfanumerickiZnak(s.at(i)) && (i==0 || !AlfanumerickiZnak(s.at(i-1)))) {
            while(i<s.length() && AlfanumerickiZnak(s.at(i))) {
                rijec.push_back(std::toupper(s.at(i)));
                i++;
            }
        }
        int indeks=rijec.length();
        if(indeks>99) throw std::range_error("Predugacka rijec!");
        if(indeks!=0) niz.at(indeks).push_back(rijec);
    }
    return niz;
}

int main ()
{
    std::string s;
    std::cout<<"Unesite recenicu: "<<std::endl;
    std::getline(std::cin, s);
    std::array<VektorStringova, 100> niz;
    try {
        niz=RazvrstajRijeciPoDuzini(s);
    }
    catch(std::range_error izuzetak) {
        std::string s=izuzetak.what();
        if(s=="Predugacka rijec!") {
            std::cout<<"Greska: Recenica sadrzi predugacku rijec!";
            return 1;
        } 
        std::cout<<izuzetak.what()<<std::endl;
        return 1;
    }
    for(int i=0; i<100; i++) {
        if(niz.at(i).size()!=0) {
            std::cout<<"Duzina "<<i<<": ";
            for(int j=0; j<niz.at(i).size(); j++) std::cout<<niz.at(i).at(j)<<" ";
            std::cout<<std::endl;
        }
    }
	return 0;
}
