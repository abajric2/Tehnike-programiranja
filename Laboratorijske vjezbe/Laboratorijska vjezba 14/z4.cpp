//TP 2021/2022: LV 14, Zadatak 4
#include <iostream>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <string>

void IzvrniDatoteku(std::string ime_datoteke) {
    std::fstream dat(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
    if(!dat) throw std::logic_error("Datoteka ne postoji");
    dat.seekg(0, std::ios::end);
    int duzina_datoteke=dat.tellg();
    int br_elemenata=duzina_datoteke/sizeof(double);
    for(int i=0; i<br_elemenata/2; i++) {
        dat.seekg(i*sizeof(double), std::ios::beg);
        double temp;
        dat.read(reinterpret_cast<char *>(&temp), sizeof temp);
        double element;
        dat.seekg(-(i+1)*int(sizeof(double)), std::ios::end);
        dat.read(reinterpret_cast<char *>(&element), sizeof element);
        dat.seekp(i*sizeof(double), std::ios::beg);
        dat.write(reinterpret_cast<char *>(&element), sizeof element);
        dat.seekp(-(i+1)*int(sizeof(double)), std::ios::end);
        dat.write(reinterpret_cast<char *>(&temp), sizeof temp);
        if(!dat) throw std::logic_error("Problemi pri citanju datoteke");
    }
}
int main ()
{
    double niz[7]{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    std::ofstream izlazni_tok("NIZ.DAT", std::ios::binary);
    izlazni_tok.write(reinterpret_cast<char *>(niz), sizeof niz);
    izlazni_tok.close();
    try {
    IzvrniDatoteku("NIZ.DAT");
    std::ifstream ulazni_tok("NIZ.DAT", std::ios::binary);
    ulazni_tok.read(reinterpret_cast<char *>(niz), sizeof niz);
    for(int i=0; i<7; i++) std::cout<<niz[i]<<" ";
    }
    catch(std::logic_error izuzetak) {
        std::cout<<izuzetak.what();
    }
	return 0;
}
