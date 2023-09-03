/* 
    TP 16/17 (LV 7, Zadatak 9)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <functional>

std::function<double(double)> plus2 (double x) {
    return [x](double y) {return x+y;};
}

std::function<std::function<double(double)>(double)> plus3 (double x) {
    return [x](double y) {return [x, y](double z) {return x+y+z;};};
}
int main ()
{
    double x, y;
    std::cout<<"Unesi dva broja: "<<std::endl;
    std::cin>>x>>y;
    std::cout<<"Zbir unesenih brojeva je: "<<plus2(x)(y);
    double a, b, c;
    std::cout<<std::endl<<"Unesi tri broja: "<<std::endl;
    std::cin>>a>>b>>c;
    std::cout<<"Zbir unesenih brojeva je: "<<plus3(a)(b)(c);
	return 0;
}