#ifndef FINDER_HH
#define FINDER_HH

using namespace std;

#include <set>
#include <map>
#include <vector>
#include "geometry.hh"
#include "utils.hh"

template <typename T>
class Finder {
private:
    // Mapa que donat un objecte retorna el seu rect
    map<T*, pro2::Rect> obj_rect_map_;
    
    // Mapa que donat un left retorna els objectes que comencen allà
    map<int, set<T*>> x_start_map_;
    map<int, set<T*>> x_end_map_;

public:
    Finder() {}

    void add(T *t);
    void update(T *t);
    void remove(T *t);

    /**
    * @brief Retorna el conjunt d'objectes amb rectangles 
    *        total o parcialment dins de `rect`.
    *
    * Si el nombre de rectangles del contenidor és `n`, el 
    * cost de l'algorisme ha de ser O(log n).
    *
    * @param rect El rectangle de cerca
    *
    * @returns Un conjunt de punters a objectes que tenen un 
    *          rectangle parcial o totalment dins de `rect`
    */
    set<T *> query(pro2::Rect rect);
};

#endif // FINDER_HH