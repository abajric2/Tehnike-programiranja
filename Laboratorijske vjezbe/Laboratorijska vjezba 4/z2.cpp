//TP 2021/2022: LV 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <string>

void IzvrniString (std::string &s) {
    for(int i=s.size()-1; i>=0; i--) s.push_back(s[i]);
    s.erase(0, s.size()/2);
}
int main ()
{
    std::string s;
    std::cout<<"Unesi string: "<<std::endl;
    std::getline(std::cin, s);
    IzvrniString(s);
    std::cout<<"Izvrnuti string je: "<<s;
	return 0;
}
