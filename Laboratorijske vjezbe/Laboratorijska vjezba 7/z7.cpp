/* 
    TP 16/17 (LV 7, Zadatak 7)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <set>
#include <string>

template <typename TipEl>
std::set<TipEl> Presjek (std::set<TipEl> s1, std::set<TipEl> s2) {
    std::multiset<TipEl> pomocni;
    for(auto i=s1.begin(); i!=s1.end(); i++) pomocni.insert(*i);
    for(auto i=s2.begin(); i!=s2.end(); i++) pomocni.insert(*i);
    std::set<TipEl> presjek;
    for(auto i=pomocni.begin(); i!=pomocni.end(); i++) if(pomocni.count(*i)>1) presjek.insert(*i);
    return presjek;
}

template <typename TipEl>
std::set<TipEl> Unija (std::set<TipEl> s1, std::set<TipEl> s2) {
    std::set<TipEl> unija;
    for(auto i=s1.begin(); i!=s1.end(); i++) unija.insert(*i);
    for(auto i=s2.begin(); i!=s2.end(); i++) unija.insert(*i);
    return unija;
}

int main ()
{
    std::set<std::string> s1{"Skup za provjeru", "testni", "provjera"};
    std::set<std::string> s2{"Ovo je recenica za provjeru.", "provjera", "testni", "Neka recenica."};
    auto unija=Unija(s1, s2);
    std::cout<<"Unija skupova je: "<<std::endl;
    for(auto el : unija) std::cout<<el<<" ";
    auto presjek=Presjek(s1, s2);
    std::cout<<std::endl<<"Presjek skupova je: "<<std::endl;
    for(auto el : presjek) std::cout<<el<<" ";
	return 0;
}