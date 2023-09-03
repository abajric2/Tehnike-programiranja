//TP 2021/2022: Zadaća 5, Zadatak 3
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
class Skladiste {
    std::vector<std::shared_ptr<Spremnik>> v;
    public:
    Skladiste() {}
    Skladiste(const Skladiste &s);
    Skladiste(Skladiste &&s);
    Skladiste &operator =(const Skladiste &s);
    Skladiste &operator =(Skladiste &&s);
    Spremnik *DodajSanduk(double tezina, std::string naziv, std::vector<double> tezine_predmeta) {
        std::shared_ptr<Spremnik> p=std::make_shared<Sanduk>(tezina, naziv, tezine_predmeta);
        v.push_back(p);
        return p.get();
    }
    Spremnik *DodajVrecu(double tezina, std::string naziv, double tezina_materije) {
        std::shared_ptr<Spremnik> p=std::make_shared<Vreca>(tezina, naziv, tezina_materije);
        v.push_back(p);
        return p.get();
    }
    Spremnik *DodajBure(double tezina, std::string naziv, double gustina, double zapremina) {
        std::shared_ptr<Spremnik> p=std::make_shared<Bure>(tezina, naziv, gustina, zapremina);
        v.push_back(p);
        return p.get();
    }
    Spremnik *DodajSpremnik(Spremnik *objekat, bool vlasnistvo);
    void BrisiSpremnik(Spremnik *s);
    Spremnik &DajNajlaksi();
    Spremnik &DajNajtezi();
    int BrojPreteskih(int t) const;
    void IzlistajSkladiste() const;
    void UcitajIzDatoteke(std::string ime_datoteke);
};
Skladiste::Skladiste(const Skladiste &s) {
    try {
        for(int i=0; i<s.v.size(); i++) v.push_back(std::shared_ptr<Spremnik>(s.v[i]->DajKopiju()));
    }
    catch(...) {
        for(int i=0; i<v.size(); i++) v[i]=nullptr;
        throw;
    }
}
Skladiste::Skladiste(Skladiste &&s) : v(s.v) {
    for(int i=0; i<s.v.size(); i++) s.v[i]=nullptr;
    s.v.resize(0);
}
Skladiste &Skladiste::operator =(const Skladiste &s) {
    for(int i=0; i<v.size(); i++) v[i]=nullptr;
    try {
        v.resize(s.v.size());
        for(int i=0; i<v.size(); i++) v[i]=std::shared_ptr<Spremnik>(s.v[i]->DajKopiju());
    }
    catch(...) {
        for(int i=0; i<v.size(); i++) v[i]=nullptr;
        throw;
    }
    return *this;
}
Skladiste &Skladiste::operator =(Skladiste &&s) {
    for(int i=0; i<v.size(); i++) v[i]=nullptr;
    v=s.v;
    for(int i=0; i<s.v.size(); i++) s.v[i]=nullptr;
    s.v.resize(0);
    return *this;
}
Spremnik *Skladiste::DodajSpremnik(Spremnik *objekat, bool vlasnistvo) {
    if(vlasnistvo) {
        v.push_back(std::shared_ptr<Spremnik>(objekat));
        return objekat;
    }
    else {
        std::shared_ptr<Spremnik> p=std::shared_ptr<Spremnik>(objekat->DajKopiju());
        v.push_back(p);
        return p.get();
    }
}
void Skladiste::BrisiSpremnik(Spremnik *s) {
    for(int i=0; i<v.size(); i++) {
        if(v[i].get()==s) {
            v[i]=nullptr; 
            v.erase(v.begin()+i); 
            return;
        }
    }
}
Spremnik &Skladiste::DajNajlaksi() {
    if(!v.size()) throw std::range_error("Skladiste je prazno");
    std::shared_ptr<Spremnik> s=*std::min_element(v.begin(), v.end(), [](std::shared_ptr<Spremnik> p1, std::shared_ptr<Spremnik> p2) {
        return p1->DajTezinu()<p2->DajTezinu();
    });
    return *s;
}
Spremnik &Skladiste::DajNajtezi() {
    if(!v.size()) throw std::range_error("Skladiste je prazno");
    std::shared_ptr<Spremnik> s=*std::max_element(v.begin(), v.end(), [](std::shared_ptr<Spremnik> p1, std::shared_ptr<Spremnik> p2) {
        return p1->DajTezinu()<p2->DajTezinu();
    });
    return *s;
}
int Skladiste::BrojPreteskih(int t) const{
    return std::count_if(v.begin(), v.end(), [t](std::shared_ptr<Spremnik> p) {return p->DajUkupnuTezinu()>t;});
}
void Skladiste::IzlistajSkladiste() const {
    std::vector<std::shared_ptr<Spremnik>> pomocni(v);
    std::sort(pomocni.begin(), pomocni.end(), [](std::shared_ptr<Spremnik> p1, std::shared_ptr<Spremnik> p2) {
        return p1->DajUkupnuTezinu()>p2->DajUkupnuTezinu();
    });
    std::for_each(pomocni.begin(), pomocni.end(), [](std::shared_ptr<Spremnik> p) {p->Ispisi();});
}
void Skladiste::UcitajIzDatoteke(std::string ime_datoteke) {
    std::ifstream dat(ime_datoteke);
    if(!dat) throw std::logic_error("Trazena datoteka ne postoji");
    for(int i=0; i<v.size(); i++) v[i]=nullptr; 
    v.resize(0);
    for(;;) {
        std::string red;
        std::getline(dat, red);
        if(dat.eof()) break;
        if(!dat) throw std::logic_error("Problemi pri citanju datoteke");
        if(*red.begin()!='S' && *red.begin()!='B' && *red.begin()!='V') throw std::logic_error("Datoteka sadrzi besmislene podatke");
        if(*red.begin()=='S') {
            int br_pred;
            double el, tez_sanduka;
            if(!(dat>>tez_sanduka>>br_pred)) throw std::logic_error("Datoteka sadrzi besmislene podatke");
            std::vector<double> pomocni;
            for(int i=0; i<br_pred; i++) {
                if(dat>>el) pomocni.push_back(el);
                else throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            for(auto i=red.begin(); i!=red.end(); i++) {
                if(i!=red.begin() && *i!=' ') {
                    red=red.substr(i-red.begin(), red.end()-i); break;
                }
            }
            dat.ignore(10000, '\n');
            v.push_back(std::make_shared<Sanduk>(tez_sanduka, red, pomocni));
            if(dat.eof()) break;
        }
        else if(*red.begin()=='B') {
            double tez, gust, zapr;
            if(!(dat>>tez>>gust>>zapr)) throw std::logic_error("Datoteka sadrzi besmislene podatke");
            for(auto i=red.begin(); i!=red.end(); i++) {
                if(i!=red.begin() && *i!=' ') {
                    red=red.substr(i-red.begin(), red.end()-i); break;
                }
            }
            dat.ignore(10000, '\n');
            v.push_back(std::make_shared<Bure>(tez, red, gust, zapr));
            if(dat.eof()) break;
        }
        else {
            double tez, tez_mat;
            if(!(dat>>tez>>tez_mat)) throw std::logic_error("Datoteka sadrzi besmislene podatke");
            for(auto i=red.begin(); i!=red.end(); i++) {
                if(i!=red.begin() && *i!=' ') {
                    red=red.substr(i-red.begin(), red.end()-i); break;
                }
            }
            dat.ignore(10000, '\n');
            v.push_back(std::make_shared<Vreca>(tez, red, tez_mat));
            if(dat.eof()) break;
        }
    }
}
int main ()
{
    std::ifstream dat("ROBA.TXT");
    try {
        Skladiste s;
        s.UcitajIzDatoteke("ROBA.TXT");
        s.IzlistajSkladiste();
    }
    catch(std::logic_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    catch(std::bad_alloc) {
        std::cout<<"Problemi sa memorijom";
    }
   /* Skladiste s;
    auto p1=s.DodajSanduk(20,"tepsije", {10,20,30});
    s.IzlistajSkladiste();
    auto p2=s.DodajSanduk(30, "serpe", {5,6,7,8,9});
    auto p3=s.DodajVrecu(5, "sljunak", 50);
    s.IzlistajSkladiste();
    s.BrisiSpremnik(p1); return 0;
s.IzlistajSkladiste();
Skladiste s2(s);
std::cout<<"......"<<std::endl;
s2.IzlistajSkladiste();
Skladiste s3(std::move(s)); std::cout<<"...."<<std::endl;
s.IzlistajSkladiste();
Skladiste s4;
s4.DodajBure(50, "voda", 1000, 5);*/
//s4.IzlistajSkladiste();
//s4=s2; //s4.IzlistajSkladiste();
/*s4=std::move(s3); s4.IzlistajSkladiste(); std::cout<<"..."<<std::endl;
s3.IzlistajSkladiste();
Spremnik &p=s4.DajNajlaksi();
p.Ispisi();
Spremnik &n=s4.DajNajtezi(); n.Ispisi();
std::cout<<s4.BrojPreteskih(20);*/
  /*  std::shared_ptr<Spremnik> s;
    s=std::make_shared<Bure>(12, "asd", 13 , 13);
 //   Skladiste s1;
   // s1.v.resize(3);
//    for(int i=0; i<3; i++) s1.v[i]=std::make_shared<Bure>(1, "asd", 2, 3);
    Skladiste s2;
    s2.v.resize(4);
    for(int i=0; i<4; i++) s2.v[i]=std::make_shared<Vreca>(2, "pgh", 8);
  //  for(int i=0; i<4; i++) s2.v[i]->Ispisi();
    Skladiste s3;
    s3.v.resize(3);
    s3=s2;
   // s1=s2;
   Skladiste s4(s3);
    for(int i=0; i<s4.v.size(); i++) s4.v[i]->Ispisi();
    std::cout<<"------"<<std::endl;
    Skladiste s5; s5.v.resize(5); for(int i=0; i<5; i++) s5.v[i]=std::make_shared<Bure>(1, "ASD", 2, 3);
    s4=s5;
    for(int i=0; i<s4.v.size(); i++) s4.v[i]->Ispisi();
 //   s4=s5;
  //  Skladiste s4(s2);
*/
	return 0;
}
