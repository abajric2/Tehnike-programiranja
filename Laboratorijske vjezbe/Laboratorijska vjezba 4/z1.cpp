//TP 2021/2022: LV 4, Zadatak 1
#include <iostream>
#include <cmath>

int Cifre (long long int n, int &c_min, int &c_max) {
    int cifra=n%10;
    if(cifra<0) cifra=-cifra;
    c_min=cifra;
    c_max=cifra;
    int broj_cifara=0;
    do {
        broj_cifara++;
        cifra=n%10;
        if(cifra<0) cifra=-cifra;
        if(cifra<c_min) c_min=cifra;
        if(cifra>c_max) c_max=cifra;
        n/=10;
    } while(n!=0);
    return broj_cifara;
}
int main ()
{
    long long int n;
    std::cout<<"Unesite broj: "<<std::endl;
    std::cin>>n;
    int c_min, c_max, broj_cifara;
    broj_cifara=Cifre(n, c_min, c_max);
    std::cout<<"Broj "<<n<<" ima "<<broj_cifara<<" cifara, najveca je "<<c_max<<" a najmanja "<<c_min<<".";
	return 0;
}
