/* 
    TP 16/17 (LV 7, Zadatak 2)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cstring>
#include <algorithm>

int main ()
{
    int br_recenica;
    std::cout<<"Koliko zelite recenica: "<<std::endl;
    std::cin>>br_recenica;
    std::cin.ignore(10000, '\n');
    char** recenice{};
    try {
        std::cout<<"Unesite recenice: "<<std::endl;
        recenice=new char *[br_recenica]{};
        for(int i=0; i<br_recenica; i++) {
            char recenica[1000];
            std::cin.getline(recenica, sizeof recenica);
            recenice[i]=new char [std::strlen(recenica)+1];
            std::strcpy(recenice[i], recenica);
        }
        std::sort(recenice, recenice+br_recenica, [](const char *x, const char *y) {return std::strcmp(x,y)<0;});
        std::cout<<"Sortirane recenice: "<<std::endl;
        for(int i=0; i<br_recenica; i++) std::cout<<recenice[i]<<std::endl;
        for(int i=0; i<br_recenica; i++) delete[] recenice[i];
        delete[] recenice;
    }
    catch(std::bad_alloc) {
        if(recenice) for(int i=0; i<br_recenica; i++) delete[] recenice[i];
        delete[] recenice;
        std::cout<<"Problemi s memorijom!";
        return 1;
    }
	return 0;
}