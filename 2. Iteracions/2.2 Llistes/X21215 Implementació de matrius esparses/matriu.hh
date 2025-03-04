#include <vector>
#include <list>
#include <iostream>
#include "PRO2Excepcio.hh"

using namespace std;

template <typename T> class matriu{

private:

	struct parint{
		int col;
		T val;
	};

	vector <list<parint> > files; 	// elements de la matriu
	int nfil;   					// dimensions de la matriu
	int ncol;

	// Representació de matrius amb implementació dispersa
	// (només desem els valors diferents de zero).
	// Les files es desen en un vector de parells tals que 
	// per al parell (j,x) de la fila i:
	//
	// x != 0 <=> m[i][j] = x <=> (j,x) \in files[i] 
	//
	// Els parells de la llista estan ordenats creixentment pel primer element del parell.

public:

	// Constructores

	matriu (int m, int n);
	/* Pre: n>0 */ 
	/* Post: matriu de mXn amb tots els elements a 0 */

	// Modificadores 

	void modif_pos (int i, int j, T x);
	/* Pre: 0<=i< num files del paràmetre implícit;  0<=j< num columnes del 
	paràmetre implícit */
	/* Post: el paràmetre implícit queda com l'original però amb x a la
	la posició [i][j] */

	void suma (const matriu& m1, const matriu& m2);
	/* Pre: m1 i m2 tenen la mateixa dimensió */
	/* Post: el paràmetre implícit és la suma de m1 i m2 */

	void producte (const matriu& m1, const matriu& m2);
	/* Pre: el número de columnes de m1 és igual al número de files de m2 */
	/* Post: el paràmetre implícit és el producte de m1 i m2 */

	// Consultores

	int num_files () const;
	/* Pre: cert */ 
	/* Post: El resultat es el número de files del paràmetre implícit */

	int num_columnes () const;
	/* Pre: cert */ 
	/* Post: El resultat es el número de columnes del paràmetre implícit */

	T pos (int i, int j) const;
	/* Pre: 0<=i< num files del paràmetre implícit;  0<=j< num columnes del 
	paràmetre implícit */ 
	/* Post: El resultat és l'element [i][j] del paràmetre implícit */

	// Lectura i escriptura.

	void llegeix (int m, int n);
	/* Pre: el canal estàndard d'entrada té parells d'enters que
	representen una matriu mXn representada de forma esparça; al principi
	de cada fila apareix el seu número de valores diferents de 0 */

	/* Post: El parametre implícit té la matriz formada per parells
	del canal estàndard d'entrada original; si m o n no coincideixen amb les
	dimensions del p.i. el qual queda redimensionat */

	void escriu () const;
	/* Pre: cert */
	/* Post: La sortida estàndard té els valors de la matriu de forma canònica
	(valors fila per fila). */

     
};
