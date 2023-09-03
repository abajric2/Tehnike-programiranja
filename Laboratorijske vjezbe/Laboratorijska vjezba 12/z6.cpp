/* 
    TP 16/17 (LV 12, Zadatak 6)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <string>


template <typename TipEl>
 class Matrica {
 char ime_matrice;
 int br_redova, br_kolona;
 TipEl **elementi;
 static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
 static void DealocirajMemoriju(TipEl **elementi, int br_redova);
 void KopirajElemente(TipEl **elementi);
 public:
 Matrica(int br_redova, int br_kolona, char ime = 0);
 Matrica(const Matrica &m);
 Matrica(Matrica &&m);
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
 for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
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
 void Test() {
    Matrica <double> a(2,2,'a');
    a[0][0]=10; a[0][1]=2; a[1][0]=4; a[1][1]=5;
    std::cout<<std::string(a);
 }
int main() {
 int m, n;
 std::cout << "Unesi broj redova i kolona za matrice:\n";
 std::cin >> m >> n;
 try {
 Matrica<double> a(m, n, 'A'), b(m, n, 'B');
 std::cout << "Unesi matricu A:\n";
 std::cin>>a;
 std::cout << "Unesi matricu B:\n";
 std::cin>>b;
 std::cout << "Zbir ove dvije matrice je:\n";
 std::cout<<std::setw(7)<<a+b;
 }
 catch(std::bad_alloc) {
 std::cout << "Nema dovoljno memorije!\n";
 }
 return 0;
}