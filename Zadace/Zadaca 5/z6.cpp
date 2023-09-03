//TP 2021/2022: Zadaća 5, Zadatak 6
#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>
#include <stdexcept>

template <typename TipElemenata>
void SortirajBinarnuDatoteku(const char ime_datoteke[], std::function<bool(TipElemenata, TipElemenata)>kriterij=std::less<TipElemenata>()) {
    std::fstream dat(ime_datoteke, std::ios::out | std::ios::in | std::ios::binary);
    if(!dat) throw std::logic_error("Datoteka ne postoji");
    dat.seekg(0, std::ios::end);
    int duzina_datoteke=dat.tellg();
    int br_elemenata=duzina_datoteke/sizeof(TipElemenata);
    for(int i=0; i<br_elemenata-1; i++) {
        for(int j=0; j<br_elemenata-1-i; j++) {
            TipElemenata el1;
            dat.seekg(j*sizeof(TipElemenata), std::ios::beg);
            dat.read(reinterpret_cast<char *>(&el1), sizeof el1);
            TipElemenata el2;
            dat.seekg((j+1)*sizeof(TipElemenata), std::ios::beg);
            dat.read(reinterpret_cast<char *>(&el2), sizeof el2);
            if(!kriterij(el1, el2)) {
                TipElemenata temp=el1;
                dat.seekp(j*sizeof(TipElemenata), std::ios::beg);
                dat.write(reinterpret_cast<char *>(&el2), sizeof el2);
                dat.seekp((j+1)*sizeof(TipElemenata), std::ios::beg);
                dat.write(reinterpret_cast<char *>(&temp), sizeof temp);
            }
            if(!dat) throw std::logic_error("Problemi u pristupu datoteci");
        }
    }
}
int main ()
{
    std::ofstream izlazni_tok("SORTIRAJ.DAT", std::ios::binary);
    double niz[]{-856,0.35,265.282,-656,101,368352,0.0001,-0.0001,35,126};
    izlazni_tok.write(reinterpret_cast<char *>(niz), sizeof niz);
    izlazni_tok.close();
    SortirajBinarnuDatoteku<double>("SORTIRAJ.DAT");
    try {
        std::ifstream ulazni_tok("SORTIRAJ.DAT", std::ios::binary);
        ulazni_tok.read(reinterpret_cast<char *>(niz), sizeof niz);
        for(auto el : niz) std::cout<<el<<" ";
    }
    catch(std::logic_error izuzetak) {
        std::cout<<izuzetak.what();
    }
	return 0;
}
