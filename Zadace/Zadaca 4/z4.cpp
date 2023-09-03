//TP 2021/2022: Zadaća 4, Zadatak 4
#include <iostream>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <initializer_list>
#include <algorithm>
#include <memory>
#include <vector>

class Polazak {
    std::string odrediste;
    int broj_voza, broj_perona, sat_polaska, minute_polaska, trajanje_voznje, kasnjenje;
    bool brzi_voz;
    static std::pair<int, int> PrilagodiMinuteISate(int sat, int minute) {
        return {((minute-minute%60)/60+sat)%24, minute%60};
    }
    public:
    Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz,
    int sat_polaska, int minute_polaska, int trajanje_voznje);
    void PostaviKasnjenje(int kasnjenje) {Polazak::kasnjenje=kasnjenje;}
    bool DaLiKasni() const {return kasnjenje>0;}
    int DajTrajanjeVoznje() const {return trajanje_voznje;}
    std::pair<int, int> DajOcekivanoVrijemePolaska() const {
        return Polazak::PrilagodiMinuteISate(sat_polaska, minute_polaska+kasnjenje);
    }
    std::pair<int, int> DajOcekivanoVrijemeDolaska() const {
        return Polazak::PrilagodiMinuteISate(DajOcekivanoVrijemePolaska().first, DajOcekivanoVrijemePolaska().second+trajanje_voznje);
    }
    void Ispisi() const;
};
Polazak::Polazak (std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz, 
int sat_polaska, int minute_polaska, int trajanje_voznje) {
    if(odrediste.length()==0) throw std::domain_error("Nepoznato odrediste");
    if(broj_voza<0 || broj_voza>99999) throw std::domain_error("Neispravan broj voza");
    if(broj_perona<1 || broj_perona>6) throw std::domain_error("Broj perona mora biti u opsegu [1,6]");
    if(sat_polaska<0 || sat_polaska>23) throw std::domain_error("Neispravan sat polaska");
    if(minute_polaska<0 || minute_polaska>59) throw std::domain_error("Nesipravne minute polaska");
    if(trajanje_voznje<0) throw std::domain_error("Trajanje voznje ne moze biti negativno");
    Polazak::odrediste=odrediste; Polazak::broj_voza=broj_voza; Polazak::broj_perona=broj_perona;
    Polazak::sat_polaska=sat_polaska; Polazak::minute_polaska=minute_polaska; Polazak::trajanje_voznje=trajanje_voznje;
    Polazak::brzi_voz=brzi_voz; kasnjenje=0;
}
void Polazak::Ispisi() const {
    if(DaLiKasni()) {
        if(brzi_voz) std::cout<<"Brzi voz ";
        else std::cout<<"Lokalni voz ";
        std::cout<<"broj "<<broj_voza<<", odrediste "<<odrediste<<", sa predvidjenim vremenom polaska u "<<std::setw(2)<<std::setfill('0')<<
        sat_polaska<<":"<<std::setw(2)<<minute_polaska<<", kasni oko "<<kasnjenje<<" minuta, te ce poci oko "<<std::setw(2)<<
        DajOcekivanoVrijemePolaska().first<<":"<<std::setw(2)<<DajOcekivanoVrijemePolaska().second<<". Ocekuje se da voz stigne na odrediste oko "<<
        std::setw(2)<<DajOcekivanoVrijemeDolaska().first<<":"<<std::setw(2)<<DajOcekivanoVrijemeDolaska().second<<
        ". Izvinjavamo se putnicima zbog eventualnih neugodnosti."<<std::endl;
    }
    else {
        if(brzi_voz) std::cout<<"Brzi voz ";
        else std::cout<<"Lokalni voz ";
        std::cout<<"broj "<<broj_voza<<", odrediste "<<odrediste<<", polazi sa perona "<<broj_perona<<" u "<<std::setw(2)<<std::setfill('0')<<
        DajOcekivanoVrijemePolaska().first<<":"<<std::setw(2)<<DajOcekivanoVrijemePolaska().second<<", a na odrediste stize u "<<std::setw(2)<<
        DajOcekivanoVrijemeDolaska().first<<":"<<std::setw(2)<<DajOcekivanoVrijemeDolaska().second<<". Putnicima i voznom osoblju zelimo ugodno putovanje.";
    }
}
class RedVoznje {
    std::vector<std::shared_ptr<Polazak>> polasci;
    public:
    explicit RedVoznje () {}
    RedVoznje (std::initializer_list<Polazak> lista_polazaka);
    ~RedVoznje()=default;
    RedVoznje (const RedVoznje &red_voznje);
    RedVoznje (RedVoznje &&red_voznje);
    RedVoznje &operator =(const RedVoznje &red_voznje);
    RedVoznje &operator =(RedVoznje &&red_voznje);
    void RegistrirajPolazak (std::string odrediste, int broj_voza, bool brzi_voz, int broj_perona, int sat_polaska,
    int minute_polaska, int trajanje_voznje);
    void RegistrirajPolazak (std::shared_ptr<Polazak> polazak);
    int DajBrojPolazaka() const {return polasci.size();}
    int DajBrojPolazakaKojiKasne() const {
        return std::count_if(polasci.begin(), polasci.end(), [](std::shared_ptr<Polazak> p) {return p->DaLiKasni();});
    }
    int DajProsjecnoTrajanjeVoznji() const {
        int suma=0;
        std::for_each(polasci.begin(), polasci.end(), [&suma](std::shared_ptr<Polazak> p) {suma+=p->DajTrajanjeVoznje();});
        return suma/polasci.size();
    }
    Polazak &DajPrviPolazak() const;
    Polazak &DajPosljednjiPolazak() const;
    void IsprazniRedVoznje();
    void Ispisi (int sati, int minute) const;
};
RedVoznje::RedVoznje (std::initializer_list<Polazak> lista_polazaka) {
    for(auto it=lista_polazaka.begin(); it!=lista_polazaka.end(); it++) polasci.push_back(std::make_shared<Polazak>(*it));
}
RedVoznje::RedVoznje (const RedVoznje &red_voznje) {
    for(int i=0; i<red_voznje.polasci.size(); i++) polasci.push_back(std::make_shared<Polazak>(*(red_voznje.polasci[i])));
    }
