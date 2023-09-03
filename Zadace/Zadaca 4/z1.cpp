//TP 2021/2022: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <tuple>
#include <stdexcept>
#include <vector>
#include <memory>
#include <algorithm>

const double PI=4*atan(1);
const double eps=1e-10;
class Kugla {
    double x, y, z, r;
    public:
    explicit Kugla(double r=0) {
        if(r<0) throw std::domain_error("Ilegalan poluprecnik");
        x=0; y=0; z=0; Kugla::r=r;
    }
    Kugla(double x, double y, double z, double r=0) {
        if(r<0) throw std::domain_error("Ilegalan poluprecnik");
        Kugla::x=x; Kugla::y=y; Kugla::z=z; Kugla::r=r;
    }
    explicit Kugla(const std::tuple<double, double, double> &centar, double r=0) {
        if(r<0) throw std::domain_error("Ilegalan poluprecnik");
        x=std::get<0>(centar); y=std::get<1>(centar); z=std::get<2>(centar); Kugla::r=r;
    }
    double DajX() const {return x;}
    double DajY() const {return y;}
    double DajZ() const {return z;}
    std::tuple<double, double, double> DajCentar() const {return std::make_tuple(x, y, z);}
    double DajPoluprecnik() const {return r;}
    double DajPovrsinu() const {return 4*r*r*PI;}
    double DajZapreminu() const {return (4*r*r*r*PI)/3;}
    Kugla &PostaviX(double x) {Kugla::x=x; return *this;}
    Kugla &PostaviY(double y) {Kugla::y=y; return *this;}
    Kugla &PostaviZ(double z) {Kugla::z=z; return *this;}
    Kugla &PostaviCentar(double x, double y, double z) {Kugla::x=x; Kugla::y=y; Kugla::z=z; return *this;}
    Kugla &PostaviCentar(const std::tuple<double, double, double> &centar) {
        x=std::get<0>(centar); y=std::get<1>(centar); z=std::get<2>(centar); return *this;
    }
    Kugla &PostaviPoluprecnik(double r) {
        if(r<0) throw std::domain_error("Ilegalan poluprecnik");
        Kugla::r=r; return *this;
    }
    void Ispisi() const {std::cout<<"{("<<x<<","<<y<<","<<z<<"),"<<r<<"}"<<std::endl;}
    void Transliraj(double delta_x, double delta_y, double delta_z) {x+=delta_x; y+=delta_y; z+=delta_z;}
    friend bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSePreklapaju(const Kugla &k1, const Kugla &k2);
    friend bool DaLiSeSijeku(const Kugla &k1, const Kugla &k2);
    bool DaLiSadrzi(const Kugla &k) const;
    friend double RastojanjeCentara(const Kugla &k1, const Kugla &k2);
};
bool DaLiSuKoncentricne(const Kugla &k1, const Kugla &k2) {
    return (fabs(k1.DajX()-k2.DajX())<=eps*(fabs(k1.DajX())+fabs(k2.DajX())) && 
    fabs(k1.DajY()-k2.DajY())<=eps*(fabs(k1.DajY())+fabs(k2.DajY())) && 
    fabs(k1.DajZ()-k2.DajZ())<=eps*(fabs(k1.DajZ())+fabs(k2.DajZ())));
}
bool DaLiSuPodudarne(const Kugla &k1, const Kugla &k2) {
    return fabs(k1.DajPoluprecnik()-k2.DajPoluprecnik())<=eps*(fabs(k1.DajPoluprecnik())+fabs(k2.DajPoluprecnik()));
}
bool DaLiSuIdenticne(const Kugla &k1, const Kugla &k2) {
    return DaLiSuKoncentricne(k1, k2) && DaLiSuPodudarne(k1, k2);
}
double RastojanjeCentara(const Kugla &k1, const Kugla &k2) {
    return std::sqrt((k1.DajX()-k2.DajX())*(k1.DajX()-k2.DajX())+(k1.DajY()-k2.DajY())*(k1.DajY()-k2.DajY())+(k1.DajZ()-k2.DajZ())*(k1.DajZ()-k2.DajZ()));
}
bool DaLiSeDodirujuIzvana(const Kugla &k1, const Kugla &k2) {
    return fabs(RastojanjeCentara(k1, k2)-(k1.DajPoluprecnik()+k2.DajPoluprecnik()))<=eps*
    (fabs(RastojanjeCentara(k1, k2))+fabs(k1.DajPoluprecnik()+k2.DajPoluprecnik()));
}
bool DaLiSeDodirujuIznutra(const Kugla &k1, const Kugla &k2) {
    if(k1.DajPoluprecnik()>k2.DajPoluprecnik()) {
        return fabs((k1.DajPoluprecnik()-RastojanjeCentara(k1, k2))-k2.DajPoluprecnik())<=eps*
        (fabs(k1.DajPoluprecnik()-RastojanjeCentara(k1, k2))+fabs(k2.DajPoluprecnik()));
    }
    else if(k1.DajPoluprecnik()<k2.DajPoluprecnik()) {
        return fabs((k2.DajPoluprecnik()-RastojanjeCentara(k1, k2))-k1.DajPoluprecnik())<=eps*
        (fabs(k2.DajPoluprecnik()-RastojanjeCentara(k1, k2))+fabs(k1.DajPoluprecnik()));
    }
    else return DaLiSuIdenticne(k1, k2);
}
bool DaLiSeSijeku (const Kugla &k1, const Kugla &k2) {
    if(!(RastojanjeCentara(k1, k2)<k1.DajPoluprecnik()+k2.DajPoluprecnik())) return false;
    if(k1.DajPoluprecnik()>k2.DajPoluprecnik()) {
        return !(k1.DajPoluprecnik()-RastojanjeCentara(k1, k2)>k2.DajPoluprecnik() ||
        fabs((k1.DajPoluprecnik()-RastojanjeCentara(k1, k2)-k2.DajPoluprecnik()))<=eps*
        (fabs(k1.DajPoluprecnik()-RastojanjeCentara(k1, k2))+fabs(k2.DajPoluprecnik())));         
    }
    else if(k1.DajPoluprecnik()<k2.DajPoluprecnik()) {
        return !(k2.DajPoluprecnik()-RastojanjeCentara(k1, k2)>k1.DajPoluprecnik() ||
        fabs((k2.DajPoluprecnik()-RastojanjeCentara(k1, k2)-k1.DajPoluprecnik()))<=eps*
        (fabs(k2.DajPoluprecnik()-RastojanjeCentara(k1, k2))+fabs(k1.DajPoluprecnik()))); 
    }
    return !DaLiSuIdenticne(k1, k2);
}
bool Kugla::DaLiSadrzi(const Kugla &k) const {
    if(DaLiSuIdenticne(*this, k)) return true;
    if(DaLiSuKoncentricne(*this, k)) return DajPoluprecnik()>k.DajPoluprecnik();
    if(DaLiSeSijeku(*this, k)) return false;
    if(DajPoluprecnik()>k.DajPoluprecnik()) {
        return RastojanjeCentara(*this, k)<DajPoluprecnik();
    }
    return RastojanjeCentara(*this, k)<k.DajPoluprecnik();
}
bool DaLiSePreklapaju (const Kugla &k1, const Kugla &k2) {
    return DaLiSeSijeku(k1, k2) || DaLiSuKoncentricne(k1, k2) || DaLiSuIdenticne(k1, k2) || k1.DaLiSadrzi(k2) || k2.DaLiSadrzi(k1) ||
    DaLiSeDodirujuIznutra(k1, k2);
}
int main ()
{
    int n;
    std::cout<<"Unesite broj kugla: "<<std::endl;
    std::cin>>n;
    std::vector<std::shared_ptr<Kugla>> v;
    for(int i=0; i<n; i++) {
        double x, y, z;
        std::cout<<"Unesite centar "<<i+1<<". kugle: ";
        std::cin>>x>>y>>z;
        double r;
        std::cout<<"Unesite poluprecnik "<<i+1<<". kugle: ";
        std::cin>>r;
        if(!std::cin) {
            std::cin.clear(); std::cin.ignore(10000, '\n');
            std::cout<<"Niste unijeli brojeve!"<<std::endl;
            i--; continue;
        }
        try {
            auto p=std::make_shared<Kugla>(x, y, z, r);
            v.push_back(p);
        }
        catch(std::domain_error izuzetak) {
            i--;
            std::cout<<izuzetak.what()<<std::endl;
        }
    }
        double dx, dy, dz;
        std::cout<<"Unesite parametre translacije (delta_x,delta_y,delta_z): "<<std::endl;
        std::cin>>dx>>dy>>dz;
        std::transform(v.begin(), v.end(), v.begin(), [dx, dy, dz](auto p) {
           p->Transliraj(dx, dy, dz);
           return p;
        });
        std::sort(v.begin(), v.end(), [](auto p1, auto p2) {
            return p1->DajZapreminu()<p2->DajZapreminu();
        });
        std::cout<<"Kugle nakon obavljenje transformacije imaju sljedece vrijednosti: "<<std::endl;
        std::for_each(v.begin(), v.end(), [](auto p) {p->Ispisi();});
        std::shared_ptr<Kugla> max=*std::max_element(v.begin(), v.end(), [](auto p1, auto p2) {
            return p1->DajPovrsinu()<p2->DajPovrsinu();
        });
        std::cout<<"Kugla sa najvecom povrsinom je: ";
        max->Ispisi();
        int brojac=0, i=0;
        std::for_each(v.begin(), v.end(), [v, &brojac, &i](auto p) {
            i++; [p, &brojac, v, i](){
                std::for_each(v.begin()+i, v.end(), [p, &brojac](auto p1) {
                    if(DaLiSeSijeku(*p, *p1)) {
                        std::cout<<"Presjecaju se kugle: ";
                        p->Ispisi(); p1->Ispisi();
                        brojac++;
                    }
                });
            }();
        });
        if(brojac==0) std::cout<<"Ne postoje kugle koje se presjecaju!";
	return 0;
}
