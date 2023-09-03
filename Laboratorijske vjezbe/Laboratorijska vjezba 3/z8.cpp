//TP 2021/2022: LV 3, Zadatak 8
#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>

std::string IzdvojiRijec (std::string s, int n) {
    if(n<1) throw std::range_error("Pogresan redni broj rijeci!");
    int broj_rijeci=0;
    for(int i=0; i<s.length(); i++) {
        if(s[i]!=' ' && (i==0 || s[i-1]==' ')) broj_rijeci++;
    }
    if(n>broj_rijeci) throw std::range_error("Pogresan redni broj rijeci!");
    std::string izdvojena_rijec;
    int redni_broj_rijeci=0;
    for(int i=0; i<s.length(); i++) {
        if(s[i]!=' ' && (i==0 || s[i-1]==' ')) {
            redni_broj_rijeci++;
            if(redni_broj_rijeci==n) {
                while(i<s.length() && s[i]!=' ') {
                    izdvojena_rijec.push_back(s[i]);
                    i++;
                }
                break;
            }
        }
    }
    return izdvojena_rijec;
}
int main ()
{
    int redni_broj;
    std::cout<<"Unesite redni broj rijeci: ";
    std::cin>>redni_broj;
    std::cin.ignore(10000, '\n');
    std::string recenica;
    std::cout<<"Unesite recenicu: ";
    std::getline(std::cin, recenica);
    std::string rijec;
    try {
        rijec=IzdvojiRijec(recenica, redni_broj);
    }
    catch (std::range_error izuzetak) {
        std::cout<<"IZUZETAK: "<<izuzetak.what();
        return 1;
    }
    std::cout<<"Rijec na poziciji "<<redni_broj<<" je "<<rijec;
	return 0;
}
