/* 
    TP 16/17 (LV 11, Zadatak 1)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

class NeobicnaKlasa {
    public:
    explicit NeobicnaKlasa (int) {std::cout<<"Direktna inicijalizacija"<<std::endl;}
    NeobicnaKlasa (long long int) {std::cout<<"Kopirajuca inicijalizacija"<<std::endl;}
};
int main ()
{
	return 0;
}