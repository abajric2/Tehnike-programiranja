/* 
    TP 16/17 (LV 12, Zadatak 3)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};

Dani &operator ++(Dani &d) {
    return d = Dani((int(d) + 1) % 7);
}

Dani operator ++(Dani &d, int) {
    Dani pomocni = d; ++d; return pomocni;
}

std::ostream &operator <<(std::ostream &tok, Dani &d) {
    switch(int(d)) {
        case 0: tok<<"Ponedjeljak"; break;
        case 1: tok<<"Utorak"; break;
        case 2: tok<<"Srijeda"; break;
        case 3: tok<<"Cetvrtak"; break;
        case 4: tok<<"Petak"; break;
        case 5: tok<<"Subota"; break;
        case 6: tok<<"Nedjelja"; break;
    }
    return tok;
}
int main ()
{
    for(Dani d=Ponedjeljak; d<=Nedjelja; d++) {
        std::cout<<d<<std::endl;
        if(d==Nedjelja) break;
    }
	return 0;
}