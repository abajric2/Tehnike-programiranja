/* 
    TP 16/17 (LV 13, Zadatak 1)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <memory>

const double PI=4*std::atan(1);

class Lik {
    public:
    virtual ~Lik() {};
    virtual void IspisiSpecificnosti() const = 0;
    virtual double DajObim() const = 0;
    virtual double DajPovrsinu() const = 0;
    void Ispisi() const {
        IspisiSpecificnosti(); 
        std::cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<std::endl;
    }
};
class Krug : public Lik {
    double r;
    public:
    Krug(double r) {
        if(r<=0) throw std::domain_error("Neispravni parametri");
        Krug::r=r;
    }
    void IspisiSpecificnosti() const override{
        std::cout<<"Krug poluprecnika "<<r<<std::endl;
    }
    double DajObim() const override {
        return 2*r*PI;
    }
    double DajPovrsinu() const override {
        return r*r*PI;
    }
};
class Pravougaonik : public Lik {
    double a, b;
    public:
    Pravougaonik(double a, double b) {
        if(a<=0 || b<=0) throw std::domain_error("Neispravni parametri");
        Pravougaonik::a=a; Pravougaonik::b=b;
    }
    void IspisiSpecificnosti() const override {
        std::cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<std::endl;
    }
    double DajObim() const override {
        return 2*a+2*b;
    }
    double DajPovrsinu() const override {
        return a*b;
    }
};
class Trougao : public Lik {
    double a, b, c;
    public:
    Trougao(double a, double b, double c) {
        if(a<=0 || b<=0 || c<=0 || a+b<=c || a+c<=b || b+c<=a) throw std::domain_error("Neispravni parametri");
        Trougao::a=a; Trougao::b=b; Trougao::c=c;
    }
    void IspisiSpecificnosti() const override {
        std::cout<<"Trougao sa stranicama duzine "<<a<<", "<<b<<" i "<<c<<std::endl;
    }
    double DajObim() const override {
        return a+b+c;
    }
    double DajPovrsinu() const override {
        double s=DajObim()/2;
        return std::sqrt(s*(s-a)*(s-b)*(s-c));
    }
};
int main ()
{
    int n;
    std::cout<<"Koliko zelite likova: ";
    std::cin>>n;
    std::vector<std::shared_ptr<Lik>> v;
    for(int i=0; i<n; i++) {
        std::cout<<"Lik "<<i+1<<": ";
        char znak;
        std::cin>>znak;
        if(znak=='P') {
            double a, b;
            char z;
            if(std::cin>>a>>z>>b && std::cin.peek()=='\n') {
                try {
                    v.push_back(std::make_shared<Pravougaonik>(a, b));   
                }
                catch(std::domain_error) {
                    goto greska;
                }      
            }   
        }
        else if(znak=='K') {
            double r;
            if(std::cin>>r && std::cin.peek()=='\n') {
                try {
                    v.push_back(std::make_shared<Krug>(r));
                }
                catch(std::domain_error) {
                    goto greska;
                }
            }
        }
        else if(znak=='T') {
            double a, b, c;
            char z;
            if(std::cin>>a>>z>>b>>z>>c && std::cin.peek()=='\n') {
                try {
                    v.push_back(std::make_shared<Trougao>(a,b,c));
                }
                catch(std::domain_error) {
                    goto greska;
                }
            }
        }
        else if(!(znak=='K' || znak=='P' || znak=='T') || !std::cin) {
            greska:
            std::cin.clear(); std::cin.ignore(10000, '\n');
            std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
            i--;
            continue;
        }
        if(std::cin.peek()!='\n') goto greska;
    }
    for(int i=0; i<n; i++) v[i]->Ispisi();
	return 0;
}