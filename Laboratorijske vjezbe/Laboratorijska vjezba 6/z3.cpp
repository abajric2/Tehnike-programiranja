/* 
    TP 2018/2019: LV 6, Zadatak 3
	
	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja 
	i sugestije saljite na mail: khodzic2@etf.unsa.ba
	
	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak
	
*/
#include <iostream>
#include <new>
#include <stdexcept>

int **KreirajTrougao(int n) {
    if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
    try {
        int **mat=new int*[n]{};
        try {
            for(int i=0; i<n; i++) mat[i]=new int[2*i+1];
            for(int i=0; i<n; i++) {
                int element=i+1;
                for(int j=0; j<2*i+1; j++) {
                    mat[i][j]=element;
                    if(j<i) element--;
                    else element++;
                }
            }
            return mat;
        }
        catch (std::bad_alloc) {
            for(int i=0; i<n; i++) delete[] mat[i];
            delete[] mat;
            throw;
        }
    }
    catch (std::bad_alloc) {
        throw;
    }
}
int main ()
{
    int n;
    std::cout<<"Koliko zelite redova: ";
    std::cin>>n;
    int **mat{};
    try {
        mat=KreirajTrougao(n);
        for(int i=0; i<n; i++) {
            for(int j=0; j<2*i+1; j++) std::cout<<mat[i][j]<<" ";
            std::cout<<std::endl;
        }
    }
    catch (std::domain_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
    catch(std::bad_alloc) {
        std::cout<<"Izuzetak: Nedovoljno memorije!";
    }
    if(mat) for(int i=0; i<n; i++) delete[] mat[i];
    delete[] mat;
	return 0;
}