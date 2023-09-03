//TP 2021/2022: Zadaća 4, Zadatak 5
#include <iostream>
#include <cmath>
#include <ostream>
#include <string>
#include <stdexcept>
#include <map>

struct Student {
    int broj_indeksa, godina_studija;
    std::string ime, prezime, adresa, telefon;
};
class Knjiga {
    std::string naslov, ime_pisca, zanr;
    int godinja_izdavanja;
    Student *zaduzenje;
    public:
    Knjiga(std::string naslov, std::string ime_pisca, std::string zanr, int godinja_izdavanja) : naslov(naslov), ime_pisca(ime_pisca),
        zanr(zanr), godinja_izdavanja(godinja_izdavanja), zaduzenje(nullptr) {}
    std::string DajNaslov() const {return naslov;}
    std::string DajAutora() const {return ime_pisca;}
    std::string DajZanr() const {return zanr;}
    int DajGodinuIzdavanja() const {return godinja_izdavanja;}
    void ZaduziKnjigu (Student &student) {zaduzenje=&student;}
    void RazduziKnjigu() {zaduzenje=nullptr;}
    bool DaLiJeZaduzena() const {return zaduzenje;}
    Student &DajKodKogaJe() const {
        if(!zaduzenje) throw std::domain_error("Knjiga nije zaduzena");
        return *zaduzenje;
    }
    Student *DajPokKodKogaJe() const {return zaduzenje;}
};
class Biblioteka {
    std::map<int, Student*> student;
    std::map<int, Knjiga*> knjiga;
    static void IspisiKnjigu(int evidencijski_broj, Knjiga *k);
    public:
    Biblioteka () {};
    Biblioteka(const Biblioteka &b);
    Biblioteka(Biblioteka &&b);
    Biblioteka &operator =(const Biblioteka &b); 
    Biblioteka &operator =(Biblioteka &&b);
    ~Biblioteka();
    void RegistrirajNovogStudenta (int broj_indeksa, std::string ime, std::string prezime, int godina_studija, 
        std::string adresa, std::string broj_telefona);
    void RegistrirajNovuKnjigu (int evidencijski_broj_knjige, std::string naslov, std::string ime_pisca, std::string zanr, int godina_izdavanja);
    Student &NadjiStudenta (int broj_indeksa) const {
        auto it=student.find(broj_indeksa);
        if(it==student.end()) throw std::logic_error("Student nije nadjen");
        return *(it->second);
    }
    Knjiga &NadjiKnjigu (int evidencijski_broj) const {
        auto it=knjiga.find(evidencijski_broj);
        if(it==knjiga.end()) throw std::logic_error("Knjiga nije nadjena");
        return *(it->second);
    }
    void IzlistajStudente() const;
    void IzlistajKnjige() const;
    void ZaduziKnjigu(int evidencijski_broj_knjige, int broj_indeksa);
    void RazduziKnjigu(int evidencijski_broj_knjige);
    void PrikaziZaduzenja(int broj_indeksa) const;
};
Biblioteka::Biblioteka (const Biblioteka &b) {
    for(auto it=b.student.begin(); it!=b.student.end(); it++) {
        student.insert({it->first, new Student(*(it->second))});
    }
    for(auto it=b.knjiga.begin(); it!=b.knjiga.end(); it++) {
        knjiga.insert({it->first, new Knjiga(*(it->second))});
    }
}
Biblioteka::Biblioteka (Biblioteka &&b) {
    for(auto it=b.student.begin(); it!=b.student.end(); it++) {
        student.insert({it->first, it->second}); it->second=nullptr;
    }
    for(auto it=b.knjiga.begin(); it!=b.knjiga.end(); it++) {
        knjiga.insert({it->first, it->second}); it->second=nullptr;
    }
}
Biblioteka &Biblioteka::operator =(Biblioteka &&b) {
    std::swap(student, b.student);
    std::swap(knjiga, b.knjiga);
    return *this;
}
Biblioteka &Biblioteka::operator =(const Biblioteka &b) {
    if(&b==this) return *this;
    for(auto it=student.begin(); it!=student.end();) {
        delete it->second; it=student.erase(it);
    }
    for(auto it=b.student.begin(); it!=b.student.end(); it++) {
        student.insert({it->first, new Student(*it->second)}); 
    }
    for(auto it=knjiga.begin(); it!=knjiga.end();) {
        delete it->second; it=knjiga.erase(it);
    }
    for(auto it=b.knjiga.begin(); it!=b.knjiga.end(); it++) {
        knjiga.insert({it->first, new Knjiga(*it->second)}); 
    }
    return *this;
}
Biblioteka::~Biblioteka() {
    for(auto it=student.begin(); it!=student.end(); it++) {
        delete it->second;
    }
    for(auto it=knjiga.begin(); it!=knjiga.end(); it++) {
        delete it->second;
    }
}
void Biblioteka::RegistrirajNovogStudenta (int broj_indeksa, std::string ime, std::string prezime, int godina_studija,
    std::string adresa, std::string broj_telefona) {
        if(student.find(broj_indeksa)!=student.end()) throw std::logic_error("Vec postoji student s tim brojem indeksa");
        Student *s=new Student;
        s->broj_indeksa=broj_indeksa; s->ime=ime; s->prezime=prezime; s->godina_studija=godina_studija;
        s->adresa=adresa; s->telefon=broj_telefona;
        student[broj_indeksa]=s;
    }
