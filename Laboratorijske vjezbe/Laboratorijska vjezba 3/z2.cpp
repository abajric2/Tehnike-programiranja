//TP 2021/2022: LV 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>

int suma (int n) {
    int suma=0;
    while(n!=0) {
        suma+=n%10;
        n/=10;
    }
    return suma;
}
std::vector<int> IzdvojiElemente (std::vector<int> v1, bool parna_suma) {
    std::vector<int> v2;
    for(auto element : v1) {
        if(parna_suma && suma(element)%2==0) v2.push_back(element);
        if(!parna_suma && suma(element)%2!=0) v2.push_back(element);
    }
    return v2;
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
    std::vector<int> a(n);
    std::cout<<"Unesite elemente: ";
    for(int i=0; i<n; i++) std::cin>>a[i];
    std::vector<int> b{IzdvojiElemente(a, true)}, c{IzdvojiElemente(a, false)};
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
