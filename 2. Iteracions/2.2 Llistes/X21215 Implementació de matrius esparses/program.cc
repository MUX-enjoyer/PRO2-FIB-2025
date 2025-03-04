#include "matriu.tcc"

int main() {

	int operacio;
	cin >> operacio;

	matriu <int> m1(0,0);  
	int nf1, nc1; 
	cin >> nf1 >> nc1;
	m1.llegeix (nf1,nc1);

	int nf2, nc2; 
	cin >> nf2 >> nc2;

	matriu <int> m2(0,0);  
	m2.llegeix(nf2,nc2);

	m1.escriu();
	m2.escriu();

	if (operacio == 1) {
		matriu <int> s(0,0);  

		s.suma(m1,m2);
		s.escriu();
	}

	if (operacio == 2) {
		matriu <int> p(0,0);
		  
		p.producte(m1,m2);
		p.escriu();
	}

}
