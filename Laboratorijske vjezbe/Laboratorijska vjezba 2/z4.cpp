//TP 2020/2021: Tutorijal 2, Zadatak 4
#include <iostream>
#include <complex>

int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata: "<<std::endl;
    std::cin>>n;
    std::complex<double> nazivnik(0);
    for(int i=0; i<n; i++) {
        double aktivni_otpor, reaktivni_otpor;
        std::cout<<"R"<<i+1<<" = ";
        std::cin>>aktivni_otpor;
        std::cout<<"X"<<i+1<<" = ";
        std::cin>>reaktivni_otpor;
        nazivnik+=1./std::complex<double> (aktivni_otpor, reaktivni_otpor);
    }
    std::complex<double> impedansa=1./nazivnik;
    std::cout<<"Paralelna veza ovih elemenata ima R = "
    <<std::real(impedansa)<<" i X = "<<std::imag(impedansa)<<".";
    return 0;
}