RedVoznje::RedVoznje (RedVoznje &&red_voznje) {
    for(int i=0; i<red_voznje.polasci.size(); i++) {
        polasci.push_back(red_voznje.polasci.at(i));
        red_voznje.polasci.at(i)=nullptr;
    }
}
RedVoznje &RedVoznje::operator =(const RedVoznje &red_voznje) {
    if(&red_voznje==this) return *this;
    for(int i=0; i<polasci.size(); i++) polasci.at(i)=nullptr;
    polasci.resize(red_voznje.polasci.size());
    for(int i=0; i<polasci.size(); i++) polasci.at(i)=std::make_shared<Polazak>(*(red_voznje.polasci.at(i)));
    return *this;
}
RedVoznje &RedVoznje::operator =(RedVoznje &&red_voznje) {
    std::swap(polasci, red_voznje.polasci);
    return *this;
}
void RedVoznje::RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz, int broj_perona,
int sat_polaska, int minute_polaska, int trajanje_voznje) {
    polasci.push_back(std::make_shared<Polazak>(Polazak(odrediste, broj_voza, broj_perona, brzi_voz, sat_polaska, minute_polaska, trajanje_voznje)));
}
void RedVoznje::RegistrirajPolazak(std::shared_ptr<Polazak> polazak) {
    
    polasci.push_back(polazak);
}
Polazak &RedVoznje::DajPrviPolazak() const {
    if(polasci.size()==0) throw std::domain_error("Nema registriranih polazaka");
    std::shared_ptr<Polazak> min=*std::min_element(polasci.begin(), polasci.end(), 
    [](std::shared_ptr<const Polazak>p1, std::shared_ptr<const Polazak> p2) {
        if(p1->DajOcekivanoVrijemePolaska().first<p2->DajOcekivanoVrijemePolaska().first) return true;
        else if(p1->DajOcekivanoVrijemePolaska().first>p2->DajOcekivanoVrijemePolaska().first) return false;
        return p1->DajOcekivanoVrijemePolaska().second<p2->DajOcekivanoVrijemePolaska().second;
    });
    return *min;
}
Polazak &RedVoznje::DajPosljednjiPolazak() const {
    if(polasci.size()==0) throw std::domain_error("Nema registriranih polazaka");
    std::shared_ptr<Polazak> max=*std::max_element(polasci.begin(), polasci.end(), 
    [](std::shared_ptr<const Polazak> p1, std::shared_ptr<const Polazak> p2) {
        if(p1->DajOcekivanoVrijemePolaska().first<p2->DajOcekivanoVrijemePolaska().first) return true;
        else if(p1->DajOcekivanoVrijemePolaska().first>p2->DajOcekivanoVrijemePolaska().first) return false;
        return p1->DajOcekivanoVrijemePolaska().second<p2->DajOcekivanoVrijemePolaska().second;
    });
    return *max;
}
void RedVoznje::IsprazniRedVoznje() {
    for(int i=0; i<polasci.size(); i++) {
        polasci.at(i)=nullptr;
    }
    polasci.resize(0);
}
void RedVoznje::Ispisi(int sati, int minute) const {
    std::vector<std::shared_ptr<Polazak>> pomocni(polasci);
    std::sort(pomocni.begin(), pomocni.end(), [](std::shared_ptr<const Polazak> p1, std::shared_ptr<const Polazak> p2) {
        if(p1->DajOcekivanoVrijemePolaska().first<p2->DajOcekivanoVrijemePolaska().first) return true;
        if(p1->DajOcekivanoVrijemePolaska().first>p2->DajOcekivanoVrijemePolaska().first) return false;
        return p1->DajOcekivanoVrijemePolaska().second<p2->DajOcekivanoVrijemePolaska().second;
    });
    for(int i=0; i<pomocni.size(); i++) {
        if(pomocni[i]->DajOcekivanoVrijemePolaska().first>sati || 
        (pomocni[i]->DajOcekivanoVrijemePolaska().first==sati && pomocni[i]->DajOcekivanoVrijemePolaska().second>=minute)) {
            pomocni[i]->Ispisi(); std::cout<<std::endl;
        }
    }
}

