//TP 2021/2022: LV 14, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>

class Spremnik {
    protected:
    double tezina;
    char naziv[100];
    public:
    virtual ~Spremnik() {}
    Spremnik(double tezina, const char naziv[]) : tezina(tezina) {
        std::strcpy(Spremnik::naziv, naziv);
    }
    double DajTezinu() const {return tezina;}
    virtual double DajUkupnuTezinu() const = 0;
    virtual void Ispisi() const = 0;
    virtual Spremnik *DajKopiju() const = 0;
};
class Sanduk : public Spremnik {
    double tezina_predmeta;
    int broj_predmeta;
    public:
    Sanduk(double tezina, const char naziv[], int broj_predmeta, double tezina_predmeta) : Spremnik(tezina, naziv), broj_predmeta(broj_predmeta),
        tezina_predmeta(tezina_predmeta) {}
    double DajUkupnuTezinu() const override {return tezina+broj_predmeta*tezina_predmeta;}
    void Ispisi() const override;
    Spremnik *DajKopiju() const override {return new Sanduk(*this);}
};
void Sanduk::Ispisi() const {
    std::cout<<"Vrsta spremnika: Sanduk"<<std::endl<<"Sadrzaj: "<<naziv<<std::endl<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl<<
    "Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}
class Bure : public Spremnik {
    double tezina_tecnosti;
    public:
    Bure(double tezina, const char naziv[], double tezina_tecnosti) : Spremnik(tezina, naziv), tezina_tecnosti(tezina_tecnosti) {}
    double DajUkupnuTezinu() const override {return tezina+tezina_tecnosti;}
    void Ispisi() const override;
    Spremnik *DajKopiju() const override {return new Bure(*this);}
};
void Bure::Ispisi() const {
    std::cout<<"Vrsta spremnika: Bure"<<std::endl<<"Sadrzaj: "<<naziv<<std::endl<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl<<
    "Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}
class Skladiste {
    Spremnik **roba;
    int kapacitet, broj_pohranjenih;
    public:
    explicit Skladiste(int kapacitet) : kapacitet(kapacitet), broj_pohranjenih(0), roba(new Spremnik *[kapacitet]{}) {}
    ~Skladiste();
    Skladiste(const Skladiste &s);
    Skladiste(Skladiste &&s);
    Skladiste &operator =(const Skladiste &s);
    Skladiste &operator =(Skladiste &&s);
    void DodajSanduk(double tezina, const char naziv[], int broj_predmeta, double tezina_predmeta);
    void DodajBure(double tezina, const char naziv[], double tezina_tecnosti);
    Spremnik &DajNajlaksi();
    Spremnik &DajNajtezi();
    int BrojPreteskih(int t) const;
    void IzlistajSkladiste() const;
    void UcitajIzDatoteke(std::string ime_datoteke);
};
Skladiste::~Skladiste() {
    for(int i=0; i<broj_pohranjenih; i++) delete roba[i];
    delete[] roba;
}
Skladiste::Skladiste(const Skladiste &s) : roba(new Spremnik *[s.kapacitet]{}), kapacitet(s.kapacitet), broj_pohranjenih(s.broj_pohranjenih) {
    try {
        for(int i=0; i<broj_pohranjenih; i++) roba[i]=s.roba[i]->DajKopiju();
    }
    catch(...) {
        for(int i=0; i<broj_pohranjenih; i++) delete roba[i];
        delete[] roba;
        throw;
    }
}
Skladiste::Skladiste(Skladiste &&s) : roba(s.roba), kapacitet(s.kapacitet), broj_pohranjenih(s.broj_pohranjenih) {
    s.roba=nullptr; s.broj_pohranjenih=0;
}
Skladiste &Skladiste::operator =(const Skladiste &s) {
    if(this==&s) return *this;
    for(int i=0; i<broj_pohranjenih; i++) delete roba[i];
    delete[] roba;
    broj_pohranjenih=0;
    roba=new Spremnik *[s.kapacitet]{};
    try {
        for(int i=0; i<s.broj_pohranjenih; i++) roba[i]=s.roba[i]->DajKopiju();
        kapacitet=s.kapacitet; broj_pohranjenih=s.broj_pohranjenih;
    }
    catch(...) {
        for(int i=0; i<s.broj_pohranjenih; i++) delete roba[i];
        delete[] roba;
        broj_pohranjenih=0;
        throw;
    }
    return *this;
}
Skladiste &Skladiste::operator =(Skladiste &&s) {
    if(&s==this) return *this;
    for(int i=0; i<broj_pohranjenih; i++) delete roba[i];
    delete[] roba;
    broj_pohranjenih=0;
    roba=s.roba; kapacitet=s.kapacitet; broj_pohranjenih=s.broj_pohranjenih;
    s.roba=nullptr; s.broj_pohranjenih=0;
    return *this; 
}
void Skladiste::DodajBure(double tezina, const char naziv[], double tezina_tecnosti) {
    if(broj_pohranjenih>=kapacitet) throw std::domain_error("Popunjeno skladiste");
    roba[broj_pohranjenih++]=new Bure(tezina, naziv, tezina_tecnosti);
}
void Skladiste::DodajSanduk(double tezina, const char *naziv, int broj_predmeta, double tezina_predmeta) {
    if(broj_pohranjenih>=kapacitet) throw std::domain_error("Popunjeno skladiste");
    roba[broj_pohranjenih++]=new Sanduk(tezina, naziv, broj_predmeta, tezina_predmeta);
}
Spremnik &Skladiste::DajNajlaksi() {
    if(!broj_pohranjenih) throw std::range_error("Skladiste je prazno");
    Spremnik *min=*std::min_element(roba, roba+broj_pohranjenih, [](Spremnik *p1, Spremnik *p2) {return p1->DajTezinu()<p2->DajTezinu();});
    return *min;
}
Spremnik &Skladiste::DajNajtezi() {
    if(!broj_pohranjenih) throw std::range_error("Skladiste je prazno");
    Spremnik *max=*std::max_element(roba, roba+broj_pohranjenih, [](Spremnik *p1, Spremnik *p2) {return p1->DajTezinu()<p2->DajTezinu();});
    return *max;
}
int Skladiste::BrojPreteskih(int t) const {
    return std::count_if(roba, roba+broj_pohranjenih, [t](Spremnik *p) {return p->DajUkupnuTezinu()>t;});
}
void Skladiste::IzlistajSkladiste() const {
    std::sort(roba, roba+broj_pohranjenih, [](Spremnik *p1, Spremnik *p2) {return p1->DajUkupnuTezinu()>p2->DajUkupnuTezinu();});
    std::for_each(roba, roba+broj_pohranjenih, [](Spremnik *p) {p->Ispisi();});
}
void Skladiste::UcitajIzDatoteke(std::string ime_datoteke) {
    std::ifstream dat(ime_datoteke);
    if(!dat) throw std::logic_error("Trazena datoteka ne postoji");
    kapacitet=0;
    for(;;) {
        std::string red;
        std::getline(dat, red);
        if(dat.eof()) break;
        if(!dat) {
            throw std::logic_error("Problemi pri citanju datoteke");
        }
            if(*red.begin()!='S' && *red.begin()!='B') throw std::logic_error("Datoteka sadrzi besmislene podatke");
            if(*red.begin()=='S') {
                double tez, tez_predmeta;
                int br_predmeta;
                if(!(dat>>tez>>br_predmeta>>tez_predmeta)) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                dat.ignore(10000, '\n');
                kapacitet++;
            }
            else {
                double tez, tez_tecnosti;
                if(!(dat>>tez>>tez_tecnosti)) throw std::logic_error("Datoteka sadrzi besmislene podatke");
                dat.ignore(10000, '\n');
                kapacitet++;
            }
    }
    dat.close();
    dat.open(ime_datoteke);
    for(int i=0; i<broj_pohranjenih; i++) delete roba[i];
    delete[] roba;
    roba=new Spremnik *[kapacitet]{};
    broj_pohranjenih=0;
    for(;;) {
        std::string red;
        std::getline(dat, red);
        if(dat.eof()) break;
        if(!dat) throw std::logic_error("Problemi pri citanju datoteke");
        if(*red.begin()!='S' && *red.begin()!='B') throw std::logic_error("Datoteka sadrzi besmislene podatke");
        if(*red.begin()=='S') {
            double tez, tez_predmeta;
            int br_predmeta;
            if(!(dat>>tez>>br_predmeta>>tez_predmeta)) throw std::logic_error("Datoteka sadrzi besmislene podatke");
            dat.ignore(10000, '\n');
            std::string pomocni;
            for(auto i=red.begin(); i!=red.end(); i++) {
                if(i!=red.begin() && *i!=' ') {
                    pomocni=red.substr(i-red.begin(), red.end()-i); break;
                }
            }
            roba[broj_pohranjenih++]=new Sanduk(tez, pomocni.c_str(), br_predmeta, tez_predmeta);
        }
        else {
            double tez, tez_tecnosti;
            if(!(dat>>tez>>tez_tecnosti)) throw std::logic_error("Datoteka sadrzi besmislene podatke");
            dat.ignore(10000, '\n');
            std::string pomocni;
            for(auto i=red.begin(); i!=red.end(); i++) {
                if(i!=red.begin() && *i!=' ') {
                    pomocni=red.substr(i-red.begin(), red.end()-i); break;
                }
            }
            roba[broj_pohranjenih++]=new Bure(tez, pomocni.c_str(), tez_tecnosti);
        }
    }
}
int main ()
{
    try {
    Skladiste s(10);
    std::ofstream dat("ROBA.TXT"); 
    dat<<"S Serpe"<<std::endl<<"20.5 10 5"<<std::endl<<"B Voda"<<std::endl<<"5.5 3"<<std::endl<<"B Ulje"<<std::endl<<"6 6"<<std::endl<<
    "S Neki teski predmeti"<<std::endl<<"10.6 5 120";
    dat.close();
    s.UcitajIzDatoteke("ROBA.TXT");
    s.IzlistajSkladiste();
    }
    catch(std::logic_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
    }
    catch(std::bad_alloc) {
        std::cout<<"Problemi sa memorijom"<<std::endl;
    }
	return 0;
}
