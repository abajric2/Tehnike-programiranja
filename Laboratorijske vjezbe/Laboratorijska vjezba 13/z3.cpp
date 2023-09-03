/* 
    TP 16/17 (LV 13, Zadatak 3)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

class ApstraktniStudent {
    std::string ime, prezime;
    int broj_indeksa, broj_polozenih_ispita;
    double prosjek;
    public:
    virtual ~ApstraktniStudent() {}
    ApstraktniStudent(std::string ime, std::string prezime, int br_indeksa) : ime(ime), prezime(prezime),
        broj_indeksa(br_indeksa), broj_polozenih_ispita(0), prosjek(5) {}
    std::string DajIme() const {return ime;}
    std::string DajPrezime() const {return prezime;}
    int DajBrojIndeksa() const {return broj_indeksa;}
    int DajBrojPolozenih() const {return broj_polozenih_ispita;}
    double DajProsjek() const {return prosjek;}
    void RegistrirajIspit(int ocjena);
    void PonistiOcjene() {broj_polozenih_ispita=0; prosjek=5;}
    virtual void IspisiPodatke() const = 0;
    virtual ApstraktniStudent *DajKopiju() const = 0;
};
void ApstraktniStudent::RegistrirajIspit(int ocjena) {
    if(ocjena<5 || ocjena>10) throw std::domain_error("Neispravna ocjena");
    if(ocjena==5) return;
    broj_polozenih_ispita++;
    if(broj_polozenih_ispita==1) prosjek=ocjena;
    else prosjek=(prosjek*(broj_polozenih_ispita-1)+ocjena)/broj_polozenih_ispita;
}
class StudentBachelor : public ApstraktniStudent {
    public:
    StudentBachelor(std::string ime, std::string prezime, int br_indeksa) : ApstraktniStudent(ime, prezime, br_indeksa) {} 
    void IspisiPodatke () const override {
        std::cout<<"Student bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<", ima prosjek "<<
        DajProsjek()<<"."<<std::endl;
    }
    ApstraktniStudent *DajKopiju() const override {return new StudentBachelor(*this);}
};
class StudentMaster : public ApstraktniStudent {
    int godina_zavrsetka_bachelora;
    public:
    StudentMaster(std::string ime, std::string prezime, int br_indeksa, int god) : ApstraktniStudent(ime, prezime, br_indeksa), godina_zavrsetka_bachelora(god) {}
    void IspisiPodatke() const override {
        std::cout<<"Student master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<std::endl<<
        "zavrsio bachelor studij godine "<<godina_zavrsetka_bachelora<<",ima prosjek "<<DajProsjek()<<"."<<std::endl;
    }
    ApstraktniStudent *DajKopiju() const override {return new StudentMaster(*this);}
};
class Fakultet {
    std::vector<ApstraktniStudent *> v;
    public:
    Fakultet() {}
    ~Fakultet();
    Fakultet(const Fakultet &f);
    Fakultet(Fakultet &&f);
    Fakultet &operator =(const Fakultet &f);
    Fakultet &operator =(Fakultet &&f);
    void UpisiStudenta(std::string ime, std::string prezime, int br_indeksa);
    void UpisiStudenta(std::string ime, std::string prezime, int br_indeksa, int god);
    void ObrisiStudenta(int br_indeksa);
    const ApstraktniStudent &operator [](int br_indeksa) const;
    ApstraktniStudent &operator [](int br_indeksa);
    void IspisiSveStudente() const;
};
Fakultet::~Fakultet() {
    for(int i=0; i<v.size(); i++) delete v[i];
}
Fakultet::Fakultet(const Fakultet &f) {
    v.resize(f.v.size());
    try {
        for(int i=0; i<v.size(); i++) v[i]=f.v[i]->DajKopiju();
    }
    catch(...) {
        for(int i=0; i<v.size(); i++) delete v[i];
        throw;
    }
}
Fakultet::Fakultet(Fakultet &&f) : v(f.v){
    for(int i=0; i<f.v.size(); i++) f.v[i]=nullptr;
    f.v.resize(0);//zasto mora rucno
}
Fakultet &Fakultet::operator =(const Fakultet &f) {
    for(int i=0; i<v.size(); i++) delete v[i];
    v.resize(f.v.size());
    try {
        for(int i=0; i<v.size(); i++) v[i]=f.v[i]->DajKopiju();
    }
    catch(...) {
        for(int i=0; i<v.size(); i++) delete v[i];
        throw;
    }
    return *this;
}
Fakultet &Fakultet::operator =(Fakultet &&f) {
    for(int i=0; i<v.size(); i++) delete v[i];
    v=f.v;
    for(int i=0; i<f.v.size(); i++) f.v[i]=nullptr;
    f.v.resize(0);
    //std::swap(v, f.v);
    return *this;
}
void Fakultet::UpisiStudenta(std::string ime, std::string prezime, int br_indeksa) {
    for(int i=0; i<v.size(); i++) if(v[i]->DajBrojIndeksa()==br_indeksa) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
    v.push_back(new StudentBachelor(ime, prezime, br_indeksa));
}
void Fakultet::UpisiStudenta(std::string ime, std::string prezime, int br_indeksa, int god) {
    for(int i=0; i<v.size(); i++) if(v[i]->DajBrojIndeksa()==br_indeksa) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
    v.push_back(new StudentMaster(ime, prezime, br_indeksa, god));
}
void Fakultet::ObrisiStudenta(int br_indeksa) {
    for(int i=0; i<v.size(); i++) {
        if(v[i]->DajBrojIndeksa()==br_indeksa) {
            delete v[i]; v.erase(v.begin()+i);
            return;
        }
    }
    throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
}
const ApstraktniStudent &Fakultet::operator [](int br_indeksa) const {
    for(int i=0; i<v.size(); i++) {
        if(v[i]->DajBrojIndeksa()==br_indeksa) return *v[i];
    }
    throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
}
ApstraktniStudent &Fakultet::operator [](int br_indeksa) {
    for(int i=0; i<v.size(); i++) {
        if(v[i]->DajBrojIndeksa()==br_indeksa) return *v[i];
    }
    throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
}
void Fakultet::IspisiSveStudente() const{
    std::vector<ApstraktniStudent *> pomocni(v);
    std::sort(pomocni.begin(), pomocni.end(), [](ApstraktniStudent *p1, ApstraktniStudent *p2) {
        if(p1->DajProsjek()>p2->DajProsjek()) return true;
        else if(p1->DajProsjek()<p2->DajProsjek()) return false;
        return p1->DajBrojIndeksa()<p2->DajBrojIndeksa();
    });
    std::for_each(pomocni.begin(), pomocni.end(), [](ApstraktniStudent *p){p->IspisiPodatke();});
}

int main ()
{
    Fakultet f1;
    f1.UpisiStudenta("Meho", "Mehic", 1234);
    f1.UpisiStudenta("Huso", "Husic", 1243, 2020);
    f1.IspisiSveStudente();
    f1[1234].RegistrirajIspit(10);
    std::cout<<f1[1234].DajProsjek()<<std::endl;
    f1[1234].PonistiOcjene();
    f1.IspisiSveStudente();
    const Fakultet f2(f1);
    f2.IspisiSveStudente();
    f2[1234].IspisiPodatke();
    Fakultet f3(std::move(f2));
    f3.UpisiStudenta("Neko", "Tamo", 1256);
    f3.UpisiStudenta("Jedan", "Student", 4321, 2018);
    f3.IspisiSveStudente();
    f3.ObrisiStudenta(1234);
    f1=f3;
    f1.IspisiSveStudente();
    f1=std::move(f3);
    f3.IspisiSveStudente();
	return 0;
}