int main ()
{
    Polazak p("Mostar", 123, 5, false, 12, 0, 126);
    p.PostaviKasnjenje(30);
    if(p.DaLiKasni()) std::cout<<"Voz kasni"<<std::endl;
    else std::cout<<"Voz ne kasni"<<std::endl;
    std::cout<<"Voznja traje "<<p.DajTrajanjeVoznje()<<" minuta."<<std::endl<<"Ocekivano vrijeme polaska: "<<p.DajOcekivanoVrijemePolaska().first<<" i "<<
    p.DajOcekivanoVrijemePolaska().second<<std::endl<<"Ocekivano vrijeme dolaska: "<<p.DajOcekivanoVrijemeDolaska().first<<" i "<<
    p.DajOcekivanoVrijemeDolaska().second<<std::endl;
    p.Ispisi();std::cout<<std::endl;
    RedVoznje r1;
    RedVoznje r2{{"Sarajevo", 125, 2, true, 1, 15, 145}, {"Tuzla", 124, 1, false, 2, 20, 55}, {"Bihac", 598, 3, false, 18, 15, 205}};
    r2.DajPrviPolazak().PostaviKasnjenje(10);
    RedVoznje r3(r2);
    std::cout<<r3.DajBrojPolazaka()<<" "<<r3.DajBrojPolazakaKojiKasne()<<" "<<r3.DajProsjecnoTrajanjeVoznji()<<std::endl;
    r1.RegistrirajPolazak("Konjic", 654, false, 3, 12, 15, 208);
    r1.RegistrirajPolazak("Zenica", 165, false, 2, 8, 15, 35);
    r1.Ispisi(11, 15); std::cout<<std::endl;
    RedVoznje r4=std::move(r1);
    r2.Ispisi(2, 0); std::cout<<std::endl;
    r2=std::move(r3);
    auto p1=r2.DajPrviPolazak();
    std::cout<<p1.DajOcekivanoVrijemePolaska().first<<" "<<p1.DajOcekivanoVrijemePolaska().second<<std::endl;
    auto p2=r4.DajPosljednjiPolazak();
    std::cout<<p2.DajOcekivanoVrijemePolaska().first<<" "<<p2.DajOcekivanoVrijemePolaska().second<<std::endl;
    std::shared_ptr<Polazak> p3=std::make_shared<Polazak>(Polazak("Neum", 256, 1, true, 4, 15, 185));
    r4.RegistrirajPolazak(p3);
    r4.Ispisi(0, 0); std::cout<<std::endl;
    RedVoznje r5{p1, p2};
    RedVoznje r6=r5;
    r6.Ispisi(1, 10); std::cout<<std::endl;
    r5.Ispisi(0, 0); std::cout<<std::endl;
    r2=r4;
    r2.Ispisi(0, 15); std::cout<<std::endl;
    r4.IsprazniRedVoznje();
    r4.Ispisi(0, 0); std::cout<<std::endl;
	return 0;
}
