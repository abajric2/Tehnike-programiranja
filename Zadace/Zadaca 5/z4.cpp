//TP 2021/2022: Zadaća 5, Zadatak 4
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>

class Spremnik {
    protected:
    double tezina;
    std::string naziv;
    public:
    virtual ~Spremnik() {}
    Spremnik(double tezina, std::string naziv) : tezina(tezina), naziv(naziv) {}
    double DajTezinu() const {return tezina;}
    virtual double DajUkupnuTezinu() const = 0;
    virtual void Ispisi() const = 0;
    virtual Spremnik *DajKopiju() const = 0;
};
class Sanduk : public Spremnik {
    std::vector<double> tezine_predmeta;
    public:
    Sanduk(double tezina, std::string naziv, std::vector<double> tezine_predmeta) : Spremnik(tezina, naziv), tezine_predmeta(tezine_predmeta) {}
    double DajUkupnuTezinu() const override;
    void Ispisi() const override;
    Spremnik *DajKopiju() const override {return new Sanduk(*this);}
};
double Sanduk::DajUkupnuTezinu() const {
    double ukupna_tezina=DajTezinu();
    for(auto el : tezine_predmeta) ukupna_tezina+=el;
    return ukupna_tezina;
}
void Sanduk::Ispisi() const {
    std::cout<<"Vrsta spremnika: Sanduk"<<std::endl<<"Sadrzaj: "<<naziv<<std::endl<<"Tezine predmeta: ";
    for(auto el : tezine_predmeta) std::cout<<el<<" "; 
    std::cout<<"(kg)"<<std::endl<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
}
class Vreca : public Spremnik {
    double tezina_materije;
    public:
    Vreca(double tezina, std::string naziv, double tezina_materije): Spremnik(tezina, naziv), tezina_materije(tezina_materije) {}
    double DajUkupnuTezinu() const override {return DajTezinu()+tezina_materije;}
    void Ispisi() const override;
    Spremnik *DajKopiju() const override {return new Vreca(*this);}
};
void Vreca::Ispisi() const {
    std::cout<<"Vrsta spremnika: Vreca"<<std::endl<<"Sadrzaj: "<<naziv<<std::endl<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl<<
    "Tezina pohranjene materije: "<<tezina_materije<<" (kg)"<<std::endl<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
}
class Bure : public Spremnik {
    double gustina_tecnosti, zapremina_tecnosti;
    public:
    Bure(double tezina, std::string naziv, double gustina_tecnosti, double zapremina_tecnosti) : Spremnik(tezina, naziv), gustina_tecnosti(gustina_tecnosti),
        zapremina_tecnosti(zapremina_tecnosti) {}
    double DajUkupnuTezinu() const override {return DajTezinu()+gustina_tecnosti*zapremina_tecnosti*0.001;}
    void Ispisi() const override;
    Spremnik *DajKopiju() const override {return new Bure(*this);}
};
void Bure::Ispisi() const {
    std::cout<<"Vrsta spremnika: Bure"<<std::endl<<"Sadrzaj: "<<naziv<<std::endl<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl<<
    "Specificna tezina tecnosti: "<<gustina_tecnosti<<" (kg/m^3)"<<std::endl<<"Zapremina tecnosti: "<<zapremina_tecnosti<<" (l)"<<std::endl<<
    "Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
}
class PolimorfniSpremnik {
    Spremnik *p_spremnik;
    public:
    PolimorfniSpremnik() : p_spremnik(nullptr) {}
    ~PolimorfniSpremnik() {delete p_spremnik;}
    PolimorfniSpremnik(const Spremnik &s) : p_spremnik(s.DajKopiju()) {}
    PolimorfniSpremnik(const PolimorfniSpremnik &s) {
        if(!s.p_spremnik) p_spremnik=nullptr;
        else p_spremnik=s.p_spremnik->DajKopiju(); 
    }
    PolimorfniSpremnik(PolimorfniSpremnik &&s) {
        p_spremnik=s.p_spremnik; s.p_spremnik=nullptr;
    }
    PolimorfniSpremnik &operator =(const PolimorfniSpremnik &s) {
        delete p_spremnik; 
        if(s.p_spremnik) p_spremnik=s.p_spremnik->DajKopiju(); 
        else p_spremnik=nullptr;
        return *this;
    }
    PolimorfniSpremnik &operator =(PolimorfniSpremnik &&s) {
        delete p_spremnik;
        p_spremnik=s.p_spremnik; s.p_spremnik=nullptr;
        return *this;
    }
    double DajTezinu() const {
        if(!p_spremnik) throw std::logic_error("Nespecificiran spremnik");
        return p_spremnik->DajTezinu();
    }
    double DajUkupnuTezinu() const {
        if(!p_spremnik) throw std::logic_error("Nespecificiran spremnik");
        return p_spremnik->DajUkupnuTezinu();
    }
    void Ispisi() const {
        if(!p_spremnik) throw std::logic_error("Nespecificiran spremnik");
        p_spremnik->Ispisi();
    }
};
int main() {
    PolimorfniSpremnik s1(Sanduk(10, "Tepsije", {1,2,3,4}));
    PolimorfniSpremnik s2, s3(s1);
    s1.Ispisi(); std::cout<<"--------------------------------------------"<<std::endl;
    s3.Ispisi(); std::cout<<"--------------------------------------------"<<std::endl;
    s2=Vreca(0.3, "Brasno", 10);
    s2.Ispisi(); std::cout<<"--------------------------------------------"<<std::endl;
    s2=s1;
    s2.Ispisi(); std::cout<<"--------------------------------------------"<<std::endl;
    s3=std::move(s2);
   // s2.Ispisi(); std::cout<<"-------------------------";
    s3.Ispisi(); std::cout<<"--------------------------------------------"<<std::endl;
    PolimorfniSpremnik s4(std::move(s3));
    s4.Ispisi(); std::cout<<"--------------------------------------------"<<std::endl;
    s4=Bure(10, "ulje", 900, 5);
    s4.Ispisi(); std::cout<<"--------------------------------------------"<<std::endl;
    std::cout<<s4.DajTezinu()<<" "<<s4.DajUkupnuTezinu()<<std::endl<<s1.DajTezinu()<<" "<<s1.DajUkupnuTezinu();
    return 0;
}