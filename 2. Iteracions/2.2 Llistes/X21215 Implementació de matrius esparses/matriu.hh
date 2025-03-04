#include <iostream>
#include <list>
#include <vector>

#include "PRO2Excepcio.hh"

using namespace std;

template <typename T>
class matriu {
   private:
    struct parint {
        int col;
        T val;
    };

    vector<list<parint> > files;  // elements de la matriu
    int nfil;                     // dimensions de la matriu
    int ncol;

    // Representaci� de matrius amb implementaci� dispersa
    // (nom�s desem els valors diferents de zero).
    // Les files es desen en un vector de parells tals que
    // per al parell (j,x) de la fila i:
    //
    // x != 0 <=> m[i][j] = x <=> (j,x) \in files[i]
    //
    // Els parells de la llista estan ordenats creixentment pel primer element del parell.

   public:
    // Constructores

    matriu(int m, int n);
    /* Pre: n>0 */
    /* Post: matriu de mXn amb tots els elements a 0 */

    // Modificadores

    void modif_pos(int i, int j, T x);
    /* Pre: 0<=i< num files del par�metre impl�cit;  0<=j< num columnes del
    par�metre impl�cit */
    /* Post: el par�metre impl�cit queda com l'original per� amb x a la
    la posici� [i][j] */

    void suma(const matriu& m1, const matriu& m2);
    /* Pre: m1 i m2 tenen la mateixa dimensi� */
    /* Post: el par�metre impl�cit �s la suma de m1 i m2 */

    void producte(const matriu& m1, const matriu& m2);
    /* Pre: el n�mero de columnes de m1 �s igual al n�mero de files de m2 */
    /* Post: el par�metre impl�cit �s el producte de m1 i m2 */

    // Consultores

    int num_files() const;
    /* Pre: cert */
    /* Post: El resultat es el n�mero de files del par�metre impl�cit */

    int num_columnes() const;
    /* Pre: cert */
    /* Post: El resultat es el n�mero de columnes del par�metre impl�cit */

    T pos(int i, int j) const;
    /* Pre: 0<=i< num files del par�metre impl�cit;  0<=j< num columnes del
    par�metre impl�cit */
    /* Post: El resultat �s l'element [i][j] del par�metre impl�cit */

    // Lectura i escriptura.

    void llegeix(int m, int n);
    /* Pre: el canal est�ndard d'entrada t� parells d'enters que
    representen una matriu mXn representada de forma espar�a; al principi
    de cada fila apareix el seu n�mero de valores diferents de 0 */

    /* Post: El parametre impl�cit t� la matriz formada per parells
    del canal est�ndard d'entrada original; si m o n no coincideixen amb les
    dimensions del p.i. el qual queda redimensionat */

    void escriu() const;
    /* Pre: cert */
    /* Post: La sortida est�ndard t� els valors de la matriu de forma can�nica
    (valors fila per fila). */
};
