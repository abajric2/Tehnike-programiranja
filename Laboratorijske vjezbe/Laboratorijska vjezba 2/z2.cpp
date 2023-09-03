//TP 2020/2021: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>

bool TestPerioda (std::vector<double> v, int p) {
    if(!(p>=1 && p<v.size())) return false;
    for(int i=0; i<v.size()-p; i++) if(v.at(i)!=v.at(i+p)) return false;
    return true;
}
int OdrediOsnovniPeriod (std::vector<double> v) {
    for(int i=1; i<v.size(); i++) if(TestPerioda(v, i)) return i;
    return 0;
}
int main ()
{
    std::vector<double> v;
    double broj;
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    do {
        std::cin>>broj;
        if(broj!=0) v.push_back(broj);
    } while (broj!=0);
    if(OdrediOsnovniPeriod(v)==0) std::cout<<"Slijed nije periodican!";
    else std::cout<<"Slijed je periodican sa osnovnim periodom "<<OdrediOsnovniPeriod(v)<<".";
    return 0;
}
