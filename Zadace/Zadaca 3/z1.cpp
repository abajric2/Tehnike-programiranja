//TP 2021/2022: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <stdexcept>
#include <iomanip>

std::function<double(double)> BaricentricnaInterpolacija (std::vector<std::pair<double, double>> cvorovi, int d) {
    if(d<0 || d>=cvorovi.size()) throw std::domain_error("Nedozvoljen red");
    for(int i=0; i<cvorovi.size(); i++) {
        for(int j=i+1; j<cvorovi.size(); j++) if(cvorovi.at(i).first==cvorovi.at(j).first) throw std::domain_error("Neispravni cvorovi");
    }
    std::vector<double> koeficijenti(cvorovi.size());
    for(int i=0; i<cvorovi.size(); i++) {
        int k;
        if(0>i-d) k=0; else k=i-d;
        int gornja_granica;
        if(i<cvorovi.size()-1-d) gornja_granica=i; else gornja_granica=cvorovi.size()-1-d;
        double suma=0;
        for(;k<=gornja_granica; k++) {
            double proizvod=std::pow(-1,k-1);
            for(int j=k; j<=k+d; j++) if(j!=i) proizvod*=1./(cvorovi.at(i).first-cvorovi.at(j).first);
            suma+=proizvod;
        }
        koeficijenti.at(i)=suma;
    }
    return [koeficijenti, cvorovi](double x){
        double brojnik=0, nazivnik=0;
        for(int i=0; i<cvorovi.size(); i++) {
            if(x==cvorovi.at(i).first) return cvorovi.at(i).second;
            brojnik+=(koeficijenti.at(i)*cvorovi.at(i).second)/(x-cvorovi.at(i).first);
            nazivnik+=koeficijenti.at(i)/(x-cvorovi.at(i).first);
        }
        return brojnik/nazivnik;
    };
}

std::function<double(double)> BaricentricnaInterpolacija(std::function<double(double)> fun, double Xmin, double Xmax, double deltaX, int d) {
    if(Xmin>Xmax || deltaX<=0) throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double, double>> cvorovi;
    for(double x=Xmin; x<=Xmax; x+=deltaX) {
        cvorovi.push_back({x, fun(x)});
    }
    return BaricentricnaInterpolacija(cvorovi, d);
}

double f (double x) {
    return x*x+std::sin(x);
}

int main ()
{
    int opcija;
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    std::cin>>opcija;
    switch(opcija) {
    case 1: {
        int n;
        std::cout<<"Unesite broj cvorova: ";
        std::cin>>n;
        std::vector<std::pair<double, double>> cvorovi(n);
        std::cout<<"Unesite cvorove kao parove x y: ";
        for(int i=0; i<n; i++) std::cin>>cvorovi.at(i).first>>cvorovi.at(i).second;
        int d;
        std::cout<<"Unesite red interpolacije: ";
        std::cin>>d;
        double arg;
        try {
        do {
            auto fun=BaricentricnaInterpolacija(cvorovi, d);
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>arg;
            if(std::cin) std::cout<<"f("<<arg<<") = "<<fun(arg)<<std::endl;
        } while(std::cin);
        }
        catch(std::domain_error izuzetak) {
            std::cout<<izuzetak.what();
        }
        break;
        }
    case 2: {
        double Xmin, Xmax, deltaX;
        std::cout<<"Unesite krajeve intervala i korak: ";
        std::cin>>Xmin>>Xmax>>deltaX;
        int d;
        std::cout<<"Unesite red interpolacije: ";
        std::cin>>d;
        double arg;
        try {
        do {
            auto fun=BaricentricnaInterpolacija(f, Xmin, Xmax, deltaX, d);
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>arg;
            if(std::cin) std::cout<<"f("<<arg<<") = "<<f(arg)<<" fapprox("<<arg<<") = "<<fun(arg)<<std::endl;
        } while(std::cin);
        }
        catch(std::domain_error izuzetak) {
            std::cout<<izuzetak.what();
        }
        break;
        }
    }
	return 0;
}
