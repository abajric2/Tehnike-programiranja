//TP 2016/2017: LV 1, Zadatak 4
#include <iostream>
#include <cmath>
int main ()
{
    for(;;) {
        double n;
        std::cout<<"Unesite prirodan broj ili 0 za kraj: ";
        std::cin>>n;
        if (!std::cin || n!=(int)n || n<0) {
            std::cout<<"Niste unijeli prirodan broj!"<<std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if(n==0) break;
        double suma=0;
        for(int i=1; i<n; i++) if(int(n)%i==0) suma+=i;
        if(suma<n) std::cout<<"Broj "<<n<<" je manjkav!"<<std::endl;
        else if(suma>n) std::cout<<"Broj "<<n<<" je obilan!"<<std::endl;
        else if(suma==n) std::cout<<"Broj "<<n<<" je savrsen!"<<std::endl;
    }
    std::cout<<"Dovidjenja!"<<std::endl;
	return 0;
}