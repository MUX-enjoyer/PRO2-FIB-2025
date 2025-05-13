#include "finder.hh"

using namespace pro2;
using namespace std;

#include "platform.hh"
#include "strawberry.hh"
template class Finder<Platform>;
template class Finder<Strawberry>;

// DISCLAIMER:
//NO ÉS LA VERSIÓ DEFINITIVA AMB TEMPS O(log n)

template <typename T>
void Finder<T>::add(const T *t) {
    Rect rect = t->get_rect();
    obj_rect_map_[t] = rect;
    
    // Afegir al mapa de coordenades X
    x_start_map_[rect.left].insert(t);
}

template <typename T>
void Finder<T>::remove(const T *t) {
    // Si existeix
    auto it = obj_rect_map_.find(t);
    if (it != obj_rect_map_.end()) {
        Rect rect = it->second;
        // Elimina l'objecte del mapa de coordenades X
        x_start_map_[rect.left].erase(t);
        if (x_start_map_[rect.left].empty()) {
            x_start_map_.erase(rect.left);
        }
        
        // Elimina del mapa de rectangles
        obj_rect_map_.erase(t);
    }
}

template <typename T>
void Finder<T>::update(const T *t) {
    remove(t);
    add(t);
}

template <typename T>
set<const T*> Finder<T>::query(Rect rect) const {
    set<const T*> result;
    
    // Busco el primer objecte que left <= rect.right
    // Esta operación es O(log n)
    auto it = x_start_map_.lower_bound(rect.left);
    
    // Itero només amb aquells objectes que left > rect.right
    while (it != x_start_map_.end() && it->first <= rect.right) {
        // Per cada objecte
        for (const T* obj : it->second) {
            // Agafo el rectàngle
            const Rect& obj_rect = obj_rect_map_.at(obj);
            
            // Comprovo si esta dins (podria estar abaix o dalt)
            if (obj_rect.left <= rect.right &&
                obj_rect.right >= rect.left &&
                obj_rect.top <= rect.bottom &&
                obj_rect.bottom >= rect.top) {
                
                result.insert(obj);
            }
        }
        ++it;
    }

    return result;
}