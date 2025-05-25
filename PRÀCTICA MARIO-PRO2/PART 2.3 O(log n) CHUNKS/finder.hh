#ifndef FINDER_HH
#define FINDER_HH

using namespace std;

#include <set>
#include <map>
#include <vector>
#include "geometry.hh"

const int chunk_size = 50; // Tamany del chunk

template <typename T>
class Finder {
private:
    // Mapa que donat un objecte retorna el seu rect
    map<const T*, pro2::Rect> obj_rect_map_;

    map<int, set<T*>> chunks_;

public:
    Finder() {}

    void add(T *t) {
        pro2::Rect rect = t->get_rect();

        int chunk_l = rect.left / chunk_size;
        int chunk_r = rect.right / chunk_size;

        // Si el rectangle ocupa més d'un chunk
        for (int i = chunk_l; i <= chunk_r; ++i) {
            chunks_[i].insert(t);
        }

        // Afegir al mapa de obj -> rect
        obj_rect_map_[t] = rect;
    }

    void update(T *t) {
        remove(t);
        add(t);
    }

    void remove(T *t) {
        // Si existeix
        auto it = obj_rect_map_.find(t);
        if (it != obj_rect_map_.end()) {
            pro2::Rect rect = it->second;

            int chunk_l = rect.left / chunk_size;
            int chunk_r = rect.right / chunk_size;

            // Si el rectangle ocupa més d'un chunk
            for (int i = chunk_l; i <= chunk_r; ++i) {
                chunks_[i].erase(t);
            }
        }
        // Elimina del mapa de rectangles
        obj_rect_map_.erase(t);
    }

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
    set<T *> query(pro2::Rect rect) {
        set<T *> result;
        int chunk_l = rect.left / chunk_size;
        int chunk_r = rect.right / chunk_size;
        // Recorre els chunks que poden contenir objectes
        // que intersecten amb el rectangle
        for (int i = chunk_l; i <= chunk_r; ++i) {
            typename set<T*>::iterator it;
            for (it = chunks_[i].begin(); it != chunks_[i].end(); ++it) {
                // Agafo el rectàngle
                pro2::Rect obj_rect = (*it)->get_rect();  
                // Comprovo si esta dins (podria estar abaix o dalt)
                if (obj_rect.left <= rect.right &&
                    obj_rect.right >= rect.left &&
                    obj_rect.top <= rect.bottom &&
                    obj_rect.bottom >= rect.top) {
                    result.insert(*it);
                }
            }
        }
        return result;
    }
};

#endif // FINDER_HH

#include "platform.hh"
template class Finder<Platform>;
#include "strawberry.hh"
template class Finder<Strawberry>;