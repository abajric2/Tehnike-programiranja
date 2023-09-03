//TP 2021/2022: LV 3, Zadatak 4
#include <iostream>
#include <cmath>
#include <deque>

int suma (int n) {
    int suma=0;
    while(n!=0) {
        suma+=n%10;
        n/=10;
    }
    return suma;
}
std::deque<int> IzdvojiElemente (std::deque<int> d1, bool parna_suma) {
    std::deque<int> d2;
    for(auto element : d1) {
        if(parna_suma && suma(element)%2==0) d2.push_front(element);
        if(!parna_suma && suma(element)%2!=0) d2.push_front(element);
    }
    return d2;
}
int main ()
{
    int n;
    std::cout<<"Koliko zelite unijeti elemenata: ";
    std::cin>>n;
    if(n==0) {
        std::cout<<"Broj elemenata mora biti veci od 0!";
        return 1;
    }
    std::deque<int> a(n);
    std::cout<<"Unesite elemente: ";
    for(int i=0; i<n; i++) std::cin>>a[i];
    std::deque<int> b{IzdvojiElemente(a, true)}, c{IzdvojiElemente(a, false)};
    for(int i=0; i<b.size(); i++) {
        std::cout<<b[i];
        if(i<b.size()-1) std::cout<<",";
        else std::cout<<std::endl;
    }
    for(int i=0; i<c.size(); i++) {
        std::cout<<c[i];
        if(i<c.size()-1) std::cout<<",";
        else std::cout<<std::endl;
    }

	return 0;
}
