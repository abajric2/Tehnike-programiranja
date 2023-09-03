//TP 2021/2022: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <set>
#include <algorithm>

bool AlfanumerickiZnak (char znak) {
    return (znak>='A' && znak<='Z') || (znak>='a' && znak<='z') || (znak>='0' && znak<='9');
}

std::map<std::string, std::set<int>> KreirajIndeksPojmova (std::string s) {
    std::map<std::string, std::set<int>> m;
    std::for_each(s.begin(), s.end(), [](char &znak) {if(znak>='A' && znak<='Z') znak+='a'-'A';});
    for(auto i=s.begin(); i!=s.end(); i++) {
        if(AlfanumerickiZnak(*i)) {
            std::string rijec;
            while(i!=s.end() && AlfanumerickiZnak(*i)) rijec.push_back(*i++);
            i--;
            if(m.count(rijec)) continue;
            std::set<int> pozicije;
            for(auto j=s.begin(); j!=s.end(); j++) {
                if(std::distance(j, s.end())>=rijec.size() && s.substr(j-s.begin(), rijec.size())==rijec && (j==s.begin() || !AlfanumerickiZnak(*std::prev(j,1)))
                && (std::next(j, rijec.size())==s.end() || !AlfanumerickiZnak(*std::next(j, rijec.size())))) pozicije.insert(j-s.begin());
            }
            m.insert({rijec, pozicije});
        }
    }
    return m;
}

std::set<int> PretraziIndeksPojmova (std::string rijec, std::map<std::string, std::set<int>> indeks_pojmova) {
    for(auto el : indeks_pojmova) {
        if(el.first.length()==rijec.length() && std::equal(el.first.begin(), el.first.end(), rijec.begin(), 
        [](char znak1, char znak2){if(znak1>='A' && znak1<='Z') znak1+='a'-'A'; if(znak2>='A' && znak2<='Z') znak2+='a'-'A'; return znak1==znak2;})) 
        return indeks_pojmova[el.first];
    }
    throw std::logic_error("Pojam nije nadjen");
}

void IspisiIndeksPojmova (std::map<std::string, std::set<int>> indeks_pojmova) {
    for(auto el : indeks_pojmova) {
        std::cout<<el.first<<": ";
        for(auto i=el.second.begin(); i!=el.second.end(); i++) {
            std::cout<<*i;
            if(i!=std::next(el.second.begin(),el.second.size()-1)) std::cout<<",";
        }
        std::cout<<std::endl;
    }
}

void IspisiSkup(std::set<int> skup) {
    for(auto el : skup) std::cout<<el<<" ";
    std::cout<<std::endl;
}
int main ()
{
    std::string s;
    std::cout<<"Unesite tekst: "<<std::endl;
    std::getline(std::cin, s);
    auto indeks_pojmova=KreirajIndeksPojmova(s);
    IspisiIndeksPojmova(indeks_pojmova);
    for(;;) {
        std::string rijec;
        std::cout<<"Unesite rijec: "<<std::endl;
        std::getline(std::cin, rijec);
        if(rijec==".") break;
        try {
        IspisiSkup(PretraziIndeksPojmova(rijec, indeks_pojmova));
        }
        catch(std::logic_error) {
            std::cout<<"Unesena rijec nije nadjena!"<<std::endl;
        }
    }
	return 0;
}
