#ifndef FINDER_HH
#define FINDER_HH

using namespace std;

#include <set>
#include <map>
#include <vector>
#include "geometry.hh"
#include "utils.hh"

// DISCLAIMER:
//NO ÉS LA VERSIÓ DEFINITIVA AMB TEMPS O(log n)

template <typename T>
class Finder {
private:
    // Mapa que donat un objecte retorna el seu rect
    map<const T*, pro2::Rect> obj_rect_map_;
    
    // Mapa que donat un left retorna els objectes que comencen allà
    map<int, set<const T*>> x_start_map_;

public:
    Finder() {}

    void add(const T *t);
    void update(const T *t);
    void remove(const T *t);

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
    set<const T *> query(pro2::Rect rect) const;
};

#endif // FINDER_HH