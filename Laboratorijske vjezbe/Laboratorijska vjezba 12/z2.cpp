/* 
    TP 16/17 (LV 12, Zadatak 2)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <set>
#include <utility>

template <typename TipEl>
std::set<TipEl> &operator *=(std::set<TipEl> &s1, const std::set<TipEl> &s2) {
    std::multiset<TipEl> pomocni;
    for(auto i=s1.begin(); i!=s1.end(); i++) pomocni.insert(*i);
    for(auto i=s2.begin(); i!=s2.end(); i++) pomocni.insert(*i);
    std::set<TipEl> presjek;
    for(auto i=pomocni.begin(); i!=pomocni.end(); i++) if(pomocni.count(*i)>1) presjek.insert(*i);
    s1=presjek;
    return s1;
}

template <typename TipEl>
std::set<TipEl> &operator +=(std::set<TipEl> &s1, const std::set<TipEl> &s2) {
    std::set<TipEl> unija;
    for(auto i=s1.begin(); i!=s1.end(); i++) unija.insert(*i);
    for(auto i=s2.begin(); i!=s2.end(); i++) unija.insert(*i);
    s1=unija;
    return s1;
}
template <typename TipEl>
std::set<TipEl> operator +(const std::set<TipEl> &s1, const std::set<TipEl> &s2) {
    std::set<TipEl> s=s1; s+=s2; return s;
}
template <typename TipEl>
std::set<TipEl> operator *(const std::set<TipEl> &s1, const std::set<TipEl> &s2) {
    std::set<TipEl> s=s1; s*=s2; return s;
} 
template<typename Tip1, typename Tip2>
std::ostream &operator<< (std::ostream &tok, const std::pair<Tip1, Tip2> &p) {
    return tok<<"("<<p.first<<","<<p.second<<")";
}
template <typename TipEl>
std::ostream &operator <<(std::ostream &tok, const std::set<TipEl> &s) {
    tok<<"{";
    for(auto it=s.begin(); it!=s.end(); it++) {
        tok<<*it;
        if(std::next(it)!=s.end()) tok<<",";
    }
    tok<<"}";
    return tok;
}
template <typename Tip1, typename Tip2>
std::set<std::pair<Tip1, Tip2>> operator %(const std::set<Tip1> &s1, const std::set<Tip2> &s2) {
    std::set<std::pair<Tip1, Tip2>> p;
    for(auto it=s1.begin(); it!=s1.end(); it++) {
        for(auto it2=s2.begin(); it2!=s2.end(); it2++) {
            p.insert({*it, *it2});
        }
    }
    return p;
}

int main ()
{
    std::set<int> s1{1,2,3,4}, s2{3,4,5,6};
    s1+=s2;
    std::cout<<s1<<std::endl;
    std::cout<<s1*s2<<std::endl;
    std::set<char> s3{'A', 'B', 'C'};
    std::set<int> s4{1,2};
    std::cout<<s3%s4;

	return 0;
}