//TP 2021/2022: Zadaća 2, Zadatak 1
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <limits>

enum class Pravci {Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad, Sjeverozapad};
enum class Smjer {Nalijevo, Nadesno};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
enum class Komande{Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};

bool robot_aktivan=true;

void AktivirajRobota() {
    robot_aktivan=true;
}
void DeaktivirajRobota() {
    robot_aktivan=false;
}
void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu) {
    if(!robot_aktivan) return;
    std::vector<Pravci> pravci{Pravci::Sjever, Pravci::Sjeveroistok, Pravci::Istok, Pravci::Jugoistok, Pravci::Jug, Pravci::Jugozapad,
    Pravci::Zapad, Pravci::Sjeverozapad};
    for(int i=0; i<pravci.size(); i++) {
        if(orijentacija==pravci.at(i)) {
            if(na_koju_stranu==Smjer::Nalijevo) {
                if(i>0) orijentacija=pravci.at(i-1);
                else orijentacija=pravci.at(pravci.size()-1);
            }
            else {
                if(i<pravci.size()-1) orijentacija=pravci.at(i+1);
                else orijentacija=pravci.at(0);
            }
            return;
        }
    }
}
bool IzlaziIzOpsega(int &a, int korak, int znak_a) {
    if(static_cast<long long int>(a)+korak*znak_a>std::numeric_limits<int>::max()) {
        a=std::numeric_limits<int>::max();
        return true;
    }
    else if(static_cast<long long int>(a)+korak*znak_a<std::numeric_limits<int>::min()) {
        a=std::numeric_limits<int>::min();
        return true;
    }
    else return false;
}
void Idi(int &x, int &y, Pravci orijentacija, int korak) {
    if(!robot_aktivan) return;
    std::vector<Pravci> vertikala{Pravci::Sjever, Pravci::Jug};
    std::vector<Pravci> horizontala{Pravci::Istok, Pravci::Zapad};
    std::vector<Pravci> mjesoviti{Pravci::Sjeveroistok, Pravci::Jugoistok, Pravci::Jugozapad, Pravci::Sjeverozapad};
    std::vector<Pravci> poz_x{Pravci::Sjeveroistok, Pravci::Istok, Pravci::Jugoistok};
    std::vector<Pravci> poz_y{Pravci::Sjeveroistok, Pravci::Sjever, Pravci::Sjeverozapad};
    int znak_x=-1, znak_y=-1;
    for(int i=0; i<poz_x.size(); i++) if(orijentacija==poz_x.at(i)) znak_x=1;
    for(int i=0; i<poz_y.size(); i++) if(orijentacija==poz_y.at(i)) znak_y=1;
    for(int i=0; i<mjesoviti.size(); i++) {
        if(orijentacija==mjesoviti.at(i)) {
            if(!IzlaziIzOpsega(x, korak, znak_x)) x+=korak*znak_x;
            if(!IzlaziIzOpsega(y, korak, znak_y)) y+=korak*znak_y;
            return;
        }
        if(i>=2) continue;
        if(orijentacija==vertikala.at(i)) {
            if(!IzlaziIzOpsega(y, korak, znak_y)) y+=korak*znak_y; 
            return;
        }
        else if(orijentacija==horizontala.at(i)) {
            if(!IzlaziIzOpsega(x, korak, znak_x)) x+=korak*znak_x; 
            return;
        }
    }
}
void IspisiPoziciju(int x, int y, Pravci orijentacija) {
    std::string status;
    if(robot_aktivan) status="aktivan";
    else status="neaktivan";
    std::vector<Pravci> pravci{Pravci::Sjever, Pravci::Sjeveroistok, Pravci::Istok, Pravci::Jugoistok, Pravci::Jug, Pravci::Jugozapad, Pravci::Zapad, Pravci::Sjeverozapad};
    std::vector<std::string> s{"sjever", "sjeveroistok", "istok", "jugoistok", "jug", "jugozapad", "zapad", "sjeverozapad"};
    std::string pravac;
    for(int i=0; i<pravci.size(); i++) 
        if(orijentacija==pravci.at(i)) {
            pravac=s.at(i); break;
        }
    std::cout<<"Robot je "<<status<<", nalazi se na poziciji ("<<x<<","<<y<<") i gleda na "<<pravac<<"."<<std::endl;
}
void PrijaviGresku(KodoviGresaka kod_greske) {
    std::vector<KodoviGresaka> greske{KodoviGresaka::PogresnaKomanda, KodoviGresaka::NedostajeParametar, KodoviGresaka::SuvisanParametar, KodoviGresaka::NeispravanParametar};
    std::vector<std::string> poruke{"Nerazumljiva komanda!", "Komanda trazi parametar koji nije naveden!", "Zadan je suvisan parametar nakon komande!",
    "Parametar komande nije ispravan!"};
    for(int i=0; i<greske.size(); i++) 
        if(kod_greske==greske.at(i)) {
            std::cout<<poruke.at(i)<<std::endl; return;
        }
}
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija) {
    if(komanda==Komande::Aktiviraj) AktivirajRobota();
    else if(komanda==Komande::Deaktiviraj) DeaktivirajRobota();
    else if(komanda==Komande::Nalijevo) Rotiraj(orijentacija, Smjer::Nalijevo);
    else if(komanda==Komande::Nadesno) Rotiraj(orijentacija, Smjer::Nadesno);
    else if(komanda==Komande::Idi) Idi(x, y, orijentacija, parametar);
}
bool SuvisniParametri(char slovo, KodoviGresaka &kod_greske) {
    char provjera;
    while((provjera=std::cin.get())!='\n')
        if(provjera!=' ') {
            if(slovo=='I') kod_greske=KodoviGresaka::NeispravanParametar;
            else kod_greske=KodoviGresaka::SuvisanParametar;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return true;
        }
    return false;
}
bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
    char slovo;
    std::cin>>slovo;
    if(slovo=='L' || slovo=='D' || slovo=='K') {
        if(SuvisniParametri(slovo, kod_greske)) return false;
        if(slovo=='L') komanda=Komande::Nalijevo; 
        if(slovo=='D') komanda=Komande::Nadesno; 
        if(slovo=='K') komanda=Komande::Kraj;
        return true; 
    }
    if(slovo=='A') {
        char znak;
        do {
            znak=std::cin.get();
            if(znak!=' ') break;
        } while(znak!='\n');
        if(znak=='\n' || (znak!='+' && znak!='-')) {
            kod_greske=KodoviGresaka::PogresnaKomanda; 
            return false;
        }
        if(SuvisniParametri(slovo, kod_greske)) return false;
        if(znak=='+') {
            komanda=Komande::Aktiviraj; return true;
        }
        if(znak=='-') {
            komanda=Komande::Deaktiviraj; return true;
        }
    }
    if(slovo=='I') {
        char znak;
        while((znak=std::cin.peek())==' ') std::cin.get();
        /*do {
            znak=std::cin.peek();
            if(znak!=' ') break;
        } while(znak!='\n');*/
        if(znak=='\n') {
            kod_greske=KodoviGresaka::NedostajeParametar;
            return false;
        }
        int broj=0;
        if(!(std::cin>>broj)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            if(!(broj==std::numeric_limits<int>::max() || broj==std::numeric_limits<int>::min())) { 
                kod_greske=KodoviGresaka::NeispravanParametar;
                return false;
            }
        }
        if(SuvisniParametri(slovo, kod_greske)) return false;
        komanda=Komande::Idi;
        parametar=broj;
        return true;
    }
    kod_greske=KodoviGresaka::PogresnaKomanda;
    return false;
}
int main ()
{
    int x=0, y=0;
    Pravci orijentacija=Pravci::Sjever;
    IspisiPoziciju(x, y, orijentacija);
    Komande komanda;
    bool kraj=false;
    do {
        std::cout<<"Unesi komandu: "<<std::endl;
        int parametar;
        KodoviGresaka kod_greske;
        bool ispravna_komanda=UnosKomande(komanda, parametar, kod_greske);
        if(ispravna_komanda) {
            IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
            if(komanda!=Komande::Kraj) IspisiPoziciju(x, y, orijentacija);
            else kraj=true;
        }
        else PrijaviGresku(kod_greske);
    } while(!kraj);
    std::cout<<"Dovidjenja!";
	return 0;
}
