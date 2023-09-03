//TP 2021/2022: Zadaća 5, Zadatak 5
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <string>
#include <fstream>

template <typename TipEl>
 class Matrica {
 char ime_matrice;
 int br_redova, br_kolona;
 TipEl **elementi;
 static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
 static void DealocirajMemoriju(TipEl **elementi, int br_redova);
 void KopirajElemente(TipEl **elementi);
 static void AnalizirajTekstualnuDatoteku(std::string ime_datoteke, int &br_redova, int &br_kolona);
 void RegulisiMatricu(std::string ime_datoteke);
 public:
 Matrica(int br_redova, int br_kolona, char ime = 0);
 Matrica(const Matrica &m);
 Matrica(Matrica &&m);
 Matrica(std::string ime_datoteke, bool vrsta_datoteke);
 ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
 Matrica &operator =(const Matrica &m);
 Matrica &operator =(Matrica &&m);
 template <typename Tip3>
 friend std::istream &operator >>(std::istream &tok, Matrica<Tip3> &m);
 template <typename Tip4>
 friend std::ostream &operator <<(std::ostream &tok, const Matrica<Tip4> &m);
 template <typename Tip2>
 friend Matrica<Tip2> operator +(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2);
 template <typename Tip7>
 friend Matrica<Tip7> operator *(const Matrica<Tip7> &m1, const Matrica<Tip7> &m2);
 template <typename TipEl5, typename Tip5>
 friend auto operator *(const Matrica<TipEl5> &m, Tip5 n);
 template <typename Tip6, typename TipEl6>
 friend auto operator *(Tip6 n, const Matrica<TipEl6> &m);
 template <typename Tip8>
 friend Matrica<Tip8> &operator +=(Matrica<Tip8> &m1, const Matrica<Tip8> &m2);
 template <typename Tip9>
 friend Matrica<Tip9> &operator -=(Matrica<Tip9> &m1, const Matrica<Tip9> &m2);
 template <typename Tip10>
 friend Matrica<Tip10> operator -(const Matrica<Tip10> &m1, const Matrica<Tip10> &m2);
 template <typename Tip11>
 friend Matrica<Tip11> &operator *=(Matrica<Tip11> &m1, const Matrica<Tip11> &m2);
 template <typename TipEl12, typename Tip12>
 friend Matrica<TipEl12> &operator *=(Matrica<TipEl12> &m, Tip12 n);
 auto &operator [](int indeks) {
    return elementi[indeks];
 }
 auto operator [](int indeks) const {
     return elementi[indeks];
 }
 TipEl &operator() (int i, int j);
 TipEl operator() (int i, int j) const;
 operator std::string() const;
 void SacuvajUBinarnuDatoteku(std::string ime_datoteke) const;
 void ObnoviIzBinarneDatoteke(std::string ime_datoteke);
 void SacuvajUTekstualnuDatoteku(std::string ime_datoteke) const;
 void ObnoviIzTekstualneDatoteke(std::string ime_datoteke);
 };
template <typename TipEl>
 TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {
 TipEl **elementi = new TipEl*[br_redova]{};
 try {
 for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
 }
 catch(...) {
 DealocirajMemoriju(elementi, br_redova); throw;
 }
 return elementi;
 }
template <typename TipEl>
 void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {
 for(int i = 0; i < br_redova; i++) delete[] elementi[i];
 delete[] elementi;
 }
template <typename TipEl>
 Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :
 br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
 elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
template <typename TipEl>
 void Matrica<TipEl>::KopirajElemente(TipEl **elementi) {
 for(int i = 0; i < br_redova; i++)
 for(int j = 0; j < br_kolona; j++)
 Matrica::elementi[i][j] = elementi[i][j];
 }
template <typename TipEl>
 Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova),
 br_kolona(m.br_kolona), ime_matrice(m.ime_matrice),
 elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)) {
 KopirajElemente(m.elementi);
 }
template <typename TipEl>
 Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova),
 br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice) {
 m.br_redova = 0; m.elementi = nullptr;
 }
