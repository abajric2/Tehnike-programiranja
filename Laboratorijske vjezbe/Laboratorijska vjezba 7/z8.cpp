/* 
    TP 16/17 (LV 7, Zadatak 8)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>

std::string IzvrniBezRazmaka (std::string s) {
    std::string s2;
    std::remove_copy(s.rbegin(), s.rend(), std::back_inserter(s2), ' ');
    return s2;
}

int main ()
{
    std::string s;
    std::cout<<"Unesite neku recenicu: "<<std::endl;
    std::getline(std::cin, s);
    s=IzvrniBezRazmaka(s);
    std::cout<<"Recenica izvrnuta bez razmaka glasi: "<<std::endl;
    std::cout<<s;
	return 0;
}