/* 
    TP 16/17 (LV 11, Zadatak 4)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iomanip>
#include <initializer_list>
#include <algorithm>

class Tim {
    char ime_tima[20];
    int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza, broj_datih, broj_primljenih, broj_poena;
    public:
    Tim (const char ime[]);
    void ObradiUtakmicu (int broj_datih, int broj_primljenih);
    const char *DajImeTima() const {return ime_tima;}
    int DajBrojPoena() const {return broj_poena;}
    int DajGolRazliku() const {return broj_datih-broj_primljenih;}
    void IspisiPodatke() const;
};
Tim::Tim (const char ime[]) {
    if(std::strlen(ime)>20) throw std::range_error("Predugacko ime tima");
    std::strcpy(ime_tima, ime);
    broj_odigranih=broj_pobjeda=broj_nerijesenih=broj_poraza=broj_datih=broj_primljenih=broj_poena=0;
}
void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih) {
    if(broj_datih<0 || broj_primljenih<0) throw std::range_error("Neispravan broj golova");
    broj_odigranih++; 
    if(broj_datih>broj_primljenih) {
        broj_pobjeda++;
        broj_poena+=3;
    }
    else if(broj_datih<broj_primljenih) broj_poraza++;
    else {
        broj_nerijesenih++;
        broj_poena++;
    }
    Tim::broj_datih+=broj_datih; Tim::broj_primljenih+=broj_primljenih;
}
void Tim::IspisiPodatke() const {
    std::cout<<std::setw(20)<<std::left<<ime_tima<<std::right<<std::setw(4)<<broj_odigranih<<
    std::setw(4)<<broj_pobjeda<<std::setw(4)<<broj_nerijesenih<<std::setw(4)<<broj_poraza<<
    std::setw(4)<<broj_datih<<std::setw(4)<<broj_primljenih<<std::setw(4)<<broj_poena<<std::endl;
}
class Liga {
    int broj_timova;
    const int max_broj_timova;
    Tim** timovi;
    public:
    explicit Liga (int velicina_lige);
    explicit Liga (std::initializer_list<Tim> lista_timova);
    ~Liga ();
    Liga (const Liga &l);
    Liga (Liga &&l);
    Liga &operator =(const Liga &l);
    Liga &operator =(Liga &&l);
    void DodajNoviTim (const char ime_tima[]);
    void RegistrirajUtakmicu (const char tim1[], const char tim2[], int rezultat_1, int rezultat_2);
    void IspisiTabelu();
};
Liga::Liga (int velicina_lige) : max_broj_timova(velicina_lige), broj_timova(0), timovi(new Tim *[velicina_lige]{}) {}

void Liga::DodajNoviTim(const char *ime_tima) {
    if(broj_timova>=max_broj_timova) throw std::range_error("Liga popunjena");
    for(int i=0; i<broj_timova; i++) 
        if(!std::strcmp(timovi[i]->DajImeTima(), ime_tima)) throw std::logic_error("Tim vec postoji");
    timovi[broj_timova++]=new Tim(ime_tima);
}

Liga::Liga (std::initializer_list<Tim> lista_timova) : max_broj_timova(lista_timova.size()) , broj_timova(0), timovi(new Tim *[lista_timova.size()]{}) {
    for(auto it=lista_timova.begin(); it!=lista_timova.end(); it++) DodajNoviTim(it->DajImeTima());
}

Liga::~Liga() {
    for(int i=0; i<broj_timova; i++) delete timovi[i];
    delete[] timovi;
}

Liga::Liga (const Liga &l) : timovi(new Tim *[l.max_broj_timova]{}), max_broj_timova(l.max_broj_timova), broj_timova(l.broj_timova) {
    try {
        for(int i=0; i<l.broj_timova; i++) timovi[i]=new Tim(l.timovi[i]->DajImeTima());
        for(int i=0; i<l.broj_timova; i++) *timovi[i]=*l.timovi[i];
    }
    catch(...) {
        for(int i=0; i<l.broj_timova; i++) delete timovi[i];
        delete[] timovi;
        throw;
    }
}

Liga &Liga::operator =(const Liga &l) {
    if(l.max_broj_timova!=max_broj_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
    if(l.broj_timova>broj_timova) {
        try {
            for(int i=broj_timova; i<l.broj_timova; i++) timovi[i]=new Tim(l.timovi[i]->DajImeTima());
        }
        catch(...) {
            for(int i=broj_timova; i<l.broj_timova; i++) {
                delete timovi[i]; timovi[i]=nullptr;
            }
            throw;
        }
    }
    else {
        for(int i=l.broj_timova; i<broj_timova; i++) {
            delete timovi[i]; timovi[i]=nullptr;
        }
    }
    broj_timova=l.broj_timova;
    for(int i=0; i<broj_timova; i++) *timovi[i]=*l.timovi[i];
    return *this;
}

Liga::Liga (Liga &&l) : timovi(l.timovi), max_broj_timova(l.max_broj_timova), broj_timova(l.broj_timova) {
    l.timovi=nullptr; l.broj_timova=0;
}

Liga &Liga::operator =(Liga &&l) {
    if(max_broj_timova!=l.max_broj_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
    std::swap(broj_timova, l.broj_timova);
    std::swap(timovi, l.timovi);
    return *this;
}

void Liga::RegistrirajUtakmicu(const char *tim1, const char *tim2, int rezultat_1, int rezultat_2) {
    bool prvi_nadjen=false, drugi_nadjen=false;
    for(int i=0; i<broj_timova; i++) {
        if(!std::strcmp(timovi[i]->DajImeTima(), tim1)) prvi_nadjen=true;
        if(!std::strcmp(timovi[i]->DajImeTima(), tim2)) drugi_nadjen=true;
    }
    if(!prvi_nadjen || !drugi_nadjen) throw std::logic_error("Tim nije nadjen");
    if(rezultat_1<0 || rezultat_2<0) throw std::range_error("Neispravan broj golova");
    for(int i=0; i<broj_timova; i++) {
        if(!std::strcmp(timovi[i]->DajImeTima(), tim1)) timovi[i]->ObradiUtakmicu(rezultat_1, rezultat_2);
        if(!std::strcmp(timovi[i]->DajImeTima(), tim2)) timovi[i]->ObradiUtakmicu(rezultat_2, rezultat_1);   
    }
}

void Liga::IspisiTabelu() {
    std::sort(timovi, timovi+broj_timova, [](const Tim *t1, const Tim *t2) {
        if(t1->DajBrojPoena()>t2->DajBrojPoena()) return true;
        else if(t1->DajBrojPoena()<t2->DajBrojPoena()) return false;
        if(t1->DajGolRazliku()>t2->DajGolRazliku()) return true;
        else if(t1->DajGolRazliku()<t2->DajGolRazliku()) return false;
        else if(std::strcmp(t1->DajImeTima(), t2->DajImeTima())<0) return true;
        else return false;
    });
    for(int i=0; i<broj_timova; i++) timovi[i]->IspisiPodatke();
}
int main ()
{
    Liga l1(3); 
    Liga l2{"PrviKlub", "DrugiKlub", "TreciKlub"};
    Liga l3(l1);
    l1=l2;
    l3.DodajNoviTim("NekiKlub");
    l2.RegistrirajUtakmicu("PrviKlub", "DrugiKlub", 1, 1);
    l1.IspisiTabelu(); std::cout<<std::endl;
    l2.IspisiTabelu(); std::cout<<std::endl;
    l3.IspisiTabelu(); std::cout<<std::endl;
    Liga l4(std::move(l1));
    l4.IspisiTabelu(); std::cout<<std::endl;
    l4=std::move(l2);
    l4.IspisiTabelu(); std::cout<<std::endl;
    Liga l{"Borac", "Celik", "Jedinstvo", "Sarajevo", "Zeljeznicar", "Zrinjski"};
    for(;;) {
        l.IspisiTabelu();
        char ime[20];
        std::cout<<"Unesite ime prvog tima (ENTER za kraj): ";
        std::cin.getline(ime, sizeof ime);
        if(!std::strlen(ime)) break;
        char ime2[20];
        std::cout<<"Unesite ime drugog tima: ";
        std::cin.getline(ime2, sizeof ime2);
        int golovi1, golovi2;
        std::cout<<"Unesite broj postignutih golova za oba tima: ";
        std::cin>>golovi1>>golovi2;
        std::cin.ignore(10000, '\n');
        try {
            l.RegistrirajUtakmicu(ime, ime2, golovi1, golovi2);
        }
        catch(std::logic_error izuzetak) {
            std::cout<<izuzetak.what()<<std::endl;
        }
        catch(std::range_error izuzetak) {
            std::cout<<izuzetak.what()<<std::endl;
        }
    }
	return 0;
}