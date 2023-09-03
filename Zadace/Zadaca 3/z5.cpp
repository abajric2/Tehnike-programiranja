//TP 2021/2022: Zadaća 3, Zadatak 5
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <set>
#include <stdexcept>

struct Dijete {
    std::string ime;
    Dijete *sljedeci;
};

bool AlfanumerickiZnak (char znak) {
    return (znak>='0' && znak<='9') || (znak>='A' && znak<='a') || (znak>='a' && znak<='z');
}

int BrojSlova (std::string s) {
    int broj_slova=0;
    for(auto i=s.begin(); i!=s.end(); i++) if(AlfanumerickiZnak(*i)) broj_slova++;
    return broj_slova;
}

auto KreirajListu (std::vector<std::string> v) {
    Dijete *pocetak=nullptr, *prethodni;
    for(int i=0; i<v.size(); i++) {
        Dijete *novi=new Dijete{v.at(i), nullptr};
        if(!pocetak) pocetak=novi;
        else prethodni->sljedeci=novi;
        prethodni=novi;
    }
    if(pocetak) prethodni->sljedeci=pocetak;
    return pocetak;
}
auto NadjiPrethodni(Dijete *p, int br_el) {
    int brojac=0;
    for(auto i=p; brojac++<br_el; i=i->sljedeci) if(i->sljedeci==p) return i;
    return p;
}
std::vector<std::set<std::string>> Razvrstavanje (std::vector<std::string> imena_djece, int broj_timova) {
    if(broj_timova<1 || broj_timova>imena_djece.size()) throw std::logic_error("Razvrstavanje nemoguce");
    int redni_broj_tima=0;
    int br_clanova=imena_djece.size()/broj_timova+1;
    auto djeca=KreirajListu(imena_djece);
    std::vector<std::set<std::string>> v;
    int br_djece=imena_djece.size();
    for(;;) {
        std::set<std::string> tim;
        redni_broj_tima++;
        if(redni_broj_tima>broj_timova) break;
        if(redni_broj_tima==br_djece%broj_timova+1) br_clanova--;
        for(;;) {
            if(tim.size()<br_clanova) tim.insert(djeca->ime);
            else {
                v.push_back(tim);
                break;
            }
            int korak=BrojSlova(djeca->ime);
            auto prethodni=NadjiPrethodni(djeca, br_djece);
            prethodni->sljedeci=djeca->sljedeci;
            auto za_obrisat=djeca;
            for(int i=0; i<korak; i++) djeca=djeca->sljedeci;
            delete za_obrisat;
        }
    }
    return v;
}
int main ()
{
    int broj_djece=0;
    std::cout<<"Unesite broj djece: "<<std::endl;
    std::cin>>broj_djece;
    std::cin.ignore(10000, '\n');
    std::vector<std::string> imena_djece(broj_djece);
    std::cout<<"Unesite imena djece: "<<std::endl;
    for(int i=0; i<broj_djece; i++) std::getline(std::cin, imena_djece.at(i));
    int broj_timova=0;
    std::cout<<"Unesite broj timova: "<<std::endl;
    std::cin>>broj_timova;
    try {
        auto timovi=Razvrstavanje(imena_djece, broj_timova);
        for(int i=0; i<broj_timova; i++) {
            std::cout<<"Tim "<<i+1<<": ";
            for(auto it=timovi.at(i).begin(); it!=timovi.at(i).end(); it++) {
                std::cout<<*it;
                if(std::distance(it, timovi.at(i).end())>1) std::cout<<", ";
            }
            std::cout<<std::endl;
        }
    }
    catch(std::logic_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
	return 0;
}
