/* 
    TP 16/17 (LV 7, Zadatak 10)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <functional>

std::function<int(int)> IteriranaFunkcija (std::function<int(int)> f, int n) {
    return [f, n](int x){for(int i=0; i<n; i++) x=f(x); return x;};
}

int main ()
{
    int n;
    std::cout<<"Broj uzastopnih pozivanja funkcije: "<<std::endl;
    std::cin>>n;
    int x;
    std::cout<<"Argument funkcije: "<<std::endl;
    std::cin>>x;
    std::cout<<"n puta primijenjena funkcija nad unesenim argumentom daje: "<<IteriranaFunkcija([](int x){return 2*x;}, n)(x);
	return 0;
}