template <typename TipEl>
 Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m) {
 if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
 TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
 DealocirajMemoriju(elementi, br_redova);
 elementi = novi_prostor;
 }
 else if(br_redova > m.br_redova)
 for(int i = m.br_redova; i < br_redova; i++) delete[] elementi[i];
 br_redova = m.br_redova; br_kolona = m.br_kolona;
 ime_matrice = m.ime_matrice; KopirajElemente(m.elementi);
 return *this;
 }
template <typename TipEl>
 Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m) {
 std::swap(br_redova, m.br_redova); std::swap(br_kolona, m.br_kolona);
 std::swap(ime_matrice, m.ime_matrice); std::swap(elementi, m.elementi);
 return *this;
 }
 template <typename TipEl>
 std::istream &operator >>(std::istream &tok, Matrica<TipEl> &m) {
 for(int i = 0; i < m.br_redova; i++)
 for(int j = 0; j < m.br_kolona; j++) {
 std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
 std::cin >> m.elementi[i][j];
 }
 return tok;
 }
template <typename TipEl>
std::ostream &operator <<(std::ostream &tok, const Matrica<TipEl> &m) {
    int n=std::cout.width();
 for(int i = 0; i < m.br_redova; i++) {
 for(int j = 0; j < m.br_kolona; j++)
 std::cout << std::setw(n) << m.elementi[i][j];
 std::cout << std::endl;
 }
 return tok;
 }
