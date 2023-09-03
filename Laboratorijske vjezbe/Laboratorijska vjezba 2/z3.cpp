//TP 2020/2021: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>

int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata: "<<std::endl;
    std::cin>>n;
    std::complex<double> nazivnik(0);
    for(int i=0; i<n; i++) {
        std::complex<double> z;
        std::cout<<"Z_"<<i+1<<" = ";
        std::cin>>z;
        nazivnik+=1./z;
    }
    std::complex<double> impedansa=1./nazivnik;
    std::cout<<std::endl<<"Paralelna veza ovih elemenata ima impedansu Z_ = "<<impedansa<<".";
    return 0;
}
