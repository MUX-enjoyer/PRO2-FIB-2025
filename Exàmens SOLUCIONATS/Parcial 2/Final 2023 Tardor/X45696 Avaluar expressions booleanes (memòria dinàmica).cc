// NOTA; la version de laboratorio contiene excepciones para controlar
// las situaciones de error

using namespace std;

template <class T> class Arbre { 
private:     
  struct node_arbre {
    T info;
    node_arbre* segE;
    node_arbre* segD;
  };
  node_arbre* primer_node;

  // especificació operacions privades
static node_arbre* copia_node_arbre(node_arbre* m)
  /* Pre: cert */
  /* Post: el resultat és NULL si m és NULL; en cas contrari, el resultat apunta
     al node arrel d'una jerarquia de nodes que és una còpia de la 
     jerarquia de nodes que té el node apuntat per m com a arrel */
  {
    node_arbre* n;
    if (m==NULL) n=NULL;
    else {
      n = new node_arbre;
      n->info = m->info;
      n->segE = copia_node_arbre(m->segE);
      n->segD = copia_node_arbre(m->segD);
    }
    return n;
  }

static void esborra_node_arbre(node_arbre* m) 
  /* Pre: cert */
  /* Post no fa res si m és NULL; en cas contrari, allibera espai de tots els nodes
     de la jerarquia que té el node apuntat per m com a arrel */
  {
    if (m != NULL) {
      esborra_node_arbre(m->segE);
      esborra_node_arbre(m->segD);
      delete m;
    }
  }

public:
  // especificació operacions públiques
  Arbre() 
  /* Pre: cert */
  /* Post: el p.i. és un arbre buit */
  {
    primer_node= NULL;
  }

  Arbre(const Arbre& original) 
  /* Pre: cert */
  /* Post: el p.i. és una còpia d'original */
  {
    primer_node = copia_node_arbre(original.primer_node);
  }

  ~Arbre() {
    esborra_node_arbre(primer_node);
  }

  Arbre& operator=(const Arbre& original) {
    if (this != &original) {
      esborra_node_arbre(primer_node);
      primer_node = copia_node_arbre(original.primer_node);
    }
    return *this;
  }

  void swap(Arbre &a) // a1.swap(a2);
    /* Pre: a=A, p.i. = P */
    /* Post: el p.i. passa a ser A; a passa a ser P */
  {
    node_arbre* aux;
    // o tambien swap(primer_node, a.primer_node);
    aux = a.primer_node;
    a.primer_node = primer_node;
    primer_node = aux;
  }

  void a_buit() 
  /* Pre: cert */
  /* Post: el p.i. és un arbre buit */
  {
    esborra_node_arbre(primer_node);
    primer_node = NULL;
  }        

  // a.plantar(x,a1,a2);
  void plantar(const T &x, Arbre &a1, Arbre &a2) 
  /* Pre: El paràmetre implícit és buit, a1 = A1, a2 = A2, el p.i. és
     buit però no és el mateix objecte que a1 ni a2 */
  /* Post: El paràmetre implícit té x com a arrel, A1 com a fill esquerre
     i A2 com a fill dret; a1 i a2 són buits; si A1 i A2 són el mateix objecte,
     el fill dret n'és una còpia  */ 
  {
    node_arbre* aux; // se puede hacer sin aux
    aux = new node_arbre;
    aux->info = x;
    aux->segE= a1.primer_node;
    // HAY QUE EVITAR LA COMPARTICION DE NODOS:
    if (a1.primer_node == a2.primer_node) aux->segD = copia_node_arbre(a1.primer_node);
    else  aux->segD = a2.primer_node;
    primer_node = aux;
    a1.primer_node = NULL;
    a2.primer_node = NULL;
    /* sin aux
   
    primer_node = new node_arbre;
    primer_node->info = x;
    primer_node->segE= a1.primer_node;
    // HAY QUE EVITAR LA COMPARTICION DE NODOS:
    if (a1.primer_node == a2.primer_node) primer_node->segD= copia_node_arbre(a1.primer_node);
    else  primer_node->segD= a2.primer_node;
    a1.primer_node = NULL;
    a2.primer_node = NULL;
  
    */
  }

  void fills (Arbre &fe, Arbre &fd) 
  /* Pre: El paràmetre implícit no és buit; fe, fd són buits i no
     són el matex objecte */ // a.fills(b,b); NO
  /* Post: fe és el fill esquerre del paràmetre implícit original; fd és
     el fill dret del paràmetre implícit original, el paràmetre implícit
     és buit */
  {
    node_arbre* aux;  // se puede hacer sin aux
    aux = primer_node;
    fe.primer_node = aux->segE;
    fd.primer_node = aux->segD;
    primer_node = NULL;
    delete aux;

    /* sin aux
      fe.primer_node = primer_node->segE;
      fd.primer_node = primer_node->segD;
      delete primer_node;
      primer_node = NULL;
    */
  }

  T arrel() const 
  /* Pre: el p.i. no és buit */
  /* Post: el resultat és l'arrel del p.i. */
  {  
    return primer_node->info;
  }

  bool es_buit() const 
  /* Pre: cert */
  /* Post: el resultat indica si el p.i. és un arbre buit */
  {  
    return (primer_node==NULL);
  }

  // Extensión -----------------------------------------------------

// Pre:  el, p.i. és un arbre no buit que representa una expressió booleana correcta
//       sobre els valors true,false i els operadors and,or,not.
// Post: Retorna l'avaluació de l'expressió representada pel p.i.  
// Descomenteu les següents dues linies i implementeu el mètode:
  bool evaluate() const{
    return evaluate_aux(primer_node);
  }

private:
  static bool evaluate_aux(node_arbre *n ) {
    if (n != NULL) {
      if (n->info == "true") return true;
      else if (n->info == "false") return false;
      else if (n->info == "not") return !evaluate_aux(n->segE);
      else if (n->info == "and") return evaluate_aux(n->segE) && evaluate_aux(n->segD); 
      else if (n->info == "or") return evaluate_aux(n->segE) || evaluate_aux(n->segD);
      // Com que les operacions "and" i "or" de C++ ja estan optimitzades
      // no cal que la fem nosaltres manualment...
    }
    return true;
  }
};