void Biblioteka::RegistrirajNovuKnjigu(int evidencijski_broj_knjige, std::string naslov, std::string ime_pisca, std::string zanr, int godina_izdavanja) {
    if(knjiga.find(evidencijski_broj_knjige)!=knjiga.end()) throw std::logic_error("Knjiga s tim evidencijskim brojem vec postoji");
    knjiga[evidencijski_broj_knjige]=new Knjiga(naslov, ime_pisca, zanr, godina_izdavanja);
}
void Biblioteka::IzlistajStudente() const {
    for(auto it=student.begin(); it!=student.end(); it++) {
        std::cout<<"Broj indeksa: "<<it->second->broj_indeksa<<std::endl<<"Ime i prezime: "<<it->second->ime<<" "<<it->second->prezime<<
        std::endl<<"Godina studija: "<<it->second->godina_studija<<std::endl<<"Adresa: "<<it->second->adresa<<std::endl<<
        "Broj telefona: "<<it->second->telefon<<std::endl<<std::endl;
    }
}
void Biblioteka::IspisiKnjigu (int evidencijski_broj, Knjiga *k) {
    std::cout<<"Evidencijski broj: "<<evidencijski_broj<<std::endl<<"Naslov: "<<k->DajNaslov()<<std::endl<<"Pisac: "<<
    k->DajAutora()<<std::endl<<"Zanr: "<<k->DajZanr()<<std::endl<<"Godina izdavanja: "<<k->DajGodinuIzdavanja()<<std::endl;
}
void Biblioteka::IzlistajKnjige() const {
    for(auto it=knjiga.begin(); it!=knjiga.end(); it++) {
        Biblioteka::IspisiKnjigu(it->first, it->second);
        if(it->second->DaLiJeZaduzena()) std::cout<<"Zaduzena kod studenta: "<<it->second->DajKodKogaJe().ime<<" "<<it->second->DajKodKogaJe().prezime<<
        " ("<<it->second->DajKodKogaJe().broj_indeksa<<")"<<std::endl;
        std::cout<<std::endl;
    }
}
void Biblioteka::ZaduziKnjigu(int evidencijski_broj_knjige, int broj_indeksa) {
    NadjiKnjigu(evidencijski_broj_knjige);
    NadjiStudenta(broj_indeksa);
    if(NadjiKnjigu(evidencijski_broj_knjige).DaLiJeZaduzena()) throw std::logic_error("Knjiga vec zaduzena");
    NadjiKnjigu(evidencijski_broj_knjige).ZaduziKnjigu(NadjiStudenta(broj_indeksa));
}
void Biblioteka::RazduziKnjigu(int evidencijski_broj_knjige) {
    if(!NadjiKnjigu(evidencijski_broj_knjige).DaLiJeZaduzena()) throw std::logic_error("Knjiga nije zaduzena");
    NadjiKnjigu(evidencijski_broj_knjige).RazduziKnjigu();
}
void Biblioteka::PrikaziZaduzenja(int broj_indeksa) const {
    int br_zaduzenja=0;
    for(auto it=knjiga.begin(); it!=knjiga.end(); it++) {
        if(it->second->DaLiJeZaduzena() && it->second->DajKodKogaJe().broj_indeksa==NadjiStudenta(broj_indeksa).broj_indeksa) {
            Biblioteka::IspisiKnjigu(it->first, it->second);
            std::cout<<std::endl;
            br_zaduzenja++;
        }
    }
    if(br_zaduzenja==0) std::cout<<"Nema zaduzenja za tog studenta!"<<std::endl;
}
int main ()
{
    Biblioteka b;
    for(;;) {
    std::cout<<"Unesite broj za opciju koju zelite odabrati"<<std::endl<<"1 - Registrovanje novog studenta"<<std::endl<<"2 - Registrovanje nove knjige"<<std::endl<<
    "3 - Traznje studenta sa unesenim brojem indeksa"<<std::endl<<"4 - Trazenje knjige sa unesenim evidencijskim brojem"<<std::endl<<
    "5 - Ispis studenata"<<std::endl<<"6 - Ispis knjiga"<<std::endl<<"7 - Zaduzivanje knjige"<<std::endl<<"8 - Razduzivanje knjige"<<std::endl<<
    "9 - Prikaz zaduzenja"<<std::endl<<"10 - kraj"<<std::endl;
    int opcija;
    std::cin>>opcija;
    switch(opcija) {
        case 1: {
            int br_indeksa, godina_studija;
            std::string ime, prezime, adresa, br_tel;
            std::cout<<"Uneiste podatke za studenta - broj indeksa, ime, prezime, godinu studija, adresu i broj telefona (ENTER nakon svakog podatka): ";
            std::cin>>br_indeksa;
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, ime);
            std::getline(std::cin, prezime);
            std::cin>>godina_studija;
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, adresa);
            std::getline(std::cin, br_tel);
            try {
            b.RegistrirajNovogStudenta(br_indeksa, ime, prezime, godina_studija, adresa, br_tel);
            }
            catch(std::logic_error izuzetak) {
                std::cout<<izuzetak.what()<<std::endl;
            }
            break;
        }
        case 2: {
            int evidencijski_broj, godina_izdavanja;
            std::string naslov, ime_pisca, zanr;
            std::cout<<"Unesite podatke o knjizi - evidencijski broj, naslov, ime pisca, zanr i godinu izdavanja (ENTER nakon svakog podatka):";
            std::cin>>evidencijski_broj;
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, naslov);
            std::getline(std::cin, ime_pisca);
            std::getline(std::cin, zanr);
            std::cin>>godina_izdavanja;
            std::cin.ignore(10000, '\n');
            try {
            b.RegistrirajNovuKnjigu(evidencijski_broj, naslov, ime_pisca, zanr, godina_izdavanja);
            }
            catch(std::logic_error izuzetak) {
                std::cout<<izuzetak.what()<<std::endl;
            }
            break;
        }
        case 3: {
            int br_indeksa;
            std::cout<<"Unesite broj indeksa studenta: ";
            std::cin>>br_indeksa;
            try {
                Student s=b.NadjiStudenta(br_indeksa);
                std::cout<<"Ime i prezime studenta sa tim indeksom je "<<s.ime<<" "<<s.prezime<<std::endl;
            }
            catch(std::logic_error izuzetak) {
                std::cout<<izuzetak.what()<<std::endl;
            }
            break;
        }
        case 4: {
            int evidencijski_broj;
            std::cout<<"Unesite evidencijski broj knjige: ";
            std::cin>>evidencijski_broj;
            try {
                Knjiga k=b.NadjiKnjigu(evidencijski_broj);
                std::cout<<"Naslov knjige je "<<k.DajNaslov()<<std::endl;
            }
            catch(std::logic_error izuzetak) {
                std::cout<<izuzetak.what()<<std::endl;
            }
            break;
        }
        case 5: {
            try {
            b.IzlistajStudente();
            std::cout<<std::endl;
            }
            catch(std::logic_error izuzetak) {
                std::cout<<izuzetak.what()<<std::endl;
            }
            break;
        }
        case 6: {
            try {
            b.IzlistajKnjige();
            std::cout<<std::endl;
            }
            catch(std::domain_error izuzetak) {
                std::cout<<izuzetak.what()<<std::endl;
            }
            break;
        }
        case 7: {
            int evidencijski_broj, broj_indeksa;
            std::cout<<"Unesite evidencijski broj knjige i broj indeksa studenta kod kojeg zelite zaduziti knjigu: ";
            std::cin>>evidencijski_broj>>broj_indeksa;
            try {
            b.ZaduziKnjigu(evidencijski_broj, broj_indeksa);
            }
            catch(std::logic_error izuzetak) {
                std::cout<<izuzetak.what()<<std::endl;
            }
            break;
        }
        case 8: {
            int evidencijski_broj;
            std::cout<<"Unesite evidencijski broj knjige koju zelite razduziti: ";
            std::cin>>evidencijski_broj;
            try {
                b.RazduziKnjigu(evidencijski_broj);
            }
            catch(std::logic_error izuzetak) {
                std::cout<<izuzetak.what()<<std::endl;
            }
            break;
        }
        case 9: {
            int broj_indeksa;
            std::cout<<"Unesite broj indeksa studenta za kog zelite prikazati zaduzenja: ";
            std::cin>>broj_indeksa;
            try {
                b.PrikaziZaduzenja(broj_indeksa);
            }
            catch(std::domain_error izuetak) {
                std::cout<<izuetak.what()<<std::endl;
            }
            catch(std::logic_error izuzetak) {
                std::cout<<izuzetak.what()<<std::endl;
            }
            break;
        }
        case 10:
        std::cout<<"Dovidjenja!";
        break;
    }
    if(opcija==10) break;
    }
	return 0;
}
