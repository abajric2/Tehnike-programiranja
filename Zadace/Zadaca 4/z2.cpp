//TP 2021/2022: Zadaća 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <tuple>
#include <stdexcept>
#include <iomanip>
#include <vector>
#include <memory>
#include <algorithm>

const double eps=1e-10;
const double PI=4*atan(1);

class NepreklapajucaKugla {
    double x, y, z, r;
    NepreklapajucaKugla *prethodni;
    static NepreklapajucaKugla *posljednji;
    static bool DaLiSuIdenticne(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2);
    static bool DaLiSuKoncentricne(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2);
    static bool DaLiSeSijeku(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2);
    static bool DaLiSadrzi(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2);
    static bool DaLiSadrzi(double x1, double y1, double z1, double r1, const NepreklapajucaKugla &k2);
    static bool DaLiSePreklapaju(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2);
    static void PretraziListu(double x1, double y1, double z1, double r1, const NepreklapajucaKugla &k);
    static double RastojanjeCentara(const NepreklapajucaKugla &k, double x1, double y1, double z1);
    static void UveziUListu(NepreklapajucaKugla &k);
    static bool DaLiSeDodirujuIzvana(const NepreklapajucaKugla &k, double x2, double y2, double z2, double r2);
    static bool DaLiSeDodirujuIznutra(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2);
    public:
    explicit NepreklapajucaKugla(double r=0);
    NepreklapajucaKugla(double x, double y, double z, double r=0);
    explicit NepreklapajucaKugla(const std::tuple<double, double, double> &centar, double r=0);
    ~NepreklapajucaKugla();
    NepreklapajucaKugla(const NepreklapajucaKugla &k)=delete;
    NepreklapajucaKugla(NepreklapajucaKugla &&k)=delete;
    NepreklapajucaKugla &operator =(const NepreklapajucaKugla &k)=delete;
    NepreklapajucaKugla &operator =(NepreklapajucaKugla &&k)=delete;
    double DajX() const {return x;}
    double DajY() const {return y;}
    double DajZ() const {return z;}
    std::tuple<double, double, double> DajCentar() const {return std::make_tuple(x,y,z);}
    double DajPoluprecnik() const {return r;}
    double DajPovrsinu() const {return 4*r*r*PI;}
    double DajZapreminu() const {return (4*r*r*r*PI)/3;}
    NepreklapajucaKugla &PostaviX(double x);
    NepreklapajucaKugla &PostaviY(double y);
    NepreklapajucaKugla &PostaviZ(double z);
    NepreklapajucaKugla &PostaviCentar(double x, double y, double z);
    NepreklapajucaKugla &PostaviCentar(const std::tuple<double, double, double> &centar);
    NepreklapajucaKugla &PostaviPoluprecnik(double r);
    void Ispisi() const {std::cout<<"{("<<x<<","<<y<<","<<z<<"),"<<r<<"}"<<std::endl;}
    void Transliraj(double delta_x, double delta_y, double delta_z);
    friend double RastojanjeCentara(const NepreklapajucaKugla &k1, const NepreklapajucaKugla &k2);
};
NepreklapajucaKugla *NepreklapajucaKugla::posljednji=nullptr;
bool NepreklapajucaKugla::DaLiSuKoncentricne(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2) {
    return (fabs(k1.DajX()-x2)<=eps*(fabs(k1.DajX())+fabs(x2)) &&
    fabs(k1.DajY()-y2)<=eps*(fabs(k1.DajY())+fabs(y2)) &&
    fabs(k1.DajZ()-z2)<=eps*(fabs(k1.DajZ())+fabs(z2)));
}
bool NepreklapajucaKugla::DaLiSuIdenticne(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2) {
    return DaLiSuKoncentricne(k1, x2, y2, z2, r2) && fabs(k1.DajPoluprecnik()-r2)<=eps*(fabs(k1.DajPoluprecnik())+fabs(r2));
}
double NepreklapajucaKugla::RastojanjeCentara(const NepreklapajucaKugla &k, double x1, double y1, double z1) {
    return std::sqrt((k.DajX()-x1)*(k.DajX()-x1)+(k.DajY()-y1)*(k.DajY()-y1)+(k.DajZ()-z1)*(k.DajZ()-z1));
}
bool NepreklapajucaKugla::DaLiSeSijeku(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2) {
    if(!(RastojanjeCentara(k1, x2, y2, z2)<k1.DajPoluprecnik()+r2)) return false;
    if(k1.DajPoluprecnik()>r2) {
        return !(k1.DajPoluprecnik()-RastojanjeCentara(k1, x2, y2, z2)>r2 ||
        fabs(k1.DajPoluprecnik()-RastojanjeCentara(k1, x2, y2, z2)-r2)<=eps*
        (fabs(k1.DajPoluprecnik()-RastojanjeCentara(k1, x2, y2, z2))+fabs(r2)));
    }
    else if(k1.DajPoluprecnik()<r2) {
        return !(r2-RastojanjeCentara(k1,x2, y2, z2)>k1.DajPoluprecnik() ||
        fabs(r2-RastojanjeCentara(k1, x2, y2, z2)-k1.DajPoluprecnik())<=eps*
        (fabs(r2-RastojanjeCentara(k1,x2, y2, z2))+fabs(k1.DajPoluprecnik())));
    }
    return !DaLiSuIdenticne(k1,x2, y2, z2, r2);
}
bool NepreklapajucaKugla::DaLiSadrzi(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2) {
    if(DaLiSuIdenticne(k1,x2, y2, z2, r2)) return true;
    if(DaLiSuKoncentricne(k1, x2, y2, z2, r2)) return k1.DajPoluprecnik()>r2;
    if(DaLiSeSijeku(k1, x2, y2, z2, r2)) return false;
    if(k1.DajPoluprecnik()>r2) return RastojanjeCentara(k1, x2, y2, z2)<k1.DajPoluprecnik();
    return RastojanjeCentara(k1, x2, y2, z2)<r2;
}
bool NepreklapajucaKugla::DaLiSadrzi(double x1, double y1, double z1, double r1, const NepreklapajucaKugla &k2) {
    if(DaLiSuIdenticne(k2, x1, y1, z1, r1)) return true;
    if(DaLiSuKoncentricne(k2, x1, y1, z1, r1)) return r1>k2.DajPoluprecnik();
    if(DaLiSeSijeku(k2, x1, y1, z1, r1)) return false;
    if(r1>k2.DajPoluprecnik()) return RastojanjeCentara(k2, x1, y1, z1)<r1;
    return RastojanjeCentara(k2, x1, y1, z1)<k2.DajPoluprecnik();
}
bool NepreklapajucaKugla::DaLiSeDodirujuIzvana(const NepreklapajucaKugla &k, double x2, double y2, double z2, double r2) {
    return fabs(RastojanjeCentara(k, x2, y2, z2)-(k.DajPoluprecnik()+r2))<=eps*
    (fabs(RastojanjeCentara(k,x2,y2,z2))+fabs(k.DajPoluprecnik()+r2));
}
bool NepreklapajucaKugla::DaLiSeDodirujuIznutra(const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2) {
    if(k1.DajPoluprecnik()>r2) {
        return fabs((k1.DajPoluprecnik()-RastojanjeCentara(k1, x2, y2, z2))-r2)<=eps*
        (fabs(k1.DajPoluprecnik()-RastojanjeCentara(k1, x2, y2, z2))+fabs(r2));
    }
    else if(k1.DajPoluprecnik()<r2) {
        return fabs((r2-RastojanjeCentara(k1, x2, y2, z2))-k1.DajPoluprecnik())<=eps*
        (fabs(r2-RastojanjeCentara(k1, x2, y2, z2))+fabs(k1.DajPoluprecnik()));
    }
    else return DaLiSuIdenticne(k1, x2, y2, z2, r2);
}
bool NepreklapajucaKugla::DaLiSePreklapaju (const NepreklapajucaKugla &k1, double x2, double y2, double z2, double r2) {
    return DaLiSeSijeku(k1,x2, y2, z2, r2) || DaLiSuKoncentricne(k1,x2,y2,z2,r2) || DaLiSuIdenticne(k1, x2, y2, z2, r2) ||
    DaLiSadrzi(k1,x2,y2,z2,r2) || DaLiSadrzi(x2, y2, z2, r2, k1) || DaLiSeDodirujuIznutra(k1, x2, y2, z2, r2) ||
    DaLiSeDodirujuIzvana(k1, x2, y2, z2, r2);
}
void NepreklapajucaKugla::PretraziListu(double x1, double y1, double z1, double r1, const NepreklapajucaKugla &k) {
    for(auto p=NepreklapajucaKugla::posljednji; p!=nullptr; p=p->prethodni) {
        if(p!= &k && DaLiSePreklapaju(*p, x1, y1, z1, r1)) throw std::logic_error("Nedozvoljeno preklapanje");
    }
}
void NepreklapajucaKugla::UveziUListu(NepreklapajucaKugla &k) {
    NepreklapajucaKugla *pomocni=posljednji;
    posljednji=&k;
    posljednji->prethodni=pomocni;
}
NepreklapajucaKugla::NepreklapajucaKugla (double r) {
    if(r<0) throw std::domain_error("Ilegalan poluprecnik");
    PretraziListu(0, 0, 0, r, *this);
    x=0; y=0; z=0; NepreklapajucaKugla::r=r;
    UveziUListu(*this);
}
NepreklapajucaKugla::NepreklapajucaKugla(double x, double y, double z, double r) {
    if(r<0) throw std::domain_error("Ilegalan poluprecnik");
    PretraziListu(x, y, z, r, *this);
    NepreklapajucaKugla::x=x; NepreklapajucaKugla::y=y; NepreklapajucaKugla::z=z; NepreklapajucaKugla::r=r;
    UveziUListu(*this);
}
NepreklapajucaKugla::NepreklapajucaKugla(const std::tuple<double, double, double> &centar, double r) {
    if(r<0) throw std::domain_error("Ilegalan poluprecnik");
    PretraziListu(std::get<0>(centar), std::get<1>(centar), std::get<2>(centar), r, *this);
    x=std::get<0>(centar); y=std::get<1>(centar); z=std::get<2>(centar); NepreklapajucaKugla::r=r;
    UveziUListu(*this);
}
NepreklapajucaKugla &NepreklapajucaKugla::PostaviX(double x) {
    PretraziListu(x, y, z, r, *this);
    NepreklapajucaKugla::x=x; return *this;
}
NepreklapajucaKugla &NepreklapajucaKugla::PostaviY(double y) {
    PretraziListu(x, y, z, r, *this);
    NepreklapajucaKugla::y=y; return *this;
}
NepreklapajucaKugla &NepreklapajucaKugla::PostaviZ(double z) {
    PretraziListu(x, y, z, r, *this);
    NepreklapajucaKugla::z=z; return *this;
}
NepreklapajucaKugla &NepreklapajucaKugla::PostaviCentar(double x, double y, double z) {
    PretraziListu(x, y, z, r, *this);
    NepreklapajucaKugla::x=x; NepreklapajucaKugla::y=y; NepreklapajucaKugla::z=z; return *this;
}
NepreklapajucaKugla &NepreklapajucaKugla::PostaviCentar(const std::tuple<double,double,double> &centar) {
    PretraziListu(std::get<0>(centar), std::get<1>(centar), std::get<2>(centar), r, *this);
    x=std::get<0>(centar); y=std::get<1>(centar); z=std::get<2>(centar); 
    return *this;
}
NepreklapajucaKugla &NepreklapajucaKugla::PostaviPoluprecnik(double r) {
    if(r<0) throw std::domain_error("Ilegalan poluprecnik");
    PretraziListu(x, y, z, r, *this);
    NepreklapajucaKugla::r=r; return *this;
}
void NepreklapajucaKugla::Transliraj(double delta_x, double delta_y, double delta_z) {
    PretraziListu(x+delta_x, y+delta_y, z+delta_z, r, *this);
    x+=delta_x; y+=delta_y; z+=delta_z;
}
double RastojanjeCentara(const NepreklapajucaKugla &k1, const NepreklapajucaKugla &k2) {
    return std::sqrt((k1.DajX()-k2.DajX())*(k1.DajX()-k2.DajX())+(k1.DajY()-k2.DajY())*(k1.DajY()-k2.DajY())+(k1.DajZ()-k2.DajZ())*(k1.DajZ()-k2.DajZ()));
}
NepreklapajucaKugla::~NepreklapajucaKugla() {
    NepreklapajucaKugla *p;
    for(p=NepreklapajucaKugla::posljednji; p!=nullptr; p=p->prethodni) {
        if(p->prethodni==this) break;
        if(p==this) {
            posljednji=p->prethodni;
            p->prethodni=nullptr;
            return;
        }
    }
    p->prethodni=this->prethodni;
    this->prethodni=nullptr;
}
int main ()
{
    int n;
    std::cout<<"Unesite broj kugli: "<<std::endl;
    do {
    std::cin>>n;
    if(n<=0) std::cout<<"Neispravan broj kugli, unesite ponovo!"<<std::endl;
    }while(n<=0);
    std::vector<std::shared_ptr<NepreklapajucaKugla>> v;
    for(int i=0; i<n; i++) {
        double x, y, z;
        std::cout<<"Unesite centar za "<<i+1<<". kuglu: ";
        while(!(std::cin>>x>>y>>z)) {
            std::cin.clear(); std::cin.ignore(10000, '\n');
            std::cout<<"Neispravan centar, unesite ponovo: "<<std::endl;
        }
        double r;
        std::cout<<"Unesite poluprecnik: ";
        while(!(std::cin>>r) || r<0) {
            std::cin.clear(); std::cin.ignore(10000, '\n');
            std::cout<<"Neispravan poluprecnik, unesite ponovo: "<<std::endl;
        }
        try {
            auto p=std::make_shared<NepreklapajucaKugla>(x, y, z, r);
            v.push_back(p);
        }
        catch(std::domain_error) {
            std::cout<<"Neispravan poluprecnik, unesite ponovo: "<<std::endl;
        }
        catch(std::logic_error izuzetak) {
            i--;
            std::cout<<izuzetak.what()<<std::endl;
        }
    }
    std::sort(v.begin(), v.end(), [](auto p1, auto p2) {
        return p1->DajPovrsinu()<p2->DajPovrsinu();
    });
    std::cout<<"Kugle nakon obavljenog sortiranja: "<<std::endl;
    std::for_each(v.begin(), v.end(), [](auto p){p->Ispisi();});
	return 0;
}
