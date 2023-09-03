//TP 2021/2022: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <stdexcept>

typedef std::vector<std::vector<double>> Matrica;
typedef std::array<Matrica, 2> Matrica3D;

const double EPSILON=pow(10,-10);

Matrica KreirajMatricu (int broj_redova, int broj_kolona) {
    return Matrica(broj_redova, std::vector<double>(broj_kolona));
}
Matrica UnesiMatricu (int broj_redova, int broj_kolona) {
    Matrica m=KreirajMatricu(broj_redova, broj_kolona);
    for(int i=0; i<broj_redova; i++) {
        for(int j=0; j<broj_kolona; j++) {
            std::cin>>m.at(i).at(j);
        }
    }
    return m;
}
bool IspravnaStrukturaMatrice (Matrica m) {
    for(int i=0; i<int(m.size())-1; i++) if(m.at(i).size()!=m.at(i+1).size()) return false;
    return true;
}
int BrojRedova (Matrica m) {
    return m.size();
}
int BrojKolona (Matrica m) {
    if(m.size()==0) return 0;
    return m.at(0).size();
}
bool SaglasneZaMnozenje (Matrica m1, Matrica m2) {
    if(!IspravnaStrukturaMatrice(m1) || !IspravnaStrukturaMatrice(m2)) return false;
    return BrojKolona(m1)==BrojRedova(m2);
}
Matrica MnozenjeMatrica (Matrica m1, Matrica m2) {
    if(!IspravnaStrukturaMatrice(m1) || !IspravnaStrukturaMatrice(m2)) throw std::domain_error("Neispravna matrica!");
    if(!SaglasneZaMnozenje(m1, m2)) throw std::domain_error("Matrice nisu saglasne za mnozenje!");
    Matrica P=KreirajMatricu(BrojRedova(m1), BrojKolona(m2));
    if(m1.size()==0 && m2.size()==0) return P;
    for(int i=0; i<BrojRedova(m1); i++) {
        for(int j=0; j<BrojKolona(m2); j++) {
            double suma=0;
            for(int k=0; k<BrojRedova(m2); k++) suma+=m1.at(i).at(k)*m2.at(k).at(j);
            P.at(i).at(j)=suma;
        }
    }
    return P;
}
bool KvadratnaMatrica (Matrica m) {
    return BrojRedova(m)==BrojKolona(m);
}
Matrica3D DoolittleLU (Matrica H) {
    if(!IspravnaStrukturaMatrice(H)) throw std::domain_error("Neispravna matrica!");
    if(!KvadratnaMatrica(H)) throw std::domain_error("Matrica mora biti kvadratna!");
    Matrica L=KreirajMatricu(BrojRedova(H), BrojKolona(H));
    Matrica U=KreirajMatricu(BrojRedova(H), BrojKolona(H));
    for(int i=0; i<BrojRedova(H); i++) {
        for(int j=0; j<BrojKolona(H); j++) {
            if(j>=i) {
                double suma=0;
                for(int m=0; m<=i-1; m++) suma+=L.at(i).at(m)*U.at(m).at(j);
                U.at(i).at(j)=H.at(i).at(j)-suma;
            }
            if(j<=i) {
                if(fabs(U.at(j).at(j))<EPSILON) throw std::domain_error("Matrica je singularna!");
                double suma=0;
                for(int k=0; k<=j-1; k++) suma+=L.at(i).at(k)*U.at(k).at(j);
                L.at(i).at(j)=(1./U.at(j).at(j))*(H.at(i).at(j)-suma);
            }
        }
    }
    Matrica3D rezultat;
    rezultat.at(0)=L; 
    rezultat.at(1)=U;
    return rezultat;
}
bool ProvjeriFaktorizaciju (Matrica H, Matrica3D LU) {
    if(!IspravnaStrukturaMatrice(H) || !IspravnaStrukturaMatrice(LU.at(0)) || !IspravnaStrukturaMatrice(LU.at(1))) return false;
    if(!KvadratnaMatrica(H) || !KvadratnaMatrica(LU.at(0)) || !KvadratnaMatrica(LU.at(1))) return false;
    Matrica P;
    try{
        P=MnozenjeMatrica(LU.at(0), LU.at(1));
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
        return false;
    }
    if(BrojRedova(H)!=BrojRedova(P) || BrojKolona(H)!=BrojKolona(P)) return false;
    for(int i=0; i<BrojRedova(H); i++) {
        for(int j=0; j<BrojKolona(H); j++) {
            if(!(fabs(H.at(i).at(j)-P.at(i).at(j))<EPSILON)) return false;
        }
    }
    return true;
}
void IspisiMatricu (Matrica m) {
    for(int i=0; i<BrojRedova(m); i++) {
        for(int j=0; j<BrojKolona(m); j++) {
            std::cout<<m.at(i).at(j)<<" ";
        }
        std::cout<<std::endl;
    }
}
int main ()
{
    int n=0;
    std::cout<<"Broj redova/kolona matrice: "<<std::endl;
    std::cin>>n;
    std::cout<<"Elementi matrice: "<<std::endl;
    Matrica m=UnesiMatricu(n, n);
    Matrica3D M;
    try {
        M=DoolittleLU(m);
    }
    catch(std::domain_error izuzetak) {
        std::string s=izuzetak.what();
        if(s=="Matrica je singularna!") {
            std::cout<<"LU faktorizacija ne postoji, jer je matrica singularna!";
            return 1;
        }
        std::cout<<izuzetak.what()<<std::endl;
        return 1;
    }
    std::cout<<"Matrica L: "<<std::endl;
    IspisiMatricu(M.at(0));
    std::cout<<"Matrica U: "<<std::endl;
    IspisiMatricu(M.at(1));
	return 0;
}
