//TP 2021/2022: LV 4, Zadatak 4
#include <iostream>
#include <cmath>

template <typename NekiTip>
void UnosBroja (const std::string &obavijest, const std::string &upozorenje, NekiTip &x) {
    std::cout<<obavijest<<std::endl;
    while(!(std::cin>>x) || std::cin.peek()!='\n') {
        std::cout<<upozorenje<<std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout<<obavijest<<std::endl;
    }
}
double RacunanjeStepena (double baza, int eksponent) {
    if(eksponent==0) return 1;
    int negativan_eksponent=0;
    if(eksponent<0) {
        eksponent=-eksponent;
        negativan_eksponent=1;
    }
    int iteracija=1;
    double stepen=baza;
    while(iteracija!=eksponent) {
        stepen*=baza;
        iteracija++;
    }
    if(negativan_eksponent) stepen=1./stepen;
    return stepen;
}
int main ()
{
    std::string obavijest="Unesite bazu: ";
    std::string upozorenje="Neispravan unos, pokusajte ponovo...";
    double baza;
    UnosBroja(obavijest, upozorenje, baza);
    obavijest="Unesite cjelobrojni eksponent: ";
    int eksponent;
    UnosBroja(obavijest, upozorenje, eksponent);
    double stepen=RacunanjeStepena(baza, eksponent);
    std::cout<<baza<<" na "<<eksponent<<" iznosi "<<stepen;
	return 0;
}
