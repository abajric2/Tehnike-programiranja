//TP 2021/2022: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>

bool DaLiJeProst (int n) {
    if(n<=1) return false;
    for(int i=2; i<=sqrt(n); i++) if(n%i==0) return false;
    return true;
}
void Goldbach (int n, int &p, int &q) {
    if(n<=2) throw std::logic_error("Rastava ne postoji");
    for(int i=2; i<n-1; i++) {
        if(n%2!=0 && i>2) break;
        bool prost=DaLiJeProst(i);
        if(prost) {
            bool pronadjeno=DaLiJeProst(n-i);
            if(pronadjeno) {
                p=i; 
                q=n-i;
                return;
            }
        }
    }
    throw std::logic_error("Rastava ne postoji");
}
int main ()
{
    int broj;
    std::cout<<"Unesi broj: ";
    std::cin>>broj;
    try {
        int p, q;
        Goldbach(broj, p, q);
        std::cout<<broj<<" je zbir prostih brojeva "<<p<<" i "<<q;
    }
    catch(std::logic_error) {
        std::cout<<broj<<" nije zbir dva prosta broja!";
    }
	return 0;
}
