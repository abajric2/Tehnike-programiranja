/* 
    TP 16/17 (LV 10, Zadatak 2)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

const double PI=4*std::atan(1);

class Krug {
    double poluprecnik;
    public:
    explicit Krug (double poluprecnik) {Postavi(poluprecnik);}
    Krug &Postavi(double poluprecnik) {
        if(poluprecnik<=0) throw std::domain_error("Neispravan poluprecnik");
        Krug::poluprecnik=poluprecnik; 
        return *this;
    }
    double DajPoluprecnik() const {return poluprecnik;}
    double DajObim() const {return 2*poluprecnik*PI;}
    double DajPovrsinu() const {return poluprecnik*poluprecnik*PI;}
    Krug &Skaliraj(double faktor_skaliranja) {
        if(faktor_skaliranja<=0) throw std::domain_error("Neispravan faktor skaliranja");
        poluprecnik*=faktor_skaliranja;
        return *this;
    }
    void Ispisi() const {std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnik()<<" O="<<DajObim()<<" P="<<DajPovrsinu();}
};

class Valjak {
    Krug baza;
    double visina;
    public:
    Valjak (double poluprecnik, double visina) : baza(poluprecnik) {
        if(visina<0) throw std::domain_error("Neispravna visina");
        Valjak::visina=visina;
    }
    Valjak &Postavi (double poluprecnik, double visina) {
        baza.Postavi(poluprecnik);
        if(visina<0) throw std::domain_error("Neispravna visina");
        Valjak::visina=visina;
        return *this;
    }
    Krug DajBazu() const {return baza;}
    double DajPoluprecnikBaze() const {return baza.DajPoluprecnik();}
    double DajVisinu() const {return visina;}
    double DajPovrsinu() const {return 2*baza.DajPovrsinu()+baza.DajObim()*visina;}
    double DajZapreminu() const {return baza.DajPovrsinu()*visina;}
    Valjak &Skaliraj(double faktor_skaliranja) {
        if(faktor_skaliranja<=0) throw std::domain_error("Neispravan faktor skaliranja");
        baza.Skaliraj(faktor_skaliranja);
        visina*=faktor_skaliranja;
        return *this;
    }
    void Ispisi() const {std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnikBaze()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();}
};
int main ()
{
    Krug k(5);
    const Krug &k2(k);
    std::cout<<"Poluprecnik kruga je "<<k2.DajPoluprecnik()<<", obim "<<k2.DajObim()<<" i povrsina "<<k2.DajPovrsinu()<<std::endl;
    double faktor;
    k.Postavi(6);
    std::cout<<"Unesite faktor skaliranja: ";
    std::cin>>faktor;
    try {
        k.Skaliraj(faktor);
        std::cout<<"Nakon skaliranja: ";
        k2.Ispisi();
        std::cout<<std::endl;
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
    }
    Valjak v(2,3);
    const Valjak &v2(v);
    std::cout<<"Dimenzije valjka: "<<std::endl;
    std::cout<<"R="<<v2.DajPoluprecnikBaze()<<" H="<<v2.DajVisinu()<<" P="<<v2.DajPovrsinu()<<" V="<<v2.DajZapreminu()<<std::endl;
    v.Postavi(5,6);
    k=v2.DajBazu();
    std::cout<<"Poluprecnik baze nakon skaliranja sa 5: ";
    double r=k.Skaliraj(5).DajPoluprecnik();
    std::cout<<r;
    v.Skaliraj(6);
    std::cout<<std::endl<<"Nakon skaliranja dimenzija valjka sa 6: ";
    v2.Ispisi();
	return 0;
}