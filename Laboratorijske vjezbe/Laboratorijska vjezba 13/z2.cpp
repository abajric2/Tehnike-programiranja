/* 
    TP 16/17 (LV 13, Zadatak 2)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <string>
#include <stdexcept>

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
int main ()
{
    StudentBachelor sb("Neki", "Student", 12345);
    sb.RegistrirajIspit(8); sb.RegistrirajIspit(6); sb.RegistrirajIspit(10);
    std::cout<<sb.DajIme()<<" "<<sb.DajPrezime()<<" "<<sb.DajBrojIndeksa()<<sb.DajBrojPolozenih()
    <<" "<<sb.DajProsjek()<<std::endl;
    sb.PonistiOcjene();
    sb.IspisiPodatke();
    ApstraktniStudent *pom=sb.DajKopiju();
    pom->RegistrirajIspit(6);
    pom->IspisiPodatke();
    StudentMaster sm("Master", "Student", 12543, 2020);
    sm.RegistrirajIspit(9); sm.RegistrirajIspit(5);
    std::cout<<sm.DajIme()<<" "<<sm.DajPrezime()<<" "<<sm.DajBrojIndeksa()<<" "<<sm.DajBrojPolozenih()<<
    " "<<sm.DajProsjek()<<std::endl;
    sm.PonistiOcjene();
    sm.IspisiPodatke();
    ApstraktniStudent *m_pom=sm.DajKopiju();
    m_pom->RegistrirajIspit(10);
    m_pom->IspisiPodatke();
	return 0;
}