template <typename TipEl>
 Matrica<TipEl> &operator +=(Matrica<TipEl> &m1,
 const Matrica<TipEl> &m2) {
 if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
 throw std::domain_error("Matrice nemaju jednake dimenzije!");
 for(int i = 0; i < m1.br_redova; i++)
 for(int j = 0; j < m1.br_kolona; j++)
 m1.elementi[i][j] += m2.elementi[i][j];
 return m1;
 }
 template <typename TipEl>
 Matrica<TipEl> operator +(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
     Matrica<TipEl> m3=m1; m3+=m2; return m3;
 }
 template <typename TipEl>
 Matrica<TipEl> &operator *=(Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
     if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
     Matrica<TipEl> m3(m1.br_redova, m2.br_kolona);
     for(int i=0; i<m1.br_redova; i++) 
       for(int j=0; j<m2.br_kolona; j++) {
           TipEl suma=TipEl();
           for(int k=0; k<m2.br_redova; k++) suma+=m1.elementi[i][k]*m2.elementi[k][j];
           m3.elementi[i][j]=suma;
       }
       m1=m3;
     return m1;
 }
 template <typename TipEl>
 Matrica<TipEl> operator *(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
     Matrica<TipEl> m3=m1; m3*=m2; return m3;
 }
 template <typename Tip1, typename Tip2>
 auto operator *(const Matrica<Tip1> &m, Tip2 n) {
     Matrica<decltype(m.elementi[0][0]*n)> p(m.br_redova, m.br_kolona);
     for(int i=0; i<m.br_redova; i++) 
       for(int j=0; j<m.br_kolona; j++) p.elementi[i][j]=m.elementi[i][j]*n;
    return p;
 }
 template <typename Tip1, typename Tip2>
 Matrica<Tip1> &operator *=(Matrica<Tip1> &m, Tip2 n) {
     for(int i=0; i<m.br_redova; i++)
       for(int j=0; j<m.br_kolona; j++) m.elementi[i][j]*=n;
    return m;
 }
 template <typename Tip1, typename Tip2>
 auto operator *(Tip1 n, const Matrica<Tip2> &m) {
     Matrica<decltype(m.elementi[0][0]*n)> p(m.br_redova, m.br_kolona);
     for(int i=0; i<m.br_redova; i++)
       for(int j=0; j<m.br_kolona; j++) p.elementi[i][j]=m.elementi[i][j]*n;
    return p;
 }
 template <typename TipEl>
 Matrica<TipEl> &operator -=(Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
     if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
     for(int i=0; i<m1.br_redova; i++)
       for(int j=0; j<m1.br_kolona; j++) m1.elementi[i][j]-=m2.elementi[i][j];
    return m1;
 }
 template <typename TipEl>
 Matrica<TipEl> operator -(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
     Matrica<TipEl> m3=m1; m3-=m2; return m3;
 }
 template <typename TipEl>
 TipEl &Matrica<TipEl>::operator ()(int i, int j) {
     if(i<1 || j<1 || i>br_redova || j>br_kolona) throw std::range_error("Neispravan indeks");
     return elementi[i-1][j-1];
 }
 template <typename TipEl>
 TipEl Matrica<TipEl>::operator ()(int i, int j) const {
     if(i<1 || j<1 || i>br_redova || j>br_kolona) throw std::range_error("Neispravan indeks");
     return elementi[i-1][j-1];
 }
 template<typename TipEl>
 Matrica<TipEl>::operator std::string() const {
     std::string s;
     s.push_back('{');
     for(int i=0; i<br_redova; i++) {
         s.push_back('{');
         for(int j=0; j<br_kolona; j++) {
             std::string pomocni;
             if(int(elementi[i][j])==elementi[i][j]) pomocni=std::to_string(int(elementi[i][j]));
             for(auto it=pomocni.begin(); it!=pomocni.end(); it++) s.push_back(*it);
             if(j<br_kolona-1) s.push_back(',');
         }
         s.push_back('}');
         if(i<br_redova-1) s.push_back(',');
     }
     s.push_back('}');
     return s;
 }
 template<typename TipEl>
 void Matrica<TipEl>::SacuvajUBinarnuDatoteku(std::string ime_datoteke) const {
     std::ofstream izlazni_tok(ime_datoteke, std::ios::binary);
     if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
     izlazni_tok.write(reinterpret_cast<const char *>(this), sizeof *this);
     for(int i=0; i<br_redova; i++) {
         izlazni_tok.write(reinterpret_cast<char *>(elementi[i]), br_kolona*(sizeof *elementi[i]));
     }
     if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
 }
 template<typename TipEl>
 void Matrica<TipEl>::ObnoviIzBinarneDatoteke(std::string ime_datoteke) {
     std::ifstream ulazni_tok(ime_datoteke, std::ios::binary);
     if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
     for(int i=0; i<br_redova; i++) delete[] elementi[i];
     delete[] elementi;
     ulazni_tok.read(reinterpret_cast<char *>(this), sizeof *this);
     elementi=new TipEl *[br_redova]{};
     try {
         for(int i=0; i<br_redova; i++) {
             elementi[i]=new TipEl[br_kolona];
             ulazni_tok.read(reinterpret_cast<char *>(elementi[i]), br_kolona*(sizeof *elementi[i]));
         }
         if(!ulazni_tok) throw std::logic_error("Problemi pri citanju datoteke");
     }
     catch(...) {
         for(int i=0; i<br_redova; i++) delete[] elementi[i];
         delete[] elementi;
         throw;
     }
 }
 template<typename TipEl>
 void Matrica<TipEl>::SacuvajUTekstualnuDatoteku(std::string ime_datoteke) const {
     std::ofstream izlazni_tok(ime_datoteke);
     if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
     for(int i=0; i<br_redova; i++) {
         for(int j=0; j<br_kolona; j++) {
             izlazni_tok<<elementi[i][j];
             if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
             if(j<br_kolona-1) izlazni_tok<<",";
             if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
         }
         izlazni_tok<<std::endl;
         if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
     }
 }
 template<typename TipEl>
 void Matrica<TipEl>::AnalizirajTekstualnuDatoteku(std::string ime_datoteke, int &br_redova, int &br_kolona) {
     std::ifstream ulazni_tok(ime_datoteke);
     if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
     int pom_br_redova=br_redova, pom_br_kolona=br_kolona;
     br_redova=0; br_kolona=0;
     int temp=0, i=0;
     for(;;) {
         TipEl el;
         char znak='0';
         br_kolona=0;
         while(ulazni_tok>>el) {
             br_kolona++;
             ulazni_tok>>znak;
             if(!ulazni_tok || znak!=',') break;
         }
         if(ulazni_tok && i>0 && br_kolona!=temp) {
             br_redova=pom_br_redova; br_kolona=pom_br_kolona;
             throw std::logic_error("Datoteka sadrzi besmislene podatke");
         }
         i++; temp=br_kolona;
         if(ulazni_tok && znak!=',') {
             ulazni_tok.seekg(-int(sizeof znak), std::ios::cur);
             br_redova++;
         }
         else if(ulazni_tok.eof()) {
             br_redova++; break;
         }
         else {
             br_redova=pom_br_redova; br_kolona=pom_br_kolona;
             throw std::logic_error("Datoteka sadrzi besmislene podatke");
         }
     }
 }
  template<typename TipEl>
  void Matrica<TipEl>::RegulisiMatricu(std::string ime_datoteke) {
      std::ifstream ulazni_tok(ime_datoteke);
      if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
     elementi=new TipEl*[br_redova]{};
     try {
     for(int i=0; i<br_redova; i++) {
         elementi[i]=new TipEl[br_kolona];
     }
     for(int i=0; i<br_redova; i++) {
         for(int j=0; j<br_kolona; j++) {
             TipEl el;
             char znak;
             ulazni_tok>>el;
             elementi[i][j]=el;
             if(j<br_kolona-1) ulazni_tok>>znak;
         }
     }
     }
     catch(...) {
         for(int i=0; i<br_redova; i++) delete[] elementi[i];
         delete[] elementi;
         throw;
     }
 }
 template<typename TipEl>
 void Matrica<TipEl>::ObnoviIzTekstualneDatoteke(std::string ime_datoteke) {
     int pom_br_redova=br_redova;
     AnalizirajTekstualnuDatoteku(ime_datoteke, br_redova, br_kolona);
     for(int i=0; i<pom_br_redova; i++) delete[] elementi[i];
     delete[] elementi;
     RegulisiMatricu(ime_datoteke);
 }
 template<typename TipEl>
 Matrica<TipEl>::Matrica(std::string ime_datoteke, bool vrsta_datoteke) {
     if(vrsta_datoteke) {
         std::ifstream ulazni_tok(ime_datoteke, std::ios::binary);
         if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
         ulazni_tok.read(reinterpret_cast<char *>(this), sizeof *this);
         elementi=new TipEl *[br_redova]{};
         try {
             for(int i=0; i<br_redova; i++) {
                 elementi[i]=new TipEl[br_kolona];
                 ulazni_tok.read(reinterpret_cast<char *>(elementi[i]), br_kolona*(sizeof *elementi[i]));
             }
             if(!ulazni_tok) throw std::logic_error("Problemi pri citanju datoteke");
         }
         catch(...) {
             for(int i=0; i<br_redova; i++) delete[] elementi[i];
             delete[] elementi;
             throw;
         }
     }
     else {
         AnalizirajTekstualnuDatoteku(ime_datoteke, br_redova, br_kolona);
         RegulisiMatricu(ime_datoteke);
     }
 }
 int main() {
     Matrica<int> m1(2,3);
     std::cin>>m1;
     std::cout<<std::setw(5)<<m1<<std::endl;
     m1.SacuvajUTekstualnuDatoteku("mat.txt");
     std::ofstream dat("proba.txt");
     dat<<"1,2\n3,4";
     dat.close();
     m1.ObnoviIzTekstualneDatoteke("proba.txt");
     m1.SacuvajUTekstualnuDatoteku("mat.txt");
     std::cout<<std::setw(5)<<m1<<std::endl;
     Matrica<int> m2("proba.txt", false);
     std::cout<<std::setw(5)<<m2<<std::endl;
     std::ofstream dat1("xyz.dat", std::ios::binary);
     dat1.close();
     m2.SacuvajUBinarnuDatoteku("xyz.dat");
     m1.ObnoviIzBinarneDatoteke("xyz.dat");
     std::cout<<std::setw(5)<<m1<<std::endl;
     return 0;
 }