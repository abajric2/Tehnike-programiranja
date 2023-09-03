/* 
    TP 16/17 (LV 13, Zadatak 4)
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
class Student {
    ApstraktniStudent *p_student;
    public:
    Student() : p_student(nullptr) {}
    ~Student() {delete p_student;}
    Student(const ApstraktniStudent &s) : p_student(s.DajKopiju()) {}
    Student(const Student &s) {
        if(!s.p_student) p_student=nullptr;
        else p_student=s.p_student->DajKopiju();
    }
    Student(Student &&s) {p_student=s.p_student; s.p_student=nullptr;}
    Student &operator =(const Student &s) {
        delete p_student;
        if(!s.p_student) p_student=nullptr;
        else p_student=s.p_student->DajKopiju();
        return *this;
    }
    Student &operator =(Student &&s) {
        p_student=s.p_student; s.p_student=nullptr;
        return *this;
    }
    std::string DajIme() const {return p_student->DajIme();}
    std::string DajPrezime() const {return p_student->DajPrezime();}
    int DajBrojIndeksa() const {return p_student->DajBrojIndeksa();}
    int DajBrojPolozenih() const {return p_student->DajBrojPolozenih();}
    double DajProsjek() const {return p_student->DajProsjek();}
    void RegistrirajIspit(int ocjena) {p_student->RegistrirajIspit(ocjena);}
    void PonistiOcjene() {p_student->PonistiOcjene();}
    void IspisiPodatke() const{p_student->IspisiPodatke();}
    ApstraktniStudent *DajKopiju() const {return p_student->DajKopiju();}
};
int main ()
{
    Student s1(StudentBachelor("Neki", "Student", 1234));
    s1.RegistrirajIspit(8); s1.RegistrirajIspit(7);
    std::cout<<s1.DajIme()<<" "<<s1.DajPrezime()<<" "<<s1.DajBrojIndeksa()<<" "<<s1.DajBrojPolozenih()<<" "<<s1.DajProsjek()<<std::endl;
    s1.PonistiOcjene();
    ApstraktniStudent *s2=s1.DajKopiju();
    s2->IspisiPodatke();
    Student s3(StudentMaster("Master", "Student", 1254, 2019));
    Student s4;
    s4=StudentMaster("Drugi", "Student", 1222, 2018);
    Student s5(std::move(s1));
    s5.IspisiPodatke();
    Student s6(s3);
    s4=s3;
    s4=std::move(s3);
    s3=s6;
    s3.IspisiPodatke();
	return 0;
}