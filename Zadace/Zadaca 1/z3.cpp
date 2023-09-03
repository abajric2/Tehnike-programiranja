//TP 2021/2022: Zadaća 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>

typedef std::vector<std::vector<bool>> Matrica;

Matrica UnosOpisaSahovskePloce () {
    std::cout<<"Unesite opis sahovske ploce:\n(Q za kraljicu, bilo sta drugo za prazno polje, ENTER naprazno za kraj unosa): "<<std::endl;
    char znak, temp;
    Matrica m;
    for(int i=0; ; i++) {
        for(int j=0; ; j++) {
            znak=std::cin.get();
            if(i==0 && j==0 && znak=='\n') return m;
            if(!(i==0 && j==0) && znak=='\n' && temp=='\n') return m;
            temp=znak;
            if(znak=='\n') break;
            if(j==0) m.resize(i+1);
            if(znak=='Q') m.at(i).push_back(true);
            else m.at(i).push_back(false);
        }
    }
    return m;
}
bool DaLiJeDama (int red, int kolona, Matrica m) {
    return m.at(red).at(kolona);
}
bool ProvjeraRedaIKolone (int i, int j, Matrica M) {
    for(int k=i; k<M.size(); k++) {
        for(int l=0; l<M.at(k).size(); l++) {
            if(DaLiJeDama(k, l, M) && !(k==i && l==j) && (k==i || l==j)) return true;
        }
    }
    return false;
}
bool ProvjeraDijagonale (int i, int j, Matrica M) {
    for(int m=i+1, n=j+1, p=j-1; m<M.size(); m++, n++, p--) {
        if(p>=0 && p<M.at(m).size() && DaLiJeDama(m, p, M)) return true;
        if(n<M.at(m).size() && DaLiJeDama(m, n, M)) return true;
    }
    return false;
}
bool DaLiSeDameNapadaju (Matrica M) {
    for(int i=0; i<M.size(); i++) {
        for(int j=0; j<M.at(i).size(); j++) {
            if(DaLiJeDama(i, j, M)) {
                if(ProvjeraRedaIKolone(i, j, M)) return true;
                if(ProvjeraDijagonale(i, j, M)) return true;
            }
        }
    }
    return false;
}
int main ()
{
	Matrica m=UnosOpisaSahovskePloce();
    if(DaLiSeDameNapadaju(m)) std::cout<<"Dame se medjusobno napadaju."<<std::endl;
    else std::cout<<"Dame se medjusobno ne napadaju."<<std::endl;
    return 0;
}
