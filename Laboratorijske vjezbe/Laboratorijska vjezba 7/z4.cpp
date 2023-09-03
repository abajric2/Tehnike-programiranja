/* 
    TP 16/17 (LV 7, Zadatak 4)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <memory>

typedef std::shared_ptr<std::string> pok_na_string;

int main ()
{
    int br_recenica;
    std::cout<<"Koliko zelite recenica: "<<std::endl;
    std::cin>>br_recenica;
    std::cin.ignore(10000, '\n');
    try{
        std::cout<<"Unesite recenice: "<<std::endl;
        auto recenice=std::make_unique<pok_na_string[]>(br_recenica);
        for(int i=0; i<br_recenica; i++) {
            recenice[i]=std::make_shared<std::string>();//std::shared_ptr<std::string>(new std::string);
            std::getline(std::cin, *recenice[i]);
        }
        std::sort(recenice.get(), recenice.get()+br_recenica, [](auto x, auto y) {return *x<*y;});
        std::cout<<"Sortirane recenice: "<<std::endl;
        for(int i=0; i<br_recenica; i++) std::cout<<*recenice[i]<<std::endl;
    }
    catch(std::bad_alloc) {
        std::cout<<"Problemi s memorijom!";
        return 1;
    }
	return 0;
}