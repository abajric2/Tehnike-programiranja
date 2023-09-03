/* 
    TP 16/17 (LV 11, Zadatak 3)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iomanip>

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
int main ()
{
    Tim t("NekiTim");
    t.ObradiUtakmicu(3, 2);
    std::cout<<"Ime tima: "<<t.DajImeTima()<<std::endl<<"Broj poena: "<<t.DajBrojPoena()<<std::endl<<
    "Gol razlika: "<<t.DajGolRazliku()<<std::endl;
    t.IspisiPodatke();
	return 0;
}