/* 
    TP 16/17 (LV 7, Zadatak 6)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <list>

template <typename TipEl>
std::list<TipEl> SortirajListu(std::list<TipEl> &l) {
    std::list<TipEl> l2;
    //auto it=l2.begin();
    for(auto i=l.begin(); i!=l.end(); i++) {
        auto min=i;
        for(auto j=std::next(i); j!=l.end(); j++) {
            if(*j<*min) min=j;
        }
        l2.push_back(*min);
        //l2.insert(it++, *min);
        auto pomocna=*i;
        *i=*min;
        *min=pomocna;
    }
    return l2;
}
int main ()
{
    int n;
    std::cout<<"Koliko ima elemenata: "<<std::endl;
    std::cin>>n;
    std::list<int> l;
    auto it=l.begin();
    std::cout<<"Unesite elemente: "<<std::endl;
    for(int i=0; i<n; i++) {
        int element;
        std::cin>>element;
        l.insert(it++, element);
    }
    l=SortirajListu(l);
    std::cout<<"Sortirana lista: "<<std::endl;
    for(auto el : l) std::cout<<el<<" ";
	return 0;
}