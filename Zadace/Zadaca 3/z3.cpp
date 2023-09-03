//TP 2021/2022: Zadaća 3, Zadatak 3
#include <iostream>
#include <cmath>
#include <iomanip>
#include <iterator>
#include <stdexcept>
#include <new>
#include <vector>

template <typename TipElemenata>
struct Matrica {
    char ime_matrice;
    int br_redova, br_kolona;
    TipElemenata **elementi=nullptr;
};

template <typename TipElemenata>
void UnistiMatricu (Matrica<TipElemenata> &mat) {
    if(!mat.elementi) return;
    for(int i=0; i<mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi=nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu (int br_redova, int br_kolona, char ime=0) {
    Matrica<TipElemenata> mat;
    mat.br_redova=br_redova; mat.br_kolona=br_kolona; mat.ime_matrice=ime;
    mat.elementi=new TipElemenata*[br_redova]{};
    try {
        for(int i=0; i<br_redova; i++) mat.elementi[i]=new TipElemenata[br_kolona];
    }
    catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}

template <typename TipElemenata>
void UnesiMatricu (char ime, Matrica<TipElemenata> &mat) {
    for(int i=0; i<mat.br_redova; i++) 
        for(int j=0; j<mat.br_kolona; j++) {
            std::cout<<ime<<"("<<i+1<<","<<j+1<<") = ";
            std::cin>>mat.elementi[i][j];
        }
}

template <typename TipElemenata>
void IspisiMatricu (Matrica<TipElemenata> mat, int sirina_ispisa, int preciznost=6, bool treba_brisati=false) {
    for(int i=0; i<mat.br_redova; i++) {
        for(int j=0; j<mat.br_kolona; j++) std::cout<<std::setprecision(preciznost)<<std::setw(sirina_ispisa)<<mat.elementi[i][j];
        std::cout<<std::endl;
    }
    if(treba_brisati) UnistiMatricu(mat);
}

template <typename TipElemenata> 
Matrica<TipElemenata> ZbirMatrica (const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
    if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3=StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for(int i=0; i<m1.br_redova; i++)
        for(int j=0; j<m1.br_kolona; j++) m3.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
    return m3;
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica (const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
    if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    auto m3=StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona);
    for(int i=0; i<m1.br_redova; i++) {
        for(int j=0; j<m2.br_kolona; j++) {
            TipElemenata suma=TipElemenata();
            for(int k=0; k<m2.br_redova; k++) suma+=m1.elementi[i][k]*m2.elementi[k][j];
            m3.elementi[i][j]=suma;
        }
    }
    return m3;
}
template <typename TipElemenata>
Matrica<TipElemenata> JedinicnaMatrica (int br_redova, int br_kolona) {
    Matrica<TipElemenata> mat=StvoriMatricu<TipElemenata>(br_redova, br_kolona);
    for(int i=0; i<br_redova; i++) 
        for(int j=0; j<br_kolona; j++) {
            if(i==j) mat.elementi[i][j]=1;
            else mat.elementi[i][j]=0;
       }
    return mat;
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktSaKoeficijentom (const Matrica<TipElemenata> &mat, double koeficijent) {
    Matrica<TipElemenata> produkt=StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
    for(int i=0; i<mat.br_redova; i++)
        for(int j=0; j<mat.br_kolona; j++) produkt.elementi[i][j]=mat.elementi[i][j]*koeficijent;
    return produkt;
}

template <typename TipElemenata>
void PopuniNulama (Matrica<TipElemenata> &mat) {
    for(int i=0; i<mat.br_redova; i++)
        for(int j=0; j<mat.br_kolona; j++) mat.elementi[i][j]=0;
}

template <typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom (const Matrica<TipElemenata> &matA, const std::vector<double> &p) {
    if(matA.br_redova!=matA.br_kolona) throw std::domain_error("Matrica mora biti kvadratna");
    Matrica<TipElemenata> stepen_matrice;
    Matrica<TipElemenata> rezultat=StvoriMatricu<TipElemenata>(matA.br_redova, matA.br_kolona);
    PopuniNulama(rezultat);
    for(int i=0; i<p.size(); i++) {
        if(i==0) stepen_matrice=JedinicnaMatrica<TipElemenata>(matA.br_redova, matA.br_kolona);
        else {
            Matrica<TipElemenata> obrisi_stepen=stepen_matrice;
            stepen_matrice=ProduktMatrica<TipElemenata>(stepen_matrice, matA);
            UnistiMatricu(obrisi_stepen);
        }
        Matrica<TipElemenata> produkt, za_brisati=rezultat;
        rezultat=ZbirMatrica(produkt=ProduktSaKoeficijentom(stepen_matrice, p.at(i)), rezultat);
        UnistiMatricu(za_brisati); UnistiMatricu(produkt);
    }
    if(p.size()) UnistiMatricu(stepen_matrice);
    return rezultat;
}

int main ()
{
    int dimenzija;
    std::cout<<"Unesite dimenziju kvadratne matrice: "<<std::endl;
    std::cin>>dimenzija;
    std::cout<<"Unesite elemente matrice A: "<<std::endl;
    auto mat=StvoriMatricu<double>(dimenzija, dimenzija, 'A');
    UnesiMatricu('A', mat);
    int n;
    std::cout<<"Unesite red polinoma: "<<std::endl;
    std::cin>>n;
    std::vector<double> p(n+1);
    std::cout<<"Unesite koeficijente polinoma: "<<std::endl;
    for(int i=0; i<=n; i++) std::cin>>p.at(i);
    IspisiMatricu(MatricniPolinom(mat, p), 10, 6, true);
    UnistiMatricu(mat); 
	return 0;
}
