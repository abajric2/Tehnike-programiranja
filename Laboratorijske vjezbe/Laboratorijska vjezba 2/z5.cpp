//TP 2020/2021: Tutorijal 2, Zadatak 5
#include <iostream>
#include <complex>
#include <cmath>

int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata: "<<std::endl;
    std::cin>>n;
    std::complex<double> nazivnik(0);
    const double PI=4*atan(1);
    for(int i=0; i<n; i++) {
        double prividni_otpor, fazni_pomak;
        std::cout<<"Z"<<i+1<<" = ";
        std::cin>>prividni_otpor;
        std::cout<<"fi"<<i+1<<" = ";
        std::cin>>fazni_pomak;
        nazivnik+=1./std::polar(prividni_otpor, fazni_pomak*(PI/180));
    }
    std::complex<double> impedansa=1./nazivnik;
    std::cout<<"Paralelna veza ovih elemenata ima Z = "
    <<std::abs(impedansa)<<" i fi = "<<std::arg(impedansa)*(180/PI)<<".";
    return 0;
}
