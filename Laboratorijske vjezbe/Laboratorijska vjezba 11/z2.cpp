/* 
    TP 16/17 (LV 11, Zadatak 2)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>

class StedniRacun {
    double stanje_racuna;
    static int broj_kreiranih, broj_aktivnih;
    public:
    StedniRacun (double pocetna_vrijednost=0) {
        if(pocetna_vrijednost<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        stanje_racuna=pocetna_vrijednost; broj_kreiranih++; broj_aktivnih++;
    }
    StedniRacun (const StedniRacun &r) {broj_aktivnih++; broj_kreiranih++;}
    ~StedniRacun () {broj_aktivnih--;}
    static int DajBrojKreiranih() {return broj_kreiranih;}
    static int DajBrojAktivnih() {return broj_aktivnih;}
    StedniRacun &Ulozi (double iznos) {
        if(stanje_racuna+iznos<0) throw std::logic_error("Transakcija odbijena");
        stanje_racuna+=iznos;
        return *this;
    }
    StedniRacun &Podigni (double iznos) {
        if(iznos>stanje_racuna) throw std::logic_error("Transakcija odbijena");
        stanje_racuna-=iznos;
        return *this;
    }
    double DajStanje() const {return stanje_racuna;}
    StedniRacun &ObracunajKamatu (double kamatna_stopa) {
        if(kamatna_stopa<0) throw std::logic_error("Nedozvoljena kamatna stopa");
        stanje_racuna+=(kamatna_stopa/100)*stanje_racuna;
        return *this;
    }
};
int StedniRacun::broj_aktivnih=0, StedniRacun::broj_kreiranih=0;
int main ()
{
    StedniRacun racun;
    try {
        double iznos;
        std::cout<<"Koliki iznos zelite uplatiti na svoj racun: ";
        std::cin>>iznos;
        racun.Ulozi(iznos);
    }
    catch(std::logic_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
    }
    const StedniRacun &racun2(racun);
    std::cout<<"Vase trenutno stanje na racunu iznosi: "<<racun2.DajStanje()<<std::endl;
    try {
        double za_podici;
        std::cout<<"Unesite iznos koji zelite podici sa racuna: ";
        std::cin>>za_podici;
        racun.Podigni(za_podici);
    }
    catch(std::logic_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try {
        double kamatna_stopa;
        std::cout<<"Unesite kamatnu stopu (u postotcima): ";
        std::cin>>kamatna_stopa;
        racun.ObracunajKamatu(kamatna_stopa);
        std::cout<<"Stanje racuna nakon obracuna kamatne stope je: "<<racun2.DajStanje()<<std::endl;
    }
    catch(std::logic_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}