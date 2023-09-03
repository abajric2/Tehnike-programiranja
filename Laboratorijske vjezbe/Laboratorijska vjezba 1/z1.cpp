//TP 2016/2017: LV 1, Zadatak 1
#include <iostream>
#include <cmath>
int main ()
{
    int a, b, c;
    std::cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    std::cin>>a>>b>>c;
    int d;
    std::cout<<"Unesite sirinu plocice u centimetrima: "<<std::endl;
    std::cin>>d;
    a*=100; //Pretvorimo sve u cm
    b*=100;
    c*=100;
    if(a%d!=0 || b%d!=0 || c%d!=0) {
        std::cout<<"Poplocavanje  bazena dimenzija "<<a/100<<"x"<<b/100<<"x"<<c/100<<"m sa plocicama dimenzija "
        <<d<<"x"<<d<<"cm nije izvodljivo bez lomljenja plocica!"<<std::endl;
        return 0;
    }
    std::cout<<"Za poplocavanje bazena dimenzija "<<a/100<<"x"<<b/100<<"x"<<c/100<<"m sa plocicama dimenzija "
    <<d<<"x"<<d<<"cm potrebno je "<<(a*b+2*a*c+2*b*c)/(d*d)<<" plocica."<<std::endl;
	return 0;
}